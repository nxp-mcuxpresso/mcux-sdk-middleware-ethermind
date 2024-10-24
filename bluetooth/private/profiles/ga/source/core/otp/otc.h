
/**
 *  \file otc.h
 *
 *  \brief This file defines the Object Transfer Client Interface - includes
 *         Data Structures and Methods.
 */

/*
 *  Copyright (C) 2020. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_OTC_
#define _H_OTC_

/* --------------------------------------------- Header File Inclusion */
#include "GA_common.h"
#include "GA_bearer_api.h"

#ifdef OTP_CLIENT

/* --------------------------------------------- Global Definitions */
/**
 * \defgroup otp_ce_events Events
 * \{
 * This section lists the Asynchronous Events notified to Application by the
 * Module. Represented as \ref OTP_CE_EVT_ID.
 */

/**
 * On completion of discovery of service, char and desc, MCP Handle is
 * provided to the application with the event along with the status.
 * In case where service is not found, \ref GA_FAILURE is sent as the event status.
 */
#define OTP_CE_SETUP_CNF                      0x01

/**
 * On completion of establishment of a Data Channel, this event is notified
 * with the status.
 */
#define OTP_CE_DATA_CHANNEL_UP_CNF            0x02

/**
 * On release of a Data Channel, this event is notified with the status.
 * The peer can also trigger a release of Data Channel which can lead to the
 * below event.
 */
#define OTP_CE_DATA_CHANNEL_DOWN_CNF          0x03

/**
 * This event is notified with status as \ref GA_SUCCESS or \ref GA_FAILURE
 * based on the completion of the functionality.
 */
#define OTP_CE_ENABLE_ALL_CFG_CNF             0x04

/**
 * This event is notified with status as \ref GA_SUCCESS or \ref GA_FAILURE
 * based on the completion of the functionality.
 */
#define OTP_CE_DISABLE_ALL_CFG_CNF            0x05

/**
 * Indication for this is usually when a OACP Read Proc is written on the
 * Control Point and a response is received for the same as part of this
 * Indication.
 */
#define OTP_CE_OACP_READ_IND                  0x06
#define OTP_CE_OLCP_GOTO_IND                  0x07

/** Whenever a Object change occurs on the remote, it is notified */
#define OTP_CE_OBJ_CHGD_IND                   0x08

/**
 * The below events are notified whenever read request is successful and a
 * response is received from the peer.
 * Status is set to \ref GA_SUCCESS or \ref GA_FAILURE based on the result.
 */
#define OTP_CE_READ_FEATURE_NAME_CNF          0x09
#define OTP_CE_READ_OBJ_NAME_CNF              0x0A
#define OTP_CE_READ_OBJ_TYPE_CNF              0x0B
#define OTP_CE_READ_OBJ_SIZE_CNF              0x0C
#define OTP_CE_READ_OBJ_FIRST_CREATED_CNF     0x0D
#define OTP_CE_READ_OBJ_LAST_MOD_CNF          0x0E
#define OTP_CE_READ_OBJ_ID_CNF                0x0F
#define OTP_CE_READ_OBJ_PROP_CNF              0x10
#define OTP_CE_READ_OBJ_LIST_FILTER_CNF       0x11

/**
 * The event is notified whenever write is successful and a write
 * response is received from peer.
 * This applies to only requests that was triggered with write type -
 * Write Request \ref GA_MCP_CE_WRITE_REQUEST.
 */
#define OTP_CE_OACP_READ_CNF                  0x12
#define OTP_CE_OLCP_GOTO_CNF                  0x13
#define OTP_CE_OLF_NO_FILTER_INST1_CNF        0x14
#define OTP_CE_OLF_NO_FILTER_INST2_CNF        0x15
#define OTP_CE_OLF_NO_FILTER_INST3_CNF        0x16
#define OTP_CE_OLF_NO_FILTER_ALL_INST_CNF     0x17

/**
 * This event is generated when Object contents data is received on COC
 * channel from peer. This is a part of OACP Read Procedure.
 */
#define OTP_CE_OBJ_DATA_IND                   0x16

/** \} */

/**
 * \defgroup otp_ce_data_channel_mode Events
 * \{
 * This section lists the Data Channel modes. Represented as
 * \ref OTP_CE_DATA_CHANNEL_MODE.
 */

