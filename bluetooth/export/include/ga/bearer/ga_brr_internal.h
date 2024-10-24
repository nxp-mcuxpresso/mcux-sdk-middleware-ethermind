
/**
 *  \file ga_brr_internal.h
 *
 *  \brief This file defines the Generic Audio Bearer Internal Interface - includes
 *  Data Structures and Methods.
 */

/**
 *  Copyright (C) 2020. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_GA_BRR_INTERNAL_
#define _H_GA_BRR_INTERNAL_

/* --------------------------------------------- Header File Inclusion */
#include "GA_bearer_api.h"
#include "ga_brr_pl.h"

/* --------------------------------------------- Debug Macros */
#define GA_BRR_ERR                 GA_BRR_PL_ERR
#define GA_BRR_TRC                 GA_BRR_PL_TRC
#define GA_BRR_INF                 GA_BRR_PL_INF
#define GA_brr_debug_dump_bytes    GA_brr_pl_debug_dump_bytes


/* --------------------------------------------- Global Definitions */

/* --------------------------------------------- Data types /Structures */
typedef struct _GA_BRR_CONTEXT
{
    /** Context callback */
    GA_BRR_CB cb;

    /** Profile Module ID */
    UINT32 pid;

    /** Service ID */
    UINT8 sid;

} GA_BRR_CONTEXT;

/* --------------------------------------------- Macros */

/* --------------------------------------------- APIs */
GA_RESULT ga_brr_context_alloc
          (
              /* OUT */ UINT8 * id
          );
GA_RESULT ga_brr_context_free
          (
              /* IN */ UINT8 id
          );
GA_RESULT ga_brr_context_search_pid
          (
              /* IN */ UINT32 id,
              /* OUT */ GA_BRR_PRF_HANDLE * pid
          );
GA_RESULT ga_brr_context_search_sid
          (
              /* IN  */ GA_BRR_SVC_INST sid,
              /* OUT */ UCHAR           * id
          );

GA_RESULT ga_brr_int_cb
          (
              /* IN */ GA_BRR_DEVICE * device,
              /* IN */ void          * context,
              /* IN */ UCHAR         brr_role,
              /* IN */ void          * inst_handle,
              /* IN */ UINT8         event_type,
              /* IN */ UINT16        event_status,
              /* IN */ void          * event_data,
              /* IN */ UINT16        event_datalen
          );

/** GA Bearer Internal Initialization */
GA_RESULT ga_brr_int_init(void);

/** Bearer interface function declarations */
GA_RESULT ga_brr_init(GA_BRR_CB cb);
GA_RESULT ga_brr_shutdown(void);

GA_RESULT ga_brr_add_service
          (
              /* IN  */ GA_BRR_UUID service_uuid,
              /* IN  */ UINT8 service_type,
              /* IN  */ GA_BRR_SERVICE_CB cb,
              /* OUT */ GA_BRR_SVC_INST * sid
          );
GA_RESULT ga_brr_remove_service
          (
              /* IN  */ GA_BRR_SVC_INST sid
          );
GA_RESULT ga_brr_include_service
          (
              /* IN  */ GA_BRR_SVC_INST sid,
              /* IN  */ GA_BRR_UUID service_uuid,
              /* IN  */ UINT8 service_state,
              /* OUT */ GA_BRR_SVC_INST * isid
          );
GA_RESULT ga_brr_add_characteristic
          (
              /* IN  */ GA_BRR_SVC_INST sid,
              /* IN  */ GA_BRR_UUID     char_uuid,
              /* IN  */ UINT16          char_property,
              /* IN  */ GA_BRR_CHR_VAL  * value,
              /* OUT */ GA_BRR_CHR_INST * cid
          );
GA_RESULT ga_brr_manage_service
          (
              /* IN  */ UINT8 sid,
              /* IN  */ UINT8 iid,
              /* IN  */ UINT8 state
          );
GA_RESULT ga_brr_manage_characteristic
          (
              /* IN  */ UINT8 sid,
              /* IN  */ UINT8 cid,
              /* IN  */ UINT8 state
          );
GA_RESULT ga_brr_write_characteristic_rsp
          (
              /* IN */ GA_BRR_DEVICE      * device,
              /* IN */ GA_BRR_CHR_CONTEXT * ctx,
              /* IN */ UINT16             status
          );
