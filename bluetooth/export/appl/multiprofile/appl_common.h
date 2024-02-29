
/**
 *  \file appl_common.h
 *
 *  Header file for the common test application
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_APPL_COMMON_
#define _H_APPL_COMMON_

/* --------------------------------------------- Header File Inclusion */
#include "appl_a2dp.h"
#include "a2dp_pl.h"
#include "appl_avrcp.h"
#include "appl_hfp_unit.h"
#include "appl_hfp_ag.h"
#include "appl_avrcp_ct.h"
#include "appl_avrcp_tg.h"

#include "BT_common.h"
#include "BT_hci_api.h"
#include "BT_sm_api.h"
#include "BT_sdp_api.h"
#include "BT_config.h"
#include "appl_utils.h"

#ifdef MULTI_PROFILE_FSM_SUPPORT
#include "profile_fsm_engine.h"
#include "profile_fsm_handlers.h"
#endif /* MULTI_PROFILE_FSM_SUPPORT */

/* #define APPL_USE_STANDARD_IO */
/* --------------------------------------------- Global Definitions */
#ifdef APPL_USE_STANDARD_IO
#define APPL_LOG    printf
#else /* APPL_USE_STANDARD_IO */
#define APPL_LOG(...)
#endif /* APPL_USE_STANDARD_IO */

/* Application defines */
#define APPL_A2DP                  0x01
#define APPL_SPP                   0x02
#define APPL_HF                    0x03

#define INCLUDE_A2DP_CODEC

#define APPL_HFP_AG_OPERATION    0x01
#define APPL_HFP_UNIT_OPERATION  0x02

/* Enable for BLE */
/* #define INCLUDE_BLE */
#ifdef MULTI_PROFILE_FSM_SUPPORT
typedef UINT8 PROFILE_HANDLE;
#endif /* MULTI_PROFILE_FSM_SUPPORT */

/* Enable to log snoop */
/* #define INCLUDE_SNOOP */

/* Enable to read configuration */
/* #define INCLUDE_CONFIG */
/* --------------------------------------------- Structures/Data Types */

/* --------------------------------------------- Macros */

/* --------------------------------------------- Internal Functions */
API_RESULT appl_bluetooth_on_complete (void);
API_RESULT appl_hci_event_indication_callback
           (
               UCHAR  event_type,
               UCHAR  * event_data,
               UCHAR  event_datalen
           );
API_RESULT appl_sm_ui_notify_cb
           (
               UCHAR      event_type,
               UCHAR *    bd_addr,
               UCHAR *    event_data
           );
#ifdef SM_HAVE_MODE_2
API_RESULT appl_sm_service_cb
           (
               UCHAR      event_type,
               UCHAR *    bd_addr,
               UCHAR *    event_data
           );
#endif /* SM_HAVE_MODE_2 */
void appl_sdp_callback
     (
         UCHAR command,
         UCHAR * data,
         UINT16 length,
         UINT16 status
     );
void appl_hci_connect(UCHAR * bd_addr);
/*
 * Description: API to connect to a device based on the index selected wrt the discovered device list:
 *              INQUIRY_RESULT appl_inquiry_res[INQUIRY_NUM_RESPONSES]
 * Return: NONE
 * Params: index to the decovered device list i.e INQUIRY_RESULT appl_inquiry_res[INQUIRY_NUM_RESPONSES]
 */
void appl_hci_connect_index(UINT8 index);
void appl_hci_disconnect (UINT16 acl_handle);
void appl_sdp_open (void);
#ifdef MULTI_PROFILE_FSM_SUPPORT
UCHAR get_multiprofile_handle(void);
#endif /* MULTI_PROFILE_FSM_SUPPORT */

void appl_avrcp_start_handle (UCHAR index);
UCHAR appl_avrcp_get_free_handle (void);
API_RESULT appl_hci_set_esco_channel_parameters \
           (
               /* IN */ UCHAR               set_sco_param, \
               /* IN */ HCI_SCO_IN_PARAMS * sco_params
           );
void appl_hci_get_esco_channel_parameters(HCI_SCO_IN_PARAMS * esco_param);
void appl_dump_bytes (UCHAR *buffer, UINT16 length);
/* Moved the declaration of appl_common_main() from appl_common.c to here, because
 * it's needed by main.c file in task_main().
 */
#ifdef MULTI_PROFILE_FSM_SUPPORT
int appl_common_main (int argc, char **argv);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
#ifdef HFP_BRIDGING
int get_codec_selected();
#endif

#ifdef AVRCP_BRIDGING
UCHAR appl_get_sep_to_register_notification(void);
#endif /* AVRCP_BRIDGING */

#if defined(HFP_BRIDGING) && defined(A2DP_BRIDGING) && defined(AVRCP_BRIDGING)
#define PROFILE_INSTANCE_INVALID 0xFFU
UINT8 get_hf_support_of_peer();
#endif

#endif /* _H_APPL_COMMON_ */

