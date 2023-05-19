/* Infineon WLAN driver: Target Wake Time (TWT) Header
 *
 * Copyright 2023 Cypress Semiconductor Corporation (an Infineon company)
 * or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
 * This software, including source code, documentation and related materials
 * ("Software") is owned by Cypress Semiconductor Corporation or one of its
 * affiliates ("Cypress") and is protected by and subject to
 * worldwide patent protection (United States and foreign),
 * United States copyright laws and international treaty provisions.
 * Therefore, you may use this Software only as provided in the license agreement
 * accompanying the software package from which you obtained this Software ("EULA").
 * If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software source code
 * solely for use in connection with Cypress's integrated circuit products.
 * Any reproduction, modification, translation, compilation, or representation
 * of this Software except as specified above is prohibited without
 * the expresswritten permission of Cypress.
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * Cypress reserves the right to make changes to the Software without notice.
 * Cypress does not assume any liability arising out of the application or
 * use of the Software or any product or circuit described in the Software.
 * Cypress does not authorize its products for use in any products where a malfunction
 * or failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product").
 * By including Cypress's product in a High Risk Product, the manufacturer
 * of such system or application assumes all risk of such use and in doing so
 * agrees to indemnify Cypress against all liability.
 */

#ifndef BRCMF_TWT_H
#define BRCMF_TWT_H

#include "core.h"

/* Min TWT Default Unit */
#define WAKE_DUR_UNIT_DEF 256
/* Min TWT Unit in TUs */
#define WAKE_DUR_UNIT_TU 1024

/**
 * enum brcmf_twt_cmd - TWT iovar subcmds handled by firmware TWT module
 *
 * @BRCMF_TWT_CMD_ENAB: Enable the firmware TWT module.
 * @BRCMF_TWT_CMD_SETUP: Setup a TWT session with a TWT peer.
 * @BRCMF_TWT_CMD_TEARDOWN: Teardown the active TWT session with a TWT peer.
 */
enum brcmf_twt_cmd {
	BRCMF_TWT_CMD_ENAB,
	BRCMF_TWT_CMD_SETUP,
	BRCMF_TWT_CMD_TEARDOWN,
};

/* TWT iovar subcmd version */
#define BRCMF_TWT_SETUP_VER 0u
#define BRCMF_TWT_TEARDOWN_VER 0u

/**
 * enum brcmf_twt_flow_flag - TWT flow flags to be used in TWT iovar setup subcmd
 *
 * @BRCMF_TWT_FLOW_FLAG_BROADCAST: Broadcast TWT Session.
 * @BRCMF_TWT_FLOW_FLAG_IMPLICIT: Implcit TWT session type.
 * @BRCMF_TWT_FLOW_FLAG_UNANNOUNCED: Unannounced TWT session type.
 * @BRCMF_TWT_FLOW_FLAG_TRIGGER: Trigger based TWT Session type.
 * @BRCMF_TWT_FLOW_FLAG_WAKE_TBTT_NEGO: Wake TBTT Negotiation type.
 * @BRCMF_TWT_FLOW_FLAG_REQUEST: TWT Session setup requestor.
 * @BRCMF_TWT_FLOW_FLAG_RESPONDER_PM: Not used.
 * @BRCMF_TWT_FLOW_FLAG_UNSOLICITED: Unsolicited TWT Session Setup.
 * @BRCMF_TWT_FLOW_FLAG_PROTECT: Specifies whether Tx within SP is protected, Not used.
 */
enum brcmf_twt_flow_flag {
	BRCMF_TWT_FLOW_FLAG_BROADCAST = BIT(0),
	BRCMF_TWT_FLOW_FLAG_IMPLICIT = BIT(1),
	BRCMF_TWT_FLOW_FLAG_UNANNOUNCED = BIT(2),
	BRCMF_TWT_FLOW_FLAG_TRIGGER = BIT(3),
	BRCMF_TWT_FLOW_FLAG_WAKE_TBTT_NEGO = BIT(4),
	BRCMF_TWT_FLOW_FLAG_REQUEST = BIT(5),
	BRCMF_TWT_FLOW_FLAG_RESPONDER_PM = BIT(6),
	BRCMF_TWT_FLOW_FLAG_UNSOLICITED = BIT(7),
	BRCMF_TWT_FLOW_FLAG_PROTECT = BIT(8)
};

