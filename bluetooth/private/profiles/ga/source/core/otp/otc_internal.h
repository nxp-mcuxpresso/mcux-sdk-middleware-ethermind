
/**
 *  \file otc_internal.h
 *
 *  \brief This file defines the Object Transfer Client internal
 *         functionalities. Interaction with OTS transport, maintaining
 *         multiple contexts of OTC sessions.
 */

/*
 *  Copyright (C) 2020. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_OTC_INTERNAL_
#define _H_OTC_INTERNAL_

/* --------------------------------------------- Header File Inclusion */
#include "otc.h"
#include "otp_common.h"
#include "otc_transport.h"

#ifdef OTP_CLIENT
/** OTP Client Mutex Lock & Unlock */
#define OTP_CE_LOCK()
#define OTP_CE_UNLOCK()
#define OTP_CE_LOCK_VOID()
#define OTP_CE_UNLOCK_VOID()

/* --------------------------------------------- Global Definitions */

/**
 * Maximum number of OTC sessions that can be active concurrently.
 * This can mean different applications using OTS for different activities to
 * same or different devices.
 */
#define MAX_NUM_OF_CONCURRENT_OTC_SESSIONS     8

/**
 * Maximum number of applications registered to the OTC module with callbacks.
 * An application can register a single callback but can have multiple
 * OTS sessions to either same or different devices.
 */
#define MAX_NUM_OF_CONCURRENT_CB_CTX            5

/** By default, unused instance before session is established */
#define OTP_INST_UNUSED                         0xFF

/** Invalid Event, Do not trigger a callback to the app */
#define OTP_EVT_INVALID                         0xFF

/* Time out as per spec for any data receive is 30s. */
#define OTP_CE_TIMEOUT_RX_DATA                  30

/* Implementation Specific Timeout waiting for a CP response from remote */
#define OTP_CE_TIMEOUT_RX_CONTROL_PNT_RSP       30

typedef UINT8 OTS_TRANSPORT_STATE;

#define OTS_TRANS_IDLE                      0x01
#define OTS_TRANS_TX_IN_PROGRESS            0x02
#define OTS_TRANS_RX_IN_PROGRESS            0x03
#define OTS_TRANS_ABORT                     0x04

typedef UINT8 OTC_OP;

/* Representation of OTC_OP */
#define OTC_OP_IND_CFG                      0x01
#define OTC_OP_READ_REQ                     0x02
#define OTC_OP_WRITE_REQ                    0x03

#define OTP_CHAR_ID_OTS_FEATURE                    0U
#define OTP_CHAR_ID_OBJ_NAME                       1U
#define OTP_CHAR_ID_OBJ_TYPE                       2U
#define OTP_CHAR_ID_OBJ_SIZE                       3U
#define OTP_CHAR_ID_FIRST_CREATED                  4U
#define OTP_CHAR_ID_LAST_MOD                       5U
#define OTP_CHAR_ID_OBJ_ID                         6U
#define OTP_CHAR_ID_OBJ_PROP                       7U
#define OTP_CHAR_ID_OACP                           8U
#define OTP_CHAR_ID_OLCP                           9U
#define OTP_CHAR_ID_OBJ_LIST_FILTER                10U
#define OTP_CHAR_ID_OBJ_CHG                        11U

#define OTP_CHAR_ID_COUNT                          12U

/*
 * This provides a callback and an Identifier Look-Up. A single application
 * can have multiple OTS sessions and hence register a callback only once and
 * have multiple OTS session with same and/or different devices.
 */
typedef struct _OTP_CE_CB_CTX_
{
    OTP_CE_NTF_CB    cb;
    OTP_CE_NTF_CB_ID id;
}OTP_CE_CB_CTX;

/*
 * Context is maintained per application, though the connections made over
 * OTS is to the same device and on the same instance, the OTS channel used
 * varies. For OTS profile transactions, whenever there is a callback for a
 * particular handle range, corresponding apps who have registered will receive
 * notifications. However, for OTS Transport transactions, based on lcid, the
 * notifications will be routed to corresponding app.
 */
