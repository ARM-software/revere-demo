/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (C) 2018-2019 Arm Ltd.
 * Author: Vincent Stehlé <vincent.stehle@arm.com>
 */

#include "revere_dev.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <err.h>
#include <unistd.h>
#include "revere_hw.h"

/* Timeout for management commands, in ms */
#define TIMEOUT_MS 100

static void setup_mgt(struct revere_dev *rd)
{
	uint64_t amu_idr, amu_aidr;
	unsigned int num_rx_ams_m1, num_tx_ams_m1, num_rx_ams, num_tx_ams,
			arch_major_rev, arch_minor_rev;
	void *regs = rd->regs;

	amu_idr = revere_readq(regs, AMU_IDR);

	num_rx_ams_m1 = (amu_idr >> RVR_AMU_IDR_NUM_RX_AMS_M1_SHIFT) &
			 RVR_AMU_IDR_NUM_RX_AMS_M1_MASK;

	num_rx_ams = num_rx_ams_m1 + 1;
	num_tx_ams_m1 = amu_idr & RVR_AMU_IDR_NUM_TX_AMS_M1_MASK;
	num_tx_ams = num_tx_ams_m1 + 1;
	amu_aidr = revere_readq(regs, AMU_AIDR);

	arch_major_rev = (amu_aidr >> RVR_AMU_AIDR_ARCHMAJORREV_SHIFT) &
			     RVR_AMU_AIDR_ARCHMAJORREV_MASK;

	arch_minor_rev = (amu_aidr >> RVR_AMU_AIDR_ARCHMINORREV_SHIFT) &
			     RVR_AMU_AIDR_ARCHMINORREV_MASK;

	printf("num_rx_ams: %d\n", num_rx_ams);
	printf("idr: %#lx\n", amu_idr);
	printf("num_tx_ams: %d\n", num_tx_ams);
	printf("aidr: %#lx\n", amu_aidr);
	printf("Revere AMU v%d.%d\n", arch_major_rev, arch_minor_rev);
	printf("iidr: %#lx\n", revere_readq(regs, AMU_IIDR));

	// Check version
	if (arch_major_rev != 2)
		errx(1, "Unsupported Revere version");

	// Enable AMU
	revere_writeq(regs, AMU_CR_EN, AMU_CR);

	/* Command */
	revere_writeq(regs, rd->iova + offsetof(struct revere_buffers, cmd),
		      CMD_BASE_PTR);

	revere_writeq(regs,
		      (MGT_SLOT_DOUBLEWORDS_POT << LOG2_MSG_LENGTH_SHIFT),
		      CMD_CTRL);

	/* Response */
	revere_writeq(regs, rd->iova + offsetof(struct revere_buffers, resp),
		      RESP_BASE_PTR);

	revere_writeq(regs,
		      (MGT_SLOT_DOUBLEWORDS_POT << LOG2_MSG_LENGTH_SHIFT),
		      RESP_CTRL);

	/* Exception */
	revere_writeq(regs, rd->iova + offsetof(struct revere_buffers, exc),
		      EXC_BASE_PTR);

	revere_writeq(regs,
		      (MGT_SLOT_DOUBLEWORDS_POT << LOG2_MSG_LENGTH_SHIFT),
		      EXC_CTRL);
}

static const char *command_name(enum rvr_opcode o)
{
	const char *r = "<unknown>";

	switch (o) {
#undef M
#define M(X) case RVR_##X: r = #X; break

	M(PF_PROBE);
	M(F_PROBE);
	M(PF_F_ENABLE);
	M(PF_F_DISABLE);
	M(F_TYPEB_TABLE_CONFIGURE);
	M(PF_AMI_SW_MAP);
	M(PF_AMI_SW_UNMAP);
	M(PF_AMI_SW_CONFIGURE);
	M(PF_AMI_SW_SAVE);
	M(PF_AMI_SW_RESET);
	M(F_AMI_SW_CONFIGURE);
	M(F_AMI_SW_SAVE);
	M(F_AMI_SW_RESET);
	M(F_AMI_SW_ENABLE);
	M(F_AMI_SW_DISABLE);
	M(PF_ASN_CREATE);
	M(PF_ASN_DESTROY);
	M(PF_AMS_RING_CONFIGURE);
	M(PF_AMS_RING_SAVE);
	M(F_AMS_RING_CONFIGURE);
	M(F_AMS_RING_SAVE);
	M(PF_RESPONSE_TO_VF);
	M(PF_AMI_HW_MAP);
	M(PF_AMI_HW_UNMAP);
	M(PF_AMI_HW_CONFIGURE);
	M(PF_AMI_HW_SAVE);
	M(PF_AMI_HW_RESET);
	M(VF_COMMAND_TO_PF);
	M(F_PROF_TABLE_FLUSH);
	M(F_AMI_HW_CONFIGURE);
	M(F_AMI_HW_SAVE);
	M(F_AMI_HW_RESET);
	M(F_AMI_HW_ENABLE);
	M(F_AMI_HW_DISABLE);
	M(F_AMS_PROF_CONFIGURE);
	M(F_AMS_TRACE_CONFIGURE);
	}

	return r;
}

