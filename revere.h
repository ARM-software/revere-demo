// SPDX-License-Identifier: BSD-3-Clause
/*
 * Revere-AMU commands definitions.
 * THIS IS A GENERATED FILE!
 *
 * Generated Wed Nov 28 10:44:08 2018 by vinste01,
 * from commit f7d4135143d4991481fc864a075f1311bcc199cc.
 *
 * Notes: we need __packed and u64.
 */

#ifndef _REVERE_H_INCLUDED
#define _REVERE_H_INCLUDED

/**********************************************************************
 *			Commands and responses
 **********************************************************************/

enum rvr_opcode {
	RVR_PF_PROBE = 1,
	RVR_F_PROBE = 2,
	RVR_PF_F_ENABLE = 3,
	RVR_PF_F_DISABLE = 4,
	RVR_F_TYPEB_TABLE_CONFIGURE = 5,
	RVR_PF_AMI_SW_MAP = 6,
	RVR_PF_AMI_SW_UNMAP = 7,
	RVR_PF_AMI_SW_CONFIGURE = 8,
	RVR_PF_AMI_SW_SAVE = 9,
	RVR_PF_AMI_SW_RESET = 10,
	RVR_F_AMI_SW_CONFIGURE = 11,
	RVR_F_AMI_SW_SAVE = 12,
	RVR_F_AMI_SW_RESET = 13,
	RVR_F_AMI_SW_ENABLE = 14,
	RVR_F_AMI_SW_DISABLE = 15,
	RVR_PF_ASN_CREATE = 16,
	RVR_PF_ASN_DESTROY = 17,
	RVR_PF_AMS_RING_CONFIGURE = 18,
	RVR_PF_AMS_RING_SAVE = 19,
	RVR_F_AMS_RING_CONFIGURE = 20,
	RVR_F_AMS_RING_SAVE = 21,
	RVR_PF_RESPONSE_TO_VF = 22,
	RVR_PF_AMI_HW_MAP = 23,
	RVR_PF_AMI_HW_UNMAP = 24,
	RVR_PF_AMI_HW_CONFIGURE = 25,
	RVR_PF_AMI_HW_SAVE = 26,
	RVR_PF_AMI_HW_RESET = 27,
	RVR_VF_COMMAND_TO_PF = 28,
	RVR_F_PROF_TABLE_FLUSH = 29,
	RVR_F_AMI_HW_CONFIGURE = 30,
	RVR_F_AMI_HW_SAVE = 31,
	RVR_F_AMI_HW_RESET = 32,
	RVR_F_AMI_HW_ENABLE = 33,
	RVR_F_AMI_HW_DISABLE = 34,
	RVR_F_AMS_PROF_CONFIGURE = 35,
	RVR_F_AMS_TRACE_CONFIGURE = 36,
};

/**********************************************************************
 *			F-AMI-HW-CONFIGURE (opcode 30)
 **********************************************************************/

/*
 * F-AMI-HW-CONFIGURE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_HW_ID (16b)
 *	AMI-HW within the Function to be configured
 * @0x8 [19:0] ([83:64]) PASID (20b)
 *	PASID value
 * @0x8 [20:20] ([84:84]) PASID_ENABLED (1b)
 *	1: Enable PASID
 *	0: Disable PASID
 */

#define RVR_F_AMI_HW_CONFIGURE_CMD_OPCODE_OFFSET 0
#define RVR_F_AMI_HW_CONFIGURE_CMD_OPCODE_SHIFT 0
#define RVR_F_AMI_HW_CONFIGURE_CMD_OPCODE_MASK 0xffff
#define RVR_F_AMI_HW_CONFIGURE_CMD_AMI_HW_ID_OFFSET 4
#define RVR_F_AMI_HW_CONFIGURE_CMD_AMI_HW_ID_SHIFT 0
#define RVR_F_AMI_HW_CONFIGURE_CMD_AMI_HW_ID_MASK 0xffff
#define RVR_F_AMI_HW_CONFIGURE_CMD_PASID_OFFSET 8
#define RVR_F_AMI_HW_CONFIGURE_CMD_PASID_SHIFT 0
#define RVR_F_AMI_HW_CONFIGURE_CMD_PASID_MASK 0xfffff
#define RVR_F_AMI_HW_CONFIGURE_CMD_PASID_ENABLED_OFFSET 8
#define RVR_F_AMI_HW_CONFIGURE_CMD_PASID_ENABLED_SHIFT 20
#define RVR_F_AMI_HW_CONFIGURE_CMD_PASID_ENABLED_MASK 0x1

struct rvr_f_ami_hw_configure_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_hw_id:16;
	u64 _reserved_2:16;
	u64 pasid:20;
	u64 pasid_enabled:1;
	u64 _reserved_3:11;
} __packed;

/*
 * F-AMI-HW-CONFIGURE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMI-HW configured successfully
 *	1: AMI-HW is not mapped in Function
 *	2: AMI-HW is not disabled
 */

#define RVR_F_AMI_HW_CONFIGURE_RESP_OPCODE_OFFSET 0
#define RVR_F_AMI_HW_CONFIGURE_RESP_OPCODE_SHIFT 0
#define RVR_F_AMI_HW_CONFIGURE_RESP_OPCODE_MASK 0xffff
#define RVR_F_AMI_HW_CONFIGURE_RESP_STATUS_OFFSET 0
#define RVR_F_AMI_HW_CONFIGURE_RESP_STATUS_SHIFT 16
#define RVR_F_AMI_HW_CONFIGURE_RESP_STATUS_MASK 0xffff

struct rvr_f_ami_hw_configure_resp {
	u64 opcode:16;
	u64 status:16;
} __packed;

/**********************************************************************
 *			F-AMI-HW-DISABLE (opcode 34)
 **********************************************************************/

/*
 * F-AMI-HW-DISABLE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_HW_ID (16b)
 *	AMI-HW within the Function to be enabled
 */

#define RVR_F_AMI_HW_DISABLE_CMD_OPCODE_OFFSET 0
#define RVR_F_AMI_HW_DISABLE_CMD_OPCODE_SHIFT 0
#define RVR_F_AMI_HW_DISABLE_CMD_OPCODE_MASK 0xffff
#define RVR_F_AMI_HW_DISABLE_CMD_AMI_HW_ID_OFFSET 4
#define RVR_F_AMI_HW_DISABLE_CMD_AMI_HW_ID_SHIFT 0
#define RVR_F_AMI_HW_DISABLE_CMD_AMI_HW_ID_MASK 0xffff

struct rvr_f_ami_hw_disable_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_hw_id:16;
	u64 _reserved_2:16;
} __packed;

/*
 * F-AMI-HW-DISABLE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMI-HW disabled successfully
 *	1: AMI-HW is not mapped in Function
 */

#define RVR_F_AMI_HW_DISABLE_RESP_OPCODE_OFFSET 0
#define RVR_F_AMI_HW_DISABLE_RESP_OPCODE_SHIFT 0
#define RVR_F_AMI_HW_DISABLE_RESP_OPCODE_MASK 0xffff
#define RVR_F_AMI_HW_DISABLE_RESP_STATUS_OFFSET 0
#define RVR_F_AMI_HW_DISABLE_RESP_STATUS_SHIFT 16
#define RVR_F_AMI_HW_DISABLE_RESP_STATUS_MASK 0xffff

struct rvr_f_ami_hw_disable_resp {
	u64 opcode:16;
	u64 status:16;
} __packed;

/**********************************************************************
 *			F-AMI-HW-ENABLE (opcode 33)
 **********************************************************************/

/*
 * F-AMI-HW-ENABLE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_HW_ID (16b)
 *	AMI-HW within the Function to be enabled
 */

#define RVR_F_AMI_HW_ENABLE_CMD_OPCODE_OFFSET 0
#define RVR_F_AMI_HW_ENABLE_CMD_OPCODE_SHIFT 0
#define RVR_F_AMI_HW_ENABLE_CMD_OPCODE_MASK 0xffff
#define RVR_F_AMI_HW_ENABLE_CMD_AMI_HW_ID_OFFSET 4
#define RVR_F_AMI_HW_ENABLE_CMD_AMI_HW_ID_SHIFT 0
#define RVR_F_AMI_HW_ENABLE_CMD_AMI_HW_ID_MASK 0xffff

struct rvr_f_ami_hw_enable_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_hw_id:16;
	u64 _reserved_2:16;
} __packed;

/*
 * F-AMI-HW-ENABLE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMI-HW enabled successfully
 *	1: AMI-HW is not mapped in Function
 */

#define RVR_F_AMI_HW_ENABLE_RESP_OPCODE_OFFSET 0
#define RVR_F_AMI_HW_ENABLE_RESP_OPCODE_SHIFT 0
#define RVR_F_AMI_HW_ENABLE_RESP_OPCODE_MASK 0xffff
#define RVR_F_AMI_HW_ENABLE_RESP_STATUS_OFFSET 0
#define RVR_F_AMI_HW_ENABLE_RESP_STATUS_SHIFT 16
#define RVR_F_AMI_HW_ENABLE_RESP_STATUS_MASK 0xffff

struct rvr_f_ami_hw_enable_resp {
	u64 opcode:16;
	u64 status:16;
} __packed;

/**********************************************************************
 *			F-AMI-HW-RESET (opcode 32)
 **********************************************************************/

/*
 * F-AMI-HW-RESET command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_HW_ID (16b)
 *	AMI-HW within the Function to be reset
 */

#define RVR_F_AMI_HW_RESET_CMD_OPCODE_OFFSET 0
#define RVR_F_AMI_HW_RESET_CMD_OPCODE_SHIFT 0
#define RVR_F_AMI_HW_RESET_CMD_OPCODE_MASK 0xffff
#define RVR_F_AMI_HW_RESET_CMD_AMI_HW_ID_OFFSET 4
#define RVR_F_AMI_HW_RESET_CMD_AMI_HW_ID_SHIFT 0
#define RVR_F_AMI_HW_RESET_CMD_AMI_HW_ID_MASK 0xffff

struct rvr_f_ami_hw_reset_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_hw_id:16;
	u64 _reserved_2:16;
} __packed;

/*
 * F-AMI-HW-RESET response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMI-HW reset successfully
 *	1: AMI-HW is not mapped in Function
 *	2: AMI-HW is not disabled
 */

#define RVR_F_AMI_HW_RESET_RESP_OPCODE_OFFSET 0
#define RVR_F_AMI_HW_RESET_RESP_OPCODE_SHIFT 0
#define RVR_F_AMI_HW_RESET_RESP_OPCODE_MASK 0xffff
#define RVR_F_AMI_HW_RESET_RESP_STATUS_OFFSET 0
#define RVR_F_AMI_HW_RESET_RESP_STATUS_SHIFT 16
#define RVR_F_AMI_HW_RESET_RESP_STATUS_MASK 0xffff

struct rvr_f_ami_hw_reset_resp {
	u64 opcode:16;
	u64 status:16;
} __packed;

/**********************************************************************
 *			F-AMI-HW-SAVE (opcode 31)
 **********************************************************************/

/*
 * F-AMI-HW-SAVE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_HW_ID (16b)
 *	AMI-HW within the Function to be saved
 */

#define RVR_F_AMI_HW_SAVE_CMD_OPCODE_OFFSET 0
#define RVR_F_AMI_HW_SAVE_CMD_OPCODE_SHIFT 0
#define RVR_F_AMI_HW_SAVE_CMD_OPCODE_MASK 0xffff
#define RVR_F_AMI_HW_SAVE_CMD_AMI_HW_ID_OFFSET 4
#define RVR_F_AMI_HW_SAVE_CMD_AMI_HW_ID_SHIFT 0
#define RVR_F_AMI_HW_SAVE_CMD_AMI_HW_ID_MASK 0xffff

struct rvr_f_ami_hw_save_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_hw_id:16;
	u64 _reserved_2:16;
} __packed;

/*
 * F-AMI-HW-SAVE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMI-HW saved successfully
 *	1: AMI-HW is not mapped in Function
 *	2: AMI-HW is not disabled
 * @0x4 [19:0] ([51:32]) PASID (20b)
 *	PASID value
 * @0x4 [20:20] ([52:52]) PASID_ENABLED (1b)
 *	1: PASID is enabled
 *	0: PASID is disabled
 */

#define RVR_F_AMI_HW_SAVE_RESP_OPCODE_OFFSET 0
#define RVR_F_AMI_HW_SAVE_RESP_OPCODE_SHIFT 0
#define RVR_F_AMI_HW_SAVE_RESP_OPCODE_MASK 0xffff
#define RVR_F_AMI_HW_SAVE_RESP_STATUS_OFFSET 0
#define RVR_F_AMI_HW_SAVE_RESP_STATUS_SHIFT 16
#define RVR_F_AMI_HW_SAVE_RESP_STATUS_MASK 0xffff
#define RVR_F_AMI_HW_SAVE_RESP_PASID_OFFSET 4
#define RVR_F_AMI_HW_SAVE_RESP_PASID_SHIFT 0
#define RVR_F_AMI_HW_SAVE_RESP_PASID_MASK 0xfffff
#define RVR_F_AMI_HW_SAVE_RESP_PASID_ENABLED_OFFSET 4
#define RVR_F_AMI_HW_SAVE_RESP_PASID_ENABLED_SHIFT 20
#define RVR_F_AMI_HW_SAVE_RESP_PASID_ENABLED_MASK 0x1

struct rvr_f_ami_hw_save_resp {
	u64 opcode:16;
	u64 status:16;
	u64 pasid:20;
	u64 pasid_enabled:1;
	u64 _reserved_:11;
} __packed;

/**********************************************************************
 *			F-AMI-SW-CONFIGURE (opcode 11)
 **********************************************************************/

/*
 * F-AMI-SW-CONFIGURE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_SW_ID (16b)
 *	AMI-SW within the Function to be configured
 * @0x8 [19:0] ([83:64]) PASID (20b)
 *	PASID value
 * @0x8 [20:20] ([84:84]) PASID_ENABLED (1b)
 *	1: Enable PASID
 *	0: Disable PASID
 * @0xc [10:0] ([106:96]) TX_VECTOR (11b)
 *	Value to use for TX_VECTOR
 * @0xc [21:11] ([117:107]) RX_VECTOR (11b)
 *	Value to use for RX_VECTOR
 * @0xc [22:22] ([118:118]) TX_IRQ_ENABLE (1b)
 *	1: Enable TX Interrupt Generation
 *	0: Disable TX Interrupt Generation
 * @0xc [23:23] ([119:119]) RX_IRQ_ENABLE (1b)
 *	1: Enable RX Interrupt Generation
 *	0: Disable RX Interrupt Generation
 */

#define RVR_F_AMI_SW_CONFIGURE_CMD_OPCODE_OFFSET 0
#define RVR_F_AMI_SW_CONFIGURE_CMD_OPCODE_SHIFT 0
#define RVR_F_AMI_SW_CONFIGURE_CMD_OPCODE_MASK 0xffff
#define RVR_F_AMI_SW_CONFIGURE_CMD_AMI_SW_ID_OFFSET 4
#define RVR_F_AMI_SW_CONFIGURE_CMD_AMI_SW_ID_SHIFT 0
#define RVR_F_AMI_SW_CONFIGURE_CMD_AMI_SW_ID_MASK 0xffff
#define RVR_F_AMI_SW_CONFIGURE_CMD_PASID_OFFSET 8
#define RVR_F_AMI_SW_CONFIGURE_CMD_PASID_SHIFT 0
#define RVR_F_AMI_SW_CONFIGURE_CMD_PASID_MASK 0xfffff
#define RVR_F_AMI_SW_CONFIGURE_CMD_PASID_ENABLED_OFFSET 8
#define RVR_F_AMI_SW_CONFIGURE_CMD_PASID_ENABLED_SHIFT 20
#define RVR_F_AMI_SW_CONFIGURE_CMD_PASID_ENABLED_MASK 0x1
#define RVR_F_AMI_SW_CONFIGURE_CMD_TX_VECTOR_OFFSET 12
#define RVR_F_AMI_SW_CONFIGURE_CMD_TX_VECTOR_SHIFT 0
#define RVR_F_AMI_SW_CONFIGURE_CMD_TX_VECTOR_MASK 0x7ff
#define RVR_F_AMI_SW_CONFIGURE_CMD_RX_VECTOR_OFFSET 12
#define RVR_F_AMI_SW_CONFIGURE_CMD_RX_VECTOR_SHIFT 11
#define RVR_F_AMI_SW_CONFIGURE_CMD_RX_VECTOR_MASK 0x7ff
#define RVR_F_AMI_SW_CONFIGURE_CMD_TX_IRQ_ENABLE_OFFSET 12
#define RVR_F_AMI_SW_CONFIGURE_CMD_TX_IRQ_ENABLE_SHIFT 22
#define RVR_F_AMI_SW_CONFIGURE_CMD_TX_IRQ_ENABLE_MASK 0x1
#define RVR_F_AMI_SW_CONFIGURE_CMD_RX_IRQ_ENABLE_OFFSET 12
#define RVR_F_AMI_SW_CONFIGURE_CMD_RX_IRQ_ENABLE_SHIFT 23
#define RVR_F_AMI_SW_CONFIGURE_CMD_RX_IRQ_ENABLE_MASK 0x1

struct rvr_f_ami_sw_configure_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_sw_id:16;
	u64 _reserved_2:16;
	u64 pasid:20;
	u64 pasid_enabled:1;
	u64 _reserved_3:11;
	u64 tx_vector:11;
	u64 rx_vector:11;
	u64 tx_irq_enable:1;
	u64 rx_irq_enable:1;
	u64 _reserved_4:8;
} __packed;

/*
 * F-AMI-SW-CONFIGURE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMI-SW configured successfully
 *	1: AMI-SW is not mapped in Function
 *	2: AMI-SW is not disabled
 */

#define RVR_F_AMI_SW_CONFIGURE_RESP_OPCODE_OFFSET 0
#define RVR_F_AMI_SW_CONFIGURE_RESP_OPCODE_SHIFT 0
#define RVR_F_AMI_SW_CONFIGURE_RESP_OPCODE_MASK 0xffff
#define RVR_F_AMI_SW_CONFIGURE_RESP_STATUS_OFFSET 0
#define RVR_F_AMI_SW_CONFIGURE_RESP_STATUS_SHIFT 16
#define RVR_F_AMI_SW_CONFIGURE_RESP_STATUS_MASK 0xffff

struct rvr_f_ami_sw_configure_resp {
	u64 opcode:16;
	u64 status:16;
} __packed;

/**********************************************************************
 *			F-AMI-SW-DISABLE (opcode 15)
 **********************************************************************/

/*
 * F-AMI-SW-DISABLE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_SW_ID (16b)
 *	AMI-SW within the Function to be enabled
 */