typedef struct _OTC_SESSION
{
    /* Associate the Callback Identifier of the App to this session */
    OTP_CE_NTF_CB_ID otp_ce_ntf_cb_id;

    /* OTC Transport Layer Parameters */
    OTP_DATA_CHANNEL_CTX otc_data_channel_ctx;

    /* Device Address */
    GA_ENDPOINT dev;

#if 0
    /* OTS Handles */
    UINT16 ots_feature_hndl;
    UINT16 ots_obj_name_hndl;
    UINT16 ots_obj_type_hndl;
    UINT16 ots_obj_size_hndl;
    UINT16 ots_obj_first_created_hndl;
    UINT16 ots_obj_last_mod_hndl;
    UINT16 ots_obj_id_hndl;
    UINT16 ots_obj_prop_hndl;
    UINT16 ots_obj_oacp_hndl;
    UINT16 ots_obj_olcp_hndl;
    UINT16 ots_obj_olf_hndl_inst1;
    UINT16 ots_obj_olf_hndl_inst2;
    UINT16 ots_obj_olf_hndl_inst3;
    UINT16 ots_obj_chgd_hndl;
#endif /* 0 */

    /* Channel Identifier gets updated during conn/disconnection */
    UINT16  lcid;

    /* App associated with this service handle range */
    GA_BRR_SVC_RANGE svc_hndl_range;

    /**
     * Characteristic Information
     */
    GA_CHAR_INFO char_info[OTP_CHAR_ID_COUNT];

    UINT8 char_config_id;

    /* Expected Event for the Operation that is active */
    OTP_CE_EVT_ID otc_evt_id;
}OTC_SESSION;

typedef struct _OTC_OACP_RSP_IND
{
    UINT8 opc;
    UINT8 req_opc;
    UINT8 res_code;
}OTC_OACP_RSP_IND;

/* --------------------------------------------- Data types /Structures */
/* Callback registered with GA Bearer for Client Callbacks only */
GA_RESULT otc_ga_brr_client_callback
          (
              /* IN */ GA_BRR_DEVICE * device,
              /* IN */ void *          context,
              /* IN */ UINT8           event_type,
              /* IN */ UINT16          event_status,
              /* IN */ void *          event_data,
              /* IN */ UINT16          event_datalen
          );
/* --------------------------------------------- Macros */


#define IS_OTS_DEV_SAME(index, dev) \
        (0 == EM_mem_cmp((dev), &otc_sess[(index)].dev, sizeof(GA_ENDPOINT)))

#define IS_OACP_CHAR_HNDL(index, char_hndl) \
        (otc_sess[(index)].char_info[OTP_CHAR_ID_OACP].handle == char_hndl)

#define IS_OLCP_CHAR_HNDL(index, char_hndl) \
        (otc_sess[(index)].char_info[OTP_CHAR_ID_OLCP].handle == char_hndl)
/* --------------------------------------------- APIs */
/* Utility Functions - Callback related */
GA_RESULT otc_fetch_entry_pos_for_cb(UINT8 * cb_id);

/* Utility Functions - Session related */
UINT8 otp_ce_get_char_id_from_uuid(UINT16 uuid);
UINT8 otp_ce_get_char_id_from_handle(UINT16 char_handle, OTC_SESSION* otc);
UINT8 otp_ce_get_next_char_config(UINT8 char_id, OTC_SESSION* otc);

/*
 * This function fetches the OTC Session ID wrt the device input and also for
 * the same Svc Handle range provided.
 */
GA_RESULT otc_find_ots_ctx_for_dev_svc_hndl_range
           (
               /* IN */   GA_ENDPOINT * dev,
               /* IN */   GA_BRR_SVC_RANGE * svc_hndl_range,
               /* OUT */  OTP_CE_SESSION_ID* otc_sess_id
           );

/*
 * This function fetches the OTC Session ID wrt the device address.
 */
GA_RESULT otc_find_ots_ctx_for_dev_addr
           (
               /* IN */   GA_ENDPOINT * dev,
               /* OUT */  OTP_CE_SESSION_ID * otc_sess_id
           );

/*
 * This function fetches the OTC Session ID wrt the lcid.
 */