GA_RESULT ga_brr_read_characteristic_rsp
          (
              /* IN */ GA_BRR_DEVICE      * device,
              /* IN */ GA_BRR_CHR_CONTEXT * ctx,
              /* IN */ UINT16             status,
              /* IN */ GA_BRR_CHR_VAL     * value
          );
GA_RESULT ga_brr_notify_characteristic
          (
              /* IN */ GA_BRR_DEVICE   * device,
              /* IN */ GA_BRR_SVC_INST sid,
              /* IN */ GA_BRR_UUID     char_uuid,
              /* IN */ GA_BRR_CHR_INST cid,
              /* IN */ GA_BRR_CHR_VAL  * value,
              /* IN */ UINT8           nwr
          );
GA_RESULT ga_brr_setup_transport
          (
              /* IN */ GA_BRR_PRF_HANDLE pid,
              /* IN */ UINT8 type,
              /* IN */ UINT8 enable
          );
GA_RESULT ga_brr_discover_service
          (
              /* IN */ GA_BRR_PRF_HANDLE pid,
              /* IN */ GA_BRR_DEVICE     * device,
              /* IN */ GA_BRR_SVC_INFO   * svc_info,
              /* IN */ UCHAR             disc_type,
              /* IN */ void              * context
          );
GA_RESULT ga_brr_get_service_composition
          (
              /* IN */ GA_BRR_PRF_HANDLE   pid,
              /* IN */ GA_BRR_DEVICE     * device,
              /* IN */ GA_BRR_SVC_INFO   * service,
              /* IN */ void              * context
          );
GA_RESULT ga_brr_get_characteristic_composition
          (
              /* IN */ GA_BRR_PRF_HANDLE   pid,
              /* IN */ GA_BRR_DEVICE     * device,
              /* IN */ GA_BRR_CHAR_RANGE * characteristic,
              /* IN */ void              * context
          );
GA_RESULT ga_brr_read_characteristic
          (
              /* IN */ GA_BRR_PRF_HANDLE pid,
              /* IN */ GA_BRR_DEVICE     * device,
              /* IN */ GA_BRR_CHR_HANDLE characteristic,
              /* IN */ void              * context
          );
GA_RESULT ga_brr_write_characteristic
          (
              /* IN */ GA_BRR_PRF_HANDLE pid,
              /* IN */ GA_BRR_DEVICE     * device,
              /* IN */ GA_BRR_CHR_HANDLE characteristic,
              /* IN */ GA_BRR_CHR_VAL    * value,
              /* IN */ UINT8             wwr,
              /* IN */ void              * context
          );
GA_RESULT ga_brr_config_notification
          (
              /* IN */ GA_BRR_PRF_HANDLE pid,
              /* IN */ GA_BRR_DEVICE     * device,
              /* IN */ GA_BRR_CHR_HANDLE characteristic,
              /* IN */ UINT8             state,
              /* IN */ void              * context
          );
GA_RESULT ga_brr_register_profile
          (
              /* IN  */ UINT32 id,
              /* IN  */ GA_BRR_PROFILE_CB cb,
              /* OUT */ GA_BRR_PRF_HANDLE * pid
          );
GA_RESULT ga_brr_unregister_profile
          (
              /* IN */ GA_BRR_PRF_HANDLE pid
          );
GA_RESULT ga_brr_dispatch_event
          (
              /* IN */ GA_BRR_PRF_HANDLE        pid,
              /* IN */ GA_BRR_DEVICE           *device,
              /* IN */ GA_BRR_EVENT_PARAMS     *event_params,
              /* IN */ void                    *context
          );
GA_RESULT ga_brr_rpa_operate
          (
              /* IN */ GA_BRR_PRF_HANDLE     pid,
              /* IN */ UCHAR               * addr,
              /* IN */ UCHAR               * irk,
              /* IN */ void                * context
          );
GA_RESULT ga_brr_crypto
          (
              /* IN */ UCHAR             op,
              /* IN */ void            * info,
              /* IN */ GA_BRR_CRYPTO_CB  cb,
              /* IN */ void            * context
          );

#endif /* _H_GA_BRR_INTERNAL_ */