#define OTP_CE_DATA_CHANNEL_MODE_CBFC         0x01
#define OTP_CE_DATA_CHANNEL_MODE_ECBFC        0x02

/** \} */

/** Object ID Length */
#define OTP_OBJ_ID_LEN                         6

#define OTP_CE_IS_SESSION_ID_VALID(otp_ce_sess_id) \
    ((otp_ce_sess_id) < MAX_NUM_OF_CONCURRENT_OTC_SESSIONS)
/* --------------------------------------------- Data types /Structures */

/**
 *  \addtogroup otp_ce_defines Defines
 *  \{
 */

/** Event that will be notified by the OTP CE module. */
typedef UINT8 OTP_CE_EVT_ID;

/**
 * Session ID provided to Application once the OTS session is established.
 * All further calls to OTP CE module needs to provide this ID for reference.
 */
typedef UINT8 OTP_CE_SESSION_ID;

/**
 * Callback ID provided to Application once the app registers a callback.
 */
typedef UINT8 OTP_CE_NTF_CB_ID;

/**
 * Represents the type of Data Channel Mode.
 */
typedef UINT8 OTP_CE_DATA_CHANNEL_MODE;

/** \} */

/**
 *  \addtogroup otp_ce_structures Structures
 *  \{
 */

typedef struct _OTC_OACP_PROC_READ_PARAM_
{
    UINT8  opcode;
    UINT32 offset;
    UINT32 len;
}OTC_OACP_PROC_READ_PARAM;

typedef struct _OTC_OLCP_GOTO_PARAM_
{
    UINT8 opcode;
    UINT8 obj_id[OTP_OBJ_ID_LEN];
}OTC_OLCP_GOTO_PARAM;

typedef struct _OTC_OBJ_
{
    UINT8    type;
    void   * data;
    UINT16   len;
}OTC_OBJ;

/* OTP CE Callback to be registered by the Application */
typedef GA_RESULT (* OTP_CE_NTF_CB)
                  (
                      OTP_CE_SESSION_ID   otp_ce_sess_id,
                      OTP_CE_EVT_ID       evt_id,
                      UINT16              evt_status,
                      void              * evt_data,
                      UINT16              evt_datalen
                  );

/** \} */
/* --------------------------------------------- Macros */

/* --------------------------------------------- APIs */
/**
 * \defgroup otp_ce_api_defs API Definitions
 * \{
 * This section describes the EtherMind OTP Profile APIs.
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief To register a callback with the OTP CE module.
 *
 *  \par Description:
 *       This function registers a callback with the OTp CE module, all events
 *       to be notified to this app will be provided to the registered
 *       callback.
 *
 *  \param [in] otp_ce_ntf_cb
 *         Application callback.
 *
 *  \param [out] otp_ce_ntf_cb_id
 *         OTC Callback ID for this application callback.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure
 */
GA_RESULT OTP_ce_register_ots_cb
          (
              /* IN */   OTP_CE_NTF_CB      otp_ce_ntf_cb,
              /* OUT */  OTP_CE_NTF_CB_ID * otp_ce_ntf_cb_id
          );

/**
 *  \brief To deregister association with OTP CE module.
 *
 *  \par Description:
 *       This function de-references the callback registered with OTP CE
 *       Module. No events generated at the OTP CE layer will be triggered
 *       post this function call.
 *
 *  \param [in] otp_ce_ntf_cb_id
 *         Application callback ID provided during init.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure
 */
GA_RESULT OTP_ce_deregister_ots_cb
          (
              /* IN */  OTP_CE_NTF_CB_ID otp_ce_ntf_cb_id
          );

/**
 *  \brief To Setup Object Transfer Service(OTS) Context
 *
 *  \par Description:
 *       This function does service,char and desc discovery for the requested
 *       service handle range and associates the service range for this
 *       session.
 *       The callback ID provided will be tagged internally and will call the
 *       corresponding callback for any events wrt this OTS Session.
 *
 *  \param [in] otp_ce_ntf_cb_id
 *         Application callback ID provided during init.
 *
 *  \param [in] dev
 *         Peer device
 *
 *  \param [in] otc_svc_hndl_range
 *         OTS Service Handle range that this app is associated with.
 *
 *  \param [out] otp_ce_sess_id
 *         OTP CE provided session ID during OTS Session context set-up.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure
 */