/* This is blocking */
static void send_command(struct revere_dev *rd,
		const union rvr_commands *cmd, union rvr_responses *resp)
{
	struct revere_buffers *b = rd->bufs;
	int i, s;
	uint64_t resp_read_index, resp_write_index, cmd_read_index,
		cmd_write_index;
	enum rvr_opcode co, ro;
	void *regs = rd->regs;

	co = cmd->pf_probe.opcode;
	printf("sending command %d %s\n", co, command_name(co));

	/* Assert resp empty */
	resp_read_index = revere_readq(regs, RESP_READ_INDEX);
	resp_write_index = revere_readq(regs, RESP_WRITE_INDEX);
	if (!ring_is_empty(resp_read_index, resp_write_index))
		errx(1, "resp ring not empty");

	memset(b->resp, 0, sizeof(b->resp));

	/* Assert command empty */
	cmd_read_index = revere_readq(regs, CMD_READ_INDEX);
	cmd_write_index = revere_readq(regs, CMD_WRITE_INDEX);
	if (!ring_is_empty(cmd_read_index, cmd_write_index))
		errx(1, "cmd ring not empty");

	memset(b->cmd, 0, sizeof(b->cmd));

	/* Send */
	assert(sizeof(*cmd) <= sizeof(b->cmd));
	memcpy(b->cmd, cmd, sizeof(*cmd));
	revere_writeq(regs, cmd_write_index + 1, CMD_WRITE_INDEX);

	/* Wait cmd empty */
	for (i = 0; i < TIMEOUT_MS; i++) {
		cmd_read_index = revere_readq(regs, CMD_READ_INDEX);
		cmd_write_index = revere_readq(regs, CMD_WRITE_INDEX);

		if (ring_is_empty(cmd_read_index, cmd_write_index))
			break;

		s = usleep(1000);
		if (s < 0)
			err(1, "usleep: %d", s);
	}

	if (i >= TIMEOUT_MS)
		errx(1, "cmd timeout");

	/* Wait for response */
	for (i = 0; i < TIMEOUT_MS; i++) {
		resp_read_index = revere_readq(regs, RESP_READ_INDEX);
		resp_write_index = revere_readq(regs, RESP_WRITE_INDEX);

		if (!ring_is_empty(resp_read_index, resp_write_index))
			break;

		s = usleep(1000);
		if (s < 0)
			err(1, "usleep: %d", s);
	}

	if (i >= TIMEOUT_MS)
		errx(1, "resp timeout");

	/* Receive */
	assert(sizeof(*resp) <= sizeof(b->resp));
	memcpy(resp, b->resp, sizeof(*resp));
	revere_writeq(regs, resp_read_index + 1, RESP_READ_INDEX);

	/* Sanity checks */
	ro = resp->pf_probe.opcode;
	if (ro != co)
		errx(1, "resp opcode mismatch: %d != %d", ro, co);

	/* Check status for all responses which have one */
	switch (ro) {
	case RVR_F_AMI_HW_CONFIGURE:
	case RVR_F_AMI_HW_DISABLE:
	case RVR_F_AMI_HW_ENABLE:
	case RVR_F_AMI_HW_RESET:
	case RVR_F_AMI_HW_SAVE:
	case RVR_F_AMI_SW_CONFIGURE:
	case RVR_F_AMI_SW_DISABLE:
	case RVR_F_AMI_SW_ENABLE:
	case RVR_F_AMI_SW_RESET:
	case RVR_F_AMI_SW_SAVE:
	case RVR_F_AMS_PROF_CONFIGURE:
	case RVR_F_AMS_RING_CONFIGURE:
	case RVR_F_AMS_RING_SAVE:
	case RVR_F_AMS_TRACE_CONFIGURE:
	case RVR_PF_AMI_HW_CONFIGURE:
	case RVR_PF_AMI_HW_MAP:
	case RVR_PF_AMI_HW_RESET:
	case RVR_PF_AMI_HW_SAVE:
	case RVR_PF_AMI_SW_CONFIGURE:
	case RVR_PF_AMI_SW_MAP:
	case RVR_PF_AMI_SW_RESET:
	case RVR_PF_AMI_SW_SAVE:
	case RVR_PF_AMS_RING_CONFIGURE:
	case RVR_PF_AMS_RING_SAVE:
	case RVR_PF_ASN_CREATE:
	case RVR_PF_ASN_DESTROY:
	case RVR_PF_RESPONSE_TO_VF:
	case RVR_VF_COMMAND_TO_PF:
		s = resp->pf_ami_sw_map.status;
		break;

	/* The following commands do not have a status */
	case RVR_F_PROBE:
	case RVR_F_PROF_TABLE_FLUSH:
	case RVR_F_TYPEB_TABLE_CONFIGURE:
	case RVR_PF_AMI_HW_UNMAP:
	case RVR_PF_AMI_SW_UNMAP:
	case RVR_PF_F_DISABLE:
	case RVR_PF_F_ENABLE:
	case RVR_PF_PROBE:
	default:
		s = 0;
		break;
	}

	if (s)
		errx(1, "resp status %d", s);
}

