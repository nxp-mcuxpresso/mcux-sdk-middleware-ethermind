
/**
 *  \file ots_internal.h
 *
 *  \brief This file defines the Object Transfer Server internal
 *         functionalities. Interaction with OTS transport, maintaining
 *         multiple contexts of OTC sessions.
 */

/*
 *  Copyright (C) 2020. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_OTS_INTERNAL_
#define _H_OTS_INTERNAL_

/* --------------------------------------------- Header File Inclusion */
#include "ots.h"
#include "otp_common.h"
#include "ots_transport.h"

#ifdef OTP_SERVER
/** OTP Server Mutex Lock & Unlock */
#define OTP_SE_LOCK()
#define OTP_SE_UNLOCK()
#define OTP_SE_LOCK_VOID()
#define OTP_SE_UNLOCK_VOID()
/* --------------------------------------------- Global Definitions */
/*
 * Maximum number of OTS sessions that can be active concurrently.
 * Can be different applications using same/different OTS service instances
 * added for different activities.
 */
#define OTP_SE_OTS_MAX_INSTANCES                 8

/*
 * Maximum number of applications registered to the OTS module with callbacks.
 * An application can register a single callback and can still have multiple
 * OTS service instances added.
 */
#define OTP_SE_OTS_MAX_NTF_CB_CTX                5

 /* OTS session not established */
#define OTS_INST_UNUSED                          0xFF
/* --------------------------------------------- Data types /Structures */
/*
 * This provides a callback and an Identifier Look-Up. A single application
 * can have multiple OTS sessions and hence register a callback only once and
 * have multiple OTS session with same and/or different devices.
 */
typedef struct _OTP_SE_NTF_CB_CTX_
{
    OTP_SE_NTF_CB cb;
    OTP_SE_CB_ID  id;
} OTP_SE_NTF_CB_CTX;

typedef struct _OTP_OTS_ENTITY_
{
	/* Primary Service Instance to which this is Included, if any */
	GA_BRR_SVC_INST gatt_pri_svc_inst;

	/* Service Instance provided by GA Bearer Module during registration */
	GA_BRR_SVC_INST ots_svc_inst_id;

	/* OTS Callback associated */
	OTP_SE_CB_ID    ots_cb_id;

	/* Char Instance provided GA Bearer Module during registration */
	GA_BRR_CHR_INST ots_char_ots_feature;
	GA_BRR_CHR_INST ots_char_obj_name;
	GA_BRR_CHR_INST ots_char_obj_type;
	GA_BRR_CHR_INST ots_char_obj_size;
	GA_BRR_CHR_INST ots_char_obj_first_created;
	GA_BRR_CHR_INST ots_char_obj_last_mod;
	GA_BRR_CHR_INST ots_char_obj_id;
	GA_BRR_CHR_INST ots_char_obj_prop;
	GA_BRR_CHR_INST ots_char_oacp;
	GA_BRR_CHR_INST ots_char_olcp;
    GA_BRR_CHR_INST ots_char_olf_inst1;
    GA_BRR_CHR_INST ots_char_olf_inst2;
    GA_BRR_CHR_INST ots_char_olf_inst3;
	GA_BRR_CHR_INST ots_char_obj_chg;

}OTP_OTS_ENTITY;

/* Callback registered with GA Bearer for Server Callbacks only */
GA_RESULT ots_ga_brr_server_callback
          (
              /* IN */ GA_BRR_DEVICE * device,
              /* IN */ void          * context,
              /* IN */ OTP_SE_EVT_ID   event_type,
              /* IN */ UINT16          event_status,
              /* IN */ void          * event_data,
              /* IN */ UINT16          event_datalen
          );
/* --------------------------------------------- Macros */
/* --------------------------------------------- APIs */
GA_RESULT ots_fetch_entry_pos_for_cb(UINT8* cb_id);

/*
 * This function fetches a free index for a new OTS Service Instance add.
 */
GA_RESULT ots_fetch_free_sess_id
           (
               /* OUT */  OTP_SE_SESSION_ID * otp_se_sess_id
           );

/*
 * This function validates if already OTS is included for this primary
 * service instance.
 */
GA_RESULT ots_find_svc_inst_already_included
           (
               /* IN */  GATT_PRIMARY_SVC_INST * pri_svc_inst,
               /* OUT */ OTP_SE_SESSION_ID     * otp_se_sess_id
           );

/*
 * This function retrieves the OTS session ID based on the char instance ID.
 * This is called when read/write request is triggered from peer OTP - Client.
 */
GA_RESULT ots_fetch_session_id_evt_id
          (
              /* IN */  UINT8               event_type,
              /* IN */  UINT16              ots_char_inst_id,
              /* OUT */ OTP_SE_SESSION_ID * ots_inst_id,
			  /* OUT */ OTP_SE_EVT_ID     * ots_evt_id
          );

/*
 * This function fetches the char inst ID wrt this char UUID on this MCS
 * session.
 */
GA_RESULT ots_fetch_char_inst_id_from_char_uuid
          (
              /* IN */   OTP_SE_SESSION_ID   ots_inst_id,
              /* IN */   UINT16              char_uuid,
              /* OUT */  UINT8             * ots_char_inst_id
          );

#endif /* OTP_SERVER */

#endif /* _H_OTS_INTERNAL_ */
