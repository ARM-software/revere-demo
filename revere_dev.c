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
#include "cmdline.h"
#include "platform.h"

static void setup_mgt(struct revere_dev *rd)
{
	uint64_t amu_idr, amu_aidr;
	unsigned int num_rx_ams_m1, num_tx_ams_m1, num_rx_ams, num_tx_ams,
			arch_major_rev, arch_minor_rev, max_log2_msg_length;
	struct platform *plat = rd->plat;
	const struct cmdline *cl = rd->cl;

	amu_idr = readq(plat, AMU_IDR);

	max_log2_msg_length = (amu_idr >> RVR_AMU_IDR_MAX_LOG2_MSG_LENGTH_SHIFT)
				& RVR_AMU_IDR_MAX_LOG2_MSG_LENGTH_MASK;

	num_rx_ams_m1 = (amu_idr >> RVR_AMU_IDR_NUM_RX_AMS_M1_SHIFT) &
			 RVR_AMU_IDR_NUM_RX_AMS_M1_MASK;

	num_rx_ams = num_rx_ams_m1 + 1;
	num_tx_ams_m1 = amu_idr & RVR_AMU_IDR_NUM_TX_AMS_M1_MASK;
	num_tx_ams = num_tx_ams_m1 + 1;
	amu_aidr = readq(plat, AMU_AIDR);

	arch_major_rev = (amu_aidr >> RVR_AMU_AIDR_ARCHMAJORREV_SHIFT) &
			     RVR_AMU_AIDR_ARCHMAJORREV_MASK;

	arch_minor_rev = (amu_aidr >> RVR_AMU_AIDR_ARCHMINORREV_SHIFT) &
			     RVR_AMU_AIDR_ARCHMINORREV_MASK;

	printf("max_log2_msg_length: %d\n", max_log2_msg_length);
	printf("num_rx_ams: %d\n", num_rx_ams);
	printf("idr: %#lx\n", amu_idr);
	printf("num_tx_ams: %d\n", num_tx_ams);
	printf("aidr: %#lx\n", amu_aidr);
	printf("Revere AMU v%d.%d\n", arch_major_rev, arch_minor_rev);
	printf("iidr: %#lx\n", readq(plat, AMU_IIDR));

	// Sanity checks
	if (arch_major_rev != 3)
		errx(1, "Unsupported Revere version");

	if (cl->log2_msg_length > (int)max_log2_msg_length)
		errx(1, "log2-msg-length %d too large!", cl->log2_msg_length);

	// Enable AMU
	writeq(plat, AMU_CR_EN, AMU_CR);

	/* Command */
	writeq(plat, rd->iova + offsetof(struct revere_buffers, cmd),
		      CMD_BASE_PTR);

	writeq(plat, (MGT_SLOT_DOUBLEWORDS_POT << LOG2_MSG_LENGTH_SHIFT),
		CMD_CTRL);

	/* Response */
	writeq(plat, rd->iova + offsetof(struct revere_buffers, resp),
		      RESP_BASE_PTR);

	writeq(plat, (MGT_SLOT_DOUBLEWORDS_POT << LOG2_MSG_LENGTH_SHIFT),
		RESP_CTRL);

	/* Exception */
	writeq(plat, rd->iova + offsetof(struct revere_buffers, exc),
		      EXC_BASE_PTR);

	writeq(plat, (MGT_SLOT_DOUBLEWORDS_POT << LOG2_MSG_LENGTH_SHIFT),
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
	M(PF_AMI_HW_MAP);
	M(PF_AMI_HW_UNMAP);
	M(PF_AMI_HW_CONFIGURE);
	M(PF_AMI_HW_SAVE);
	M(PF_AMI_HW_RESET);
	M(F_PROF_TABLE_FLUSH);
	M(F_AMI_HW_CONFIGURE);
	M(F_AMI_HW_SAVE);
	M(F_AMI_HW_RESET);
	M(F_AMI_HW_ENABLE);
	M(F_AMI_HW_DISABLE);
	M(F_AMS_PROF_CONFIGURE);
	M(F_AMS_TRACE_CONFIGURE);
	M(PF_PROBE_AHA);
	M(PF_F_TRAP_CONFIGURE);
	M(PF_F_TRAP_RESP);
	M(F_GET_AMI_MAP);
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
	const struct cmdline *cl = rd->cl;
	struct platform *plat = rd->plat;

	co = cmd->pf_probe.opcode;
	printf("sending command %d %s\n", co, command_name(co));

	/* Assert resp empty */
	resp_read_index = readq(plat, RESP_READ_INDEX);
	resp_write_index = readq(plat, RESP_WRITE_INDEX);
	if (!ring_is_empty(resp_read_index, resp_write_index))
		errx(1, "resp ring not empty");

	memset(b->resp, 0, sizeof(b->resp));

	/* Assert command empty */
	cmd_read_index = readq(plat, CMD_READ_INDEX);
	cmd_write_index = readq(plat, CMD_WRITE_INDEX);
	if (!ring_is_empty(cmd_read_index, cmd_write_index))
		errx(1, "cmd ring not empty");

	memset(b->cmd, 0, sizeof(b->cmd));

	/* Send */
	assert(sizeof(*cmd) <= sizeof(b->cmd));
	memcpy(b->cmd, cmd, sizeof(*cmd));
	writeq(plat, cmd_write_index + 1, CMD_WRITE_INDEX);

	/* Wait cmd empty */
	for (i = 0; i < cl->timeout; i++) {
		cmd_read_index = readq(plat, CMD_READ_INDEX);
		cmd_write_index = readq(plat, CMD_WRITE_INDEX);

		if (ring_is_empty(cmd_read_index, cmd_write_index))
			break;

		msleep(plat);
	}

	if (i >= cl->timeout)
		errx(1, "cmd timeout");

	/* Wait for response */
	for (i = 0; i < cl->timeout; i++) {
		resp_read_index = readq(plat, RESP_READ_INDEX);
		resp_write_index = readq(plat, RESP_WRITE_INDEX);

		if (!ring_is_empty(resp_read_index, resp_write_index))
			break;

		msleep(plat);
	}

	if (i >= cl->timeout)
		errx(1, "resp timeout");

	/* Receive */
	assert(sizeof(*resp) <= sizeof(b->resp));
	memcpy(resp, b->resp, sizeof(*resp));
	writeq(plat, resp_read_index + 1, RESP_READ_INDEX);

	/* Sanity checks */
	ro = resp->pf_probe.opcode;
	if (ro != co)
		errx(1, "resp opcode mismatch: %d != %d", ro, co);

	/* Check status */
	s = resp->pf_ami_sw_map.status;
	if (s)
		errx(1, "resp status %d", s);
}

static void probe_amu(struct revere_dev *rd)
{
	union rvr_commands cmd;
	union rvr_responses resp;
	unsigned int max_ami_sw, max_asn, ami_per_f, num_aha;
	const struct cmdline *cl = rd->cl;

	cmd.pf_probe = (struct rvr_pf_probe_cmd){
		.opcode = RVR_PF_PROBE,
	};
	send_command(rd, &cmd, &resp);

	max_ami_sw = resp.pf_probe.max_ami_sw;
	max_asn = resp.pf_probe.max_asn;
	num_aha = resp.pf_probe.num_aha;
	printf("max_ami_sw: %d\n", max_ami_sw);
	printf("max_asn: %d\n", max_asn);
	printf("num_aha: %d\n", num_aha);

	// Sanity checks
	if (max_ami_sw < 1)
		errx(1, "Not enough AMI-SW");

	if (max_asn < (cl->loopback ? 1 : 2))
		errx(1, "Not enough ASN");

	if (!cl->loopback) {
		if ((int)num_aha < cl->aha + 1)
			errx(1, "Not enough AHA");

		cmd.pf_probe_aha = (struct rvr_pf_probe_aha_cmd){
			.opcode = RVR_PF_PROBE_AHA,
			.aha_id = cl->aha,
		};
		send_command(rd, &cmd, &resp);

		printf("aha %d aha_iidr: %#lx\n", cl->aha,
			resp.pf_probe_aha.aha_iidr);
	}

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

static void reset_ami_hw(struct revere_dev *rd, unsigned ami_hw_id)
{
	union rvr_commands cmd;
	union rvr_responses resp;

	cmd.f_ami_hw_disable = (struct rvr_f_ami_hw_disable_cmd){
		.opcode = RVR_F_AMI_HW_DISABLE,
		.ami_hw_id = ami_hw_id,
	};
	send_command(rd, &cmd, &resp);

	cmd.f_ami_hw_reset = (struct rvr_f_ami_hw_reset_cmd){
		.opcode = RVR_F_AMI_HW_RESET,
		.ami_hw_id = ami_hw_id,
	};
	send_command(rd, &cmd, &resp);

	cmd.f_ami_hw_enable = (struct rvr_f_ami_hw_enable_cmd){
		.opcode = RVR_F_AMI_HW_ENABLE,
		.ami_hw_id = ami_hw_id,
	};
	send_command(rd, &cmd, &resp);
}

static void configure(struct revere_dev *rd)
{
	union rvr_commands cmd;
	union rvr_responses resp;
	const struct cmdline *cl = rd->cl;

	// Map AMI-SW 0
	cmd.pf_ami_sw_map = (struct rvr_pf_ami_sw_map_cmd){
		.opcode = RVR_PF_AMI_SW_MAP,
		.any_phy_ami_sw = 1,
		.ami_sw_id = 0,
		.f_owner = 0,
	};
	send_command(rd, &cmd, &resp);
	rd->phy_ami_sw = resp.pf_ami_sw_map.phy_ami_sw_id;

	if (cl->loopback) {
		/* Create session 0
		 * From AMI-SW 0, Tx AMS 0
		 * To AMI-SW 0, Rx AMS 0 */
		cmd.pf_asn_create = (struct rvr_pf_asn_create_cmd){
			.opcode = RVR_PF_ASN_CREATE,
			.dst_ami_type = 0,	// SW
			.src_ami_type = 0,	// SW
			.src_phy_ami_id = rd->phy_ami_sw,
			.dst_phy_ami_id = rd->phy_ami_sw,
			.dst_ams = 0,
			.src_ams = 0,
			.asn_id = 0,
			.prof_ctl = 0,
			.trace_ctl = 0,
			.mfo = 0,
			.log2_msg_length = cl->log2_msg_length,
		};
		send_command(rd, &cmd, &resp);

	} else {
		// Map Rx AMI-HW
		cmd.pf_ami_hw_map = (struct rvr_pf_ami_hw_map_cmd){
			.opcode = RVR_PF_AMI_HW_MAP,
			.phy_ami_hw_id = cl->rx_ami_hw,
			.aha_id = cl->aha,
			.ami_hw_id = cl->rx_ami_hw,
			.f_owner = 0,
		};
		send_command(rd, &cmd, &resp);

		if (cl->rx_ami_hw != cl->tx_ami_hw) {
			// Map Tx AMI-HW
			cmd.pf_ami_hw_map = (struct rvr_pf_ami_hw_map_cmd){
				.opcode = RVR_PF_AMI_HW_MAP,
				.phy_ami_hw_id = cl->tx_ami_hw,
				.aha_id = cl->aha,
				.ami_hw_id = cl->tx_ami_hw,
				.f_owner = 0,
			};
			send_command(rd, &cmd, &resp);
		}

		/* Create session 0
		 * From AMI-SW 0, Tx AMS 0
		 * To Rx AMI-HW, Rx AMS 0 */
		cmd.pf_asn_create = (struct rvr_pf_asn_create_cmd){
			.opcode = RVR_PF_ASN_CREATE,
			.dst_ami_type = 1,	// HW
			.src_ami_type = 0,	// SW
			.src_phy_ami_id = rd->phy_ami_sw,
			.dst_phy_ami_id = cl->rx_ami_hw,
			.dst_aha_id = cl->aha,
			.dst_ams = 0,
			.src_ams = 0,
			.asn_id = 0,
			.prof_ctl = 0,
			.trace_ctl = 0,
			.mfo = 0,
			.log2_msg_length = cl->log2_msg_length,
		};
		send_command(rd, &cmd, &resp);

		/* Create session 1
		 * From Tx AMI-HW, Tx AMS 0
		 * To AMI-SW 0, Rx AMS 0 */
		cmd.pf_asn_create = (struct rvr_pf_asn_create_cmd){
			.opcode = RVR_PF_ASN_CREATE,
			.dst_ami_type = 0,	// SW
			.src_ami_type = 1,	// HW
			.src_phy_ami_id = cl->tx_ami_hw,
			.src_aha_id = cl->aha,
			.dst_phy_ami_id = rd->phy_ami_sw,
			.dst_ams = 0,
			.src_ams = 0,
			.asn_id = 1,
			.prof_ctl = 0,
			.trace_ctl = 0,
			.mfo = 0,
			.log2_msg_length = cl->log2_msg_length,
		};
		send_command(rd, &cmd, &resp);
	}

	// Configure AMI-SW 0
	cmd.f_ami_sw_disable = (struct rvr_f_ami_sw_disable_cmd){
		.opcode = RVR_F_AMI_SW_DISABLE,
		.ami_sw_id = 0,
	};
	send_command(rd, &cmd, &resp);

	cmd.f_ami_sw_reset = (struct rvr_f_ami_sw_reset_cmd){
		.opcode = RVR_F_AMI_SW_RESET,
		.ami_sw_id = 0,
	};
	send_command(rd, &cmd, &resp);

	cmd.f_ami_sw_configure = (struct rvr_f_ami_sw_configure_cmd){
		.opcode = RVR_F_AMI_SW_CONFIGURE,
		.ami_sw_id = 0,
		.pasid_enabled = 0,
		.tx_irq_enable = 0,
		.rx_irq_enable = 0,
	};
	send_command(rd, &cmd, &resp);

	cmd.f_ams_ring_configure = (struct rvr_f_ams_ring_configure_cmd){
		.opcode = RVR_F_AMS_RING_CONFIGURE,
		.ami_sw_id = 0,
		.ams_id = 0,
		.ams_type = 0,	// Rx
		.rx_mode = 0,
		.log2_size = RING_SLOTS_POT,
		.threshold = 0,
		.ring_base = (rd->iova +
				offsetof(struct revere_buffers, rx)) >> 3,
	};
	send_command(rd, &cmd, &resp);

	cmd.f_ams_ring_configure = (struct rvr_f_ams_ring_configure_cmd){
		.opcode = RVR_F_AMS_RING_CONFIGURE,
		.ami_sw_id = 0,
		.ams_id = 0,
		.ams_type = 1,	// Tx
		.log2_size = RING_SLOTS_POT,
		.threshold = 0,
		.ring_base = (rd->iova +
				offsetof(struct revere_buffers, tx)) >> 3,
	};
	send_command(rd, &cmd, &resp);

	cmd.f_ami_sw_enable = (struct rvr_f_ami_sw_enable_cmd){
		.opcode = RVR_F_AMI_SW_ENABLE,
		.ami_sw_id = 0,
	};
	send_command(rd, &cmd, &resp);

	if (!cl->loopback) {
		// Reset Rx AMI-HW
		reset_ami_hw(rd, cl->rx_ami_hw);

		if (cl->rx_ami_hw != cl->tx_ami_hw) {
			// Reset Tx AMI-HW
			reset_ami_hw(rd, cl->tx_ami_hw);
		}
	}
}

void revere_dev_setup(struct revere_dev *rd, struct revere_buffers *bufs,
			struct platform *plat, uint64_t iova,
			const struct cmdline *cl)
{
	assert(rd);
	assert(bufs);
	assert(plat);
	assert(iova);
	assert(cl);

	*rd = (struct revere_dev){
		.bufs = bufs,
		.plat = plat,
		.iova = iova,
		.cl = cl,
	};

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
	const struct cmdline *cl;
	struct platform *plat;

	assert(rd);

	cl = rd->cl;
	plat = rd->plat;

	// Disable AMI-SW 0
	cmd.f_ami_sw_disable = (struct rvr_f_ami_sw_disable_cmd){
		.opcode = RVR_F_AMI_SW_DISABLE,
		.ami_sw_id = 0,
	};
	send_command(rd, &cmd, &resp);

	if (!cl->loopback) {
		// Disable Rx AMI-HW
		cmd.f_ami_hw_disable = (struct rvr_f_ami_hw_disable_cmd){
			.opcode = RVR_F_AMI_HW_DISABLE,
			.ami_hw_id = cl->rx_ami_hw,
		};
		send_command(rd, &cmd, &resp);

		if (cl->rx_ami_hw != cl->tx_ami_hw) {
			// Disable Tx AMI-HW
			cmd.f_ami_hw_disable = (struct rvr_f_ami_hw_disable_cmd){
				.opcode = RVR_F_AMI_HW_DISABLE,
				.ami_hw_id = cl->tx_ami_hw,
			};
			send_command(rd, &cmd, &resp);
		}
	}

	// Destroy session 0
	cmd.pf_asn_destroy = (struct rvr_pf_asn_destroy_cmd){
		.opcode = RVR_PF_ASN_DESTROY,
		.asn_id = 0,
	};
	send_command(rd, &cmd, &resp);

	if (!cl->loopback) {
		// Destroy session 1
		cmd.pf_asn_destroy = (struct rvr_pf_asn_destroy_cmd){
			.opcode = RVR_PF_ASN_DESTROY,
			.asn_id = 1,
		};
		send_command(rd, &cmd, &resp);
	}

	// Unmap AMI-SW 0
	cmd.pf_ami_sw_unmap = (struct rvr_pf_ami_sw_unmap_cmd){
		.opcode = RVR_PF_AMI_SW_UNMAP,
		.phy_ami_sw_id = rd->phy_ami_sw,
	};
	send_command(rd, &cmd, &resp);

	if (!cl->loopback) {
		// Unmap Rx AMI-HW
		cmd.pf_ami_hw_unmap = (struct rvr_pf_ami_hw_unmap_cmd){
			.opcode = RVR_PF_AMI_HW_UNMAP,
			.phy_ami_hw_id = cl->rx_ami_hw,
			.aha_id = cl->aha,
		};
		send_command(rd, &cmd, &resp);

		if (cl->rx_ami_hw != cl->tx_ami_hw) {
			// Unmap AMI-HW 1
			cmd.pf_ami_hw_unmap = (struct rvr_pf_ami_hw_unmap_cmd){
				.opcode = RVR_PF_AMI_HW_UNMAP,
				.phy_ami_hw_id = cl->tx_ami_hw,
				.aha_id = cl->aha,
			};
			send_command(rd, &cmd, &resp);
		}
	}

	// Disable AMU
	writeq(plat, 0, AMU_CR);

#ifndef NDEBUG
	memset(rd, 0, sizeof(*rd));
#endif
}
