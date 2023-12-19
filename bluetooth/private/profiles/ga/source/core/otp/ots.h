
/**
 *  \file otc.h
 *
 *  \brief This file defines the Object Transfer Server Interface - includes
 *         Data Structures and Methods.
 */

/*
 *  Copyright (C) 2020. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_OTS_
#define _H_OTS_

/* --------------------------------------------- Header File Inclusion */
#include "GA_common.h"
#include "GA_bearer_api.h"

#ifdef OTP_SERVER
/* --------------------------------------------- Global Definitions */
/* --------------------------------------------- Data types /Structures */
/**
 *  \addtogroup otp_se_defines Defines
 *  \{
 */

/* Status of function returns or the event callbacks */
typedef UINT16 OTP_RESULT;
/*
 * Session ID provided to Application once the OTS session is established.
 * All further calls to OTC module needs to provide this ID for reference.
 */
typedef UINT8 OTP_SE_SESSION_ID;

/*
 * Callback ID provided to Application once the app registers a callback.
 */
typedef UINT8 OTP_SE_CB_ID;

/*
 * Events generated as part of callback from OTC module to the application.
 */
typedef UINT8 OTP_SE_EVT_ID;

/* Primary Service Instance added ID for Included Service addition */
typedef UINT8 GATT_PRIMARY_SVC_INST;

/** Context to identify the request and response */
typedef GA_BRR_CHR_CONTEXT OTP_SE_RSP_CONTEXT;

typedef UINT8 OTP_SE_SVC_TYPE;

/** \} */

/**
 *  \addtogroup otp_se_structures Structures
 *  \{
 */

/** OTS Callback to be registerd by the Application */
typedef GA_RESULT (* OTP_SE_NTF_CB)
                   (
                       OTP_SE_SESSION_ID   otp_se_sess_id,
                       GA_ENDPOINT       * device,
                       void              * ctx,
                       OTP_SE_EVT_ID       evt_id,
                       UINT16              evt_status,
                       void              * evt_data,
                       UINT16              evt_datalen
                   );

/** \} */
/* --------------------------------------------- Macros */
/**
 *  \addtogroup otp_ce_defines Macros
 *  \{
 */

/* Defines the type of service to be added OTP_SE_SVC_TYPE */
#define OTP_SE_SVC_TYPE_PRIMARY  1
#define OTP_SE_SVC_TYPE_INCLUDED 2

/**
 * \defgroup otp_se_events Events
 * \{
 * This section lists the Asynchronous Events notified to Application by the
 * Module. Represented as \ref OTP_SE_EVT_ID.
 */

/* Invalid event */
#define OTS_INVALID_EVT              0xFF

/**
 * The below event is notified whenever a read request from peer is received.
 * Response to this request has to be sent by calling /ref
 * ().
 * If the char requires Data Channel to send the data, post providing the
 * read response, the module must call function
 * /ref GA_mcp_se_data_channel_write() post this call.
 */
#define OTP_SE_READ_OTS_FEATURE_IND       0x01
#define OTP_SE_READ_OBJ_NAME_IND          0x02
#define OTP_SE_READ_OBJ_TYPE_IND          0x03
#define OTP_SE_READ_OBJ_SIZE_IND          0x04
#define OTP_SE_READ_OBJ_FIRST_CREATED_IND 0x05
#define OTP_SE_READ_OBJ_LAST_MOD_IND      0x06
#define OTP_SE_READ_OBJ_OBJ_ID_IND        0x07
#define OTP_SE_READ_OBJ_PROP_IND          0x08
#define OTP_SE_READ_OBJ_FILTER_IND        0x09

/* Indicates a write request */
#define OTP_SE_WRITE_OBJ_NAME_IND          0x0A
#define OTP_SE_WRITE_OBJ_FIRST_CREATED_IND 0x0B
#define OTP_SE_WRITE_OBJ_LAST_MOD_IND      0x0C
#define OTP_SE_WRITE_OBJ_PROP_IND          0x0D
#define OTP_SE_WRITE_OACP_IND              0x0E
#define OTP_SE_WRITE_OLCP_IND              0x0F
#define OTP_SE_WRITE_OBJ_FILTER_IND        0x10

/*
 * This event is generated when OTS transport channel is established.
 */
#define OTP_SE_DATA_CHANNEL_UP_IND         0x11

 /*
  * This event is generated when OTS transport channel is disconnected.
  */
#define OTP_SE_DATA_CHANNEL_DOWN_IND       0x12

/* After data write is successful, number of bytes written is indicated */
#define OTP_SE_DATA_WRITE_IND              0x13

/** \} */
/** \} */
/* --------------------------------------------- APIs */
/**
 * \defgroup otp_se_api_defs API Definitions
 * \{
 * This section describes the EtherMind OTP Profile APIs.
 */

