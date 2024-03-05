
/**
 *  \file appl_hci.h
 *
 *  Header File for HCI Command Line Application
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

/*   Copyright 2008-2020 NXP
 *
 *  NXP CONFIDENTIAL
 *  The source code contained or described herein and all documents related to
 *  the source code ("Materials") are owned by NXP, its
 *  suppliers and/or its licensors. Title to the Materials remains with NXP,
 *  its suppliers and/or its licensors. The Materials contain
 *  trade secrets and proprietary and confidential information of NXP, its
 *  suppliers and/or its licensors. The Materials are protected by worldwide copyright
 *  and trade secret laws and treaty provisions. No part of the Materials may be
 *  used, copied, reproduced, modified, published, uploaded, posted,
 *  transmitted, distributed, or disclosed in any way without NXP's prior
 *  express written permission.
 *
 *  No license under any patent, copyright, trade secret or other intellectual
 *  property right is granted to or conferred upon you by disclosure or delivery
 *  of the Materials, either expressly, by implication, inducement, estoppel or
 *  otherwise. Any license under such intellectual property rights must be
 *  express and approved by NXP in writing.
 *
 */

#ifndef _H_APPL_HCI_
#define _H_APPL_HCI_

#ifdef MULTI_PROFILE_FSM_SUPPORT
#include "appl_common.h"
#endif /* MULTI_PROFILE_FSM_SUPPORT */
/* ----------------------------------------- Header File Inclusion */
#include "BT_hci_api.h"
#include "appl_utils.h"

/* ----------------------------------------- Global Definitions */

/*
 *  Default Voice Settings to be used for Wideband Speech Synchronous Connection:
 *  Input Coding: A-Law
 *  Input Format: 2's Compliment
 *  Input Sample Size: 16-bit
 *  Linear PCM Bit Position: 3
 *  Air Coding Format: TRANSPARENT
 */
#define APPL_WIDEBAND_VOICE_SETTING_DEFAULT \
    (LMP_VOICE_INPUT_CODING_LINEAR | \
    LMP_VOICE_INPUT_FORMAT_2S_COMPLEMENT | \
    LMP_VOICE_INPUT_SAMPLE_16_BIT | \
    LMP_VOICE_LINEAR_BIT_POS_0 | \
    LMP_VOICE_AIR_CODING_TRANSPARENT)

/*
 * Max length of EIR is 240 bytes.
 * If there are no other data to be sent in EIR, local name can go upto 238 bytes
 * (1 byte for Len and 1 byte for EIR data type)
 * If there are no memory constrains, local name length can be increased
 */
#define INQUIRY_LOCAL_NAME_LEN 100U
/* ----------------------------------------- Structures/Data Types */
typedef struct
{
    UINT16    opcode;
    char *    command_name;
} APPL_HCI_OPCODE_NAME;

/* The HCI Profile Event Indication Callback Type */
typedef struct
{
    /* Pointer to HCI callback function  */
    API_RESULT (* hci_event_ind_cb) (UINT8 event_code, UCHAR *event_data, UINT8 event_datalen);

} APPL_HCI_CB_PTR;

/*
 * Structure for discovered devices.
 * The list of the same is maintained to save the discovered devices and is returned to the GUI
 */
typedef struct
{
	UINT8  valid;
	UCHAR  bd_addr[BT_BD_ADDR_SIZE];
	UCHAR  page_scan_repetition_mode;
	UINT32 class_of_device;
	UINT16 clock_offset;
	UCHAR  rssi;
	UCHAR  local_name[INQUIRY_LOCAL_NAME_LEN];

} INQUIRY_RESULT;

#define INQUIRY_NUM_RESPONSES 0x10U

/* ----------------------------------------- Macros */
#define appl_hci_print_bd_addr(bd)      appl_dump_bytes((bd), 6);

/*
 *  Maximum number of HCI Profile Event Indication Callbacks that Profiles
 *  and Applications on top of HCI (EtherMind Stack) can register
 *  with HCI Application.
 *
 *  Minimum Value: 1
 *  Maximum Value: 254
 */
