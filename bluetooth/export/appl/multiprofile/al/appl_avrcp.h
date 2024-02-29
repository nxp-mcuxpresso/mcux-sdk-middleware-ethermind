

/**
 *  \file appl_avrcp.h
 *
 *  Header file for AVRCP command line applicaiton for both CT & TG roles.
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_APPL_AVRCP_
#define _H_APPL_AVRCP_

/* --------------------------------------------- Header File Inclusion */
#include "BT_hci_api.h"
#include "BT_sdp_api.h"
#include "BT_avrcp_al_api.h"
#include "appl_common.h"


/* --------------------------------------------- Global Definitions */

/* --------------------------------------------- Structures/Data Types */

/* --------------------------------------------- Macros */

/* --------------------------------------------- External Global Variables */
/* AVRCP Handles */
extern AVRCP_HANDLE appl_avrcp_handle[AVRCP_MAX_PROFILES];

/* AVRCP Peer BD Address */
extern UCHAR appl_avrcp_bd_addr[BT_BD_ADDR_SIZE];

#ifdef AVRCP_BRIDGING 
extern UINT8 appl_avrcp_instace;
extern UINT8 temp_inst;
#endif /* AVRCP_BRIDGING  TODO: check tl type usage*/
/* --------------------------------------------- Internal Functions */

/* --------------------------------------------- API Declarations */

void main_avrcp_operations (void);

void appl_avrcp_init_handles (void);

void appl_avrcp_init (void);

void appl_avrcp_shutdown (void);

void appl_avrcp_start_handle (UCHAR index);

void appl_avrcp_start (void);

void appl_avrcp_stop (void);

void appl_avrcp_choose_handle (UCHAR * retval);

void appl_avrcp_show_handles (void);

void appl_avrcp_ctl_ch_connect_req (void);

void appl_avrcp_ctl_ch_disconnect_req (void);

UCHAR appl_avrcp_get_free_handle (void);

#ifdef AVRCP_1_4

void appl_avrcp_brow_ch_connect_req (void);

void appl_avrcp_brow_ch_disconnect_req (void);

#endif /* AVRCP_1_4 */

API_RESULT appl_avrcp_choose_acl_connection (UINT16 * indx);

API_RESULT appl_avrcp_ntf_cb
           (
               AVRCP_HANDLE * avrcp_handle,
               UCHAR          event_type,
               UINT16         event_result,
               void  *        event_data,
               UINT16         event_datalen
           );

void appl_avrcp_print_opcode (UCHAR opcode);

void appl_avrcp_print_response_type (UCHAR rsp_type);

void appl_avrcp_print_operation_id (UCHAR operation_id);

UCHAR appl_avrcp_get_connected_handle (UCHAR * bd_addr);

void appl_avrcp_sdp_callback
     (
         UCHAR command,
         UCHAR * data,
         UINT16 length,
         UINT16 status
     );

void appl_get_avrcp_sdp_record(UCHAR * bd_addr);

#ifdef AVRCP_BRIDGING
UCHAR appl_get_avrcp_tl_message_type(void);
API_RESULT appl_handle_avrcp_bridging_cmd_ind(uint8_t inst);
API_RESULT appl_handle_avrcp_bridging_cmd_rsp(uint8_t inst);
uint8_t avrcp_find_avrcp_instance (UCHAR *bd_addr);
uint8_t avrcp_find_second_avrcp_instance (uint8_t current_instance);
AVRCP_AL_CT_CMD_INFO* appl_avrcp_get_cmd_info(void);
AVRCP_AL_VD_CMD_INFO* appl_avrcp_get_vendor_cmd_info(void);
AVRCP_AL_CT_RSP_INFO* appl_avrcp_get_rsp_info(void);
void appl_reset_cmd_infos(void);
void appl_a2dp_avrcp_disconnect(UCHAR * bd_addr);
UINT8 appl_avrcp_is_browsing_supported(void);
#endif /* AVRCP_BRIDGING */

#endif /* _H_APPL_AVRCP_ */