/**
 * TWT IE (sec 9.4.2.200)
 */

/* TWT element - top (Figure 9-589av) */
struct brcmf_twt_ie_top {
	u8 id;
	u8 len;
	u8 ctrl; /* Control */
};

/* S1G Action IDs */
#define S1G_ACTION_TWT_SETUP 6u
#define S1G_ACTION_TWT_TEARDOWN 7u
#define S1G_ACTION_TWT_INFO 11u

/* S1G Action frame offsets */
#define S1G_AF_CAT_OFF 0u
#define S1G_AF_ACT_OFF 1u

/* TWT Setup */
#define S1G_AF_TWT_SETUP_TOKEN_OFF 2u
#define S1G_AF_TWT_SETUP_TWT_IE_OFF 3u

/* TWT Teardown */
#define S1G_AF_TWT_TEARDOWN_FLOW_OFF 2u

/* TWT Information */
#define S1G_AF_TWT_INFO_OFF 2u

#define BRCMF_TWT_BCAST_WAKE_TIME_OFFSET 10u
#define BRCMF_TWT_BCAST_WAKE_TIME_SHIFT 10u
#define BRCMF_TWT_BCAST_WAKE_TIME_MASK 0x03FFFC00u
#define BRCMF_TWT_BCAST_WAKE_TIME_ZERO_BIT_SZ 10u

/* Control field (Figure 9-589aw) */
#define BRCMF_TWT_CTRL_NDP_PAGING_IND 0x01u /* NDP Paging Indication */
#define BRCMF_TWT_CTRL_RESP_PM_MODE 0x02u /* Respondor PM Mode */
#define BRCMF_TWT_CTRL_NEGO_TYPE_IDX 2u
#define BRCMF_TWT_CTRL_NEGO_TYPE_MASK 0x0Cu /* TWT Negotiation Type */
#define BRCMF_TWT_CTRL_NEGO_TYPE_SHIFT 2u
#define BRCMF_TWT_CTRL_INFO_FRM_DISABLED 0x10u /* TWT info frame disabled */
#define BRCMF_TWT_CTRL_WAKEDUR_UNIT 0x20u /* Wake duration unit */

/* TWT Negotiation Type (Table 9-262j1) */
enum brcmf_twt_ctrl_nego_type {
	BRCMF_TWT_CTRL_NEGO_TYPE_ITWT = 0, /* Individual TWT Setup */
	BRCMF_TWT_CTRL_NEGO_TYPE_WAKE_TBTT = 1, /* Wake TBTT Negotiation */
	BRCMF_TWT_CTRL_NEGO_TYPE_BTWT_IE_BCN =
		2, /* Broadcast TWT IE in Beacon */
	BRCMF_TWT_CTRL_NEGO_TYPE_BTWT = 3, /* Broadcast TWT memberships */
};

/* Request Type field (Figure 9-589ay) */
#define BRCMF_TWT_REQ_TYPE_REQUEST 0x0001u /* Request */
#define BRCMF_TWT_REQ_TYPE_SETUP_CMD_MASK 0x000eu /* Setup Command */
#define BRCMF_TWT_REQ_TYPE_SETUP_CMD_SHIFT 1u
#define BRCMF_TWT_REQ_TYPE_TRIGGER 0x0010u /* Trigger */
#define BRCMF_TWT_REQ_TYPE_IMPLICIT 0x0020u /* Implicit */
#define BRCMF_TWT_REQ_TYPE_LAST_BCAST_PARAM \
	0x0020u /* Last Broadcast Parameter Set */
#define BRCMF_TWT_REQ_TYPE_FLOW_TYPE 0x0040u /* Flow Type */
#define BRCMF_TWT_REQ_TYPE_FLOW_ID_MASK 0x0380u /* Flow Identifier */
#define BRCMF_TWT_REQ_TYPE_FLOW_ID_SHIFT 7u
#define BRCMF_TWT_REQ_TYPE_BTWT_RECOMM_MASK \
	0x0380u /* Broadcast TWT Recommendation */
#define BRCMF_TWT_REQ_TYPE_BTWT_RECOMM_SHIFT 7u
#define BRCMF_TWT_REQ_TYPE_WAKE_EXP_MASK 0x7c00u /* Wake Interval Exponent */
#define BRCMF_TWT_REQ_TYPE_WAKE_EXP_SHIFT 10u
#define BRCMF_TWT_REQ_TYPE_PROTECTION 0x8000u /* Protection */