#define RVR_F_AMI_SW_DISABLE_CMD_OPCODE_OFFSET 0
#define RVR_F_AMI_SW_DISABLE_CMD_OPCODE_SHIFT 0
#define RVR_F_AMI_SW_DISABLE_CMD_OPCODE_MASK 0xffff
#define RVR_F_AMI_SW_DISABLE_CMD_AMI_SW_ID_OFFSET 4
#define RVR_F_AMI_SW_DISABLE_CMD_AMI_SW_ID_SHIFT 0
#define RVR_F_AMI_SW_DISABLE_CMD_AMI_SW_ID_MASK 0xffff

struct rvr_f_ami_sw_disable_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_sw_id:16;
	u64 _reserved_2:16;
} __packed;

/*
 * F-AMI-SW-DISABLE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMI-SW disabled successfully
 *	1: AMI-SW is not mapped in Function
 */

#define RVR_F_AMI_SW_DISABLE_RESP_OPCODE_OFFSET 0
#define RVR_F_AMI_SW_DISABLE_RESP_OPCODE_SHIFT 0
#define RVR_F_AMI_SW_DISABLE_RESP_OPCODE_MASK 0xffff
#define RVR_F_AMI_SW_DISABLE_RESP_STATUS_OFFSET 0
#define RVR_F_AMI_SW_DISABLE_RESP_STATUS_SHIFT 16
#define RVR_F_AMI_SW_DISABLE_RESP_STATUS_MASK 0xffff

struct rvr_f_ami_sw_disable_resp {
	u64 opcode:16;
	u64 status:16;
} __packed;

/**********************************************************************
 *			F-AMI-SW-ENABLE (opcode 14)
 **********************************************************************/

/*
 * F-AMI-SW-ENABLE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_SW_ID (16b)
 *	AMI-SW within the Function to be enabled
 */

#define RVR_F_AMI_SW_ENABLE_CMD_OPCODE_OFFSET 0
#define RVR_F_AMI_SW_ENABLE_CMD_OPCODE_SHIFT 0
#define RVR_F_AMI_SW_ENABLE_CMD_OPCODE_MASK 0xffff
#define RVR_F_AMI_SW_ENABLE_CMD_AMI_SW_ID_OFFSET 4
#define RVR_F_AMI_SW_ENABLE_CMD_AMI_SW_ID_SHIFT 0
#define RVR_F_AMI_SW_ENABLE_CMD_AMI_SW_ID_MASK 0xffff

struct rvr_f_ami_sw_enable_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_sw_id:16;
	u64 _reserved_2:16;
} __packed;

/*
 * F-AMI-SW-ENABLE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMI-SW enabled successfully
 *	1: AMI-SW is not mapped in Function
 */

#define RVR_F_AMI_SW_ENABLE_RESP_OPCODE_OFFSET 0
#define RVR_F_AMI_SW_ENABLE_RESP_OPCODE_SHIFT 0
#define RVR_F_AMI_SW_ENABLE_RESP_OPCODE_MASK 0xffff
#define RVR_F_AMI_SW_ENABLE_RESP_STATUS_OFFSET 0
#define RVR_F_AMI_SW_ENABLE_RESP_STATUS_SHIFT 16
#define RVR_F_AMI_SW_ENABLE_RESP_STATUS_MASK 0xffff

struct rvr_f_ami_sw_enable_resp {
	u64 opcode:16;
	u64 status:16;
} __packed;

/**********************************************************************
 *			F-AMI-SW-RESET (opcode 13)
 **********************************************************************/

/*
 * F-AMI-SW-RESET command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_SW_ID (16b)
 *	AMI-SW within the Function to be reset
 */

#define RVR_F_AMI_SW_RESET_CMD_OPCODE_OFFSET 0
#define RVR_F_AMI_SW_RESET_CMD_OPCODE_SHIFT 0
#define RVR_F_AMI_SW_RESET_CMD_OPCODE_MASK 0xffff
#define RVR_F_AMI_SW_RESET_CMD_AMI_SW_ID_OFFSET 4
#define RVR_F_AMI_SW_RESET_CMD_AMI_SW_ID_SHIFT 0
#define RVR_F_AMI_SW_RESET_CMD_AMI_SW_ID_MASK 0xffff

struct rvr_f_ami_sw_reset_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_sw_id:16;
	u64 _reserved_2:16;
} __packed;

/*
 * F-AMI-SW-RESET response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMI-SW reset successfully
 *	1: AMI-SW is not mapped in Function
 *	2: AMI-SW is not disabled
 */

#define RVR_F_AMI_SW_RESET_RESP_OPCODE_OFFSET 0
#define RVR_F_AMI_SW_RESET_RESP_OPCODE_SHIFT 0
#define RVR_F_AMI_SW_RESET_RESP_OPCODE_MASK 0xffff
#define RVR_F_AMI_SW_RESET_RESP_STATUS_OFFSET 0
#define RVR_F_AMI_SW_RESET_RESP_STATUS_SHIFT 16
#define RVR_F_AMI_SW_RESET_RESP_STATUS_MASK 0xffff

struct rvr_f_ami_sw_reset_resp {
	u64 opcode:16;
	u64 status:16;
} __packed;

/**********************************************************************
 *			F-AMI-SW-SAVE (opcode 12)
 **********************************************************************/

/*
 * F-AMI-SW-SAVE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_SW_ID (16b)
 *	AMI-SW within the Function to be saved
 */

#define RVR_F_AMI_SW_SAVE_CMD_OPCODE_OFFSET 0
#define RVR_F_AMI_SW_SAVE_CMD_OPCODE_SHIFT 0
#define RVR_F_AMI_SW_SAVE_CMD_OPCODE_MASK 0xffff
#define RVR_F_AMI_SW_SAVE_CMD_AMI_SW_ID_OFFSET 4
#define RVR_F_AMI_SW_SAVE_CMD_AMI_SW_ID_SHIFT 0
#define RVR_F_AMI_SW_SAVE_CMD_AMI_SW_ID_MASK 0xffff

struct rvr_f_ami_sw_save_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_sw_id:16;
	u64 _reserved_2:16;
} __packed;

/*
 * F-AMI-SW-SAVE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMI-SW saved successfully
 *	1: AMI-SW is not mapped in Function
 *	2: AMI-SW is not disabled
 * @0x8 [19:0] ([83:64]) PASID (20b)
 *	PASID value
 * @0x8 [20:20] ([84:84]) PASID_ENABLED (1b)
 *	1: PASID is enabled
 *	0: PASID is disabled
 * @0xc [10:0] ([106:96]) TX_VECTOR (11b)
 *	TX_VECTOR value
 * @0xc [21:11] ([117:107]) RX_VECTOR (11b)
 *	RX_VECTOR value
 * @0xc [22:22] ([118:118]) TX_IRQ_ENABLE (1b)
 *	1: Enable TX Interrupt Generation
 *	0: Disable TX Interrupt Generation
 * @0xc [23:23] ([119:119]) RX_IRQ_ENABLE (1b)
 *	1: Enable RX Interrupt Generation
 *	0: Disable RX Interrupt Generation
 */

#define RVR_F_AMI_SW_SAVE_RESP_OPCODE_OFFSET 0
#define RVR_F_AMI_SW_SAVE_RESP_OPCODE_SHIFT 0
#define RVR_F_AMI_SW_SAVE_RESP_OPCODE_MASK 0xffff
#define RVR_F_AMI_SW_SAVE_RESP_STATUS_OFFSET 0
#define RVR_F_AMI_SW_SAVE_RESP_STATUS_SHIFT 16
#define RVR_F_AMI_SW_SAVE_RESP_STATUS_MASK 0xffff
#define RVR_F_AMI_SW_SAVE_RESP_PASID_OFFSET 8
#define RVR_F_AMI_SW_SAVE_RESP_PASID_SHIFT 0
#define RVR_F_AMI_SW_SAVE_RESP_PASID_MASK 0xfffff
#define RVR_F_AMI_SW_SAVE_RESP_PASID_ENABLED_OFFSET 8
#define RVR_F_AMI_SW_SAVE_RESP_PASID_ENABLED_SHIFT 20
#define RVR_F_AMI_SW_SAVE_RESP_PASID_ENABLED_MASK 0x1
#define RVR_F_AMI_SW_SAVE_RESP_TX_VECTOR_OFFSET 12
#define RVR_F_AMI_SW_SAVE_RESP_TX_VECTOR_SHIFT 0
#define RVR_F_AMI_SW_SAVE_RESP_TX_VECTOR_MASK 0x7ff
#define RVR_F_AMI_SW_SAVE_RESP_RX_VECTOR_OFFSET 12
#define RVR_F_AMI_SW_SAVE_RESP_RX_VECTOR_SHIFT 11
#define RVR_F_AMI_SW_SAVE_RESP_RX_VECTOR_MASK 0x7ff
#define RVR_F_AMI_SW_SAVE_RESP_TX_IRQ_ENABLE_OFFSET 12
#define RVR_F_AMI_SW_SAVE_RESP_TX_IRQ_ENABLE_SHIFT 22
#define RVR_F_AMI_SW_SAVE_RESP_TX_IRQ_ENABLE_MASK 0x1
#define RVR_F_AMI_SW_SAVE_RESP_RX_IRQ_ENABLE_OFFSET 12
#define RVR_F_AMI_SW_SAVE_RESP_RX_IRQ_ENABLE_SHIFT 23
#define RVR_F_AMI_SW_SAVE_RESP_RX_IRQ_ENABLE_MASK 0x1

struct rvr_f_ami_sw_save_resp {
	u64 opcode:16;
	u64 status:16;
	u64 _reserved_:32;
	u64 pasid:20;
	u64 pasid_enabled:1;
	u64 _reserved_2:11;
	u64 tx_vector:11;
	u64 rx_vector:11;
	u64 tx_irq_enable:1;
	u64 rx_irq_enable:1;
	u64 _reserved_3:8;
} __packed;

/**********************************************************************
 *			F-AMS-PROF-CONFIGURE (opcode 35)
 **********************************************************************/

/*
 * F-AMS-PROF-CONFIGURE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_ID (16b)
 *	AMI within F_OWNER to be configured
 * @0x4 [16:16] ([48:48]) AMI_TYPE (1b)
 *	0: AMI-SW
 *	1: AMI-HW
 * @0x4 [22:17] ([54:49]) AMS_ID (6b)
 *	AMS within AMI to be configured
 * @0x4 [23:23] ([55:55]) AMS_TYPE (1b)
 *	0: RX AMS
 *	1: TX AMS
 * @0x8 [63:0] ([127:64]) PROF_MASK (64b)
 *	Profiling mask
 * @0x10 [63:0] ([191:128]) PROF_TBL_BASE (64b)
 *	Profiling table base pointer
 * @0x18 [15:0] ([207:192]) PROF_CTL (16b)
 *	Profiling controls configured in the associated ASN
 */

#define RVR_F_AMS_PROF_CONFIGURE_CMD_OPCODE_OFFSET 0
#define RVR_F_AMS_PROF_CONFIGURE_CMD_OPCODE_SHIFT 0
#define RVR_F_AMS_PROF_CONFIGURE_CMD_OPCODE_MASK 0xffff
#define RVR_F_AMS_PROF_CONFIGURE_CMD_AMI_ID_OFFSET 4
#define RVR_F_AMS_PROF_CONFIGURE_CMD_AMI_ID_SHIFT 0
#define RVR_F_AMS_PROF_CONFIGURE_CMD_AMI_ID_MASK 0xffff
#define RVR_F_AMS_PROF_CONFIGURE_CMD_AMI_TYPE_OFFSET 4
#define RVR_F_AMS_PROF_CONFIGURE_CMD_AMI_TYPE_SHIFT 16
#define RVR_F_AMS_PROF_CONFIGURE_CMD_AMI_TYPE_MASK 0x1
#define RVR_F_AMS_PROF_CONFIGURE_CMD_AMS_ID_OFFSET 4
#define RVR_F_AMS_PROF_CONFIGURE_CMD_AMS_ID_SHIFT 17
#define RVR_F_AMS_PROF_CONFIGURE_CMD_AMS_ID_MASK 0x3f
#define RVR_F_AMS_PROF_CONFIGURE_CMD_AMS_TYPE_OFFSET 4
#define RVR_F_AMS_PROF_CONFIGURE_CMD_AMS_TYPE_SHIFT 23
#define RVR_F_AMS_PROF_CONFIGURE_CMD_AMS_TYPE_MASK 0x1
#define RVR_F_AMS_PROF_CONFIGURE_CMD_PROF_MASK_OFFSET 8
#define RVR_F_AMS_PROF_CONFIGURE_CMD_PROF_MASK_SHIFT 0
#define RVR_F_AMS_PROF_CONFIGURE_CMD_PROF_MASK_MASK 0xffffffffffffffff
#define RVR_F_AMS_PROF_CONFIGURE_CMD_PROF_TBL_BASE_OFFSET 16
#define RVR_F_AMS_PROF_CONFIGURE_CMD_PROF_TBL_BASE_SHIFT 0
#define RVR_F_AMS_PROF_CONFIGURE_CMD_PROF_TBL_BASE_MASK 0xffffffffffffffff
#define RVR_F_AMS_PROF_CONFIGURE_CMD_PROF_CTL_OFFSET 24
#define RVR_F_AMS_PROF_CONFIGURE_CMD_PROF_CTL_SHIFT 0
#define RVR_F_AMS_PROF_CONFIGURE_CMD_PROF_CTL_MASK 0xffff

struct rvr_f_ams_prof_configure_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_id:16;
	u64 ami_type:1;
	u64 ams_id:6;
	u64 ams_type:1;
	u64 _reserved_2:8;
	u64 prof_mask:64;
	u64 prof_tbl_base:64;
	u64 prof_ctl:16;
	u64 _reserved_3:16;
} __packed;

/*
 * F-AMS-PROF-CONFIGURE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMS configured successfully
 *	1: AMI is not mapped in Function
 *	2: AMI is not disabled
 *	3: Function is not the monitoring owner
 */

#define RVR_F_AMS_PROF_CONFIGURE_RESP_OPCODE_OFFSET 0
#define RVR_F_AMS_PROF_CONFIGURE_RESP_OPCODE_SHIFT 0
#define RVR_F_AMS_PROF_CONFIGURE_RESP_OPCODE_MASK 0xffff
#define RVR_F_AMS_PROF_CONFIGURE_RESP_STATUS_OFFSET 0
#define RVR_F_AMS_PROF_CONFIGURE_RESP_STATUS_SHIFT 16
#define RVR_F_AMS_PROF_CONFIGURE_RESP_STATUS_MASK 0xffff

struct rvr_f_ams_prof_configure_resp {
	u64 opcode:16;
	u64 status:16;
} __packed;

/**********************************************************************
 *			F-AMS-RING-CONFIGURE (opcode 20)
 **********************************************************************/

/*
 * F-AMS-RING-CONFIGURE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_SW_ID (16b)
 *	AMI_SW within the Function to be configured
 * @0x8 [5:0] ([69:64]) AMS_ID (6b)
 *	AMS within AMI_SW to be configured
 * @0x8 [6:6] ([70:70]) AMS_TYPE (1b)
 *	0: RX AMS
 *	1: TX AMS
 * @0xc [1:1] ([97:97]) RX_MODE (1b)
 *	0: Back-pressure
 *	1: Overwriting
 * @0xc [5:2] ([101:98]) LOG2_SIZE (4b)
 *	Size of the ring in slots as log~2~(SIZE)
 * @0xc [9:6] ([105:102]) THRESHOLD (4b)
 *	Controls the change of DIGEST bits
 * @0x10 [63:0] ([191:128]) BASE_PTR (64b)
 *	64-bit virtual address of the slot array
 */

#define RVR_F_AMS_RING_CONFIGURE_CMD_OPCODE_OFFSET 0
#define RVR_F_AMS_RING_CONFIGURE_CMD_OPCODE_SHIFT 0
#define RVR_F_AMS_RING_CONFIGURE_CMD_OPCODE_MASK 0xffff
#define RVR_F_AMS_RING_CONFIGURE_CMD_AMI_SW_ID_OFFSET 4
#define RVR_F_AMS_RING_CONFIGURE_CMD_AMI_SW_ID_SHIFT 0
#define RVR_F_AMS_RING_CONFIGURE_CMD_AMI_SW_ID_MASK 0xffff
#define RVR_F_AMS_RING_CONFIGURE_CMD_AMS_ID_OFFSET 8
#define RVR_F_AMS_RING_CONFIGURE_CMD_AMS_ID_SHIFT 0
#define RVR_F_AMS_RING_CONFIGURE_CMD_AMS_ID_MASK 0x3f
#define RVR_F_AMS_RING_CONFIGURE_CMD_AMS_TYPE_OFFSET 8
#define RVR_F_AMS_RING_CONFIGURE_CMD_AMS_TYPE_SHIFT 6
#define RVR_F_AMS_RING_CONFIGURE_CMD_AMS_TYPE_MASK 0x1
#define RVR_F_AMS_RING_CONFIGURE_CMD_RX_MODE_OFFSET 12
#define RVR_F_AMS_RING_CONFIGURE_CMD_RX_MODE_SHIFT 1
#define RVR_F_AMS_RING_CONFIGURE_CMD_RX_MODE_MASK 0x1
#define RVR_F_AMS_RING_CONFIGURE_CMD_LOG2_SIZE_OFFSET 12
#define RVR_F_AMS_RING_CONFIGURE_CMD_LOG2_SIZE_SHIFT 2
#define RVR_F_AMS_RING_CONFIGURE_CMD_LOG2_SIZE_MASK 0xf
#define RVR_F_AMS_RING_CONFIGURE_CMD_THRESHOLD_OFFSET 12
#define RVR_F_AMS_RING_CONFIGURE_CMD_THRESHOLD_SHIFT 6
#define RVR_F_AMS_RING_CONFIGURE_CMD_THRESHOLD_MASK 0xf
#define RVR_F_AMS_RING_CONFIGURE_CMD_BASE_PTR_OFFSET 16
#define RVR_F_AMS_RING_CONFIGURE_CMD_BASE_PTR_SHIFT 0
#define RVR_F_AMS_RING_CONFIGURE_CMD_BASE_PTR_MASK 0xffffffffffffffff

struct rvr_f_ams_ring_configure_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_sw_id:16;
	u64 _reserved_2:16;
	u64 ams_id:6;
	u64 ams_type:1;
	u64 _reserved_3:25;
	u64 _reserved_4:1;
	u64 rx_mode:1;
	u64 log2_size:4;
	u64 threshold:4;
	u64 _reserved_5:22;
	u64 base_ptr:64;
} __packed;

/*
 * F-AMS-RING-CONFIGURE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMS ring configured successfully
 *	1: AMI-SW is not mapped in Function
 *	2: AMI-SW is not disabled
 */

#define RVR_F_AMS_RING_CONFIGURE_RESP_OPCODE_OFFSET 0
#define RVR_F_AMS_RING_CONFIGURE_RESP_OPCODE_SHIFT 0
#define RVR_F_AMS_RING_CONFIGURE_RESP_OPCODE_MASK 0xffff
#define RVR_F_AMS_RING_CONFIGURE_RESP_STATUS_OFFSET 0
#define RVR_F_AMS_RING_CONFIGURE_RESP_STATUS_SHIFT 16
#define RVR_F_AMS_RING_CONFIGURE_RESP_STATUS_MASK 0xffff