#ifdef __cplusplus
extern "C" {
#endif
/**
 *  \brief To register a callback with the OTP SE module.
 *
 *  \par Description:
 *       This function registers a callback with the OTS module, all events
 *       to be notified to this app will be provided to the registered
 *       callback.
 *
 *  \param [in] ots_cb
 *         Application callback.
 *
 *  \param [out] ots_cb_id
 *         OTS Callback ID for this application callback.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
GA_RESULT OTP_se_register_ots_cb
           (
               /* IN */   OTP_SE_NTF_CB   ots_cb,
               /* OUT */  OTP_SE_CB_ID  * ots_cb_id
           );

/**
 *  \brief To deregister association with OTP SE module.
 *
 *  \par Description:
 *       This function removes the registration of callback. No events post
 *       this will be notified to this application.
 *
 *  \param [in] ots_cb_id
 *         Application callback ID provided during init.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
GA_RESULT OTP_se_deregister_ots_cb
          (
              /* IN */  OTP_SE_CB_ID ots_cb_id
          );

/**
 *  \brief To add OTS service to the DB.
 *
 *  \par Description:
 *       This function adds the OTS Service to the DB and saves the
 *       service and char handles.
 *
 *  \param [in] ots_cb_id
 *         Application callback ID provided during init.
 *
 *  \param [in] ots_svc_type
 *         OTS Service type, Primary or Secondary.
 *
 *  \param [out] otp_se_sess_id
 *         OTS provided session ID post addition of service.
 *
 *  \param [out] ots_svc_inst_id
 *         OTS provided Instance ID post addition of service.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
GA_RESULT OTP_se_add_ots_service
          (
              /* IN */  OTP_SE_CB_ID            ots_cb_id,
              /* IN */  OTP_SE_SVC_TYPE         ots_svc_type,
              /* IN */  GATT_PRIMARY_SVC_INST * pri_svc_inst,
              /* OUT */ OTP_SE_SESSION_ID     * otp_se_sess_id,
              /* OUT */ GA_BRR_SVC_INST       * ots_svc_inst_id
          );

/**
 *  \brief To trigger sending of response for read or write request.
 *
 *  \par Description:
 *       This function triggers sending of response for read/write.
 *
 *  \param [in] dev
 *         Remote device address
 *
 *  \param [in] ctx
 *         Assigned UUID of this GATT Characteristic.
 *
 *  \param [in] ots_evt_id
 *         Event ID on which request occurred.
 *
 *  \param [in] rsp_status
 *         Response Status for read/write request.
 *
 *  \param [in] char_val
 *         Response packet to be sent - Valid for Read request event type only.
 *         NULL - For Write request.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
GA_RESULT OTP_se_send_rsp
          (
              /* IN */ GA_ENDPOINT        * dev,
              /* IN */ OTP_SE_RSP_CONTEXT * ctx,
              /* IN */ OTP_SE_EVT_ID        ots_evt_id,
              /* IN */ GA_RESULT            rsp_status,
              /* IN */ GA_BRR_CHR_VAL     * char_val
          );

/**
 *  \brief To send Indications to the peer OTC.
 *
 *  \par Description:
 *       This function send indications to the peer device based on the
 *       address and if configuration is enabled.
 *
 *  \param [in] dev
 *         If NULL, Ind to all connected OTC sessions will be passed.
 *         Else, to the corresponsing address passed.
 *
 *  \param [in] ots_inst_id
 *         OTS provided session ID post addition of service.
 *
 *  \param [in] char_uuid
 *         Char UUID.
 *
 *  \param [in] char_val
 *         Data to be sent as part of the notification.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
GA_RESULT OTP_se_send_ind
          (
              /* IN */ GA_ENDPOINT       * dev,
              /* IN */ OTP_SE_SESSION_ID   otp_se_sess_id,
              /* IN */ UINT16              char_uuid,
              /* IN */ GA_BRR_CHR_VAL    * char_val
          );

/**
 *  \brief To trigger a write on L2CAP COC for this OTS session.
 *
 *  \par Description:
 *       This function triggers a L2CAP COC write.
 *
 *  \param [in] dev
 *         Remote device address
 *
 *  \param [in] cid
 *         Channel Identifier provided as part of OTC_DATA_CHANNEL_UP_IND.
 *
 *  \param [in] buffer
 *         Buffer containing packet to be sent
 *
 *  \param [in] buffer_len
 *         Packet length
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
GA_RESULT OTP_se_data_channel_write
          (
              /* IN */ GA_ENDPOINT * dev,
              /* IN */ UINT16        cid,
              /* IN */ UCHAR       * buffer,
              /* IN */ UINT16        buffer_len
          );

/**
 *  \brief To Disconnect Object Transfer Service(OTS) Transport Channel
 *
 *  \par Description:
 *       This function enables to disconnect the OTS transport channel whenever
 *       required.
 *
 *  \param [in] otp_se_sess_id
 *         OTS provided session ID during OTS Session context set-up.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure.
 *          If OTS Transport Channel is removed, OTS_TRANS_DOWN_EVT is
 *          notified.
 */
GA_RESULT OTP_se_disconn_ots_trans_channel
          (
              /* IN */  OTP_SE_SESSION_ID otp_se_sess_id
          );

#ifdef __cplusplus
};
#endif

/** \} */

#endif /* OTP_SERVER */

#endif /* _H_OTS_ */