/* Set,p Command field (Table 9-262k) */
enum brcmf_twt_setup_cmd {
	BRCMF_TWT_SETUP_CMD_REQUEST_TWT = 0, /* Request TWT */
	BRCMF_TWT_SETUP_CMD_SUGGEST_TWT = 1, /* Suggest TWT */
	BRCMF_TWT_SETUP_CMD_DEMAND_TWT = 2, /* Demand TWT */
	BRCMF_TWT_SETUP_CMD_GROUPING_TWT = 3, /* Grouping TWT */
	BRCMF_TWT_SETUP_CMD_ACCEPT_TWT = 4, /* Accept TWT */
	BRCMF_TWT_SETUP_CMD_ALTERNATE_TWT = 5, /* Alternate TWT */
	BRCMF_TWT_SETUP_CMD_DICTATE_TWT = 6, /* Dictate TWT */
	BRCMF_TWT_SETUP_CMD_REJECT_TWT = 7, /* Reject TWT */
};

/* Broadcast TWT Recommendation field (Table 9-262k1) */
#define BRCMF_TWT_BCAST_FRAME_RECOMM_0 \
	0u /* No constrains on frames in Broadcast TWT SP */
#define BRCMF_TWT_BCAST_FRAME_RECOMM_1 \
	1u /* Do not contain RUs for random access */
#define BRCMF_TWT_BCAST_FRAME_RECOMM_2 \
	2u /* Can contain RUs for random access */
#define BRCMF_TWT_BCAST_FRAME_RECOMM_3 3u

/* Target Wake Time - 8 octets or 0 octet */
typedef u64 twt_target_wake_time_t; /* 64 bit TSF time of TWT Responding STA */
typedef u16 twt_bcast_wake_time_t; /* 16 bit Wake Time of Bcast scheduling STA */
typedef u16 twt_bcast_twt_info_t; /* 16 bit Broadcast TWT Info subfield */

/* TWT Group Assignment Info - 9 octets (long format) or 3 octets (short format) or 0 octet */
/* Group Assignment Info field - short format - Zero Offset Preset field is 0 */
struct brcmf_twt_grp_short {
	u8 grpid_n_0off; /* Group ID and Zero Offset Present */
	u16 unit_n_off; /* TWT Unit and TWT Offset */
};

/* Group Assignment Info field - long format - Zero Offset Preset field is 1 */
#define BRCMF_TWT_ZERO_OFF_GRP_LEN 6u
struct brcmf_twt_grp_long {
	u8 grpid_n_0off; /* Group ID and Zero Offset Present */
	u8 grp_0off[BRCMF_TWT_ZERO_OFF_GRP_LEN]; /* Zero Offset of Group */
	u16 unit_n_off; /* Unit and Offset */
};

/* TWT Unit and TWT Offset field */
#define BRCMF_TWT_UNIT_MASK 0x000fu /* TWT Unit */
#define BRCMF_TWT_OFFSET_MASK 0xfff0u /* TWT Offset */
#define BRCMF_TWT_OFFSET_SHIFT 4u

/* TWT Unit field (table 8-248m) */
#define BRCMF_TWT_UNIT_32us 0u
#define BRCMF_TWT_UNIT_256us 1u
#define BRCMF_TWT_UNIT_1024us 2u
#define BRCMF_TWT_UNIT_8ms192us 3u
#define BRCMF_TWT_UNIT_32ms768us 4u
#define BRCMF_TWT_UNIT_262ms144us 5u
#define BRCMF_TWT_UNIT_1s048576us 6u
#define BRCMF_TWT_UNIT_8s388608us 7u
#define BRCMF_TWT_UNIT_33s554432us 8u
#define BRCMF_TWT_UNIT_268s435456us 9u
#define BRCMF_TWT_UNIT_1073s741824us 10u
#define BRCMF_TWT_UNIT_8589s934592us 11u

/* TWT element - bottom */
struct brcmf_twt_ie_itwt_bottom {
	u8 nom_wake_dur; /* Nominal Minimum Wake Duration */
	u16 wake_int_mant; /* TWT Wake Interval Mantissa */
	u8 channel; /* TWT Channel */
	/* NDP Paging field */
};