struct rvr_f_ams_ring_configure_resp {
	u64 opcode:16;
	u64 status:16;
} __packed;

/**********************************************************************
 *			F-AMS-RING-SAVE (opcode 21)
 **********************************************************************/

/*
 * F-AMS-RING-SAVE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_SW_ID (16b)
 *	AMI_SW within the Function to be saved
 * @0x4 [21:16] ([53:48]) AMS_ID (6b)
 *	AMS within AMI_SW to be saved
 * @0x4 [22:22] ([54:54]) AMS_TYPE (1b)
 *	0: RX AMS
 *	1: TX AMS
 */

#define RVR_F_AMS_RING_SAVE_CMD_OPCODE_OFFSET 0
#define RVR_F_AMS_RING_SAVE_CMD_OPCODE_SHIFT 0
#define RVR_F_AMS_RING_SAVE_CMD_OPCODE_MASK 0xffff
#define RVR_F_AMS_RING_SAVE_CMD_AMI_SW_ID_OFFSET 4
#define RVR_F_AMS_RING_SAVE_CMD_AMI_SW_ID_SHIFT 0
#define RVR_F_AMS_RING_SAVE_CMD_AMI_SW_ID_MASK 0xffff
#define RVR_F_AMS_RING_SAVE_CMD_AMS_ID_OFFSET 4
#define RVR_F_AMS_RING_SAVE_CMD_AMS_ID_SHIFT 16
#define RVR_F_AMS_RING_SAVE_CMD_AMS_ID_MASK 0x3f
#define RVR_F_AMS_RING_SAVE_CMD_AMS_TYPE_OFFSET 4
#define RVR_F_AMS_RING_SAVE_CMD_AMS_TYPE_SHIFT 22
#define RVR_F_AMS_RING_SAVE_CMD_AMS_TYPE_MASK 0x1

struct rvr_f_ams_ring_save_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_sw_id:16;
	u64 ams_id:6;
	u64 ams_type:1;
	u64 _reserved_2:9;
} __packed;

/*
 * F-AMS-RING-SAVE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMS ring saved successfully
 *	1: AMI-SW is not mapped in the Function
 *	2: AMI-SW is not disabled
 * @0x4 [1:1] ([33:33]) RX_MODE (1b)
 *	0: Back-pressure
 *	1: Overwriting
 * @0x4 [5:2] ([37:34]) LOG2_SIZE (4b)
 *	Size of the ring in slots as log~2~(SIZE)
 * @0x4 [9:6] ([41:38]) THRESHOLD (4b)
 *	Controls the change of DIGEST bits
 * @0x8 [63:0] ([127:64]) BASE_PTR (64b)
 *	64-bit virtual address of the slot array
 */

#define RVR_F_AMS_RING_SAVE_RESP_OPCODE_OFFSET 0
#define RVR_F_AMS_RING_SAVE_RESP_OPCODE_SHIFT 0
#define RVR_F_AMS_RING_SAVE_RESP_OPCODE_MASK 0xffff
#define RVR_F_AMS_RING_SAVE_RESP_STATUS_OFFSET 0
#define RVR_F_AMS_RING_SAVE_RESP_STATUS_SHIFT 16
#define RVR_F_AMS_RING_SAVE_RESP_STATUS_MASK 0xffff
#define RVR_F_AMS_RING_SAVE_RESP_RX_MODE_OFFSET 4
#define RVR_F_AMS_RING_SAVE_RESP_RX_MODE_SHIFT 1
#define RVR_F_AMS_RING_SAVE_RESP_RX_MODE_MASK 0x1
#define RVR_F_AMS_RING_SAVE_RESP_LOG2_SIZE_OFFSET 4
#define RVR_F_AMS_RING_SAVE_RESP_LOG2_SIZE_SHIFT 2
#define RVR_F_AMS_RING_SAVE_RESP_LOG2_SIZE_MASK 0xf
#define RVR_F_AMS_RING_SAVE_RESP_THRESHOLD_OFFSET 4
#define RVR_F_AMS_RING_SAVE_RESP_THRESHOLD_SHIFT 6
#define RVR_F_AMS_RING_SAVE_RESP_THRESHOLD_MASK 0xf
#define RVR_F_AMS_RING_SAVE_RESP_BASE_PTR_OFFSET 8
#define RVR_F_AMS_RING_SAVE_RESP_BASE_PTR_SHIFT 0
#define RVR_F_AMS_RING_SAVE_RESP_BASE_PTR_MASK 0xffffffffffffffff

struct rvr_f_ams_ring_save_resp {
	u64 opcode:16;
	u64 status:16;
	u64 _reserved_:1;
	u64 rx_mode:1;
	u64 log2_size:4;
	u64 threshold:4;
	u64 _reserved_2:22;
	u64 base_ptr:64;
} __packed;

/**********************************************************************
 *			F-AMS-TRACE-CONFIGURE (opcode 36)
 **********************************************************************/

/*
 * F-AMS-TRACE-CONFIGURE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_ID (16b)
 *	AMI within F_OWNER to be configured
 * @0x4 [16:16] ([48:48]) AMI_TYPE (1b)
 *	0: AMI-SW
 *	1: AMI-HW
 * @0x4 [22:17] ([54:49]) AMS_ID (6b)
 *	AMS within AMI to be configured
 * @0x4 [23:23] ([55:55]) AMS_TYPE (1b)
 *	0: RX AMS
 *	1: TX AMS
 * @0x8 [15:0] ([79:64]) TRACE_CTL (16b)
 *	Tracing controls configured in the associated ASN
 */

#define RVR_F_AMS_TRACE_CONFIGURE_CMD_OPCODE_OFFSET 0
#define RVR_F_AMS_TRACE_CONFIGURE_CMD_OPCODE_SHIFT 0
#define RVR_F_AMS_TRACE_CONFIGURE_CMD_OPCODE_MASK 0xffff
#define RVR_F_AMS_TRACE_CONFIGURE_CMD_AMI_ID_OFFSET 4
#define RVR_F_AMS_TRACE_CONFIGURE_CMD_AMI_ID_SHIFT 0
#define RVR_F_AMS_TRACE_CONFIGURE_CMD_AMI_ID_MASK 0xffff
#define RVR_F_AMS_TRACE_CONFIGURE_CMD_AMI_TYPE_OFFSET 4
#define RVR_F_AMS_TRACE_CONFIGURE_CMD_AMI_TYPE_SHIFT 16
#define RVR_F_AMS_TRACE_CONFIGURE_CMD_AMI_TYPE_MASK 0x1
#define RVR_F_AMS_TRACE_CONFIGURE_CMD_AMS_ID_OFFSET 4
#define RVR_F_AMS_TRACE_CONFIGURE_CMD_AMS_ID_SHIFT 17
#define RVR_F_AMS_TRACE_CONFIGURE_CMD_AMS_ID_MASK 0x3f
#define RVR_F_AMS_TRACE_CONFIGURE_CMD_AMS_TYPE_OFFSET 4
#define RVR_F_AMS_TRACE_CONFIGURE_CMD_AMS_TYPE_SHIFT 23
#define RVR_F_AMS_TRACE_CONFIGURE_CMD_AMS_TYPE_MASK 0x1
#define RVR_F_AMS_TRACE_CONFIGURE_CMD_TRACE_CTL_OFFSET 8
#define RVR_F_AMS_TRACE_CONFIGURE_CMD_TRACE_CTL_SHIFT 0
#define RVR_F_AMS_TRACE_CONFIGURE_CMD_TRACE_CTL_MASK 0xffff

struct rvr_f_ams_trace_configure_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_id:16;
	u64 ami_type:1;
	u64 ams_id:6;
	u64 ams_type:1;
	u64 _reserved_2:8;
	u64 trace_ctl:16;
	u64 _reserved_3:16;
} __packed;

/*
 * F-AMS-TRACE-CONFIGURE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMS configured successfully
 *	1: AMI is not mapped in Function
 *	2: AMI is not disabled
 *	3: Function is not the monitoring owner
 */

#define RVR_F_AMS_TRACE_CONFIGURE_RESP_OPCODE_OFFSET 0
#define RVR_F_AMS_TRACE_CONFIGURE_RESP_OPCODE_SHIFT 0
#define RVR_F_AMS_TRACE_CONFIGURE_RESP_OPCODE_MASK 0xffff
#define RVR_F_AMS_TRACE_CONFIGURE_RESP_STATUS_OFFSET 0
#define RVR_F_AMS_TRACE_CONFIGURE_RESP_STATUS_SHIFT 16
#define RVR_F_AMS_TRACE_CONFIGURE_RESP_STATUS_MASK 0xffff

struct rvr_f_ams_trace_configure_resp {
	u64 opcode:16;
	u64 status:16;
} __packed;

/**********************************************************************
 *			F-PROBE (opcode 2)
 **********************************************************************/

/*
 * F-PROBE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 */

#define RVR_F_PROBE_CMD_OPCODE_OFFSET 0
#define RVR_F_PROBE_CMD_OPCODE_SHIFT 0
#define RVR_F_PROBE_CMD_OPCODE_MASK 0xffff

struct rvr_f_probe_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
} __packed;

/*
 * F-PROBE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [31:0] ([63:32]) ASN_PROF_N_COUNTERS (32b)
 *	Number of ASN profiling counters implemented
 * @0x8 [15:0] ([79:64]) AMI_PER_F_M1 (16b)
 *	Maximum number (minus one) of AMI supported per Function
 *	AMI_PER_F = (AMI_PER_F_M1 + 1)
 * @0x8 [20:16] ([84:80]) PASID_WIDTH (5b)
 *	PASID width supported by the implementation
 * @0x8 [21:21] ([85:85]) PASID_SUPPORTED (1b)
 *	PASID is supported by the implementation
 */

#define RVR_F_PROBE_RESP_OPCODE_OFFSET 0
#define RVR_F_PROBE_RESP_OPCODE_SHIFT 0
#define RVR_F_PROBE_RESP_OPCODE_MASK 0xffff
#define RVR_F_PROBE_RESP_ASN_PROF_N_COUNTERS_OFFSET 4
#define RVR_F_PROBE_RESP_ASN_PROF_N_COUNTERS_SHIFT 0
#define RVR_F_PROBE_RESP_ASN_PROF_N_COUNTERS_MASK 0xffffffff
#define RVR_F_PROBE_RESP_AMI_PER_F_M1_OFFSET 8
#define RVR_F_PROBE_RESP_AMI_PER_F_M1_SHIFT 0
#define RVR_F_PROBE_RESP_AMI_PER_F_M1_MASK 0xffff
#define RVR_F_PROBE_RESP_PASID_WIDTH_OFFSET 8
#define RVR_F_PROBE_RESP_PASID_WIDTH_SHIFT 16
#define RVR_F_PROBE_RESP_PASID_WIDTH_MASK 0x1f
#define RVR_F_PROBE_RESP_PASID_SUPPORTED_OFFSET 8
#define RVR_F_PROBE_RESP_PASID_SUPPORTED_SHIFT 21
#define RVR_F_PROBE_RESP_PASID_SUPPORTED_MASK 0x1

struct rvr_f_probe_resp {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 asn_prof_n_counters:32;
	u64 ami_per_f_m1:16;
	u64 pasid_width:5;
	u64 pasid_supported:1;
	u64 _reserved_2:10;
} __packed;

/**********************************************************************
 *			F-PROF-TABLE-FLUSH (opcode 29)
 **********************************************************************/

/*
 * F-PROF-TABLE-FLUSH command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 */

#define RVR_F_PROF_TABLE_FLUSH_CMD_OPCODE_OFFSET 0
#define RVR_F_PROF_TABLE_FLUSH_CMD_OPCODE_SHIFT 0
#define RVR_F_PROF_TABLE_FLUSH_CMD_OPCODE_MASK 0xffff

struct rvr_f_prof_table_flush_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
} __packed;

/*
 * F-PROF-TABLE-FLUSH response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 */

#define RVR_F_PROF_TABLE_FLUSH_RESP_OPCODE_OFFSET 0
#define RVR_F_PROF_TABLE_FLUSH_RESP_OPCODE_SHIFT 0
#define RVR_F_PROF_TABLE_FLUSH_RESP_OPCODE_MASK 0xffff

struct rvr_f_prof_table_flush_resp {
	u64 opcode:16;
	u64 _reserved_:16;
} __packed;

/**********************************************************************
 *			F-TYPEB-TABLE-CONFIGURE (opcode 5)
 **********************************************************************/

/*
 * F-TYPEB-TABLE-CONFIGURE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [31:0] ([63:32]) TYPEB_TBL_SIZE (32b)
 *	Size of the table in bytes
 * @0x8 [63:0] ([127:64]) TYPEB_TBL_BASE (64b)
 *	64-bit virtual address of the table
 */

#define RVR_F_TYPEB_TABLE_CONFIGURE_CMD_OPCODE_OFFSET 0
#define RVR_F_TYPEB_TABLE_CONFIGURE_CMD_OPCODE_SHIFT 0
#define RVR_F_TYPEB_TABLE_CONFIGURE_CMD_OPCODE_MASK 0xffff
#define RVR_F_TYPEB_TABLE_CONFIGURE_CMD_TYPEB_TBL_SIZE_OFFSET 4
#define RVR_F_TYPEB_TABLE_CONFIGURE_CMD_TYPEB_TBL_SIZE_SHIFT 0
#define RVR_F_TYPEB_TABLE_CONFIGURE_CMD_TYPEB_TBL_SIZE_MASK 0xffffffff
#define RVR_F_TYPEB_TABLE_CONFIGURE_CMD_TYPEB_TBL_BASE_OFFSET 8
#define RVR_F_TYPEB_TABLE_CONFIGURE_CMD_TYPEB_TBL_BASE_SHIFT 0
#define RVR_F_TYPEB_TABLE_CONFIGURE_CMD_TYPEB_TBL_BASE_MASK 0xffffffffffffffff

struct rvr_f_typeb_table_configure_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 typeb_tbl_size:32;
	u64 typeb_tbl_base:64;
} __packed;

/*
 * F-TYPEB-TABLE-CONFIGURE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 */

#define RVR_F_TYPEB_TABLE_CONFIGURE_RESP_OPCODE_OFFSET 0
#define RVR_F_TYPEB_TABLE_CONFIGURE_RESP_OPCODE_SHIFT 0
#define RVR_F_TYPEB_TABLE_CONFIGURE_RESP_OPCODE_MASK 0xffff

struct rvr_f_typeb_table_configure_resp {
	u64 opcode:16;
	u64 _reserved_:16;
} __packed;

/**********************************************************************
 *			PF-AMI-HW-CONFIGURE (opcode 25)
 **********************************************************************/

/*
 * PF-AMI-HW-CONFIGURE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_HW_ID (16b)
 *	AMI-HW within F_OWNER to be configured
 * @0x4 [31:16] ([63:48]) F_OWNER (16b)
 *	Function that owns the AMI-HW to be configured
 * @0x8 [19:0] ([83:64]) PASID (20b)
 *	PASID value
 * @0x8 [20:20] ([84:84]) PASID_ENABLED (1b)
 *	1: Enable PASID
 *	0: Disable PASID
 * @0x8 [31:21] ([95:85]) HW_CRED_SIZE (11b)
 *	Credit size to use for this AMI-HW
 * @0xc [0:0] ([96:96]) ENABLE (1b)
 *	1: Enable AMI-HW
 *	0: Disable AMI-HW
 */

#define RVR_PF_AMI_HW_CONFIGURE_CMD_OPCODE_OFFSET 0
#define RVR_PF_AMI_HW_CONFIGURE_CMD_OPCODE_SHIFT 0
#define RVR_PF_AMI_HW_CONFIGURE_CMD_OPCODE_MASK 0xffff
#define RVR_PF_AMI_HW_CONFIGURE_CMD_AMI_HW_ID_OFFSET 4
#define RVR_PF_AMI_HW_CONFIGURE_CMD_AMI_HW_ID_SHIFT 0
#define RVR_PF_AMI_HW_CONFIGURE_CMD_AMI_HW_ID_MASK 0xffff
#define RVR_PF_AMI_HW_CONFIGURE_CMD_F_OWNER_OFFSET 4
#define RVR_PF_AMI_HW_CONFIGURE_CMD_F_OWNER_SHIFT 16
#define RVR_PF_AMI_HW_CONFIGURE_CMD_F_OWNER_MASK 0xffff
#define RVR_PF_AMI_HW_CONFIGURE_CMD_PASID_OFFSET 8
#define RVR_PF_AMI_HW_CONFIGURE_CMD_PASID_SHIFT 0
#define RVR_PF_AMI_HW_CONFIGURE_CMD_PASID_MASK 0xfffff
#define RVR_PF_AMI_HW_CONFIGURE_CMD_PASID_ENABLED_OFFSET 8
#define RVR_PF_AMI_HW_CONFIGURE_CMD_PASID_ENABLED_SHIFT 20
#define RVR_PF_AMI_HW_CONFIGURE_CMD_PASID_ENABLED_MASK 0x1
#define RVR_PF_AMI_HW_CONFIGURE_CMD_HW_CRED_SIZE_OFFSET 8
#define RVR_PF_AMI_HW_CONFIGURE_CMD_HW_CRED_SIZE_SHIFT 21
#define RVR_PF_AMI_HW_CONFIGURE_CMD_HW_CRED_SIZE_MASK 0x7ff
#define RVR_PF_AMI_HW_CONFIGURE_CMD_ENABLE_OFFSET 12
#define RVR_PF_AMI_HW_CONFIGURE_CMD_ENABLE_SHIFT 0
#define RVR_PF_AMI_HW_CONFIGURE_CMD_ENABLE_MASK 0x1

struct rvr_pf_ami_hw_configure_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_hw_id:16;
	u64 f_owner:16;
	u64 pasid:20;
	u64 pasid_enabled:1;
	u64 hw_cred_size:11;
	u64 enable:1;
	u64 _reserved_2:31;
} __packed;

/*
 * PF-AMI-HW-CONFIGURE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMI-HW configured successfully
 *	1: AMI-HW is not mapped in F_OWNER
 *	2: AMI-HW is not disabled
 */

#define RVR_PF_AMI_HW_CONFIGURE_RESP_OPCODE_OFFSET 0
#define RVR_PF_AMI_HW_CONFIGURE_RESP_OPCODE_SHIFT 0
#define RVR_PF_AMI_HW_CONFIGURE_RESP_OPCODE_MASK 0xffff
#define RVR_PF_AMI_HW_CONFIGURE_RESP_STATUS_OFFSET 0
#define RVR_PF_AMI_HW_CONFIGURE_RESP_STATUS_SHIFT 16
#define RVR_PF_AMI_HW_CONFIGURE_RESP_STATUS_MASK 0xffff