#define APPL_MAX_NUM_HCI_CB     2U

/**
 *  To Lock APPL HCI Global Mutex.
 *  Since in the sample applications are called from the main task context
 *  this is just a place holder, and implement only if required.
 */
#define APPL_HCI_MUTEX_LOCK()

/**
 *  To Unlock APPL HCI Global Mutex.
 *  Since in the sample applications are called from the main task context
 *  this is just a place holder, and implement only if required.
 */
#define APPL_HCI_MUTEX_UNLOCK()


/* ----------------------------------------- Function Declarations */
/* HCI Application Event Indication Callback */
API_RESULT appl_hci_event_indication_callback
           (
               UCHAR  event_type,
               UCHAR  * event_data,
               UCHAR  event_datalen
           );

/* HCI Error Indication Callback */
API_RESULT appl_hci_error_indication_callback
           (
               UINT16  opcode,
               UINT16  error_code
           );

/* To show HCI Inquiry Results */
void appl_hci_show_inq_result
     (UCHAR inq_resp_recvd, UCHAR *inq_bytes);
void appl_hci_show_inq_result_with_rssi
     (UCHAR inq_resp_recvd, UCHAR *inq_bytes);

void appl_hci_esco_audio_config(UCHAR coding);

#ifdef HCI_SCO
void appl_hci_sco_audio_mic_record_callback
     (
         /* IN */ UCHAR     *mic_data,
         /* IN */ UINT16     mic_datalen
     );

void appl_hci_sco_audio_spkr_playack_callback
     (
         /* IN */ UCHAR     *data,
         /* IN */ UINT16     datalen
     );

API_RESULT appl_hci_esco_msbc_data_handler
           (
               /* IN */ UCHAR    * packet,
               /* IN */ UINT16     packet_len
           );
#endif /* HCI_SCO */


/* HCI API Handlers */
void appl_hci_inquiry (void);
void appl_hci_create_connection (void);
void appl_hci_add_sco_connection (void);
void appl_hci_setup_synchronous_connection (void);
void appl_hci_setup_synchronous_connection_response (void);

#ifdef HCI_ENH_SCO
void appl_hci_read_local_supported_codecs (void);
void appl_hci_enhanced_setup_synchronous_connection (void);
void appl_hci_enhanced_setup_synchronous_connection_response (void);
#endif /* HCI_ENH_SCO */

/*void appl_hci_disconnect (void);Re-visit*/
void appl_hci_remote_name_request (void);
void appl_hci_role_discovery (void);
void appl_hci_switch_role (void);
void appl_hci_sniff_mode(void);
void appl_hci_qos_setup(void);
void appl_hci_change_packet_type(void);
void appl_change_esco_packet_type(void);
void appl_hci_sniff_subrating(void);
void appl_hci_park_mode(void);
void appl_hci_hold_mode(void);
void appl_hci_exit_sniff_mode(void);
void appl_hci_exit_park_mode(void);
void appl_hci_write_link_policy(void);

void appl_hci_read_connection_accept_timeout (void);
void appl_hci_write_connection_accept_timeout (void);
void appl_hci_read_page_timeout (void);
void appl_hci_write_page_timeout (void);
void appl_hci_read_page_scan_activity (void);
void appl_hci_write_page_scan_activity (void);
void appl_hci_read_inquiry_scan_activity (void);
void appl_hci_write_inquiry_scan_activity (void);
void appl_hci_read_class_of_device (void);
API_RESULT appl_hci_write_class_of_device (void);
void appl_hci_read_scan_enable (void);
API_RESULT appl_hci_write_scan_enable (void);
void appl_hci_read_local_name (void);
void appl_hci_change_local_name (void);
void appl_hci_read_inquiry_mode (void);
void appl_hci_write_inquiry_mode (void);
void appl_hci_read_inquiry_scan_type (void);
void appl_hci_write_inquiry_scan_type (void);
void appl_hci_read_page_scan_type (void);
void appl_hci_write_page_scan_type (void);
void appl_hci_read_current_iaclap(void);
void appl_hci_write_current_iaclap(void);
void appl_hci_get_connection_details (void);
void appl_cancel_inquiry_scan(void);
void appl_hci_read_buffersize (void);
void appl_hci_read_link_policy ( void );
void appl_hci_generic_command(void);
void appl_hci_read_default_link_policy_settings (void);
void appl_hci_write_default_link_policy_settings (void);