/* Target Wake Time - 8 octets or 0 octet */
typedef u64 twt_target_wake_time_t; /* 64 bit TSF time of TWT Responding STA */
typedef u16 twt_bcast_wake_time_t; /* 16 bit Wake Time of Bcast scheduling STA */
typedef u16 twt_bcast_twt_info_t; /* 16 bit Broadcast TWT Info subfield */

/* TWT element - bottom */
struct brcmf_twt_ie_btwt_bottom {
	u8 nom_wake_dur; /* Nominal Minimum Wake Duration */
	u16 wake_int_mant; /* TWT Wake Interval Mantissa */
	u16 btwt_info; /* Broadcast TWT Info */
	/* NDP Paging field */
};

/* Request Type subfield - 2 octets */
typedef u16 twt_request_type_t; /* 16 bit request type */

/* TWT IE structure for broadcast TWT */
struct brcmf_twt_last_bcast_ie {
	struct brcmf_twt_ie_top top; /* Element id, len, control fields */
	u16 req_type; /* request type field */
	u16 twt; /* twt field */
	struct brcmf_twt_ie_btwt_bottom btwt_bottom; /* wake dur, int, BID Info */
};
/* Nominal Minimum Wake Duration */
#define BRCMF_TWT_WAKE_DUR_UNIT_256us \
	256u /* Nom.Min. Wake Duration is in 256us units */
#define BRCMF_TWT_WAKE_DUR_UNIT_1ms \
	1024u /* Nom. Min. Wake Duration is in 1ms units */

/* to be deprecated */
#define BRCMF_TWT_NOM_WAKE_DUR_UNIT \
	256u /* Nominal Minimum Wake Duration is in 256us units */

/* TWT IE field lengths */
#define BRCMF_TWT_IE_NOM_MIN_TWT_WK_DUR_SZ 1u /* 1 byte */
#define BRCMF_TWT_IE_TWT_WAKE_INT_MANT_SZ 2u /* 2 bytes */
#define BRCMF_TWT_IE_BCAST_TWT_INFO_SZ 2u /* 2 byte */
#define BRCMF_TWT_IE_TWT_CHANNEL_SZ 1u /* 1 byte */

/* Broadcast TWT info subfield format (figure 9-589ay1) */
#define BRCMF_TWT_BTWT_PERSIST_EXPO_MASK \
	0x0007u /* Broadcast TWT Persistence Exponent */
#define BRCMF_TWT_BCAST_TWT_ID_MASK 0x00F8u /* Broadcast TWT ID */
#define BRCMF_TWT_BCAST_TWT_ID_SHIFT 3u
#define BRCMF_TWT_BTWT_PERSIST_MANT_MASK \
	0xFF00u /* Broadcast TWT Persistence Mantissa */
#define BRCMF_TWT_BTWT_PERSIST_MANT_SHIFT 8u

#define BRCMF_TWT_BTWT_PERSIST_INDEFINITE 0xFFu

/* NDP Paging field - 4 octets or 0 octet */
typedef u32 twt_ndp_paging_t;

#define BRCMF_TWT_NDP_PAGING_PID 0x000001ffu /* P-ID */
#define BRCMF_TWT_NDP_PAGING_MAX_PERIOD 0x0001fe00u /* Max NDP Paging Period */
#define BRCMF_TWT_NDP_PAGING_PART_TSF_OFF 0x001e0000u /* Partial TSF Offset */
#define BRCMF_TWT_NDP_PAGING_ACTION 0x00e00000u /* Action */
#define BRCMF_TWT_NDP_PAGING_MIN_SLEEP 0x3f000000u /* Min Sleep Duration */

/* Action field (table 8-248n) */
#define BRCMF_TWT_ACTION_SEND_PSP_TRIG \
	0u /* Send a PS-Poll or uplink trigger frame */
#define BRCMF_TWT_ACTION_WAKE_MIN_SLEEP \
	1u /* Wake up at the time indicated by
						 * Min Sleep Duration
						 */
#define BRCMF_TWT_ACTION_WAKE_RCV_BCN 2u /* Wake up to receive the Beacon */
#define BRCMF_TWT_ACTION_WAKE_RCV_DTIM \
	3u /* Wake up to receive the DTIM Beacon */