struct rvr_pf_ami_hw_configure_resp {
	u64 opcode:16;
	u64 status:16;
} __packed;

/**********************************************************************
 *			PF-AMI-HW-MAP (opcode 23)
 **********************************************************************/

/*
 * PF-AMI-HW-MAP command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) PHY_AMI_HW_ID (16b)
 *	Physical AMI-HW within AHA_ID to be mapped
 * @0x4 [31:16] ([63:48]) AHA_ID (16b)
 *	ID of the AHA that contains the physical AMI-HW
 * @0x8 [15:0] ([79:64]) AMI_HW_ID (16b)
 *	ID to assign to the AMI-HW within F_OWNER
 * @0x8 [31:16] ([95:80]) F_OWNER (16b)
 *	Function to map the AMI-HW to
 */

#define RVR_PF_AMI_HW_MAP_CMD_OPCODE_OFFSET 0
#define RVR_PF_AMI_HW_MAP_CMD_OPCODE_SHIFT 0
#define RVR_PF_AMI_HW_MAP_CMD_OPCODE_MASK 0xffff
#define RVR_PF_AMI_HW_MAP_CMD_PHY_AMI_HW_ID_OFFSET 4
#define RVR_PF_AMI_HW_MAP_CMD_PHY_AMI_HW_ID_SHIFT 0
#define RVR_PF_AMI_HW_MAP_CMD_PHY_AMI_HW_ID_MASK 0xffff
#define RVR_PF_AMI_HW_MAP_CMD_AHA_ID_OFFSET 4
#define RVR_PF_AMI_HW_MAP_CMD_AHA_ID_SHIFT 16
#define RVR_PF_AMI_HW_MAP_CMD_AHA_ID_MASK 0xffff
#define RVR_PF_AMI_HW_MAP_CMD_AMI_HW_ID_OFFSET 8
#define RVR_PF_AMI_HW_MAP_CMD_AMI_HW_ID_SHIFT 0
#define RVR_PF_AMI_HW_MAP_CMD_AMI_HW_ID_MASK 0xffff
#define RVR_PF_AMI_HW_MAP_CMD_F_OWNER_OFFSET 8
#define RVR_PF_AMI_HW_MAP_CMD_F_OWNER_SHIFT 16
#define RVR_PF_AMI_HW_MAP_CMD_F_OWNER_MASK 0xffff

struct rvr_pf_ami_hw_map_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 phy_ami_hw_id:16;
	u64 aha_id:16;
	u64 ami_hw_id:16;
	u64 f_owner:16;
} __packed;

/*
 * PF-AMI-HW-MAP response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMI-HW mapped successfully
 *	1: AMI-HW already mapped
 */

#define RVR_PF_AMI_HW_MAP_RESP_OPCODE_OFFSET 0
#define RVR_PF_AMI_HW_MAP_RESP_OPCODE_SHIFT 0
#define RVR_PF_AMI_HW_MAP_RESP_OPCODE_MASK 0xffff
#define RVR_PF_AMI_HW_MAP_RESP_STATUS_OFFSET 0
#define RVR_PF_AMI_HW_MAP_RESP_STATUS_SHIFT 16
#define RVR_PF_AMI_HW_MAP_RESP_STATUS_MASK 0xffff

struct rvr_pf_ami_hw_map_resp {
	u64 opcode:16;
	u64 status:16;
} __packed;

/**********************************************************************
 *			PF-AMI-HW-RESET (opcode 27)
 **********************************************************************/

/*
 * PF-AMI-HW-RESET command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_HW_ID (16b)
 *	AMI-HW within F_OWNER to be reset
 * @0x4 [31:16] ([63:48]) F_OWNER (16b)
 *	Function that owns the AMI-HW to be reset
 */

#define RVR_PF_AMI_HW_RESET_CMD_OPCODE_OFFSET 0
#define RVR_PF_AMI_HW_RESET_CMD_OPCODE_SHIFT 0
#define RVR_PF_AMI_HW_RESET_CMD_OPCODE_MASK 0xffff
#define RVR_PF_AMI_HW_RESET_CMD_AMI_HW_ID_OFFSET 4
#define RVR_PF_AMI_HW_RESET_CMD_AMI_HW_ID_SHIFT 0
#define RVR_PF_AMI_HW_RESET_CMD_AMI_HW_ID_MASK 0xffff
#define RVR_PF_AMI_HW_RESET_CMD_F_OWNER_OFFSET 4
#define RVR_PF_AMI_HW_RESET_CMD_F_OWNER_SHIFT 16
#define RVR_PF_AMI_HW_RESET_CMD_F_OWNER_MASK 0xffff

struct rvr_pf_ami_hw_reset_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_hw_id:16;
	u64 f_owner:16;
} __packed;

/*
 * PF-AMI-HW-RESET response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMI-HW configured successfully
 *	1: AMI-HW is not mapped in F_OWNER
 *	2: AMI-HW is not disabled
 */

#define RVR_PF_AMI_HW_RESET_RESP_OPCODE_OFFSET 0
#define RVR_PF_AMI_HW_RESET_RESP_OPCODE_SHIFT 0
#define RVR_PF_AMI_HW_RESET_RESP_OPCODE_MASK 0xffff
#define RVR_PF_AMI_HW_RESET_RESP_STATUS_OFFSET 0
#define RVR_PF_AMI_HW_RESET_RESP_STATUS_SHIFT 16
#define RVR_PF_AMI_HW_RESET_RESP_STATUS_MASK 0xffff

struct rvr_pf_ami_hw_reset_resp {
	u64 opcode:16;
	u64 status:16;
} __packed;

/**********************************************************************
 *			PF-AMI-HW-SAVE (opcode 26)
 **********************************************************************/

/*
 * PF-AMI-HW-SAVE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_HW_ID (16b)
 *	AMI-HW within F_OWNER to be saved
 * @0x4 [31:16] ([63:48]) F_OWNER (16b)
 *	Function that owns the AMI-HW to be saved
 */

#define RVR_PF_AMI_HW_SAVE_CMD_OPCODE_OFFSET 0
#define RVR_PF_AMI_HW_SAVE_CMD_OPCODE_SHIFT 0
#define RVR_PF_AMI_HW_SAVE_CMD_OPCODE_MASK 0xffff
#define RVR_PF_AMI_HW_SAVE_CMD_AMI_HW_ID_OFFSET 4
#define RVR_PF_AMI_HW_SAVE_CMD_AMI_HW_ID_SHIFT 0
#define RVR_PF_AMI_HW_SAVE_CMD_AMI_HW_ID_MASK 0xffff
#define RVR_PF_AMI_HW_SAVE_CMD_F_OWNER_OFFSET 4
#define RVR_PF_AMI_HW_SAVE_CMD_F_OWNER_SHIFT 16
#define RVR_PF_AMI_HW_SAVE_CMD_F_OWNER_MASK 0xffff

struct rvr_pf_ami_hw_save_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_hw_id:16;
	u64 f_owner:16;
} __packed;

/*
 * PF-AMI-HW-SAVE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMI-HW saved successfully
 *	1: AMI-HW is not mapped in F_OWNER
 *	2: AMI-HW is not disabled
 * @0x4 [19:0] ([51:32]) PASID (20b)
 *	PASID value
 * @0x4 [20:20] ([52:52]) PASID_ENABLED (1b)
 *	1: PASID is enabled
 *	0: PASID is disabled
 * @0x4 [31:21] ([63:53]) HW_CRED_SIZE (11b)
 *	Credit size being used for this AMI-HW
 * @0x8 [0:0] ([64:64]) ENABLE (1b)
 *	1: AMI-HW is enabled
 *	0: AMI-HW is enabled
 */

#define RVR_PF_AMI_HW_SAVE_RESP_OPCODE_OFFSET 0
#define RVR_PF_AMI_HW_SAVE_RESP_OPCODE_SHIFT 0
#define RVR_PF_AMI_HW_SAVE_RESP_OPCODE_MASK 0xffff
#define RVR_PF_AMI_HW_SAVE_RESP_STATUS_OFFSET 0
#define RVR_PF_AMI_HW_SAVE_RESP_STATUS_SHIFT 16
#define RVR_PF_AMI_HW_SAVE_RESP_STATUS_MASK 0xffff
#define RVR_PF_AMI_HW_SAVE_RESP_PASID_OFFSET 4
#define RVR_PF_AMI_HW_SAVE_RESP_PASID_SHIFT 0
#define RVR_PF_AMI_HW_SAVE_RESP_PASID_MASK 0xfffff
#define RVR_PF_AMI_HW_SAVE_RESP_PASID_ENABLED_OFFSET 4
#define RVR_PF_AMI_HW_SAVE_RESP_PASID_ENABLED_SHIFT 20
#define RVR_PF_AMI_HW_SAVE_RESP_PASID_ENABLED_MASK 0x1
#define RVR_PF_AMI_HW_SAVE_RESP_HW_CRED_SIZE_OFFSET 4
#define RVR_PF_AMI_HW_SAVE_RESP_HW_CRED_SIZE_SHIFT 21
#define RVR_PF_AMI_HW_SAVE_RESP_HW_CRED_SIZE_MASK 0x7ff
#define RVR_PF_AMI_HW_SAVE_RESP_ENABLE_OFFSET 8
#define RVR_PF_AMI_HW_SAVE_RESP_ENABLE_SHIFT 0
#define RVR_PF_AMI_HW_SAVE_RESP_ENABLE_MASK 0x1

struct rvr_pf_ami_hw_save_resp {
	u64 opcode:16;
	u64 status:16;
	u64 pasid:20;
	u64 pasid_enabled:1;
	u64 hw_cred_size:11;
	u64 enable:1;
	u64 _reserved_:31;
} __packed;

/**********************************************************************
 *			PF-AMI-HW-UNMAP (opcode 24)
 **********************************************************************/

/*
 * PF-AMI-HW-UNMAP command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_HW_ID (16b)
 *	AMI-HW within F_OWNER to be unmapped
 * @0x4 [31:16] ([63:48]) F_OWNER (16b)
 *	Function to unmap the AMI-HW from
 */

#define RVR_PF_AMI_HW_UNMAP_CMD_OPCODE_OFFSET 0
#define RVR_PF_AMI_HW_UNMAP_CMD_OPCODE_SHIFT 0
#define RVR_PF_AMI_HW_UNMAP_CMD_OPCODE_MASK 0xffff
#define RVR_PF_AMI_HW_UNMAP_CMD_AMI_HW_ID_OFFSET 4
#define RVR_PF_AMI_HW_UNMAP_CMD_AMI_HW_ID_SHIFT 0
#define RVR_PF_AMI_HW_UNMAP_CMD_AMI_HW_ID_MASK 0xffff
#define RVR_PF_AMI_HW_UNMAP_CMD_F_OWNER_OFFSET 4
#define RVR_PF_AMI_HW_UNMAP_CMD_F_OWNER_SHIFT 16
#define RVR_PF_AMI_HW_UNMAP_CMD_F_OWNER_MASK 0xffff

struct rvr_pf_ami_hw_unmap_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_hw_id:16;
	u64 f_owner:16;
} __packed;

/*
 * PF-AMI-HW-UNMAP response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 */

#define RVR_PF_AMI_HW_UNMAP_RESP_OPCODE_OFFSET 0
#define RVR_PF_AMI_HW_UNMAP_RESP_OPCODE_SHIFT 0
#define RVR_PF_AMI_HW_UNMAP_RESP_OPCODE_MASK 0xffff

struct rvr_pf_ami_hw_unmap_resp {
	u64 opcode:16;
	u64 _reserved_:16;
} __packed;

/**********************************************************************
 *			PF-AMI-SW-CONFIGURE (opcode 8)
 **********************************************************************/

/*
 * PF-AMI-SW-CONFIGURE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_SW_ID (16b)
 *	AMI-SW within F_OWNER to be configured
 * @0x4 [31:16] ([63:48]) F_OWNER (16b)
 *	Function that owns the AMI-SW to be configured
 * @0x8 [19:0] ([83:64]) PASID (20b)
 *	PASID value
 * @0x8 [20:20] ([84:84]) PASID_ENABLED (1b)
 *	1: Enable PASID
 *	0: Disable PASID
 * @0xc [10:0] ([106:96]) TX_VECTOR (11b)
 *	Value to use for TX_VECTOR
 * @0xc [21:11] ([117:107]) RX_VECTOR (11b)
 *	Value to use for RX_VECTOR
 * @0xc [22:22] ([118:118]) TX_IRQ_ENABLE (1b)
 *	1: Enable TX Interrupt Generation
 *	0: Disable TX Interrupt Generation
 * @0xc [23:23] ([119:119]) RX_IRQ_ENABLE (1b)
 *	1: Enable RX Interrupt Generation
 *	0: Disable RX Interrupt Generation
 * @0x10 [0:0] ([128:128]) ENABLE (1b)
 *	1: Enable AMI-SW
 *	0: Disable AMI-SW
 */

#define RVR_PF_AMI_SW_CONFIGURE_CMD_OPCODE_OFFSET 0
#define RVR_PF_AMI_SW_CONFIGURE_CMD_OPCODE_SHIFT 0
#define RVR_PF_AMI_SW_CONFIGURE_CMD_OPCODE_MASK 0xffff
#define RVR_PF_AMI_SW_CONFIGURE_CMD_AMI_SW_ID_OFFSET 4
#define RVR_PF_AMI_SW_CONFIGURE_CMD_AMI_SW_ID_SHIFT 0
#define RVR_PF_AMI_SW_CONFIGURE_CMD_AMI_SW_ID_MASK 0xffff
#define RVR_PF_AMI_SW_CONFIGURE_CMD_F_OWNER_OFFSET 4
#define RVR_PF_AMI_SW_CONFIGURE_CMD_F_OWNER_SHIFT 16
#define RVR_PF_AMI_SW_CONFIGURE_CMD_F_OWNER_MASK 0xffff
#define RVR_PF_AMI_SW_CONFIGURE_CMD_PASID_OFFSET 8
#define RVR_PF_AMI_SW_CONFIGURE_CMD_PASID_SHIFT 0
#define RVR_PF_AMI_SW_CONFIGURE_CMD_PASID_MASK 0xfffff
#define RVR_PF_AMI_SW_CONFIGURE_CMD_PASID_ENABLED_OFFSET 8
#define RVR_PF_AMI_SW_CONFIGURE_CMD_PASID_ENABLED_SHIFT 20
#define RVR_PF_AMI_SW_CONFIGURE_CMD_PASID_ENABLED_MASK 0x1
#define RVR_PF_AMI_SW_CONFIGURE_CMD_TX_VECTOR_OFFSET 12
#define RVR_PF_AMI_SW_CONFIGURE_CMD_TX_VECTOR_SHIFT 0
#define RVR_PF_AMI_SW_CONFIGURE_CMD_TX_VECTOR_MASK 0x7ff
#define RVR_PF_AMI_SW_CONFIGURE_CMD_RX_VECTOR_OFFSET 12
#define RVR_PF_AMI_SW_CONFIGURE_CMD_RX_VECTOR_SHIFT 11
#define RVR_PF_AMI_SW_CONFIGURE_CMD_RX_VECTOR_MASK 0x7ff
#define RVR_PF_AMI_SW_CONFIGURE_CMD_TX_IRQ_ENABLE_OFFSET 12
#define RVR_PF_AMI_SW_CONFIGURE_CMD_TX_IRQ_ENABLE_SHIFT 22
#define RVR_PF_AMI_SW_CONFIGURE_CMD_TX_IRQ_ENABLE_MASK 0x1
#define RVR_PF_AMI_SW_CONFIGURE_CMD_RX_IRQ_ENABLE_OFFSET 12
#define RVR_PF_AMI_SW_CONFIGURE_CMD_RX_IRQ_ENABLE_SHIFT 23
#define RVR_PF_AMI_SW_CONFIGURE_CMD_RX_IRQ_ENABLE_MASK 0x1
#define RVR_PF_AMI_SW_CONFIGURE_CMD_ENABLE_OFFSET 16
#define RVR_PF_AMI_SW_CONFIGURE_CMD_ENABLE_SHIFT 0
#define RVR_PF_AMI_SW_CONFIGURE_CMD_ENABLE_MASK 0x1

struct rvr_pf_ami_sw_configure_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_sw_id:16;
	u64 f_owner:16;
	u64 pasid:20;
	u64 pasid_enabled:1;
	u64 _reserved_2:11;
	u64 tx_vector:11;
	u64 rx_vector:11;
	u64 tx_irq_enable:1;
	u64 rx_irq_enable:1;
	u64 _reserved_3:8;
	u64 enable:1;
	u64 _reserved_4:31;
} __packed;

/*
 * PF-AMI-SW-CONFIGURE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMI-SW configured successfully
 *	1: AMI-SW is not mapped in F_OWNER
 *	2: AMI-SW is not disabled
 */

#define RVR_PF_AMI_SW_CONFIGURE_RESP_OPCODE_OFFSET 0
#define RVR_PF_AMI_SW_CONFIGURE_RESP_OPCODE_SHIFT 0
#define RVR_PF_AMI_SW_CONFIGURE_RESP_OPCODE_MASK 0xffff
#define RVR_PF_AMI_SW_CONFIGURE_RESP_STATUS_OFFSET 0
#define RVR_PF_AMI_SW_CONFIGURE_RESP_STATUS_SHIFT 16
#define RVR_PF_AMI_SW_CONFIGURE_RESP_STATUS_MASK 0xffff

struct rvr_pf_ami_sw_configure_resp {
	u64 opcode:16;
	u64 status:16;
} __packed;

/**********************************************************************
 *			PF-AMI-SW-MAP (opcode 6)
 **********************************************************************/

/*
 * PF-AMI-SW-MAP command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) PHY_AMI_SW_ID (16b)
 *	Physical AMI-SW to be mapped
 * @0x4 [16:16] ([48:48]) ANY_PHY_AMI_SW (1b)
 *	1: Map any physical AMI-SW
 *	0: Map PHY_AMI_SW_ID
 * @0x8 [15:0] ([79:64]) AMI_SW_ID (16b)
 *	ID to assign to the AMI-SW within F_OWNER
 * @0x8 [31:16] ([95:80]) F_OWNER (16b)
 *	Function to map the AMI-SW to
 */

#define RVR_PF_AMI_SW_MAP_CMD_OPCODE_OFFSET 0
#define RVR_PF_AMI_SW_MAP_CMD_OPCODE_SHIFT 0
#define RVR_PF_AMI_SW_MAP_CMD_OPCODE_MASK 0xffff
#define RVR_PF_AMI_SW_MAP_CMD_PHY_AMI_SW_ID_OFFSET 4
#define RVR_PF_AMI_SW_MAP_CMD_PHY_AMI_SW_ID_SHIFT 0
#define RVR_PF_AMI_SW_MAP_CMD_PHY_AMI_SW_ID_MASK 0xffff
#define RVR_PF_AMI_SW_MAP_CMD_ANY_PHY_AMI_SW_OFFSET 4
#define RVR_PF_AMI_SW_MAP_CMD_ANY_PHY_AMI_SW_SHIFT 16
#define RVR_PF_AMI_SW_MAP_CMD_ANY_PHY_AMI_SW_MASK 0x1
#define RVR_PF_AMI_SW_MAP_CMD_AMI_SW_ID_OFFSET 8
#define RVR_PF_AMI_SW_MAP_CMD_AMI_SW_ID_SHIFT 0
#define RVR_PF_AMI_SW_MAP_CMD_AMI_SW_ID_MASK 0xffff
#define RVR_PF_AMI_SW_MAP_CMD_F_OWNER_OFFSET 8
#define RVR_PF_AMI_SW_MAP_CMD_F_OWNER_SHIFT 16
#define RVR_PF_AMI_SW_MAP_CMD_F_OWNER_MASK 0xffff