GA_RESULT OTP_ce_setup_ots_ctx
          (
              /* IN */  OTP_CE_NTF_CB_ID    otp_ce_ntf_cb_id,
              /* IN */  GA_ENDPOINT       * dev,
              /* IN */  GA_BRR_SVC_RANGE  * otc_svc_hndl_range,
              /* IN */  OTP_CE_SESSION_ID * otp_ce_sess_id
          );

/**
 *  \brief To De-Register a OTS Session.
 *
 *  \par Description:
 *       This function de-references the session details.
 *
 *  \param [in] otp_ce_sess_id
 *         OTP CE provided session ID during OTS Session context set-up.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure
 */
GA_RESULT OTP_ce_deregister_ots_ctx
          (
              /* IN */  OTP_CE_SESSION_ID otp_ce_sess_id
          );

/**
 *  \brief To Connect Object Transfer Service(OTS) Data Channel
 *
 *  \par Description:
 *       This function enables to connect the OTS data channel on request.
 *
 *  \param [in] otp_ce_sess_id
 *         OTP CE provided session ID.
 *
 *  \param [in] otp_ce_data_channel_mode
 *         OTP CE Data Channel Mode - CBFC/ECBFC
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure
 *          If GA_SUCCESS,
 *          If OTS Channel is established, OTP_CE_DATA_CHANNEL_UP_CNF is
 *          notified.
 */
GA_RESULT OTP_ce_setup_object_data_channel
          (
              /* IN */  OTP_CE_SESSION_ID        otp_ce_sess_id,
              /* IN */  OTP_CE_DATA_CHANNEL_MODE otp_ce_data_channel_mode
          );

/**
 *  \brief To Release Object Transfer Service(OTS) Data Channel
 *
 *  \par Description:
 *       This function enables to disconnect the OTS data channel on request.
 *
 *  \param [in] otp_ce_sess_id
 *         OTP CE provided session ID.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure
 *          If GA_SUCCESS,
 *          If OTS Channel is released, OTP_CE_DATA_CHANNEL_DOWN_CNF is
 *          notified.
 */
GA_RESULT OTP_ce_release_object_data_channel
          (
              /* IN */  OTP_CE_SESSION_ID otp_ce_sess_id
          );

/**
 *  \brief To Configure a Char for Indications.
 *
 *  \par Description:
 *       This function enables/disables Indications.
 *
 *  \param [in] otp_ce_sess_id
 *         OTP CE provided session ID during OTS Session context set-up.
 *
 *  \param [in] otp_ce_exp_evt_id
 *         Expected event ID on completion of this operation.
 *
 *  \param [in] char_uuid
 *         Char UUID on which the operation is to be performed.
 *
 *  \param [in] otp_ce_ind_flag
 *         Flag to indicate enable/disable Indications
 *         0x00 -> Disable
 *         0x01 -> Enable
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure.
 *          If Ind is enabled/disabled,
 *          OTP_CE_ENABLE_ALL_CFG_CNF/OTP_CE_DISABLE_ALL_CFG_CNF is notified.
 */
GA_RESULT OTP_ce_configure_context_char
          (
              /* IN */  OTP_CE_SESSION_ID otp_ce_sess_id,
              /* IN */  OTP_CE_EVT_ID     otp_ce_exp_evt_id,
              /* IN */  UINT16            char_uuid,
              /* IN */  UINT8             otp_ce_ind_flag
          );

/**
 *  \brief To perform Read operation on a Char.
 *
 *  \par Description:
 *       This function triggers read request.
 *
 *  \param [in] otp_ce_sess_id
 *         OTP CE provided session ID during OTS Session context set-up.
 *
 *  \param [in] otp_ce_exp_evt_id
 *         Expected event ID on completion of this operation.
 *
 *  \param [in] char_uuid
 *         Char UUID on which the operation is to be performed.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure.
 *          When read response is received from peer, OTP_CE_READ_XXX_CNF is
 *          notified.
 */
GA_RESULT OTP_ce_read_request
          (
              /* IN */  OTP_CE_SESSION_ID otp_ce_sess_id,
              /* IN */  OTP_CE_EVT_ID     otp_ce_exp_evt_id,
              /* IN */  UINT16            char_uuid
          );

