
/**
 *  \file appl_a2dp.h
 *
 *  Header file for A2DP Command Line Test Application
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_APPL_A2DP_
#define _H_APPL_A2DP_

/* ----------------------------------------- Header File Inclusion */
#ifdef MULTI_PROFILE_FSM_SUPPORT
#include "appl_common.h"
#endif /* MULTI_PROFILE_FSM_SUPPORT */
#include "BT_avdtp_api.h"
#include "BT_a2dp_api.h"

#define INCLUDE_A2DP_CODEC
#ifdef INCLUDE_A2DP_CODEC
#include "BT_jpl_api.h"
#endif /* INCLUDE_A2DP_CODEC */
#include "sbc_api.h"

/* ----------------------------------------- Global Definitions */
/** Maximum Block Size of SBC Frame */
#define SBC_BLOCK_MAX           512


/* ----------------------------------------- Macros */
/* A2DP Application Streaming Status Flags */
#define APPL_A2DP_STREAM_FALSE           0x00U
#define APPL_A2DP_STREAM_TRUE            0x01U

#ifdef A2DP_BRIDGING
#define APPL_A2DP_DISCONNECTED    0x00U
#define APPL_A2DP_CONNECTED       0x01U
#endif //A2DP_BRIDGING

/* ----------------------------------------- Structures/ Data Types */
/* A2DP Codec Instances */
typedef struct
{
    /* SEP Capability */
    AVDTP_SEP_CAP sep_cap;

    /* A2DP Sink or Source */
    UCHAR role;

    /* A2DP Codec Instance */
    UCHAR a2dp_instance;

    /* Flag - Whether allocated or free */
    UCHAR allocated;

    /* A2DP Appl. stream state - TRUE or FALSE */
    UCHAR stream_state;

    /* Remote BD_ADDR */
    UCHAR bd_addr [BT_BD_ADDR_SIZE];

    /* Static/Resident Codec Capability IE Buffer */
    UCHAR codec_ie_cap [4];

    /* Static/Resident Codec Configuration IE Buffer */
    UCHAR codec_ie_conf [4];

#ifdef A2DP_BRIDGING
    /* A2DP Appl. stream state - TRUE or FALSE */
    UCHAR a2dp_connection_state;
#endif //A2DP_BRIDGING

} A2DP_APPL_INSTANCE;


/* ----------------------------------------- Function Declarations */

/* AVDTP Notification Callback Handler */
API_RESULT a2dp_appl_avdtp_notify_cb
           (
                UCHAR ,
                UINT16,
                AVDTP_HANDLE*,
                void*,
                UINT16
           );

/* A2DP Notification Callback Handler */
API_RESULT a2dp_appl_notify_cb
           (
                UCHAR,
                UCHAR,
                UINT16,
                void*,
                UINT16
           );

void a2dp_appl_init (void);
void a2dp_appl_start (UCHAR sep);
void a2dp_appl_connect (UCHAR * bd_addr);

void appl_a2dp_stream_start (UCHAR index);
void appl_a2dp_stream_suspend (UCHAR index);
void appl_a2dp_avrcp_connect(UCHAR * bd_addr);

void main_a2dp_snk_operations (void);
void main_a2dp_src_operations (void);
UCHAR appl_a2dp_get_sep_type(void);
UCHAR appl_a2dp_get_sep_type(void);
API_RESULT appl_a2dp_is_streaming(UCHAR *idx, UCHAR *bd_addr);

void a2dp_appl_free_instance (UCHAR indx);
void a2dp_appl_alloc_instance (UCHAR * indx);

void a2dp_appl_show_instance(void);
void a2dp_appl_get_instance(UCHAR* indx);
void a2dp_appl_connect_info_reset(UCHAR inst);
void a2dp_appl_print_codec_ie_configuration
(
    /* IN */  UCHAR   codec_type,
    /* IN */  UCHAR* codec_ie,
    /* IN */  UINT16  codec_ie_len
);
void a2dp_appl_save_codec_ie_configuration
(
    /* IN */  UCHAR   role,
    /* IN */  UCHAR   codec_type,
    /* IN */  UCHAR* codec_ie,
    /* IN */  UINT16   codec_ie_len
);

#ifdef A2DP_BRIDGING
uint8_t a2dp_find_codec_sink_instance (uint8_t *sep_type);
uint8_t a2dp_find_connected_a2dp_instance (uint8_t current_instance);
uint8_t a2dp_find_a2dp_instance (UCHAR *bd_addr);
UINT8 a2dp_find_free_sep_instance (UCHAR sep_type);
UCHAR a2dp_find_avrcp_target_instance ();
#endif /*A2DP_BRIDGING*/

#endif /* _H_APPL_A2DP_ */