static void probe_amu(struct revere_dev *rd)
{
	union rvr_commands cmd;
	union rvr_responses resp;
	unsigned int max_ami_sw, max_ami_hw, max_asn, ami_per_f, num_aha;

	memset(&cmd, 0, sizeof(cmd));
	cmd.pf_probe = (struct rvr_pf_probe_cmd){
		.opcode = RVR_PF_PROBE,
	};
	send_command(rd, &cmd, &resp);

	max_ami_sw = resp.pf_probe.max_ami_sw;
	max_ami_hw = resp.pf_probe.max_ami_hw;
	max_asn = resp.pf_probe.max_asn;
	num_aha = resp.pf_probe.num_aha;
	printf("max_ami_sw: %d\n", max_ami_sw);
	printf("max_ami_hw: %d\n", max_ami_hw);
	printf("max_asn: %d\n", max_asn);
	printf("num_aha: %d\n", num_aha);

	// Sanity checks
	if (max_ami_sw < 1)
		errx(1, "Not enough AMI-SW");

	if (max_ami_hw < 2)
		errx(1, "Not enough AMI-HW");

	if (max_asn < 2)
		errx(1, "Not enough ASN");

	if (num_aha < 1)
		errx(1, "Not enough AHA");

	memset(&cmd, 0, sizeof(cmd));
	cmd.f_probe = (struct rvr_f_probe_cmd){
		.opcode = RVR_F_PROBE,
	};
	send_command(rd, &cmd, &resp);

	ami_per_f = resp.f_probe.ami_per_f_m1 + 1;
	printf("ami_per_f: %d\n", ami_per_f);

	// Sanity checks
	if (ami_per_f < 1)
		errx(1, "Not enough AMI per F");
}