struct rvr_pf_ami_sw_map_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 phy_ami_sw_id:16;
	u64 any_phy_ami_sw:1;
	u64 _reserved_2:15;
	u64 ami_sw_id:16;
	u64 f_owner:16;
} __packed;

/*
 * PF-AMI-SW-MAP response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMI-SW mapped successfully
 *	1: AMI-SW already mapped
 *	2: Physical AMI-SW not available
 */

#define RVR_PF_AMI_SW_MAP_RESP_OPCODE_OFFSET 0
#define RVR_PF_AMI_SW_MAP_RESP_OPCODE_SHIFT 0
#define RVR_PF_AMI_SW_MAP_RESP_OPCODE_MASK 0xffff
#define RVR_PF_AMI_SW_MAP_RESP_STATUS_OFFSET 0
#define RVR_PF_AMI_SW_MAP_RESP_STATUS_SHIFT 16
#define RVR_PF_AMI_SW_MAP_RESP_STATUS_MASK 0xffff

struct rvr_pf_ami_sw_map_resp {
	u64 opcode:16;
	u64 status:16;
} __packed;

/**********************************************************************
 *			PF-AMI-SW-RESET (opcode 10)
 **********************************************************************/

/*
 * PF-AMI-SW-RESET command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_SW_ID (16b)
 *	AMI-SW within F_OWNER to be reset
 * @0x4 [31:16] ([63:48]) F_OWNER (16b)
 *	Function that owns the AMI-SW to be reset
 */

#define RVR_PF_AMI_SW_RESET_CMD_OPCODE_OFFSET 0
#define RVR_PF_AMI_SW_RESET_CMD_OPCODE_SHIFT 0
#define RVR_PF_AMI_SW_RESET_CMD_OPCODE_MASK 0xffff
#define RVR_PF_AMI_SW_RESET_CMD_AMI_SW_ID_OFFSET 4
#define RVR_PF_AMI_SW_RESET_CMD_AMI_SW_ID_SHIFT 0
#define RVR_PF_AMI_SW_RESET_CMD_AMI_SW_ID_MASK 0xffff
#define RVR_PF_AMI_SW_RESET_CMD_F_OWNER_OFFSET 4
#define RVR_PF_AMI_SW_RESET_CMD_F_OWNER_SHIFT 16
#define RVR_PF_AMI_SW_RESET_CMD_F_OWNER_MASK 0xffff

struct rvr_pf_ami_sw_reset_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_sw_id:16;
	u64 f_owner:16;
} __packed;

/*
 * PF-AMI-SW-RESET response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMI-SW configured successfully
 *	1: AMI-SW is not mapped in F_OWNER
 *	2: AMI-SW is not disabled
 */

#define RVR_PF_AMI_SW_RESET_RESP_OPCODE_OFFSET 0
#define RVR_PF_AMI_SW_RESET_RESP_OPCODE_SHIFT 0
#define RVR_PF_AMI_SW_RESET_RESP_OPCODE_MASK 0xffff
#define RVR_PF_AMI_SW_RESET_RESP_STATUS_OFFSET 0
#define RVR_PF_AMI_SW_RESET_RESP_STATUS_SHIFT 16
#define RVR_PF_AMI_SW_RESET_RESP_STATUS_MASK 0xffff

struct rvr_pf_ami_sw_reset_resp {
	u64 opcode:16;
	u64 status:16;
} __packed;

/**********************************************************************
 *			PF-AMI-SW-SAVE (opcode 9)
 **********************************************************************/

/*
 * PF-AMI-SW-SAVE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_SW_ID (16b)
 *	AMI-SW within F_OWNER to be saved
 * @0x4 [31:16] ([63:48]) F_OWNER (16b)
 *	Function that owns the AMI-SW to be saved
 */

#define RVR_PF_AMI_SW_SAVE_CMD_OPCODE_OFFSET 0
#define RVR_PF_AMI_SW_SAVE_CMD_OPCODE_SHIFT 0
#define RVR_PF_AMI_SW_SAVE_CMD_OPCODE_MASK 0xffff
#define RVR_PF_AMI_SW_SAVE_CMD_AMI_SW_ID_OFFSET 4
#define RVR_PF_AMI_SW_SAVE_CMD_AMI_SW_ID_SHIFT 0
#define RVR_PF_AMI_SW_SAVE_CMD_AMI_SW_ID_MASK 0xffff
#define RVR_PF_AMI_SW_SAVE_CMD_F_OWNER_OFFSET 4
#define RVR_PF_AMI_SW_SAVE_CMD_F_OWNER_SHIFT 16
#define RVR_PF_AMI_SW_SAVE_CMD_F_OWNER_MASK 0xffff

struct rvr_pf_ami_sw_save_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_sw_id:16;
	u64 f_owner:16;
} __packed;

/*
 * PF-AMI-SW-SAVE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMI-SW saved successfully
 *	1: AMI-SW is not mapped in F_OWNER
 *	2: AMI-SW is not disabled
 * @0x8 [19:0] ([83:64]) PASID (20b)
 *	PASID value
 * @0x8 [20:20] ([84:84]) PASID_ENABLED (1b)
 *	1: PASID is enabled
 *	0: PASID is disabled
 * @0xc [10:0] ([106:96]) TX_VECTOR (11b)
 *	TX_VECTOR value
 * @0xc [21:11] ([117:107]) RX_VECTOR (11b)
 *	RX_VECTOR value
 * @0xc [22:22] ([118:118]) TX_IRQ_ENABLE (1b)
 *	1: Enable TX Interrupt Generation
 *	0: Disable TX Interrupt Generation
 * @0xc [23:23] ([119:119]) RX_IRQ_ENABLE (1b)
 *	1: Enable RX Interrupt Generation
 *	0: Disable RX Interrupt Generation
 * @0x10 [0:0] ([128:128]) ENABLE (1b)
 *	1: AMI-SW is enabled
 *	0: AMI-SW is enabled
 */

#define RVR_PF_AMI_SW_SAVE_RESP_OPCODE_OFFSET 0
#define RVR_PF_AMI_SW_SAVE_RESP_OPCODE_SHIFT 0
#define RVR_PF_AMI_SW_SAVE_RESP_OPCODE_MASK 0xffff
#define RVR_PF_AMI_SW_SAVE_RESP_STATUS_OFFSET 0
#define RVR_PF_AMI_SW_SAVE_RESP_STATUS_SHIFT 16
#define RVR_PF_AMI_SW_SAVE_RESP_STATUS_MASK 0xffff
#define RVR_PF_AMI_SW_SAVE_RESP_PASID_OFFSET 8
#define RVR_PF_AMI_SW_SAVE_RESP_PASID_SHIFT 0
#define RVR_PF_AMI_SW_SAVE_RESP_PASID_MASK 0xfffff
#define RVR_PF_AMI_SW_SAVE_RESP_PASID_ENABLED_OFFSET 8
#define RVR_PF_AMI_SW_SAVE_RESP_PASID_ENABLED_SHIFT 20
#define RVR_PF_AMI_SW_SAVE_RESP_PASID_ENABLED_MASK 0x1
#define RVR_PF_AMI_SW_SAVE_RESP_TX_VECTOR_OFFSET 12
#define RVR_PF_AMI_SW_SAVE_RESP_TX_VECTOR_SHIFT 0
#define RVR_PF_AMI_SW_SAVE_RESP_TX_VECTOR_MASK 0x7ff
#define RVR_PF_AMI_SW_SAVE_RESP_RX_VECTOR_OFFSET 12
#define RVR_PF_AMI_SW_SAVE_RESP_RX_VECTOR_SHIFT 11
#define RVR_PF_AMI_SW_SAVE_RESP_RX_VECTOR_MASK 0x7ff
#define RVR_PF_AMI_SW_SAVE_RESP_TX_IRQ_ENABLE_OFFSET 12
#define RVR_PF_AMI_SW_SAVE_RESP_TX_IRQ_ENABLE_SHIFT 22
#define RVR_PF_AMI_SW_SAVE_RESP_TX_IRQ_ENABLE_MASK 0x1
#define RVR_PF_AMI_SW_SAVE_RESP_RX_IRQ_ENABLE_OFFSET 12
#define RVR_PF_AMI_SW_SAVE_RESP_RX_IRQ_ENABLE_SHIFT 23
#define RVR_PF_AMI_SW_SAVE_RESP_RX_IRQ_ENABLE_MASK 0x1
#define RVR_PF_AMI_SW_SAVE_RESP_ENABLE_OFFSET 16
#define RVR_PF_AMI_SW_SAVE_RESP_ENABLE_SHIFT 0
#define RVR_PF_AMI_SW_SAVE_RESP_ENABLE_MASK 0x1

struct rvr_pf_ami_sw_save_resp {
	u64 opcode:16;
	u64 status:16;
	u64 _reserved_:32;
	u64 pasid:20;
	u64 pasid_enabled:1;
	u64 _reserved_2:11;
	u64 tx_vector:11;
	u64 rx_vector:11;
	u64 tx_irq_enable:1;
	u64 rx_irq_enable:1;
	u64 _reserved_3:8;
	u64 enable:1;
	u64 _reserved_4:31;
} __packed;

/**********************************************************************
 *			PF-AMI-SW-UNMAP (opcode 7)
 **********************************************************************/

/*
 * PF-AMI-SW-UNMAP command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_SW_ID (16b)
 *	AMI-SW within F_OWNER to be unmapped
 * @0x4 [31:16] ([63:48]) F_OWNER (16b)
 *	Function to unmap the AMI-SW from
 */

#define RVR_PF_AMI_SW_UNMAP_CMD_OPCODE_OFFSET 0
#define RVR_PF_AMI_SW_UNMAP_CMD_OPCODE_SHIFT 0
#define RVR_PF_AMI_SW_UNMAP_CMD_OPCODE_MASK 0xffff
#define RVR_PF_AMI_SW_UNMAP_CMD_AMI_SW_ID_OFFSET 4
#define RVR_PF_AMI_SW_UNMAP_CMD_AMI_SW_ID_SHIFT 0
#define RVR_PF_AMI_SW_UNMAP_CMD_AMI_SW_ID_MASK 0xffff
#define RVR_PF_AMI_SW_UNMAP_CMD_F_OWNER_OFFSET 4
#define RVR_PF_AMI_SW_UNMAP_CMD_F_OWNER_SHIFT 16
#define RVR_PF_AMI_SW_UNMAP_CMD_F_OWNER_MASK 0xffff

struct rvr_pf_ami_sw_unmap_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_sw_id:16;
	u64 f_owner:16;
} __packed;

/*
 * PF-AMI-SW-UNMAP response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 */

#define RVR_PF_AMI_SW_UNMAP_RESP_OPCODE_OFFSET 0
#define RVR_PF_AMI_SW_UNMAP_RESP_OPCODE_SHIFT 0
#define RVR_PF_AMI_SW_UNMAP_RESP_OPCODE_MASK 0xffff

struct rvr_pf_ami_sw_unmap_resp {
	u64 opcode:16;
	u64 _reserved_:16;
} __packed;

/**********************************************************************
 *			PF-AMS-RING-CONFIGURE (opcode 18)
 **********************************************************************/

/*
 * PF-AMS-RING-CONFIGURE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_SW_ID (16b)
 *	AMI_SW within F_OWNER to be configured
 * @0x4 [31:16] ([63:48]) F_OWNER (16b)
 *	Function that owns the AMI_SW to be configured
 * @0x8 [5:0] ([69:64]) AMS_ID (6b)
 *	AMS within AMI_SW to be configured
 * @0x8 [6:6] ([70:70]) AMS_TYPE (1b)
 *	0: RX AMS
 *	1: TX AMS
 * @0xc [0:0] ([96:96]) RX_MODE (1b)
 *	0: Back-pressure
 *	1: Overwriting
 * @0xc [4:1] ([100:97]) LOG2_SIZE (4b)
 *	Size of the ring in slots as log~2~(SIZE)
 * @0xc [8:5] ([104:101]) THRESHOLD (4b)
 *	Controls the change of DIGEST bits
 * @0x10 [63:0] ([191:128]) BASE_PTR (64b)
 *	64-bit virtual address of the slot array
 */

#define RVR_PF_AMS_RING_CONFIGURE_CMD_OPCODE_OFFSET 0
#define RVR_PF_AMS_RING_CONFIGURE_CMD_OPCODE_SHIFT 0
#define RVR_PF_AMS_RING_CONFIGURE_CMD_OPCODE_MASK 0xffff
#define RVR_PF_AMS_RING_CONFIGURE_CMD_AMI_SW_ID_OFFSET 4
#define RVR_PF_AMS_RING_CONFIGURE_CMD_AMI_SW_ID_SHIFT 0
#define RVR_PF_AMS_RING_CONFIGURE_CMD_AMI_SW_ID_MASK 0xffff
#define RVR_PF_AMS_RING_CONFIGURE_CMD_F_OWNER_OFFSET 4
#define RVR_PF_AMS_RING_CONFIGURE_CMD_F_OWNER_SHIFT 16
#define RVR_PF_AMS_RING_CONFIGURE_CMD_F_OWNER_MASK 0xffff
#define RVR_PF_AMS_RING_CONFIGURE_CMD_AMS_ID_OFFSET 8
#define RVR_PF_AMS_RING_CONFIGURE_CMD_AMS_ID_SHIFT 0
#define RVR_PF_AMS_RING_CONFIGURE_CMD_AMS_ID_MASK 0x3f
#define RVR_PF_AMS_RING_CONFIGURE_CMD_AMS_TYPE_OFFSET 8
#define RVR_PF_AMS_RING_CONFIGURE_CMD_AMS_TYPE_SHIFT 6
#define RVR_PF_AMS_RING_CONFIGURE_CMD_AMS_TYPE_MASK 0x1
#define RVR_PF_AMS_RING_CONFIGURE_CMD_RX_MODE_OFFSET 12
#define RVR_PF_AMS_RING_CONFIGURE_CMD_RX_MODE_SHIFT 0
#define RVR_PF_AMS_RING_CONFIGURE_CMD_RX_MODE_MASK 0x1
#define RVR_PF_AMS_RING_CONFIGURE_CMD_LOG2_SIZE_OFFSET 12
#define RVR_PF_AMS_RING_CONFIGURE_CMD_LOG2_SIZE_SHIFT 1
#define RVR_PF_AMS_RING_CONFIGURE_CMD_LOG2_SIZE_MASK 0xf
#define RVR_PF_AMS_RING_CONFIGURE_CMD_THRESHOLD_OFFSET 12
#define RVR_PF_AMS_RING_CONFIGURE_CMD_THRESHOLD_SHIFT 5
#define RVR_PF_AMS_RING_CONFIGURE_CMD_THRESHOLD_MASK 0xf
#define RVR_PF_AMS_RING_CONFIGURE_CMD_BASE_PTR_OFFSET 16
#define RVR_PF_AMS_RING_CONFIGURE_CMD_BASE_PTR_SHIFT 0
#define RVR_PF_AMS_RING_CONFIGURE_CMD_BASE_PTR_MASK 0xffffffffffffffff

struct rvr_pf_ams_ring_configure_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_sw_id:16;
	u64 f_owner:16;
	u64 ams_id:6;
	u64 ams_type:1;
	u64 _reserved_2:25;
	u64 rx_mode:1;
	u64 log2_size:4;
	u64 threshold:4;
	u64 _reserved_3:23;
	u64 base_ptr:64;
} __packed;

/*
 * PF-AMS-RING-CONFIGURE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMS ring configured successfully
 *	1: AMI-SW is not mapped in F_OWNER
 *	2: F_OWNER is not disabled
 */

#define RVR_PF_AMS_RING_CONFIGURE_RESP_OPCODE_OFFSET 0
#define RVR_PF_AMS_RING_CONFIGURE_RESP_OPCODE_SHIFT 0
#define RVR_PF_AMS_RING_CONFIGURE_RESP_OPCODE_MASK 0xffff
#define RVR_PF_AMS_RING_CONFIGURE_RESP_STATUS_OFFSET 0
#define RVR_PF_AMS_RING_CONFIGURE_RESP_STATUS_SHIFT 16
#define RVR_PF_AMS_RING_CONFIGURE_RESP_STATUS_MASK 0xffff

struct rvr_pf_ams_ring_configure_resp {
	u64 opcode:16;
	u64 status:16;
} __packed;

/**********************************************************************
 *			PF-AMS-RING-SAVE (opcode 19)
 **********************************************************************/

/*
 * PF-AMS-RING-SAVE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) AMI_SW_ID (16b)
 *	AMI_SW within F_OWNER to be saved
 * @0x4 [31:16] ([63:48]) F_OWNER (16b)
 *	Function that owns the AMI_SW to be saved
 * @0x8 [5:0] ([69:64]) AMS_ID (6b)
 *	AMS within AMI_SW to be saved
 * @0x8 [6:6] ([70:70]) AMS_TYPE (1b)
 *	0: RX AMS
 *	1: TX AMS
 */

#define RVR_PF_AMS_RING_SAVE_CMD_OPCODE_OFFSET 0
#define RVR_PF_AMS_RING_SAVE_CMD_OPCODE_SHIFT 0
#define RVR_PF_AMS_RING_SAVE_CMD_OPCODE_MASK 0xffff
#define RVR_PF_AMS_RING_SAVE_CMD_AMI_SW_ID_OFFSET 4
#define RVR_PF_AMS_RING_SAVE_CMD_AMI_SW_ID_SHIFT 0
#define RVR_PF_AMS_RING_SAVE_CMD_AMI_SW_ID_MASK 0xffff
#define RVR_PF_AMS_RING_SAVE_CMD_F_OWNER_OFFSET 4
#define RVR_PF_AMS_RING_SAVE_CMD_F_OWNER_SHIFT 16
#define RVR_PF_AMS_RING_SAVE_CMD_F_OWNER_MASK 0xffff
#define RVR_PF_AMS_RING_SAVE_CMD_AMS_ID_OFFSET 8
#define RVR_PF_AMS_RING_SAVE_CMD_AMS_ID_SHIFT 0
#define RVR_PF_AMS_RING_SAVE_CMD_AMS_ID_MASK 0x3f
#define RVR_PF_AMS_RING_SAVE_CMD_AMS_TYPE_OFFSET 8
#define RVR_PF_AMS_RING_SAVE_CMD_AMS_TYPE_SHIFT 6
#define RVR_PF_AMS_RING_SAVE_CMD_AMS_TYPE_MASK 0x1