#ifdef BT_RF_TEST
void appl_hci_rx_test_command(void);
void appl_hci_tx_test_command(void);
#endif

#ifdef BT_3_0

#ifdef HCI_FLOW_CONTROL_COMMANDS
void appl_hci_read_flow_control_mode (void);
void appl_hci_write_flow_control_mode (void);
#endif /* HCI_FLOW_CONTROL_COMMANDS */

void appl_hci_read_enhanced_transmit_power_level (void);

#ifndef HCI_LITE
void appl_hci_read_encryption_key_size (void);
#endif /* HCI_LITE */

#endif /* BT_3_0 */

#ifdef BT_BRSC
void appl_hci_read_secure_connections_host_support (void);
void appl_hci_write_secure_connections_host_support (void);
#endif /* BT_BRSC */

#ifdef BT_BRSC_TEST
void appl_hci_write_secure_connections_test_mode (void);
#endif /* BT_BRSC_TEST */

char * appl_hci_get_command_name (UINT16 opcode);
void main_hci_operations ( void );

/* Application Interface for Profiles to Register their HCI Callbacks */
API_RESULT appl_hci_register_callback
           (
               API_RESULT (* callback_ptr)
                          (
                              UINT8    event_code,
                              UINT8 *  event_data,
                              UINT8    event_datalen
                          )
           );

API_RESULT appl_hci_unregister_callback
           (
               API_RESULT (* callback_ptr)
                          (
                              UINT8    event_code,
                              UINT8 *  event_data,
                              UINT8    event_datalen
                          )
           );

#ifndef HCI_NO_ESCO_AUTO_ACCEPT
#ifdef BT_HCI_1_2
void appl_hci_eSco_init_params(void);

API_RESULT appl_hci_set_esco_channel_parameters
           (
               /* IN */ UCHAR               set_sco_param,
               /* IN */ HCI_SCO_IN_PARAMS * sco_params
           );
//void appl_hci_get_esco_channel_parameters(HCI_SCO_IN_PARAMS * esco_param); //To revisit, is moved to appl_common.h
#ifdef HCI_ENH_SCO
API_RESULT appl_hci_set_enh_esco_channel_parameters
           (
               /* IN */ HCI_ENH_SCO_PARAMS * enh_sco_params
           );
void appl_hci_get_enh_esco_channel_parameters(HCI_ENH_SCO_PARAMS * enh_esco_param);
#endif /* HCI_ENH_SCO */
#endif /* BT_HCI_1_2 */

#else
/* Empty Macro */
#define appl_hci_set_esco_channel_parameters(set_sco_param, sco_params)
#endif /* HCI_NO_ESCO_AUTO_ACCEPT */

#ifdef BT_EIR

void appl_print_extended_inquiry_response
     (
         UCHAR *eir_data,
         UINT16 eir_datalen
     );

void appl_hci_write_extended_inquiry_response(void);

#endif /* BT_EIR */

/*
 * Description: API to reset the list of discovered devices.
 * Return: None
 * Params: None
 */
void appl_reset_hci_inquiry_result();

/*
 * Description: API to get the list of discovered devices.
 *              This API needs to be called after HCI_INQUIRY_COMPLETE_EVENT is received
 * Return: returns list of discovered devices i.e array of type INQUIRY_RESULT
 * Params: None
 */
INQUIRY_RESULT* appl_get_hci_inquiry_result();

/*
 * Description: API to print the list of discovered devices.
 *              This API needs to be called after HCI_INQUIRY_COMPLETE_EVENT is received
 * Return: Number of discovered devices
 * Params: None
 */
UINT32 appl_print_discovered_devices();

#endif /* _H_APPL_HCI_ */