static void configure(struct revere_dev *rd)
{
	union rvr_commands cmd;
	union rvr_responses resp;

	// Map AMI-SW 0
	memset(&cmd, 0, sizeof(cmd));
	cmd.pf_ami_sw_map = (struct rvr_pf_ami_sw_map_cmd){
		.opcode = RVR_PF_AMI_SW_MAP,
		.any_phy_ami_sw = 1,
		.ami_sw_id = 0,
		.f_owner = 0,
	};
	send_command(rd, &cmd, &resp);

	// Map AMI-HW 0
	memset(&cmd, 0, sizeof(cmd));
	cmd.pf_ami_hw_map = (struct rvr_pf_ami_hw_map_cmd){
		.opcode = RVR_PF_AMI_HW_MAP,
		.phy_ami_hw_id = 0,
		.aha_id = 0,
		.ami_hw_id = 0,
		.f_owner = 0,
	};
	send_command(rd, &cmd, &resp);

	// Map AMI-HW 1
	memset(&cmd, 0, sizeof(cmd));
	cmd.pf_ami_hw_map = (struct rvr_pf_ami_hw_map_cmd){
		.opcode = RVR_PF_AMI_HW_MAP,
		.phy_ami_hw_id = 1,
		.aha_id = 0,
		.ami_hw_id = 1,
		.f_owner = 0,
	};
	send_command(rd, &cmd, &resp);

	/* Create session 0
	 * From AMI-SW 0, Tx AMS 0
	 * To AMI-HW 0, Rx AMS 0 */
	memset(&cmd, 0, sizeof(cmd));
	cmd.pf_asn_create = (struct rvr_pf_asn_create_cmd){
		.opcode = RVR_PF_ASN_CREATE,
		.dst_ami_type = 1,	// HW
		.src_ami_type = 0,	// SW
		.src_ami = 0,
		.src_f_owner = 0,
		.dst_ami = 0,
		.dst_f_owner = 0,
		.dst_ams = 0,
		.src_ams = 0,
		.asn_id = 0,
		.prof_ctl = 0,
		.trace_ctl = 0,
		.mfo = 0,
		.log2_msg_length = RING_SLOT_DOUBLEWORDS_POT,
	};
	send_command(rd, &cmd, &resp);

	/* Create session 1
	 * From AMI-HW 1, Tx AMS 0
	 * To AMI-SW 0, Rx AMS 0 */
	memset(&cmd, 0, sizeof(cmd));
	cmd.pf_asn_create = (struct rvr_pf_asn_create_cmd){
		.opcode = RVR_PF_ASN_CREATE,
		.dst_ami_type = 0,	// SW
		.src_ami_type = 1,	// HW
		.src_ami = 1,
		.src_f_owner = 0,
		.dst_ami = 0,
		.dst_f_owner = 0,
		.dst_ams = 0,
		.src_ams = 0,
		.asn_id = 1,
		.prof_ctl = 0,
		.trace_ctl = 0,
		.mfo = 0,
		.log2_msg_length = RING_SLOT_DOUBLEWORDS_POT,
	};
	send_command(rd, &cmd, &resp);

	// Configure AMI-SW 0
	memset(&cmd, 0, sizeof(cmd));
	cmd.f_ami_sw_disable = (struct rvr_f_ami_sw_disable_cmd){
		.opcode = RVR_F_AMI_SW_DISABLE,
		.ami_sw_id = 0,
	};
	send_command(rd, &cmd, &resp);

	memset(&cmd, 0, sizeof(cmd));
	cmd.f_ami_sw_reset = (struct rvr_f_ami_sw_reset_cmd){
		.opcode = RVR_F_AMI_SW_RESET,
		.ami_sw_id = 0,
	};
	send_command(rd, &cmd, &resp);

	memset(&cmd, 0, sizeof(cmd));
	cmd.f_ami_sw_configure = (struct rvr_f_ami_sw_configure_cmd){
		.opcode = RVR_F_AMI_SW_CONFIGURE,
		.ami_sw_id = 0,
		.pasid_enabled = 0,
		.tx_irq_enable = 0,
		.rx_irq_enable = 0,
	};
	send_command(rd, &cmd, &resp);

	memset(&cmd, 0, sizeof(cmd));
	cmd.f_ams_ring_configure = (struct rvr_f_ams_ring_configure_cmd){
		.opcode = RVR_F_AMS_RING_CONFIGURE,
		.ami_sw_id = 0,
		.ams_id = 0,
		.ams_type = 0,	// Rx
		.rx_mode = 0,
		.log2_size = RING_SLOTS_POT,
		.threshold = 0,
		.base_ptr = rd->iova + offsetof(struct revere_buffers, rx),
	};
	send_command(rd, &cmd, &resp);

	memset(&cmd, 0, sizeof(cmd));
	cmd.f_ams_ring_configure = (struct rvr_f_ams_ring_configure_cmd){
		.opcode = RVR_F_AMS_RING_CONFIGURE,
		.ami_sw_id = 0,
		.ams_id = 0,
		.ams_type = 1,	// Tx
		.log2_size = RING_SLOTS_POT,
		.threshold = 0,
		.base_ptr = rd->iova + offsetof(struct revere_buffers, tx),
	};
	send_command(rd, &cmd, &resp);

	memset(&cmd, 0, sizeof(cmd));
	cmd.f_ami_sw_enable = (struct rvr_f_ami_sw_enable_cmd){
		.opcode = RVR_F_AMI_SW_ENABLE,
		.ami_sw_id = 0,
	};
	send_command(rd, &cmd, &resp);

	// Reset AMI-HW 0
	memset(&cmd, 0, sizeof(cmd));
	cmd.f_ami_hw_disable = (struct rvr_f_ami_hw_disable_cmd){
		.opcode = RVR_F_AMI_HW_DISABLE,
		.ami_hw_id = 0,
	};
	send_command(rd, &cmd, &resp);

	memset(&cmd, 0, sizeof(cmd));
	cmd.f_ami_hw_reset = (struct rvr_f_ami_hw_reset_cmd){
		.opcode = RVR_F_AMI_HW_RESET,
		.ami_hw_id = 0,
	};
	send_command(rd, &cmd, &resp);

	memset(&cmd, 0, sizeof(cmd));
	cmd.f_ami_hw_enable = (struct rvr_f_ami_hw_enable_cmd){
		.opcode = RVR_F_AMI_HW_ENABLE,
		.ami_hw_id = 0,
	};
	send_command(rd, &cmd, &resp);

	// Reset AMI-HW 1
	memset(&cmd, 0, sizeof(cmd));
	cmd.f_ami_hw_disable = (struct rvr_f_ami_hw_disable_cmd){
		.opcode = RVR_F_AMI_HW_DISABLE,
		.ami_hw_id = 1,
	};
	send_command(rd, &cmd, &resp);

	memset(&cmd, 0, sizeof(cmd));
	cmd.f_ami_hw_reset = (struct rvr_f_ami_hw_reset_cmd){
		.opcode = RVR_F_AMI_HW_RESET,
		.ami_hw_id = 1,
	};
	send_command(rd, &cmd, &resp);

	memset(&cmd, 0, sizeof(cmd));
	cmd.f_ami_hw_enable = (struct rvr_f_ami_hw_enable_cmd){
		.opcode = RVR_F_AMI_HW_ENABLE,
		.ami_hw_id = 1,
	};
	send_command(rd, &cmd, &resp);
}