struct rvr_pf_ams_ring_save_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_sw_id:16;
	u64 f_owner:16;
	u64 ams_id:6;
	u64 ams_type:1;
	u64 _reserved_2:25;
} __packed;

/*
 * PF-AMS-RING-SAVE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] Status (16b)
 *	Status Code
 *	0: AMS ring saved successfully
 *	1: AMI-SW is not mapped in F_OWNER
 *	2: F_OWNER is not disabled
 * @0x4 [0:0] ([32:32]) RX_MODE (1b)
 *	0: Back-pressure
 *	1: Overwriting
 * @0x4 [4:1] ([36:33]) LOG2_SIZE (4b)
 *	Size of the ring in slots as log~2~(SIZE)
 * @0x4 [8:5] ([40:37]) THRESHOLD (4b)
 *	Controls the change of DIGEST bits
 * @0x8 [63:0] ([127:64]) BASE_PTR (64b)
 *	64-bit virtual address of the slot array
 */

#define RVR_PF_AMS_RING_SAVE_RESP_OPCODE_OFFSET 0
#define RVR_PF_AMS_RING_SAVE_RESP_OPCODE_SHIFT 0
#define RVR_PF_AMS_RING_SAVE_RESP_OPCODE_MASK 0xffff
#define RVR_PF_AMS_RING_SAVE_RESP_STATUS_OFFSET 0
#define RVR_PF_AMS_RING_SAVE_RESP_STATUS_SHIFT 16
#define RVR_PF_AMS_RING_SAVE_RESP_STATUS_MASK 0xffff
#define RVR_PF_AMS_RING_SAVE_RESP_RX_MODE_OFFSET 4
#define RVR_PF_AMS_RING_SAVE_RESP_RX_MODE_SHIFT 0
#define RVR_PF_AMS_RING_SAVE_RESP_RX_MODE_MASK 0x1
#define RVR_PF_AMS_RING_SAVE_RESP_LOG2_SIZE_OFFSET 4
#define RVR_PF_AMS_RING_SAVE_RESP_LOG2_SIZE_SHIFT 1
#define RVR_PF_AMS_RING_SAVE_RESP_LOG2_SIZE_MASK 0xf
#define RVR_PF_AMS_RING_SAVE_RESP_THRESHOLD_OFFSET 4
#define RVR_PF_AMS_RING_SAVE_RESP_THRESHOLD_SHIFT 5
#define RVR_PF_AMS_RING_SAVE_RESP_THRESHOLD_MASK 0xf
#define RVR_PF_AMS_RING_SAVE_RESP_BASE_PTR_OFFSET 8
#define RVR_PF_AMS_RING_SAVE_RESP_BASE_PTR_SHIFT 0
#define RVR_PF_AMS_RING_SAVE_RESP_BASE_PTR_MASK 0xffffffffffffffff

struct rvr_pf_ams_ring_save_resp {
	u64 opcode:16;
	u64 status:16;
	u64 rx_mode:1;
	u64 log2_size:4;
	u64 threshold:4;
	u64 _reserved_:23;
	u64 base_ptr:64;
} __packed;

/**********************************************************************
 *			PF-ASN-CREATE (opcode 16)
 **********************************************************************/

/*
 * PF-ASN-CREATE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [3:0] ([35:32]) PRIO (4b)
 *	Priority to use for this ASN
 * @0x4 [4:4] ([36:36]) DST_AMI_TYPE (1b)
 *	0: AMI-SW
 *	1: AMI-HW
 * @0x4 [5:5] ([37:37]) SRC_AMI_TYPE (1b)
 *	0: AMI-SW
 *	1: AMI-HW
 * @0x4 [21:6] ([53:38]) MON_OWNER (16b)
 * @0x8 [15:0] ([79:64]) SRC_AMI (16b)
 *	Sending AMI within SRC_F_OWNER
 * @0x8 [31:16] ([95:80]) SRC_F_OWNER (16b)
 *	Function that owns the sending AMI
 * @0xc [15:0] ([111:96]) DST_AMI (16b)
 *	Receiving AMI within DST_F_OWNER
 * @0xc [31:16] ([127:112]) DST_F_OWNER (16b)
 *	Function that owns the receiving AMI
 * @0x10 [5:0] ([133:128]) DST_AMS (6b)
 *	Receiving AMS within DST_AMI
 * @0x10 [11:6] ([139:134]) SRC_AMS (6b)
 *	Sending AMS within SRC_AMI
 * @0x14 [27:0] ([187:160]) ASN_ID (28b)
 *	Physical identifier for this ASN
 * @0x18 [63:0] ([255:192]) STASH_CTL (64b)
 *	Stashing controls to use for this ASN
 * @0x20 [63:0] ([319:256]) PROF_MASK (64b)
 *	Profiling mask
 * @0x28 [63:0] ([383:320]) PROF_TBL_BASE (64b)
 *	Profiling table base pointer
 * @0x30 [15:0] ([399:384]) PROF_CTL (16b)
 *	Profiling controls to use for this ASN
 * @0x30 [31:16] ([415:400]) TRACE_CTL (16b)
 *	Tracing controls to use for this ASN
 * @0x34 [31:0] ([447:416]) MPIDR (32b)
 *	Physical location of the thread using the RX AMS
 * @0x38 [2:0] ([450:448]) MFO (3b)
 *	Message format to use for this ASN
 * @0x38 [9:3] ([457:451]) MF_OB_BUF_NUM (7b)
 *	Number of references to outband buffers
 * @0x38 [13:10] ([461:458]) LOG2_MSG_LENGTH (4b)
 *	Message length (in Doublewords) as log~2~(MSG_LENGTH)
 */

#define RVR_PF_ASN_CREATE_CMD_OPCODE_OFFSET 0
#define RVR_PF_ASN_CREATE_CMD_OPCODE_SHIFT 0
#define RVR_PF_ASN_CREATE_CMD_OPCODE_MASK 0xffff
#define RVR_PF_ASN_CREATE_CMD_PRIO_OFFSET 4
#define RVR_PF_ASN_CREATE_CMD_PRIO_SHIFT 0
#define RVR_PF_ASN_CREATE_CMD_PRIO_MASK 0xf
#define RVR_PF_ASN_CREATE_CMD_DST_AMI_TYPE_OFFSET 4
#define RVR_PF_ASN_CREATE_CMD_DST_AMI_TYPE_SHIFT 4
#define RVR_PF_ASN_CREATE_CMD_DST_AMI_TYPE_MASK 0x1
#define RVR_PF_ASN_CREATE_CMD_SRC_AMI_TYPE_OFFSET 4
#define RVR_PF_ASN_CREATE_CMD_SRC_AMI_TYPE_SHIFT 5
#define RVR_PF_ASN_CREATE_CMD_SRC_AMI_TYPE_MASK 0x1
#define RVR_PF_ASN_CREATE_CMD_MON_OWNER_OFFSET 4
#define RVR_PF_ASN_CREATE_CMD_MON_OWNER_SHIFT 6
#define RVR_PF_ASN_CREATE_CMD_MON_OWNER_MASK 0xffff
#define RVR_PF_ASN_CREATE_CMD_SRC_AMI_OFFSET 8
#define RVR_PF_ASN_CREATE_CMD_SRC_AMI_SHIFT 0
#define RVR_PF_ASN_CREATE_CMD_SRC_AMI_MASK 0xffff
#define RVR_PF_ASN_CREATE_CMD_SRC_F_OWNER_OFFSET 8
#define RVR_PF_ASN_CREATE_CMD_SRC_F_OWNER_SHIFT 16
#define RVR_PF_ASN_CREATE_CMD_SRC_F_OWNER_MASK 0xffff
#define RVR_PF_ASN_CREATE_CMD_DST_AMI_OFFSET 12
#define RVR_PF_ASN_CREATE_CMD_DST_AMI_SHIFT 0
#define RVR_PF_ASN_CREATE_CMD_DST_AMI_MASK 0xffff
#define RVR_PF_ASN_CREATE_CMD_DST_F_OWNER_OFFSET 12
#define RVR_PF_ASN_CREATE_CMD_DST_F_OWNER_SHIFT 16
#define RVR_PF_ASN_CREATE_CMD_DST_F_OWNER_MASK 0xffff
#define RVR_PF_ASN_CREATE_CMD_DST_AMS_OFFSET 16
#define RVR_PF_ASN_CREATE_CMD_DST_AMS_SHIFT 0
#define RVR_PF_ASN_CREATE_CMD_DST_AMS_MASK 0x3f
#define RVR_PF_ASN_CREATE_CMD_SRC_AMS_OFFSET 16
#define RVR_PF_ASN_CREATE_CMD_SRC_AMS_SHIFT 6
#define RVR_PF_ASN_CREATE_CMD_SRC_AMS_MASK 0x3f
#define RVR_PF_ASN_CREATE_CMD_ASN_ID_OFFSET 20
#define RVR_PF_ASN_CREATE_CMD_ASN_ID_SHIFT 0
#define RVR_PF_ASN_CREATE_CMD_ASN_ID_MASK 0xfffffff
#define RVR_PF_ASN_CREATE_CMD_STASH_CTL_OFFSET 24
#define RVR_PF_ASN_CREATE_CMD_STASH_CTL_SHIFT 0
#define RVR_PF_ASN_CREATE_CMD_STASH_CTL_MASK 0xffffffffffffffff
#define RVR_PF_ASN_CREATE_CMD_PROF_MASK_OFFSET 32
#define RVR_PF_ASN_CREATE_CMD_PROF_MASK_SHIFT 0
#define RVR_PF_ASN_CREATE_CMD_PROF_MASK_MASK 0xffffffffffffffff
#define RVR_PF_ASN_CREATE_CMD_PROF_TBL_BASE_OFFSET 40
#define RVR_PF_ASN_CREATE_CMD_PROF_TBL_BASE_SHIFT 0
#define RVR_PF_ASN_CREATE_CMD_PROF_TBL_BASE_MASK 0xffffffffffffffff
#define RVR_PF_ASN_CREATE_CMD_PROF_CTL_OFFSET 48
#define RVR_PF_ASN_CREATE_CMD_PROF_CTL_SHIFT 0
#define RVR_PF_ASN_CREATE_CMD_PROF_CTL_MASK 0xffff
#define RVR_PF_ASN_CREATE_CMD_TRACE_CTL_OFFSET 48
#define RVR_PF_ASN_CREATE_CMD_TRACE_CTL_SHIFT 16
#define RVR_PF_ASN_CREATE_CMD_TRACE_CTL_MASK 0xffff
#define RVR_PF_ASN_CREATE_CMD_MPIDR_OFFSET 52
#define RVR_PF_ASN_CREATE_CMD_MPIDR_SHIFT 0
#define RVR_PF_ASN_CREATE_CMD_MPIDR_MASK 0xffffffff
#define RVR_PF_ASN_CREATE_CMD_MFO_OFFSET 56
#define RVR_PF_ASN_CREATE_CMD_MFO_SHIFT 0
#define RVR_PF_ASN_CREATE_CMD_MFO_MASK 0x7
#define RVR_PF_ASN_CREATE_CMD_MF_OB_BUF_NUM_OFFSET 56
#define RVR_PF_ASN_CREATE_CMD_MF_OB_BUF_NUM_SHIFT 3
#define RVR_PF_ASN_CREATE_CMD_MF_OB_BUF_NUM_MASK 0x7f
#define RVR_PF_ASN_CREATE_CMD_LOG2_MSG_LENGTH_OFFSET 56
#define RVR_PF_ASN_CREATE_CMD_LOG2_MSG_LENGTH_SHIFT 10
#define RVR_PF_ASN_CREATE_CMD_LOG2_MSG_LENGTH_MASK 0xf

struct rvr_pf_asn_create_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 prio:4;
	u64 dst_ami_type:1;
	u64 src_ami_type:1;
	u64 mon_owner:16;
	u64 _reserved_2:10;
	u64 src_ami:16;
	u64 src_f_owner:16;
	u64 dst_ami:16;
	u64 dst_f_owner:16;
	u64 dst_ams:6;
	u64 src_ams:6;
	u64 _reserved_3:20;
	u64 asn_id:28;
	u64 _reserved_4:4;
	u64 stash_ctl:64;
	u64 prof_mask:64;
	u64 prof_tbl_base:64;
	u64 prof_ctl:16;
	u64 trace_ctl:16;
	u64 mpidr:32;
	u64 mfo:3;
	u64 mf_ob_buf_num:7;
	u64 log2_msg_length:4;
	u64 _reserved_5:18;
} __packed;

/*
 * PF-ASN-CREATE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] STATUS (16b)
 *	Status Code
 *	0: Message Delivered to VF
 *	1: Requested ASN ID already in use
 */

#define RVR_PF_ASN_CREATE_RESP_OPCODE_OFFSET 0
#define RVR_PF_ASN_CREATE_RESP_OPCODE_SHIFT 0
#define RVR_PF_ASN_CREATE_RESP_OPCODE_MASK 0xffff
#define RVR_PF_ASN_CREATE_RESP_STATUS_OFFSET 0
#define RVR_PF_ASN_CREATE_RESP_STATUS_SHIFT 16
#define RVR_PF_ASN_CREATE_RESP_STATUS_MASK 0xffff

struct rvr_pf_asn_create_resp {
	u64 opcode:16;
	u64 status:16;
} __packed;

/**********************************************************************
 *			PF-ASN-DESTROY (opcode 17)
 **********************************************************************/

/*
 * PF-ASN-DESTROY command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [27:0] ([59:32]) ASN_ID (28b)
 *	Physical identifier for ASN to be destroyed
 */

#define RVR_PF_ASN_DESTROY_CMD_OPCODE_OFFSET 0
#define RVR_PF_ASN_DESTROY_CMD_OPCODE_SHIFT 0
#define RVR_PF_ASN_DESTROY_CMD_OPCODE_MASK 0xffff
#define RVR_PF_ASN_DESTROY_CMD_ASN_ID_OFFSET 4
#define RVR_PF_ASN_DESTROY_CMD_ASN_ID_SHIFT 0
#define RVR_PF_ASN_DESTROY_CMD_ASN_ID_MASK 0xfffffff

struct rvr_pf_asn_destroy_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 asn_id:28;
	u64 _reserved_2:4;
} __packed;

/*
 * PF-ASN-DESTROY response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] STATUS (16b)
 *	Status Code
 *	0: Message Delivered to VF
 *	1: ASN does not exist
 * @0x4 [3:0] ([35:32]) PRIO (4b)
 *	Priority to use for this ASN
 * @0x4 [4:4] ([36:36]) DST_AMI_TYPE (1b)
 *	0: AMI-SW
 *	1: AMI-HW
 * @0x4 [5:5] ([37:37]) SRC_AMI_TYPE (1b)
 *	0: AMI-SW
 *	1: AMI-HW
 * @0x4 [21:6] ([53:38]) MON_OWNER (16b)
 * @0x8 [15:0] ([79:64]) SRC_AMI (16b)
 *	Sending AMI within SRC_F_OWNER
 * @0x8 [31:16] ([95:80]) SRC_F_OWNER (16b)
 *	Function that owns the sending AMI
 * @0xc [15:0] ([111:96]) DST_AMI (16b)
 *	Receiving AMI within DST_F_OWNER
 * @0xc [31:16] ([127:112]) DST_F_OWNER (16b)
 *	Function that owns the receiving AMI
 * @0x10 [5:0] ([133:128]) DST_AMS (6b)
 *	Receiving AMS within DST_AMI
 * @0x10 [11:6] ([139:134]) SRC_AMS (6b)
 *	Sending AMS within SRC_AMI
 * @0x14 [15:0] ([175:160]) PROF_CTL (16b)
 *	Profiling controls configured in this ASN
 * @0x14 [31:16] ([191:176]) TRACE_CTL (16b)
 *	Tracing controls configured in this ASN
 * @0x18 [63:0] ([255:192]) STASH_CTL (64b)
 *	Stashing controls configured in this ASN
 * @0x20 [63:0] ([319:256]) PROF_MASK (64b)
 *	Profiling mask
 * @0x28 [63:0] ([383:320]) PROF_TBL_BASE (64b)
 *	Profiling table base pointer
 * @0x30 [31:0] ([415:384]) MPIDR (32b)
 *	Physical location of the thread using the RX AMS
 * @0x34 [2:0] ([418:416]) MFO (3b)
 *	Message format to use for this ASN
 * @0x34 [9:3] ([425:419]) MF_OB_BUF_NUM (7b)
 *	Number of references to outband buffers
 * @0x34 [13:10] ([429:426]) LOG2_MSG_LENGTH (4b)
 *	Message length (in Doublewords) as log~2~(MSG_LENGTH)
 */