#define BRCMF_TWT_ACTION_WAKE_IND_TIME \
	4u /* Wakeup at the time indicated by the sum of
						 * the Min Sleep Duration field and the ASD subfield
						 * in the APDI field of the NDP Paging frame
						 */

/* TWT Teardown for Negotiation type 0 or 1 */
#define BRCMF_TWT_TEARDOWN_FLOW_ID_MASK 0x07u
/* TWT Teardown for Negotiation type 3 */
#define BRCMF_TWT_TEARDOWN_BTWT_ID_MASK 0x1Fu

#define BRCMF_TWT_TEARDOWN_NEGO_TYPE_MASK 0x60u
#define BRCMF_TWT_TEARDOWN_NEGO_TYPE_SHIFT 5u
/* Teardown All TWT indication */
#define BRCMF_TWT_TEARDOWN_ALL_TWT 0x80u

/* TWT Information field byte 0 */
#define BRCMF_TWT_INFO_FLOW_ID_MASK 0x07u
#define BRCMF_TWT_INFO_RESP_REQ 0x08u
#define BRCMF_TWT_INFO_NEXT_TWT_REQ 0x10u
#define BRCMF_TWT_INFO_NEXT_TWT_SIZE_MASK 0x60u
#define BRCMF_TWT_INFO_NEXT_TWT_SIZE_SHIFT 0x5u
#define BRCMF_TWT_INFO_ALL_TWT 0x80u

/* Next TWT Subfield Size field encoding */
#define BRCMF_TWT_INFO_NEXT_TWT_SIZE_0_IDX 0u /* 0 byte */
#define BRCMF_TWT_INFO_NEXT_TWT_SIZE_32_IDX 1u /* 4 bytes */
#define BRCMF_TWT_INFO_NEXT_TWT_SIZE_48_IDX 2u /* 6 bytes */
#define BRCMF_TWT_INFO_NEXT_TWT_SIZE_64_IDX 3u /* 8 bytes */

/* Next TWT Subfield Size field */
#define BRCMF_TWT_INFO_NEXT_TWT_SIZE_0 0u /* 0 byte */
#define BRCMF_TWT_INFO_NEXT_TWT_SIZE_32 4u /* 4 bytes */
#define BRCMF_TWT_INFO_NEXT_TWT_SIZE_48 6u /* 6 bytes */
#define BRCMF_TWT_INFO_NEXT_TWT_SIZE_64 8u /* 8 bytes */

/**
 * enum brcmf_twt_session_state - TWT session state in the Host driver list
 *
 * @BRCMF_TWT_SESS_STATE_UNSPEC: Reserved value 0.
 * @BRCMF_TWT_SESS_STATE_SETUP_INPROGRESS: TWT session setup request was sent
 *	to the Firmware.
 * @BRCMF_TWT_SESS_STATE_SETUP_COMPLETE: TWT session setup is complete and received
 * 	setup event from the Firmweare.
 * @BRCMF_TWT_SESS_STATE_TEARDOWN_INPROGRESS: TWT session teardown request was sent
 *	to the Firmware.
 * @BRCMF_TWT_SESS_STATE_TEARDOWN_COMPLETE: TWT session teardown is complete and
 *	received Teardown event from the Firmware.
 * @BRCMF_TWT_SESS_STATE_MAX: This acts as a the tail of state list.
 *      Make sure it located at the end of the list.
 */
enum brcmf_twt_session_state {
	BRCMF_TWT_SESS_STATE_UNSPEC,
	BRCMF_TWT_SESS_STATE_SETUP_INPROGRESS,
	BRCMF_TWT_SESS_STATE_SETUP_COMPLETE,
	BRCMF_TWT_SESS_STATE_TEARDOWN_INPROGRESS,
	BRCMF_TWT_SESS_STATE_TEARDOWN_COMPLETE,
	BRCMF_TWT_SESS_STATE_MAX
};