GA_RESULT otc_find_ots_ctx_for_lcid
           (
               /* IN */   UINT16           lcid,
               /* OUT */  OTP_CE_SESSION_ID * otc_sess_id
           );

/* This function fetches a free index for a new OTS Session. */
GA_RESULT otc_fetch_free_otp_ce_sess_id
           (
               /* OUT */  OTP_CE_SESSION_ID * otc_sess_id
           );

/*
 * To set context while sending requests to GATT PL module, this helps in
 * retrieving the context when the events are triggered for the requests.
 */
GA_RESULT otc_set_sess_ctx
           (
               /* IN */   OTP_CE_SESSION_ID     otc_sess_id,
               /* IN */   OTP_CE_EVT_ID         otc_exp_evt_id,
               /* OUT */  void            ** ctx
           );

/*
 * Based on the context saved before calling GA BRR call, fetch the right
 * instance in the callback.
 */
GA_RESULT otc_find_sess_ctx
           (
               /* IN */   void *           ctx,
               /* OUT */  OTP_CE_SESSION_ID * otc_sess_id
           );

/* Fetch the expected Event ID */
OTP_CE_EVT_ID otc_find_ctx_evt_id
           (
               /* IN */  OTP_CE_SESSION_ID otc_sess_id
           );

/* Reset the expected Event ID */
void otc_reset_ctx_evt_id
     (
         /* IN */  OTP_CE_SESSION_ID otc_sess_id
     );

/* Service, Char, Desc Results Update in the context */
GA_RESULT otc_handle_ots_composition
          (
              OTP_CE_SESSION_ID    otc_sess_id,
              GA_BRR_CHR_INFO * chr_info,
              UINT8             chr_cnt
          );

void otp_ce_handle_char_composition
     (
         /* IN */ OTC_SESSION * otc,
         /* IN */ GA_BRR_CHARACTERISTIC_COMPOSITION * comp
     );

/*
 * This function helps to set the Char Handle based on the Char UUID or
 * get the Char Handle based on the Char UUID for OTS Session.
 */
GA_RESULT otc_action_on_char_handle_for_inst
          (
              UINT8            set_handle,
              OTP_CE_SESSION_ID  otc_sess_id,
              UINT16          char_uuid,
              UINT16 *        char_handle
          );

GA_RESULT ots_prep_to_rx_obj_contents
           (
               OTP_CE_SESSION_ID otc_sess_id
           );

GA_RESULT ots_transport_reset_receive_data(OTP_CE_SESSION_ID otc_sess_id);

GA_RESULT otc_find_sess_id_for_char_hndl
           (
               /* IN */  GA_ENDPOINT      * dev,
               /* IN */  GA_BRR_CHR_HANDLE   char_hndl,
               /* IN */  OTP_CE_SESSION_ID    * otc_sess_id
           );

GA_RESULT otc_parse_oacp_olcp_ind(void* data, UINT16 len, UINT8* req_opc);

GA_RESULT otc_handle_ind
           (
               OTP_CE_SESSION_ID otc_sess_id,
               UINT16 char_hndl,
               void * data,
               UINT16 len,
               OTP_CE_EVT_ID * otc_evt_id
           );

GA_RESULT otc_receive_obj_contents
           (
               OTP_CE_SESSION_ID otc_sess_id,
               UCHAR          * data,
               UINT16         datalen
           );

GA_RESULT otc_trigger_config_char_all
          (
              /* IN */ GA_BRR_PRF_HANDLE   pid,
              /* IN */ OTP_CE_SESSION_ID      otc_sess_id,
              /* IN */ GA_BRR_DEVICE     * device,
              /* IN */ UINT8               ots_ind_flag,
              /* IN */ void              * ctx
          );

void ots_receive_data_on_timer_expiry_handler
     (
         void * data,
         UINT16 datalen
     );

void ots_receive_ctrl_pnt_rsp_on_timer_expiry_handler
     (
         void   * data,
         UINT16   datalen
     );

#endif /* OTP_CLIENT */

#endif /* _H_OTC_INTERNAL_ */