#define RVR_PF_ASN_DESTROY_RESP_OPCODE_OFFSET 0
#define RVR_PF_ASN_DESTROY_RESP_OPCODE_SHIFT 0
#define RVR_PF_ASN_DESTROY_RESP_OPCODE_MASK 0xffff
#define RVR_PF_ASN_DESTROY_RESP_STATUS_OFFSET 0
#define RVR_PF_ASN_DESTROY_RESP_STATUS_SHIFT 16
#define RVR_PF_ASN_DESTROY_RESP_STATUS_MASK 0xffff
#define RVR_PF_ASN_DESTROY_RESP_PRIO_OFFSET 4
#define RVR_PF_ASN_DESTROY_RESP_PRIO_SHIFT 0
#define RVR_PF_ASN_DESTROY_RESP_PRIO_MASK 0xf
#define RVR_PF_ASN_DESTROY_RESP_DST_AMI_TYPE_OFFSET 4
#define RVR_PF_ASN_DESTROY_RESP_DST_AMI_TYPE_SHIFT 4
#define RVR_PF_ASN_DESTROY_RESP_DST_AMI_TYPE_MASK 0x1
#define RVR_PF_ASN_DESTROY_RESP_SRC_AMI_TYPE_OFFSET 4
#define RVR_PF_ASN_DESTROY_RESP_SRC_AMI_TYPE_SHIFT 5
#define RVR_PF_ASN_DESTROY_RESP_SRC_AMI_TYPE_MASK 0x1
#define RVR_PF_ASN_DESTROY_RESP_MON_OWNER_OFFSET 4
#define RVR_PF_ASN_DESTROY_RESP_MON_OWNER_SHIFT 6
#define RVR_PF_ASN_DESTROY_RESP_MON_OWNER_MASK 0xffff
#define RVR_PF_ASN_DESTROY_RESP_SRC_AMI_OFFSET 8
#define RVR_PF_ASN_DESTROY_RESP_SRC_AMI_SHIFT 0
#define RVR_PF_ASN_DESTROY_RESP_SRC_AMI_MASK 0xffff
#define RVR_PF_ASN_DESTROY_RESP_SRC_F_OWNER_OFFSET 8
#define RVR_PF_ASN_DESTROY_RESP_SRC_F_OWNER_SHIFT 16
#define RVR_PF_ASN_DESTROY_RESP_SRC_F_OWNER_MASK 0xffff
#define RVR_PF_ASN_DESTROY_RESP_DST_AMI_OFFSET 12
#define RVR_PF_ASN_DESTROY_RESP_DST_AMI_SHIFT 0
#define RVR_PF_ASN_DESTROY_RESP_DST_AMI_MASK 0xffff
#define RVR_PF_ASN_DESTROY_RESP_DST_F_OWNER_OFFSET 12
#define RVR_PF_ASN_DESTROY_RESP_DST_F_OWNER_SHIFT 16
#define RVR_PF_ASN_DESTROY_RESP_DST_F_OWNER_MASK 0xffff
#define RVR_PF_ASN_DESTROY_RESP_DST_AMS_OFFSET 16
#define RVR_PF_ASN_DESTROY_RESP_DST_AMS_SHIFT 0
#define RVR_PF_ASN_DESTROY_RESP_DST_AMS_MASK 0x3f
#define RVR_PF_ASN_DESTROY_RESP_SRC_AMS_OFFSET 16
#define RVR_PF_ASN_DESTROY_RESP_SRC_AMS_SHIFT 6
#define RVR_PF_ASN_DESTROY_RESP_SRC_AMS_MASK 0x3f
#define RVR_PF_ASN_DESTROY_RESP_PROF_CTL_OFFSET 20
#define RVR_PF_ASN_DESTROY_RESP_PROF_CTL_SHIFT 0
#define RVR_PF_ASN_DESTROY_RESP_PROF_CTL_MASK 0xffff
#define RVR_PF_ASN_DESTROY_RESP_TRACE_CTL_OFFSET 20
#define RVR_PF_ASN_DESTROY_RESP_TRACE_CTL_SHIFT 16
#define RVR_PF_ASN_DESTROY_RESP_TRACE_CTL_MASK 0xffff
#define RVR_PF_ASN_DESTROY_RESP_STASH_CTL_OFFSET 24
#define RVR_PF_ASN_DESTROY_RESP_STASH_CTL_SHIFT 0
#define RVR_PF_ASN_DESTROY_RESP_STASH_CTL_MASK 0xffffffffffffffff
#define RVR_PF_ASN_DESTROY_RESP_PROF_MASK_OFFSET 32
#define RVR_PF_ASN_DESTROY_RESP_PROF_MASK_SHIFT 0
#define RVR_PF_ASN_DESTROY_RESP_PROF_MASK_MASK 0xffffffffffffffff
#define RVR_PF_ASN_DESTROY_RESP_PROF_TBL_BASE_OFFSET 40
#define RVR_PF_ASN_DESTROY_RESP_PROF_TBL_BASE_SHIFT 0
#define RVR_PF_ASN_DESTROY_RESP_PROF_TBL_BASE_MASK 0xffffffffffffffff
#define RVR_PF_ASN_DESTROY_RESP_MPIDR_OFFSET 48
#define RVR_PF_ASN_DESTROY_RESP_MPIDR_SHIFT 0
#define RVR_PF_ASN_DESTROY_RESP_MPIDR_MASK 0xffffffff
#define RVR_PF_ASN_DESTROY_RESP_MFO_OFFSET 52
#define RVR_PF_ASN_DESTROY_RESP_MFO_SHIFT 0
#define RVR_PF_ASN_DESTROY_RESP_MFO_MASK 0x7
#define RVR_PF_ASN_DESTROY_RESP_MF_OB_BUF_NUM_OFFSET 52
#define RVR_PF_ASN_DESTROY_RESP_MF_OB_BUF_NUM_SHIFT 3
#define RVR_PF_ASN_DESTROY_RESP_MF_OB_BUF_NUM_MASK 0x7f
#define RVR_PF_ASN_DESTROY_RESP_LOG2_MSG_LENGTH_OFFSET 52
#define RVR_PF_ASN_DESTROY_RESP_LOG2_MSG_LENGTH_SHIFT 10
#define RVR_PF_ASN_DESTROY_RESP_LOG2_MSG_LENGTH_MASK 0xf

struct rvr_pf_asn_destroy_resp {
	u64 opcode:16;
	u64 status:16;
	u64 prio:4;
	u64 dst_ami_type:1;
	u64 src_ami_type:1;
	u64 mon_owner:16;
	u64 _reserved_:10;
	u64 src_ami:16;
	u64 src_f_owner:16;
	u64 dst_ami:16;
	u64 dst_f_owner:16;
	u64 dst_ams:6;
	u64 src_ams:6;
	u64 _reserved_2:20;
	u64 prof_ctl:16;
	u64 trace_ctl:16;
	u64 stash_ctl:64;
	u64 prof_mask:64;
	u64 prof_tbl_base:64;
	u64 mpidr:32;
	u64 mfo:3;
	u64 mf_ob_buf_num:7;
	u64 log2_msg_length:4;
	u64 _reserved_3:18;
} __packed;

/**********************************************************************
 *			PF-F-DISABLE (opcode 4)
 **********************************************************************/

/*
 * PF-F-DISABLE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) F_OWNER (16b)
 *	Function to be disabled. Cannot be 0
 */

#define RVR_PF_F_DISABLE_CMD_OPCODE_OFFSET 0
#define RVR_PF_F_DISABLE_CMD_OPCODE_SHIFT 0
#define RVR_PF_F_DISABLE_CMD_OPCODE_MASK 0xffff
#define RVR_PF_F_DISABLE_CMD_F_OWNER_OFFSET 4
#define RVR_PF_F_DISABLE_CMD_F_OWNER_SHIFT 0
#define RVR_PF_F_DISABLE_CMD_F_OWNER_MASK 0xffff

struct rvr_pf_f_disable_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 f_owner:16;
	u64 _reserved_2:16;
} __packed;

/*
 * PF-F-DISABLE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 */

#define RVR_PF_F_DISABLE_RESP_OPCODE_OFFSET 0
#define RVR_PF_F_DISABLE_RESP_OPCODE_SHIFT 0
#define RVR_PF_F_DISABLE_RESP_OPCODE_MASK 0xffff

struct rvr_pf_f_disable_resp {
	u64 opcode:16;
	u64 _reserved_:16;
} __packed;

/**********************************************************************
 *			PF-F-ENABLE (opcode 3)
 **********************************************************************/

/*
 * PF-F-ENABLE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) F_OWNER (16b)
 *	Function to be enabled. Cannot be 0
 */

#define RVR_PF_F_ENABLE_CMD_OPCODE_OFFSET 0
#define RVR_PF_F_ENABLE_CMD_OPCODE_SHIFT 0
#define RVR_PF_F_ENABLE_CMD_OPCODE_MASK 0xffff
#define RVR_PF_F_ENABLE_CMD_F_OWNER_OFFSET 4
#define RVR_PF_F_ENABLE_CMD_F_OWNER_SHIFT 0
#define RVR_PF_F_ENABLE_CMD_F_OWNER_MASK 0xffff

struct rvr_pf_f_enable_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 f_owner:16;
	u64 _reserved_2:16;
} __packed;

/*
 * PF-F-ENABLE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 */

#define RVR_PF_F_ENABLE_RESP_OPCODE_OFFSET 0
#define RVR_PF_F_ENABLE_RESP_OPCODE_SHIFT 0
#define RVR_PF_F_ENABLE_RESP_OPCODE_MASK 0xffff

struct rvr_pf_f_enable_resp {
	u64 opcode:16;
	u64 _reserved_:16;
} __packed;

/**********************************************************************
 *			PF-PROBE (opcode 1)
 **********************************************************************/

/*
 * PF-PROBE command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 */

#define RVR_PF_PROBE_CMD_OPCODE_OFFSET 0
#define RVR_PF_PROBE_CMD_OPCODE_SHIFT 0
#define RVR_PF_PROBE_CMD_OPCODE_MASK 0xffff

struct rvr_pf_probe_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
} __packed;

/*
 * PF-PROBE response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4 [15:0] ([47:32]) MAX_AMI_SW (16b)
 *	Total number of AMI-SWs implemented
 * @0x4 [31:16] ([63:48]) MAX_AMI_HW (16b)
 *	Total number of AMI-HWs implemented
 * @0x8 [20:0] ([84:64]) MAX_ASN (21b)
 *	Maximum number of ASNs that can be created
 * @0xc [15:0] ([111:96]) NUM_AHA (16b)
 *	Number of AHAs in the system
 */

#define RVR_PF_PROBE_RESP_OPCODE_OFFSET 0
#define RVR_PF_PROBE_RESP_OPCODE_SHIFT 0
#define RVR_PF_PROBE_RESP_OPCODE_MASK 0xffff
#define RVR_PF_PROBE_RESP_MAX_AMI_SW_OFFSET 4
#define RVR_PF_PROBE_RESP_MAX_AMI_SW_SHIFT 0
#define RVR_PF_PROBE_RESP_MAX_AMI_SW_MASK 0xffff
#define RVR_PF_PROBE_RESP_MAX_AMI_HW_OFFSET 4
#define RVR_PF_PROBE_RESP_MAX_AMI_HW_SHIFT 16
#define RVR_PF_PROBE_RESP_MAX_AMI_HW_MASK 0xffff
#define RVR_PF_PROBE_RESP_MAX_ASN_OFFSET 8
#define RVR_PF_PROBE_RESP_MAX_ASN_SHIFT 0
#define RVR_PF_PROBE_RESP_MAX_ASN_MASK 0x1fffff
#define RVR_PF_PROBE_RESP_NUM_AHA_OFFSET 12
#define RVR_PF_PROBE_RESP_NUM_AHA_SHIFT 0
#define RVR_PF_PROBE_RESP_NUM_AHA_MASK 0xffff

struct rvr_pf_probe_resp {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 max_ami_sw:16;
	u64 max_ami_hw:16;
	u64 max_asn:21;
	u64 _reserved_2:11;
	u64 num_aha:16;
	u64 _reserved_3:16;
} __packed;

/**********************************************************************
 *			PF-RESPONSE-TO-VF (opcode 22)
 **********************************************************************/

/*
 * PF-RESPONSE-TO-VF command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] F_TARGET (16b)
 *	destination VF number
 * @0x4
 *	Use-case specific payload (arbitrary length)
 */

#define RVR_PF_RESPONSE_TO_VF_CMD_OPCODE_OFFSET 0
#define RVR_PF_RESPONSE_TO_VF_CMD_OPCODE_SHIFT 0
#define RVR_PF_RESPONSE_TO_VF_CMD_OPCODE_MASK 0xffff
#define RVR_PF_RESPONSE_TO_VF_CMD_F_TARGET_OFFSET 0
#define RVR_PF_RESPONSE_TO_VF_CMD_F_TARGET_SHIFT 16
#define RVR_PF_RESPONSE_TO_VF_CMD_F_TARGET_MASK 0xffff
#define RVR_PF_RESPONSE_TO_VF_CMD_PAYLOAD_OFFSET 4

struct rvr_pf_response_to_vf_cmd {
	u64 opcode:16;
	u64 f_target:16;
	u64 payload[];
} __packed;

/*
 * PF-RESPONSE-TO-VF response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] STATUS (16b)
 *	Status Code
 *	0: Message Delivered to VF
 *	1: Message could not be delivered
 */

#define RVR_PF_RESPONSE_TO_VF_RESP_OPCODE_OFFSET 0
#define RVR_PF_RESPONSE_TO_VF_RESP_OPCODE_SHIFT 0
#define RVR_PF_RESPONSE_TO_VF_RESP_OPCODE_MASK 0xffff
#define RVR_PF_RESPONSE_TO_VF_RESP_STATUS_OFFSET 0
#define RVR_PF_RESPONSE_TO_VF_RESP_STATUS_SHIFT 16
#define RVR_PF_RESPONSE_TO_VF_RESP_STATUS_MASK 0xffff

struct rvr_pf_response_to_vf_resp {
	u64 opcode:16;
	u64 status:16;
} __packed;

/**********************************************************************
 *			VF-COMMAND-TO-PF (opcode 28)
 **********************************************************************/

/*
 * VF-COMMAND-TO-PF command
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x4
 *	Use-case specific payload (arbitrary length)
 */

#define RVR_VF_COMMAND_TO_PF_CMD_OPCODE_OFFSET 0
#define RVR_VF_COMMAND_TO_PF_CMD_OPCODE_SHIFT 0
#define RVR_VF_COMMAND_TO_PF_CMD_OPCODE_MASK 0xffff
#define RVR_VF_COMMAND_TO_PF_CMD_PAYLOAD_OFFSET 4

struct rvr_vf_command_to_pf_cmd {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 payload[];
} __packed;

/*
 * VF-COMMAND-TO-PF response
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Command Opcode
 * @0x0 [31:16] STATUS (16b)
 *	Status Code
 *	0: Message delivered. Response is in payload
 *	1: Message could not be delivered. Payload is invalid
 * @0x4
 *	Use-case specific payload (arbitrary length)
 */

#define RVR_VF_COMMAND_TO_PF_RESP_OPCODE_OFFSET 0
#define RVR_VF_COMMAND_TO_PF_RESP_OPCODE_SHIFT 0
#define RVR_VF_COMMAND_TO_PF_RESP_OPCODE_MASK 0xffff
#define RVR_VF_COMMAND_TO_PF_RESP_STATUS_OFFSET 0
#define RVR_VF_COMMAND_TO_PF_RESP_STATUS_SHIFT 16
#define RVR_VF_COMMAND_TO_PF_RESP_STATUS_MASK 0xffff
#define RVR_VF_COMMAND_TO_PF_RESP_PAYLOAD_OFFSET 4

struct rvr_vf_command_to_pf_resp {
	u64 opcode:16;
	u64 status:16;
	u64 payload[];
} __packed;

/**********************************************************************
 *				Exceptions
 **********************************************************************/

enum rvr_exc_opcode {
	RVR_E_PF_COMMAND_FROM_VF = 1,
	RVR_E_PF_VF_RESET = 2,
	RVR_E_F_COUNTER_OVERFLOW = 3,
};

/**********************************************************************
 *			E-F-COUNTER-OVERFLOW (opcode 3)
 **********************************************************************/

/*
 * E-F-COUNTER-OVERFLOW exception
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Exception Opcode
 * @0x4 [15:0] ([47:32]) AMI_ID (16b)
 *	AMI within F_OWNER
 * @0x4 [31:16] ([63:48]) F_OWNER (16b)
 *	Function that owns the AMI_SW
 * @0x8 [5:0] ([69:64]) AMS_ID (6b)
 *	AMS within AMI_SW to be configured
 * @0x8 [6:6] ([70:70]) AMI_TYPE (1b)
 *	0: AMI-SW
 *	1: AMI-HW
 * @0x8 [7:7] ([71:71]) AMS_TYPE (1b)
 *	0: RX AMS
 *	1: TX AMS
 * @0xc [15:0] ([111:96]) COUNTER_ID (16b)
 *	Counter that overflowed
 */

#define RVR_E_F_COUNTER_OVERFLOW_EXC_OPCODE_OFFSET 0
#define RVR_E_F_COUNTER_OVERFLOW_EXC_OPCODE_SHIFT 0
#define RVR_E_F_COUNTER_OVERFLOW_EXC_OPCODE_MASK 0xffff
#define RVR_E_F_COUNTER_OVERFLOW_EXC_AMI_ID_OFFSET 4
#define RVR_E_F_COUNTER_OVERFLOW_EXC_AMI_ID_SHIFT 0
#define RVR_E_F_COUNTER_OVERFLOW_EXC_AMI_ID_MASK 0xffff
#define RVR_E_F_COUNTER_OVERFLOW_EXC_F_OWNER_OFFSET 4
#define RVR_E_F_COUNTER_OVERFLOW_EXC_F_OWNER_SHIFT 16
#define RVR_E_F_COUNTER_OVERFLOW_EXC_F_OWNER_MASK 0xffff
#define RVR_E_F_COUNTER_OVERFLOW_EXC_AMS_ID_OFFSET 8
#define RVR_E_F_COUNTER_OVERFLOW_EXC_AMS_ID_SHIFT 0
#define RVR_E_F_COUNTER_OVERFLOW_EXC_AMS_ID_MASK 0x3f
#define RVR_E_F_COUNTER_OVERFLOW_EXC_AMI_TYPE_OFFSET 8
#define RVR_E_F_COUNTER_OVERFLOW_EXC_AMI_TYPE_SHIFT 6
#define RVR_E_F_COUNTER_OVERFLOW_EXC_AMI_TYPE_MASK 0x1
#define RVR_E_F_COUNTER_OVERFLOW_EXC_AMS_TYPE_OFFSET 8
#define RVR_E_F_COUNTER_OVERFLOW_EXC_AMS_TYPE_SHIFT 7
#define RVR_E_F_COUNTER_OVERFLOW_EXC_AMS_TYPE_MASK 0x1
#define RVR_E_F_COUNTER_OVERFLOW_EXC_COUNTER_ID_OFFSET 12
#define RVR_E_F_COUNTER_OVERFLOW_EXC_COUNTER_ID_SHIFT 0
#define RVR_E_F_COUNTER_OVERFLOW_EXC_COUNTER_ID_MASK 0xffff

struct rvr_e_f_counter_overflow_exc {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 ami_id:16;
	u64 f_owner:16;
	u64 ams_id:6;
	u64 ami_type:1;
	u64 ams_type:1;
	u64 _reserved_2:24;
	u64 counter_id:16;
	u64 _reserved_3:16;
} __packed;

/**********************************************************************
 *			E-PF-COMMAND-FROM-VF (opcode 1)
 **********************************************************************/

/*
 * E-PF-COMMAND-FROM-VF exception
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Exception Opcode
 * @0x4 [15:0] ([47:32]) SOURCE (16b)
 *	Source VF
 * @0x8
 *	Use-case specific payload (arbitrary length)
 */

#define RVR_E_PF_COMMAND_FROM_VF_EXC_OPCODE_OFFSET 0
#define RVR_E_PF_COMMAND_FROM_VF_EXC_OPCODE_SHIFT 0
#define RVR_E_PF_COMMAND_FROM_VF_EXC_OPCODE_MASK 0xffff
#define RVR_E_PF_COMMAND_FROM_VF_EXC_SOURCE_OFFSET 4
#define RVR_E_PF_COMMAND_FROM_VF_EXC_SOURCE_SHIFT 0
#define RVR_E_PF_COMMAND_FROM_VF_EXC_SOURCE_MASK 0xffff
#define RVR_E_PF_COMMAND_FROM_VF_EXC_PAYLOAD_OFFSET 8

struct rvr_e_pf_command_from_vf_exc {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 source:16;
	u64 _reserved_2:16;
	u64 payload[];
} __packed;

/**********************************************************************
 *			E-PF-VF-RESET (opcode 2)
 **********************************************************************/