/**
 * struct brcmf_twt_params - TWT session parameters
 *
 * @twt_oper: TWT operation, Refer enum brcmf_twt_cmd.
 * @negotiation_type: Negotiation Type, Refer enum brcmf_twt_ctrl_nego_type.
 * @setup_cmd: Setup cmd, Refer enum brcmf_twt_setup_cmd_type.
 * @dialog_token: TWT Negotiation Dialog Token.
 * @twt: Target Wake Time.
 * @twt_offset: Target Wake Time Offset.
 * @min_twt: Nominal Minimum Wake Duration.
 * @exponent: Wake Interval Exponent.
 * @mantissa: Wake Interval Mantissa.
 * @requestor: TWT Session requestor or responder.
 * @implicit: implicit or Explicit TWT session.
 * @flow_type: Announced or Un-Announced TWT session.
 * @flow_id: Flow ID.
 * @bcast_twt_id: Broadcast TWT ID.
 * @protection: Protection, Not used.
 * @twt_channel: TWT Channel, Not used.
 * @twt_info_frame_disabled: TWT information frame disabled, Not used.
 * @min_twt_unit: Nominal Minimum Wake Duration Unit.
 * @teardown_all_twt: Teardown All TWT.
 */
struct brcmf_twt_params {
	enum brcmf_twt_cmd twt_oper;
	enum brcmf_twt_ctrl_nego_type negotiation_type;
	enum brcmf_twt_setup_cmd setup_cmd;
	u8 dialog_token;
	u64 twt;
	u64 twt_offset;
	u8 min_twt;
	u8 exponent;
	u16 mantissa;
	u8 requestor;
	u8 trigger;
	u8 implicit;
	u8 flow_type;
	u8 flow_id;
	u8 bcast_twt_id;
	u8 protection;
	u8 twt_channel;
	u8 twt_info_frame_disabled;
	u8 min_twt_unit;
	u8 teardown_all_twt;
};

/**
 * struct brcmf_twt_session - TWT session structure.
 *
 * @ifidx: interface index.
 * @bsscfgidx: bsscfg index.
 * @peer: TWT peer address.
 * @state: TWT session state, refer enum brcmf_twt_session_state.
 * @twt_params: TWT session parameters.
 * @list: linked list.
 */
struct brcmf_twt_session {
	u8 ifidx;
	s32 bsscfgidx;
	u8 peer_addr[ETH_ALEN];
	enum brcmf_twt_session_state state;
	struct brcmf_twt_params twt_params;
	struct list_head list;
};

/**
 * enum brcmf_twt_wake_time_type - Type of the struct members wake_time_{h/l} in the
 *	TWT Setup descriptor struct brcmf_twt_sdesc.
 *
 * @BRCMF_TWT_WAKE_TIME_TYPE_BSS: wake_time_{h/l} is the BSS TSF tiume.
 * @BRCMF_TWT_WAKE_TIME_TYPE_OFFSET: wake_time_{h/l} is an offset of TSF time
 *	when the iovar is processed.
 * @BRCMF_TWT_WAKE_TIME_TYPE_AUTO: The target wake time is chosen internally by the Firmware.
 */
enum brcmf_twt_wake_time_type {
	BRCMF_TWT_WAKE_TIME_TYPE_BSS,
	BRCMF_TWT_WAKE_TIME_TYPE_OFFSET,
	BRCMF_TWT_WAKE_TIME_TYPE_AUTO
};

/**
 * struct brcmf_twt_sdesc - TWT Setup Descriptor.
 *
 * @setup_cmd: Setup command and event type. Refer enum ifx_twt_oper_setup_cmd_type.
 * @flow_flags: Flow attributes, Refer enum brcmf_twt_flow_flag.
 * @flow_id: Flow ID, Range 0-7. Set to 0xFF for auto assignment.
 * @wake_type: wake_time_{h/l} type, Refer enum brcmf_twt_wake_time_type.
 * @wake_time_h: Target Wake Time, high 32 bits.
 * @wake_time_l: Target Wake Time, Low 32 bits.
 * @wake_dur: Target Wake Duration in unit of uS.
 * @wake_int: Target Wake Interval.
 * @btwt_persistence: Broadcast TWT Persistence.
 * @wake_int_max: Max Wake interval(uS) for TWT.
 * @duty_cycle_min: Min Duty cycle for TWT(Percentage).
 * @pad: 1 byte pad.
 * @bid: Brodacst TWT ID, Range 0-31. Set to 0xFF for auto assignment.
 * @channel: TWT channel - Not used.
 * @negotiation_type: Negotiation Type, Refer enum ifx_twt_param_nego_type.
 * @frame_recomm: Frame recommendation for broadcast TWTs - Not used.
 */