/**
 *  \brief To perform Write operation on a Char.
 *
 *  \par Description:
 *       This function triggers write request.
 *
 *  \param [in] otp_ce_sess_id
 *         OTC provided session ID during OTS Session context set-up.
 *
 *  \param [in] char_uuid
 *         Char UUID on which the operation is to be performed.
 *
 *  \param [in] otp_ce_exp_evt_id
 *         Expected event ID on completion of this operation.
 *
 *  \param [in] data
 *         Data to be written.
 *
 *  \param [in] len
 *         Len of the data to be written
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure.
 *          Once the response is received from peer,
 *          OTP_CE_XXX_CNF is notified, here XXX is the name of the char.
 */
GA_RESULT OTP_ce_write_request
          (
              /* IN */  OTP_CE_SESSION_ID   otp_ce_sess_id,
              /* IN */  UINT16              char_uuid,
              /* IN */  OTP_CE_EVT_ID       otp_ce_exp_evt_id,
              /* IN */  UINT8             * data,
              /* IN */  UINT16              len
          );

/**
 *  \brief To Configure OACP for Indications.
 *
 *  \par Description:
 *       This function enables/disables OACP for Indications.
 *
 *  \param [in] otp_ce_sess_id
 *         OTP CE provided session ID during OTS Session context set-up.
 *
 *  \param [in] otp_ce_ind_flag
 *         Flag to indicate enable/disable indications
 *         0x00 -> Disable
 *         0x01 -> Enable
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure.
 *          If Ind is enabled/disbaled, OTC_IND_CONFIG_CNF is notified.
 */
#define OTP_ce_config_ind_OACP(inst, otp_ce_ind_flag) \
        OTP_ce_configure_context_char((inst), (OTP_CE_OACP_READ_IND), (GA_CHAR_OTS_CHAR_OACP), (otp_ce_ind_flag))

/**
 *  \brief To Configure OLCP for Indications.
 *
 *  \par Description:
 *       This function enables/disables OLCP for Indications.
 *
 *  \param [in] otp_ce_sess_id
 *         OTP CE provided session ID during OTS Session context set-up.
 *
 *  \param [in] otp_ce_ind_flag
 *         Flag to indicate enable/disable indications
 *         0x00 -> Disable
 *         0x01 -> Enable
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure.
 *          If Ind is enabled/disbaled, OTC_IND_CONFIG_CNF is notified.
 */
#define OTP_ce_config_ind_OLCP(inst, otp_ce_ind_flag) \
        OTP_ce_configure_context_char((inst), (OTP_CE_OLCP_GOTO_IND), (GA_CHAR_OTS_CHAR_OLCP), (otp_ce_ind_flag))

/**
 *  \brief To Configure Obj Changed for Indications.
 *
 *  \par Description:
 *       This function enables/disables Obj Changed for Indications.
 *
 *  \param [in] otp_ce_sess_id
 *         OTP CE provided session ID during OTS Session context set-up.
 *
 *  \param [in] otp_ce_ind_flag
 *         Flag to indicate enable/disable indications
 *         0x00 -> Disable
 *         0x01 -> Enable
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure.
 *          If Ind is enabled/disbaled, OTC_IND_CONFIG_CNF is notified.
 */
#define OTP_ce_config_ind_obj_chgnd(inst, otp_ce_ind_flag) \
        OTP_ce_configure_context_char((inst), (OTP_CE_OBJ_CHGD_IND), (GA_CHAR_OTS_CHAR_OBJ_CHG), (otp_ce_ind_flag))

/**
 *  \brief To Read OTS Feature.
 *
 *  \par Description:
 *       This function reads OTS Feature.
 *
 *  \param [in] otp_ce_sess_id
 *         OTP CE provided session ID during OTS Session context set-up.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure.
 *          When read response is received from peer, OTC_READ_OTS_FEATURE_CNF
 *          is notified.
 */
#define OTP_ce_read_OTS_feature(otp_ce_sess_id) \
        OTP_ce_read_request((otp_ce_sess_id), (OTP_CE_READ_FEATURE_NAME_CNF), (GA_CHAR_OTS_CHAR_OTS_FEATURE))

 /**
 *  \brief To Read Object Name.
 *
 *  \par Description:
 *       This function reads Object Name.
 *
 *  \param [in] otp_ce_sess_id
 *         OTP CE provided session ID during OTS Session context set-up.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure.
 *          When read response is received from peer, OTC_READ_OBJ_NAME_CNF
 *          is notified.
 */