/*
 * E-PF-VF-RESET exception
 *
 * @0x0 [15:0] OPCODE (16b)
 *	Exception Opcode
 * @0x4 [15:0] ([47:32]) SOURCE (16b)
 *	Source VF
 */

#define RVR_E_PF_VF_RESET_EXC_OPCODE_OFFSET 0
#define RVR_E_PF_VF_RESET_EXC_OPCODE_SHIFT 0
#define RVR_E_PF_VF_RESET_EXC_OPCODE_MASK 0xffff
#define RVR_E_PF_VF_RESET_EXC_SOURCE_OFFSET 4
#define RVR_E_PF_VF_RESET_EXC_SOURCE_SHIFT 0
#define RVR_E_PF_VF_RESET_EXC_SOURCE_MASK 0xffff

struct rvr_e_pf_vf_reset_exc {
	u64 opcode:16;
	u64 _reserved_:16;
	u64 source:16;
	u64 _reserved_2:16;
} __packed;

/**********************************************************************
 *				Unions
 **********************************************************************/

union rvr_commands {
	struct rvr_f_ami_hw_configure_cmd f_ami_hw_configure;
	struct rvr_f_ami_hw_disable_cmd f_ami_hw_disable;
	struct rvr_f_ami_hw_enable_cmd f_ami_hw_enable;
	struct rvr_f_ami_hw_reset_cmd f_ami_hw_reset;
	struct rvr_f_ami_hw_save_cmd f_ami_hw_save;
	struct rvr_f_ami_sw_configure_cmd f_ami_sw_configure;
	struct rvr_f_ami_sw_disable_cmd f_ami_sw_disable;
	struct rvr_f_ami_sw_enable_cmd f_ami_sw_enable;
	struct rvr_f_ami_sw_reset_cmd f_ami_sw_reset;
	struct rvr_f_ami_sw_save_cmd f_ami_sw_save;
	struct rvr_f_ams_prof_configure_cmd f_ams_prof_configure;
	struct rvr_f_ams_ring_configure_cmd f_ams_ring_configure;
	struct rvr_f_ams_ring_save_cmd f_ams_ring_save;
	struct rvr_f_ams_trace_configure_cmd f_ams_trace_configure;
	struct rvr_f_probe_cmd f_probe;
	struct rvr_f_prof_table_flush_cmd f_prof_table_flush;
	struct rvr_f_typeb_table_configure_cmd f_typeb_table_configure;
	struct rvr_pf_ami_hw_configure_cmd pf_ami_hw_configure;
	struct rvr_pf_ami_hw_map_cmd pf_ami_hw_map;
	struct rvr_pf_ami_hw_reset_cmd pf_ami_hw_reset;
	struct rvr_pf_ami_hw_save_cmd pf_ami_hw_save;
	struct rvr_pf_ami_hw_unmap_cmd pf_ami_hw_unmap;
	struct rvr_pf_ami_sw_configure_cmd pf_ami_sw_configure;
	struct rvr_pf_ami_sw_map_cmd pf_ami_sw_map;
	struct rvr_pf_ami_sw_reset_cmd pf_ami_sw_reset;
	struct rvr_pf_ami_sw_save_cmd pf_ami_sw_save;
	struct rvr_pf_ami_sw_unmap_cmd pf_ami_sw_unmap;
	struct rvr_pf_ams_ring_configure_cmd pf_ams_ring_configure;
	struct rvr_pf_ams_ring_save_cmd pf_ams_ring_save;
	struct rvr_pf_asn_create_cmd pf_asn_create;
	struct rvr_pf_asn_destroy_cmd pf_asn_destroy;
	struct rvr_pf_f_disable_cmd pf_f_disable;
	struct rvr_pf_f_enable_cmd pf_f_enable;
	struct rvr_pf_probe_cmd pf_probe;
	struct rvr_pf_response_to_vf_cmd pf_response_to_vf;
	struct rvr_vf_command_to_pf_cmd vf_command_to_pf;
};

union rvr_responses {
	struct rvr_f_ami_hw_configure_resp f_ami_hw_configure;
	struct rvr_f_ami_hw_disable_resp f_ami_hw_disable;
	struct rvr_f_ami_hw_enable_resp f_ami_hw_enable;
	struct rvr_f_ami_hw_reset_resp f_ami_hw_reset;
	struct rvr_f_ami_hw_save_resp f_ami_hw_save;
	struct rvr_f_ami_sw_configure_resp f_ami_sw_configure;
	struct rvr_f_ami_sw_disable_resp f_ami_sw_disable;
	struct rvr_f_ami_sw_enable_resp f_ami_sw_enable;
	struct rvr_f_ami_sw_reset_resp f_ami_sw_reset;
	struct rvr_f_ami_sw_save_resp f_ami_sw_save;
	struct rvr_f_ams_prof_configure_resp f_ams_prof_configure;
	struct rvr_f_ams_ring_configure_resp f_ams_ring_configure;
	struct rvr_f_ams_ring_save_resp f_ams_ring_save;
	struct rvr_f_ams_trace_configure_resp f_ams_trace_configure;
	struct rvr_f_probe_resp f_probe;
	struct rvr_f_prof_table_flush_resp f_prof_table_flush;
	struct rvr_f_typeb_table_configure_resp f_typeb_table_configure;
	struct rvr_pf_ami_hw_configure_resp pf_ami_hw_configure;
	struct rvr_pf_ami_hw_map_resp pf_ami_hw_map;
	struct rvr_pf_ami_hw_reset_resp pf_ami_hw_reset;
	struct rvr_pf_ami_hw_save_resp pf_ami_hw_save;
	struct rvr_pf_ami_hw_unmap_resp pf_ami_hw_unmap;
	struct rvr_pf_ami_sw_configure_resp pf_ami_sw_configure;
	struct rvr_pf_ami_sw_map_resp pf_ami_sw_map;
	struct rvr_pf_ami_sw_reset_resp pf_ami_sw_reset;
	struct rvr_pf_ami_sw_save_resp pf_ami_sw_save;
	struct rvr_pf_ami_sw_unmap_resp pf_ami_sw_unmap;
	struct rvr_pf_ams_ring_configure_resp pf_ams_ring_configure;
	struct rvr_pf_ams_ring_save_resp pf_ams_ring_save;
	struct rvr_pf_asn_create_resp pf_asn_create;
	struct rvr_pf_asn_destroy_resp pf_asn_destroy;
	struct rvr_pf_f_disable_resp pf_f_disable;
	struct rvr_pf_f_enable_resp pf_f_enable;
	struct rvr_pf_probe_resp pf_probe;
	struct rvr_pf_response_to_vf_resp pf_response_to_vf;
	struct rvr_vf_command_to_pf_resp vf_command_to_pf;
};

union rvr_exceptions {
	struct rvr_e_f_counter_overflow_exc e_f_counter_overflow;
	struct rvr_e_pf_command_from_vf_exc e_pf_command_from_vf;
	struct rvr_e_pf_vf_reset_exc e_pf_vf_reset;
};

/**********************************************************************
 *				Registers
 **********************************************************************/

/*
 * @0x0 Management page
 *
 */

#define RVR_MANAGEMENT_PAGE_OFFSET 0x0

/*
 * @0x0 TX_DIGEST
 *
 */

#define RVR_TX_DIGEST_OFFSET 0x0

/*
 * @0x0 AMU_IDR
 *
 * [18:18] ASN_PROF (1b)
 *	ASN profiling is supported by this implementation
 * [17:17] TRACING (1b)
 *	Tracing is supported by this implementation
 * [16:12] AMI_TYPE (5b)
 *	AMI type implemented
 *	0b00000: Type A1
 *	0b00001: Type A2
 *	0b00010: Type B
 *	All others values are reserved
 * [11:6] NUM_RX_AMS_M1 (6b)
 *	Number of RX sockets (AMSs) per interface (AMI) minus one
 *	NUM_RX_AMS = NUM_RX_AMS_M1 + 1
 * [5:0] NUM_TX_AMS_M1 (6b)
 *	Number of TX sockets (AMSs) per interface (AMI) minus one
 *	NUM_TX_AMS = NUM_TX_AMS_M1 + 1
 */

#define RVR_AMU_IDR_OFFSET 0x0
#define RVR_AMU_IDR_ASN_PROF_SHIFT 18
#define RVR_AMU_IDR_ASN_PROF_MASK 0x1
#define RVR_AMU_IDR_TRACING_SHIFT 17
#define RVR_AMU_IDR_TRACING_MASK 0x1
#define RVR_AMU_IDR_AMI_TYPE_SHIFT 12
#define RVR_AMU_IDR_AMI_TYPE_MASK 0x1f
#define RVR_AMU_IDR_NUM_RX_AMS_M1_SHIFT 6
#define RVR_AMU_IDR_NUM_RX_AMS_M1_MASK 0x3f
#define RVR_AMU_IDR_NUM_TX_AMS_M1_SHIFT 0
#define RVR_AMU_IDR_NUM_TX_AMS_M1_MASK 0x3f

/*
 * @0x8 TX_DIGEST_MASK
 *
 */

#define RVR_TX_DIGEST_MASK_OFFSET 0x8

/*
 * @0x8 AMU_AIDR
 *
 * [7:4] ArchMajorRev (4b)
 * [3:0] ArchMinorRev (4b)
 */

#define RVR_AMU_AIDR_OFFSET 0x8
#define RVR_AMU_AIDR_ARCHMAJORREV_SHIFT 4
#define RVR_AMU_AIDR_ARCHMAJORREV_MASK 0xf
#define RVR_AMU_AIDR_ARCHMINORREV_SHIFT 0
#define RVR_AMU_AIDR_ARCHMINORREV_MASK 0xf

/*
 * @0x10 AMU_IIDR
 *
 */

#define RVR_AMU_IIDR_OFFSET 0x10

/*
 * @0x18 AMU_CR
 *
 * [18:18] ASN_PROF_EN (1b)
 *	Enable ASN performance profiling for this Function
 * [17:17] TRACE_EN (1b)
 *	Enable AMU generation and delivery of traces to the
 *	Function driver
 * [2:2] VF_TRACE_EN (1b)
 *	Enable AMU generation and delivery of traces
 *	to VF drivers.
 *	This bit is RES0 for VFs.
 * [1:1] AMU_FWD_EN (1b)
 *	Enable forwarding of messages between
 *	the PF and VF drivers.
 *	This bit is RES0 for VFs.
 * [0:0] AMU_EN (1b)
 *	Enable AMU operations. This bit is RES0 for VFs.
 */

#define RVR_AMU_CR_OFFSET 0x18
#define RVR_AMU_CR_ASN_PROF_EN_SHIFT 18
#define RVR_AMU_CR_ASN_PROF_EN_MASK 0x1
#define RVR_AMU_CR_TRACE_EN_SHIFT 17
#define RVR_AMU_CR_TRACE_EN_MASK 0x1
#define RVR_AMU_CR_VF_TRACE_EN_SHIFT 2
#define RVR_AMU_CR_VF_TRACE_EN_MASK 0x1
#define RVR_AMU_CR_AMU_FWD_EN_SHIFT 1
#define RVR_AMU_CR_AMU_FWD_EN_MASK 0x1
#define RVR_AMU_CR_AMU_EN_SHIFT 0
#define RVR_AMU_CR_AMU_EN_MASK 0x1

/*
 * @0x20 AMU_SR
 *
 */

#define RVR_AMU_SR_OFFSET 0x20

/*
 * @0x28 MGT_RX_VECTOR
 *
 * [10:0] RX_VECTOR (11b)
 *	MSI-X vector number for management AMI Rx AMSs
 */

#define RVR_MGT_RX_VECTOR_OFFSET 0x28
#define RVR_MGT_RX_VECTOR_RX_VECTOR_SHIFT 0
#define RVR_MGT_RX_VECTOR_RX_VECTOR_MASK 0x7ff

/*
 * @0x30 MGT_TX_VECTOR
 *
 * [10:0] TX_VECTOR (11b)
 *	MSI-X vector number for management AMI Tx AMSs
 */

#define RVR_MGT_TX_VECTOR_OFFSET 0x30
#define RVR_MGT_TX_VECTOR_TX_VECTOR_SHIFT 0
#define RVR_MGT_TX_VECTOR_TX_VECTOR_MASK 0x7ff

/*
 * @0x40 MGT_RX_IRQ_CTRL
 *
 * [0:0] Enable (1b)
 *	Controls interrupt generation for the Rx management Sockets
 *	0: interrupt disabled
 *	1: interrupt enabled (and is also subject to RX_DIGEST_MASK)
 */

#define RVR_MGT_RX_IRQ_CTRL_OFFSET 0x40
#define RVR_MGT_RX_IRQ_CTRL_ENABLE_SHIFT 0
#define RVR_MGT_RX_IRQ_CTRL_ENABLE_MASK 0x1

/*
 * @0x48 MGT_TX_IRQ_CTRL
 *
 * [0:0] Enable (1b)
 *	Controls interrupt generation for the Tx management Sockets
 *	0: interrupt disabled
 *	1: interrupt enabled (and is also subject to TX_DIGEST_MASK)
 */

#define RVR_MGT_TX_IRQ_CTRL_OFFSET 0x48
#define RVR_MGT_TX_IRQ_CTRL_ENABLE_SHIFT 0
#define RVR_MGT_TX_IRQ_CTRL_ENABLE_MASK 0x1

/*
 * @0x50 MGT_TRACE_RX_CTRL
 *
 * [0:0] RX_MODE (1b)
 *	Controls Trace management Socket ring operating mode
 *	0: Back-pressure
 *	1: Overwriting
 */

#define RVR_MGT_TRACE_RX_CTRL_OFFSET 0x50
#define RVR_MGT_TRACE_RX_CTRL_RX_MODE_SHIFT 0
#define RVR_MGT_TRACE_RX_CTRL_RX_MODE_MASK 0x1

/*
 * @0x60 MSK_BASE_PTR
 *
 */

#define RVR_MSK_BASE_PTR_OFFSET 0x60

/*
 * @0x68 MSK_CTRL
 *
 * [11:8] THRESHOLD (4b)
 *	Controls the change of DIGEST bits
 * [7:4] LOG2_MSG_LENGTH (4b)
 *	Maximum size of messages in Doublewords as log~2~(MSG_LENGTH)
 * [3:0] LOG2_SIZE (4b)
 *	Size of the ring in slots as log~2~(SIZE)
 */

#define RVR_MSK_CTRL_OFFSET 0x68
#define RVR_MSK_CTRL_THRESHOLD_SHIFT 8
#define RVR_MSK_CTRL_THRESHOLD_MASK 0xf
#define RVR_MSK_CTRL_LOG2_MSG_LENGTH_SHIFT 4
#define RVR_MSK_CTRL_LOG2_MSG_LENGTH_MASK 0xf
#define RVR_MSK_CTRL_LOG2_SIZE_SHIFT 0
#define RVR_MSK_CTRL_LOG2_SIZE_MASK 0xf

/*
 * @0x400 READ_INDEX_TX0
 *
 */

#define RVR_READ_INDEX_TX0_OFFSET 0x400

/*
 * @0x408 READ_INDEX_TX1
 *
 */

#define RVR_READ_INDEX_TX1_OFFSET 0x408

/*
 * @0x5c0 READ_INDEX_TX63
 *
 */

#define RVR_READ_INDEX_TX63_OFFSET 0x5c0

/*
 * @0x600 WRITE_INDEX_TX0
 *
 */

#define RVR_WRITE_INDEX_TX0_OFFSET 0x600

/*
 * @0x608 WRITE_INDEX_TX1
 *
 */

#define RVR_WRITE_INDEX_TX1_OFFSET 0x608

/*
 * @0x7f8 WRITE_INDEX_TX63
 *
 */

#define RVR_WRITE_INDEX_TX63_OFFSET 0x7f8

/*
 * @0x800 RX_DIGEST
 *
 */

#define RVR_RX_DIGEST_OFFSET 0x800

/*
 * @0x808 RX_DIGEST_MASK
 *
 */

#define RVR_RX_DIGEST_MASK_OFFSET 0x808

/*
 * @0xc00 READ_INDEX_RX0
 *
 */

#define RVR_READ_INDEX_RX0_OFFSET 0xc00

/*
 * @0xc08 READ_INDEX_RX1
 *
 */

#define RVR_READ_INDEX_RX1_OFFSET 0xc08

/*
 * @0xdf8 READ_INDEX_RX63
 *
 */

#define RVR_READ_INDEX_RX63_OFFSET 0xdf8

/*
 * @0xe00 WRITE_INDEX_RX0
 *
 */

#define RVR_WRITE_INDEX_RX0_OFFSET 0xe00

/*
 * @0xe08 WRITE_INDEX_RX1
 *
 */

#define RVR_WRITE_INDEX_RX1_OFFSET 0xe08

/*
 * @0xff8 WRITE_INDEX_RX63
 *
 */

#define RVR_WRITE_INDEX_RX63_OFFSET 0xff8

/*
 * @0x1000 MGT_TX_DIGEST
 *
 */

#define RVR_MGT_TX_DIGEST_OFFSET 0x1000

/*
 * @0x1008 MGT_TX_DIGEST_MASK
 *
 */

#define RVR_MGT_TX_DIGEST_MASK_OFFSET 0x1008

/*
 * @0x1400 MGT_READ_INDEX_TX0
 *
 */

#define RVR_MGT_READ_INDEX_TX0_OFFSET 0x1400

/*
 * @0x1600 MGT_WRITE_INDEX_TX0
 *
 */

#define RVR_MGT_WRITE_INDEX_TX0_OFFSET 0x1600

/*
 * @0x1800 MGT_RX_DIGEST
 *
 */

#define RVR_MGT_RX_DIGEST_OFFSET 0x1800

/*
 * @0x1808 MGT_RX_DIGEST_MASK
 *
 */

#define RVR_MGT_RX_DIGEST_MASK_OFFSET 0x1808

/*
 * @0x1c00 MGT_READ_INDEX_RX0
 *
 */

#define RVR_MGT_READ_INDEX_RX0_OFFSET 0x1c00

/*
 * @0x1c08 MGT_READ_INDEX_RX1
 *
 */

#define RVR_MGT_READ_INDEX_RX1_OFFSET 0x1c08

/*
 * @0x1c10 READ_INDEX_RX2
 *
 */

#define RVR_READ_INDEX_RX2_OFFSET 0x1c10

/*
 * @0x1e00 MGT_WRITE_INDEX_RX0
 *
 */

#define RVR_MGT_WRITE_INDEX_RX0_OFFSET 0x1e00

/*
 * @0x1e08 MGT_WRITE_INDEX_RX1
 *
 */

#define RVR_MGT_WRITE_INDEX_RX1_OFFSET 0x1e08

/*
 * @0x1e10 WRITE_INDEX_RX2
 *
 */

#define RVR_WRITE_INDEX_RX2_OFFSET 0x1e10

/*
 * @0x10000 AMI-SW page #0
 *
 */

#define RVR_AMI_SW_PAGE_0_OFFSET 0x10000

#endif /* _REVERE_H_INCLUDED */