void revere_dev_setup(struct revere_dev *rd)
{
	assert(rd);
	assert(rd->bufs);
	assert(rd->regs);

	 // Setup the management interface
	setup_mgt(rd);

	// Probe the device
	probe_amu(rd);

	// Configure the device for our experiment
	configure(rd);
}

void revere_dev_teardown(struct revere_dev *rd)
{
	union rvr_commands cmd;
	union rvr_responses resp;

	assert(rd);

	// Disable AMI-SW 0
	memset(&cmd, 0, sizeof(cmd));
	cmd.f_ami_sw_disable = (struct rvr_f_ami_sw_disable_cmd){
		.opcode = RVR_F_AMI_SW_DISABLE,
		.ami_sw_id = 0,
	};
	send_command(rd, &cmd, &resp);

	// Disable AMI-HW 0
	memset(&cmd, 0, sizeof(cmd));
	cmd.f_ami_hw_disable = (struct rvr_f_ami_hw_disable_cmd){
		.opcode = RVR_F_AMI_HW_DISABLE,
		.ami_hw_id = 0,
	};
	send_command(rd, &cmd, &resp);

	// Disable AMI-HW 1
	memset(&cmd, 0, sizeof(cmd));
	cmd.f_ami_hw_disable = (struct rvr_f_ami_hw_disable_cmd){
		.opcode = RVR_F_AMI_HW_DISABLE,
		.ami_hw_id = 1,
	};
	send_command(rd, &cmd, &resp);

	// Destroy session 0
	memset(&cmd, 0, sizeof(cmd));
	cmd.pf_asn_destroy = (struct rvr_pf_asn_destroy_cmd){
		.opcode = RVR_PF_ASN_DESTROY,
		.asn_id = 0,
	};
	send_command(rd, &cmd, &resp);

	// Destroy session 1
	memset(&cmd, 0, sizeof(cmd));
	cmd.pf_asn_destroy = (struct rvr_pf_asn_destroy_cmd){
		.opcode = RVR_PF_ASN_DESTROY,
		.asn_id = 1,
	};
	send_command(rd, &cmd, &resp);

	// Unmap AMI-SW 0
	memset(&cmd, 0, sizeof(cmd));
	cmd.pf_ami_sw_unmap = (struct rvr_pf_ami_sw_unmap_cmd){
		.opcode = RVR_PF_AMI_SW_UNMAP,
		.ami_sw_id = 0,
		.f_owner = 0,
	};
	send_command(rd, &cmd, &resp);

	// Unmap AMI-HW 0
	memset(&cmd, 0, sizeof(cmd));
	cmd.pf_ami_hw_unmap = (struct rvr_pf_ami_hw_unmap_cmd){
		.opcode = RVR_PF_AMI_HW_UNMAP,
		.ami_hw_id = 0,
		.f_owner = 0,
	};
	send_command(rd, &cmd, &resp);

	// Unmap AMI-HW 1
	memset(&cmd, 0, sizeof(cmd));
	cmd.pf_ami_hw_unmap = (struct rvr_pf_ami_hw_unmap_cmd){
		.opcode = RVR_PF_AMI_HW_UNMAP,
		.ami_hw_id = 1,
		.f_owner = 0,
	};
	send_command(rd, &cmd, &resp);

	// Disable AMU
	revere_writeq(rd->regs, 0, AMU_CR);
}