struct brcmf_twt_sdesc {
	u8 setup_cmd;
	u8 flow_flags;
	u8 flow_id;
	u8 wake_type;
	__le32 wake_time_h;
	__le32 wake_time_l;
	__le32 wake_dur;
	__le32 wake_int;
	__le32 btwt_persistence;
	__le32 wake_int_max;
	u8 duty_cycle_min;
	u8 pad;
	u8 bid;
	u8 channel;
	u8 negotiation_type;
	u8 frame_recomm;
};

/**
 * struct brcmf_twt_setup_event - TWT Setup Completion event data from firmware TWT module
 *
 * @version: Structure version.
 * @length:the byte count of fields from 'dialog' onwards.
 * @dialog: the dialog token user supplied to the TWT setup API.
 * @pad: 3 byte Pad.
 * @status: Event status.
 */
struct brcmf_twt_setup_event {
	u16 version;
	u16 length;
	u8 dialog;
	u8 pad[3];
	s32 status;
        /* enum brcmf_twt_sdesc sdesc; */
};

/**
 * struct brcmf_twt_setup_oper - TWT iovar Setup operation subcmd data to firmware TWT module
 *
 * @version: Structure version.
 * @length: data length (starting after this field).
 * @peer: TWT peer address.
 * @pad: 2 byte Pad.
 * @sdesc: TWT setup descriptor.
 */
struct brcmf_twt_setup_oper {
	u16 version;
	u16 length;
	u8 peer[ETH_ALEN];
	u8 pad[2];
	struct brcmf_twt_sdesc sdesc;
};

/**
 * struct brcmf_twt_teardesc - TWT Teardown descriptor.
 *
 * @negotiation_type: Negotiation Type: Refer enum ifx_twt_param_nego_type.
 * @flow_id: Flow ID: Range 0-7. Set to 0xFF for auto assignment.
 * @bid: Brodacst TWT ID: Range 0-31. Set to 0xFF for auto assignment.
 * @alltwt: Teardown all TWT sessions: set to 0 or 1.
 */
struct brcmf_twt_teardesc {
	u8 negotiation_type;
	u8 flow_id;
	u8 bid;
	u8 alltwt;
};

/**
 * struct brcmf_twt_teardown_event - TWT Teardown Completion event data from firmware TWT module.
 *
 * @version: structure version.
 * @length: the byte count of fields from 'status' onwards.
 * @status: Event status.
 */
struct brcmf_twt_teardown_event {
	u16 version;
	u16 length;
	s32 status;
	/* enum ifx_twt_teardesc teardesc; */
};

/**
 * struct brcmf_twt_teardown_oper - TWT iovar Teardown operation subcmd data to firmware TWT module.
 *
 * @version: structure version.
 * @length: data length (starting after this field).
 * @peer: TWT peer address.
 * @teardesc: TWT Teardown descriptor.
 */
struct brcmf_twt_teardown_oper {
	u16 version;
	u16 length;
	u8 peer[ETH_ALEN];
	struct brcmf_twt_teardesc teardesc;
};

/**
 * brcmf_twt_debugfs_create() - create debugfs entries.
 *
 * @drvr: driver instance.
 */
void brcmf_twt_debugfs_create(struct brcmf_pub *drvr);

/**
 * brcmf_twt_cleanup_sessions - Cleanup the TWT sessions from the driver list.
 *
 * @ifp: interface instatnce.
 */
s32 brcmf_twt_cleanup_sessions(struct brcmf_if *ifp);

/**
 * brcmf_notify_twt_event() - Handle the TWT Event notifications from Firmware.
 *
 * @ifp: interface instatnce.
 * @e: event message.
 * @data: payload of message, contains TWT session data.
 */
int brcmf_notify_twt_event(struct brcmf_if *ifp, const struct brcmf_event_msg *e,
			  void *data);

/**
 * brcmf_twt_oper() - Handle the TWT Operation requests from Userspace.
 *
 * @wiphy: wiphy object for cfg80211 interface.
 * @wdev: wireless device.
 * @twt_params: TWT session parameters.
 */
int brcmf_twt_oper(struct wiphy *wiphy, struct wireless_dev *wdev,
		   struct brcmf_twt_params twt_params);

#endif /* BRCMF_TWT_H */