#define OTP_ce_read_Obj_Name(otp_ce_sess_id) \
        OTP_ce_read_request((otp_ce_sess_id), (OTP_CE_READ_OBJ_NAME_CNF), (GA_CHAR_OTS_CHAR_OBJ_NAME))

/**
 *  \brief To Read Object Type.
 *
 *  \par Description:
 *       This function reads Object Type.
 *
 *  \param [in] otp_ce_sess_id
 *         App Registered ID provided during registration.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure.
 *          When read response is received from peer, OTP_CE_READ_OBJ_TYPE_CNF
 *          is notified.
 */
#define OTP_ce_read_obj_type(otp_ce_sess_id) \
        OTP_ce_read_request((otp_ce_sess_id), (OTP_CE_READ_OBJ_TYPE_CNF), (GA_CHAR_OTS_CHAR_OBJ_TYPE))

/**
 *  \brief To Read Obj Size Feature.
 *
 *  \par Description:
 *       This function reads OTS Object Size.
 *
 *  \param [in] otp_ce_sess_id
 *         OTP CE provided session ID during OTS Session context set-up.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure.
 *          When read response is received from peer, OTC_READ_OBJ_SIZE_CNF
 *          is notified.
 */
#define OTP_ce_read_obj_size(otp_ce_sess_id) \
        OTP_ce_read_request((otp_ce_sess_id), (OTP_CE_READ_OBJ_SIZE_CNF), (GA_CHAR_OTS_CHAR_OBJ_SIZE))

/**
 *  \brief To Read Obj First Created.
 *
 *  \par Description:
 *       This function reads Obj First Created.
 *
 *  \param [in] otp_ce_sess_id
 *         OTP CE provided session ID during OTS Session context set-up.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure.
 *          When read response is received from peer,
 *          OTP_CE_READ_OBJ_FIRST_CREATED_CNF is notified.
 */
#define OTP_ce_read_obj_first_created(otp_ce_sess_id) \
        OTP_ce_read_request((otp_ce_sess_id), (OTP_CE_READ_OBJ_FIRST_CREATED_CNF), (GA_CHAR_OTS_CHAR_FIRST_CREATED))

/**
 *  \brief To Read Obj Last Modified.
 *
 *  \par Description:
 *       This function reads Obj Last Modified.
 *
 *  \param [in] otp_ce_sess_id
 *         OTP CE provided session ID during OTS Session context set-up.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure.
 *          When read response is received from peer,
 *          OTP_CE_READ_OBJ_LAST_MOD_CNF is notified.
 */
#define OTP_ce_read_obj_last_mod(otp_ce_sess_id) \
        OTP_ce_read_request((otp_ce_sess_id), (OTP_CE_READ_OBJ_LAST_MOD_CNF), (GA_CHAR_OTS_CHAR_LAST_MOD))

/**
 *  \brief To Read Obj ID.
 *
 *  \par Description:
 *       This function reads Object ID.
 *
 *  \param [in] otp_ce_sess_id
 *         OTP CE provided session ID during OTS Session context set-up.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure.
 *          When read response is received from peer,
 *          OTP_CE_READ_OBJ_ID_CNF is notified.
 */
#define OTP_ce_read_obj_ID(otp_ce_sess_id) \
        OTP_ce_read_request((otp_ce_sess_id), (OTP_CE_READ_OBJ_ID_CNF), (GA_CHAR_OTS_CHAR_OBJ_ID))

/**
 *  \brief To Read Obj Properties.
 *
 *  \par Description:
 *       This function reads Obj Properties.
 *
 *  \param [in] otp_ce_sess_id
 *         OTP CE provided session ID during OTS Session context set-up.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure.
 *          When read response is received from peer,
 *          OTP_CE_READ_OBJ_PROP_CNF is notified.
 */
#define OTP_ce_read_obj_prop(otp_ce_sess_id) \
        OTP_ce_read_request((otp_ce_sess_id), (OTP_CE_READ_OBJ_PROP_CNF), (GA_CHAR_OTS_CHAR_OBJ_PROP))

/**
 *  \brief To Read Obj List Filter.
 *
 *  \par Description:
 *       This function reads Obj List Filter.
 *
 *  \param [in] otp_ce_sess_id
 *         OTP CE provided session ID during OTS Session context set-up.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure.
 *          When read response is received from peer,
 *          OTP_CE_READ_OBJ_LIST_FILTER_CNF is notified.
 */
