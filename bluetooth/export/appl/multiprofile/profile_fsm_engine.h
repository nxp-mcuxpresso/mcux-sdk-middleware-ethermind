
/**
 *  \file obex_fsm_defines.h
 *
 *  This file defines state and events related to OBEX FSM.
 */

/*
 *  Copyright (C) 2012. MindTree Ltd.
 *  All rights reserved.
 */

#ifndef _H_PROFILE_FSM_ENGINE_
#define _H_PROFILE_FSM_ENGINE_
#include "BT_features.h"
#ifdef MULTI_PROFILE_FSM_SUPPORT
/* --------------------------------------------- Header File Inclusion */
#include "fsm_engine.h"

/* --------------------------------------------- Global Definitions */
/* Number of PROFILE events at the FSM */
#define PROFILE_MAX_NUM_EVENTS     0x0F

#define PROFILE_MAX_INSTANCES            A2DP_MAX_CODECS

/* Local and Remote event identifier */
#define PROFILE_FSM_LOCAL_EVENT    0x00
#define PROFILE_FSM_REMOTE_EVENT   0x01

/* OBEX FSM Un-initstate */
#define PROFILE_STATE_UNINITIALIZED 0xFFU

#define PROFILE_ACCESS_STATE(i)    (multiprofile_inst[i].state)

#define PROFILE_SET_STATE(i, s)\
    (PROFILE_ACCESS_STATE((i)) =  (s))

#define PROFILE_GET_STATE(i, s)\
    ((s) = PROFILE_ACCESS_STATE((i)))
/* --------------------------------------------- External Global Variables */
/* FSM tables */
extern DECL_CONST EVENT_HANDLER_TABLE profile_event_handler_table[];
extern DECL_CONST STATE_EVENT_TABLE profile_state_event_table[];

/* --------------------------------------------- Structures/Data Types */
/** PROFILE FSM Identifier index */
extern UCHAR profile_fsm_id;
typedef struct _PROFILE_REQRSP_PARAMS
{
    UINT16 reason_code;

    UCHAR profile;

} PROFILE_REQRSP_PARAMS;

typedef struct _PROFILE_EVENT_INFO
{
    /*
     * Event Data to the handler: It will be processed in the handler function
     * and based on the event type the processed data might be passed to application or
     * lower layer
     */
    void* data;

    /* Event Data Length */
    UINT16  datalen;

    /*
     * This handle will used to refer the obex_session structure
     * for updating the tx/rx buffers, obex_state, SRM mode etc.
     */
    UCHAR   profile_fsm_handle;

    /* Event */
    EVENT_T     event_type;

    /* Additional information on event */
    UCHAR   event_info;

}PROFILE_EVENT_INFO;

/* --------------------------------------------- Functions */
API_RESULT profile_fsm_post_event (PROFILE_EVENT_INFO * profile_fsm_event);
API_RESULT profile_access_state_handler (void * param, STATE_T * state);
API_RESULT profile_set_state_handler ( void * param, STATE_T state);
/* ----------------------------------------------- Static Global Variables */
/* PROFILE FSM entity */
DECL_STATIC DECL_CONST FSM_MODULE_TABLE_T profile_fsm =
{
    profile_access_state_handler,

    NULL,

    profile_event_handler_table,

    profile_state_event_table,

    PROFILE_MAX_NUM_EVENTS
};

typedef struct profile_session
{
    UCHAR dev_handle;

    /* Remote BD_ADDR */
    UCHAR bd_addr [BT_BD_ADDR_SIZE];

    /* Current state of a profile session */
    UINT32 state;

    /* Previous state of a profile session */
    UINT32 prev_state;
}PROFILE_SESSION;

typedef enum
{
    ev_pro_a2dp_connect = 0x01U,
    ev_pro_a2dp_disconnect = 0x02U,
    ev_pro_a2dp_start = 0x03U,
    ev_pro_a2dp_suspend = 0x04U,
    ev_pro_a2dp_stop = 0x05U,
    ev_pro_hfp_connect = 0x06U,
    ev_pro_hfp_disconnect = 0x07U,
    ev_pro_hfp_sco_connect = 0x08U,
    ev_pro_hfp_sco_disconnect = 0x09U,
    ev_pro_avrcp_sdp_done = 0x0AU,
    ev_pro_avrcp_connect = 0x0BU,
    ev_pro_avrcp_disconnect = 0x0CU,
	ev_pro_avrcp_message_ind = 0x0DU,
	ev_pro_avrcp_message_cnf = 0x0EU,
    ev_pro_error_rsp = 0x10U
} PROFILE_FSM_EVENTS;

typedef enum
{
    SL_A2DP_INITIALIZED = 0x00000001U,
    SL_A2DP_STARTED = 0x00000002U,
    SL_A2DP_CONNECTED = 0x00000004U,
    SL_A2DP_STREAM_STARTED = 0x00000008U,
    SL_HF_INITIALIZED = 0x00000010U,
    SL_HF_STARTED = 0x00000020U,
    SL_HF_CONNECTED = 0x00000040U,
    SL_HF_SCO_CONNECTED = 0x00000080U,
    SL_A2DP_SUSPEND_ON_SCO = 0x000000100U,
    SL_AVRCP_STARTED = 0x000000200U,
    SL_AVRCP_CONNECTED = 0x000000400U,
    SL_AVRCP_DISCONNECTED = 0x000000800U,
} PROFILE_STATES_LEVEL;
#endif /* _H_PROFILE_FSM_ENGINE_ */
#endif /* MULTI_PROFILE_FSM_SUPPORT */