#define OTP_ce_read_obj_list_filter(otp_ce_sess_id) \
        OTP_ce_read_request((otp_ce_sess_id), (OTP_CE_READ_OBJ_LIST_FILTER_CNF), (GA_CHAR_OTS_CHAR_OBJ_LIST_FILTER))

/**
 *  \brief To perform Write - OACP Read Opcode.
 *
 *  \par Description:
 *       This function triggers write request on OACP Char - Read Opcode.
 *       It performs a read of Object contents of the current object ID.
 *       Offset and length specified will be used to get the Obj contents from
 *       remote peer. This involves data receive on OTS Transport channel.
 *
 *  \param [in] otp_ce_sess_id
 *         OTP CE provided session ID during OTS Session context set-up.
 *
 *  \param [in] otc_oacp_proc_read_param
 *         Offset and Length of the Object to be read via OACP Read.
 *
 *  \param [in] obj_type
 *         Type of the object to be read
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure.
 *          Once write response is receieved, OTP_CE_OACP_READ_CNF is
 *          notified. This also indicates that the object contents read will
 *          be notified in event OTP_CE_OBJ_DATA_IND.
 */
GA_RESULT OTP_ce_proc_OACP_read
           (
               /* IN */  OTP_CE_SESSION_ID          otp_ce_sess_id,
               /* IN */  OTC_OACP_PROC_READ_PARAM * otc_oacp_proc_read_param,
               /* IN */  UINT8                      obj_type
           );

/**
 *  \brief To perform Write - OLCP Goto Opcode.
 *
 *  \par Description:
 *       This function triggers write request on OLCP Char - Goto Opcode.
 *
 *  \param [in] otp_ce_sess_id
 *         OTP CE provided session ID during OTS Session context set-up.
 *
 *  \param [in] otc_obj_id
 *         Opcode and the Object ID to which the OTS need to point to.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure.
 *          Once write response is receieved, OTP_CE_OLCP_GOTO_CNF is
 *          notified.
 */
#define OTP_ce_proc_OLCP_goto(otp_ce_sess_id, otc_obj_id) \
        OTP_ce_write_request((otp_ce_sess_id), (GA_CHAR_OTS_CHAR_OLCP), (OTP_CE_OLCP_GOTO_CNF), ((UINT8 *)(otc_obj_id)), (sizeof(OTC_OLCP_GOTO_PARAM)))

/**
 *  \brief To perform Write - OLF No Filter.
 *
 *  \par Description:
 *       This function triggers write request on OLF Char - No Filter Opcode.
 *
 *  \param [in] otp_ce_sess_id
 *         OTS Session ID provided during OTS Session context set-up.
 *
 *  \param [in] otp_ce_olf_inst_id
 *         If otp_ce_olf_inst_id is 0, No Filter is applied to all the 3 instances.
 *         Else, only to the reequested instance i.e. 1/2/3.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure.
 *          If is 0, Once the filter is applied to all the 3 instances,
 *          OTP_CE_OLF_NO_FILTER_ALL_INST_CNF is received with status.
 *          Else, based on the instance requested,
 *          OTP_CE_OLF_NO_FILTER_INSTX_CNF is notified, where X is the
 *          instance requested.
 */
GA_RESULT OTP_ce_proc_OLF_no_filter
          (
              /* IN */  OTP_CE_SESSION_ID otp_ce_sess_id,
              /* IN */  UINT8             otp_ce_olf_inst_id
          );

/**
 *  \brief To Configure all Char for Indications.
 *
 *  \par Description:
 *       This function enables/disables Indications.
 *
 *  \param [in] otp_ce_sess_id
 *         OTP CE provided session ID during OTS Session context set-up.
 *
 *  \param [in] otp_ce_ind_flag
 *         Flag to indicate enable/disable Indications
 *         0x00 -> Disable
 *         0x01 -> Enable
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure.
 *          If Ind is enabled/disabled,
 *          OTP_CE_ENABLE_ALL_CFG_CNF/OTP_CE_DISABLE_ALL_CFG_CNF is notified.
 */
GA_RESULT OTP_ce_config_ind_all
          (
              /* IN */  OTP_CE_SESSION_ID otp_ce_sess_id,
              /* IN */  UINT8             otp_ce_ind_flag
          );

#ifdef __cplusplus
};
#endif

/** \} */

#endif /* OTP_CLIENT */

#endif /* _H_OTC_ */
