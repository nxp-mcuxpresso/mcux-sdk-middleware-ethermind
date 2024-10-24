
/**
 *  \file ga_brr_pl.h
 *
 *
 */

/*
 *  Copyright (C) 2020. Mindtree Limited.
 *  All rights reserved.
 */

#ifndef _H_GA_BRR_PL_
#define _H_GA_BRR_PL_
/* --------------------------------------------- Header File Inclusion */
/* GA Bearer Related Includes */
#include "GA_bearer_api.h"
#include "BT_device_queue.h"
#if (defined GATT_CLIENT || defined GATT_SERVER)
#include "BT_att_api.h"
#endif /* (defined GATT_CLIENT || defined GATT_SERVER) */

/* Enable MTU Exchange handling at Bearer */
#define GA_BRR_HANDLE_MTUXCHG

/* --------------------------------------------- Global Definitions */
/** TODO :
 * Move this section to some other location
 */
#if 0
#define GA_BRR_PL_ERR(...) CONSOLE_OUT(__VA_ARGS__)
#define GA_BRR_PL_TRC(...) CONSOLE_OUT(__VA_ARGS__)
#define GA_BRR_PL_INF(...) CONSOLE_OUT(__VA_ARGS__)
#define GA_brr_pl_debug_dump_bytes(b,l)  appl_dump_bytes((b), (l))
#else /* 0 */
#define GA_BRR_PL_ERR(...)               EM_debug_error(GA_MODULE_ID,__VA_ARGS__)
#define GA_BRR_PL_TRC(...)               EM_debug_trace(GA_MODULE_ID,__VA_ARGS__)
#define GA_BRR_PL_INF(...)               EM_debug_info(GA_MODULE_ID,__VA_ARGS__)
#define GA_brr_pl_debug_dump_bytes(b,l)  EM_debug_dump_bytes(GA_MODULE_ID, (b), (l))
#endif /* 0 */

/* ============================= Limits ============================== */
#define GA_BRR_MAX_CONTEXTS                                   25U
#define GA_BRR_MAX_DEVICE_LIST_COUNT                          5U
#define GA_BRR_MAX_ACTIVITY_CNTX                              10U

#define GA_BRR_DEVICE_INVALID_MTU                             0x0000U
#define GA_BRR_DEVICE_DEFAULT_MTU                             64U

/* --------------------------------------------- Structures/Data Types */
typedef struct _GA_BRR_EXTENDED_SCAN_PARAMS
{
    UINT8  own_addr_type;
    UINT8  scan_filter_policy;
    UINT8  scan_phy;
    UINT8  scan_type;
    UINT16 scan_interval;
    UINT16 scan_window;
    UINT8  filter_duplicates;
    UINT16 duration;
    UINT16 period;
}GA_BRR_EXTENDED_SCAN_PARAMS;

typedef struct _GA_BRR_PERIODIC_SYNC_PARAMS
{
    UINT8   options;
    UINT16  skip;
    UINT16  sync_timeout;
    UINT8   sync_cte_type;
}GA_BRR_PERIODIC_SYNC_PARAMS;

typedef struct _GA_BRR_PERIODIC_ADV_PARAMS
{
    UINT16  per_adv_interval_min;
    UINT16  per_adv_interval_max;
    UINT16  per_adv_prty;
}GA_BRR_PERIODIC_ADV_PARAMS;

typedef struct _GA_BRR_EXTENDED_ADV_PARAMS
{
    UINT16  adv_event_properties;
    UINT32  pri_adv_interval_min;
    UINT32  pri_adv_interval_max;
    UINT8   pri_adv_channel_map;
    UINT8   own_addr_type;
    /* Own Address: Used for Broadcast Announcements with Random Address */
    UINT8   own_addr[GA_BD_ADDR_SIZE];
    UINT8   peer_addr_type;
    UINT8   peer_addr[GA_BD_ADDR_SIZE];
    UINT8   adv_filter_policy;
    INT8    adv_tx_power;
    UINT8   pri_adv_phy;
    UINT8   sec_adv_max_skip;
    UINT8   sec_adv_phy;
    UINT8   scan_req_nfy_enable;
    UINT16  duration;
    /* TODO: If we need to have more than 1 Set ID? */
    UINT8   max_ext_adv_evts;
    UINT8   frag_pref;
} GA_BRR_EXTENDED_ADV_PARAMS;

typedef struct _GA_BRR_BROADCAST_SYNC_PARAMS
{
    UINT8   mse;
    UINT16  sync_timeout;
}GA_BRR_BROADCAST_SYNC_PARAMS;

typedef struct _GA_BRR_BCTEST_PARAMS
{
    UINT16 iso_interval;
    UINT16 max_pdu;
    UINT8  nse;
    UINT8  bn;
    UINT8  irc;
    UINT8  pto;
} GA_BRR_BCTEST_PARAMS;

typedef struct _GA_BRR_DISPATCH_BH_PARAMS
{
    GA_BRR_PRF_HANDLE        pid;
    GA_BRR_DEVICE            device;
    GA_BRR_EVENT_PARAMS      event_params;
    void                    *context;
} GA_BRR_DISPATCH_BH_PARAMS;

/* Configuration structure */
typedef struct _GA_BRR_CONFIG
{
    /* Max supported Profile and Service contexts at bearer */
    UINT8 config_GA_BRR_MAX_CONTEXTS;

    /* Max supported device connection instances */
    UINT8 config_GA_BRR_MAX_DEVICE_LIST_COUNT;

    /* Max supported activity contexts */
    UINT8 config_GA_BRR_MAX_ACTIVITY_CNTX;

} GA_BRR_CONFIG;

/* Global Configuration for GA Bearer */
extern GA_BRR_CONFIG ga_brr_global_config;

/**
 * Call Back to Inform GA BRR Internal layer from GA BRR Platform Abstraction
 *
 * \param [in] device        Peer Device Info
 * \param [in] context       Reference context
 * \param [in] brr_role      Bearer Internal Role
 * \param [in] inst_handle   Instance handle
 * \param [in] event_type    Event Type
 * \param [in] event_status  Event Status
 * \param [in] event_data    Event Data
 * \param [in] event_datalen Event Data Length
 */
typedef GA_RESULT (* GA_BRR_PL_CB)
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

/* --------------------------------------------- Macros */
/* Initialize the global configuration */
#define GA_BRR_INIT_CONFIG(config) \
    (config).config_GA_BRR_MAX_CONTEXTS = GA_BRR_MAX_CONTEXTS; \
    (config).config_GA_BRR_MAX_DEVICE_LIST_COUNT = GA_BRR_MAX_DEVICE_LIST_COUNT; \
    (config).config_GA_BRR_MAX_ACTIVITY_CNTX = GA_BRR_MAX_ACTIVITY_CNTX;

/* Macro to access global configuration */
#define GA_BRR_CONFIG_LIMITS(x) ga_brr_global_config.config_##x

/* Macros to Define, Declare, Init and DeInit global configuration */
#define GA_BRR_DEFINE_GLOBAL_ARRAY  GA_DEFINE_GLOBAL_ARRAY
#define GA_BRR_DECLARE_GLOBAL_ARRAY GA_DECLARE_GLOBAL_ARRAY
#define GA_BRR_INIT_GLOBAL_ARRAY    GA_INIT_GLOBAL_ARRAY
#define GA_BRR_DEINIT_GLOBAL_ARRAY  GA_DEINIT_GLOBAL_ARRAY
#define GA_BRR_DEFINE_LOCAL_ARRAY   GA_DEFINE_LOCAL_ARRAY
#define GA_BRR_INIT_LOCAL_ARRAY     GA_INIT_LOCAL_ARRAY
#define GA_BRR_DEINIT_LOCAL_ARRAY   GA_DEINIT_LOCAL_ARRAY

/* --------------------------------------------- Internal Functions */

/* --------------------------------------------- API Declarations */
/* ----------------------------------------------------------------------- */
/* ======================General - Role Agnostic========================== */
/* ----------------------------------------------------------------------- */
void ga_brr_register(void);

GA_RESULT ga_brr_init_pl(void);
GA_RESULT ga_brr_register_pl_cb(GA_BRR_PL_CB cb);
GA_RESULT ga_brr_shutdown_pl(void);

void ga_rpa_complete(UCHAR evt, GA_RESULT status, UCHAR* data, UINT16 datalen);

GA_RESULT ga_search_remote_addr
          (
              /* OUT */ UCHAR       * hndl, /* Device Reference */
              /* IN */  GA_ENDPOINT * addr, /* Remote Device to be searched */
              /* IN */  UCHAR         link_type
          );

GA_RESULT ga_get_bd_addr_from_dev_hndl
           (
               DEVICE_HANDLE  * hndl,
               GA_ENDPOINT * bd_addr
           );

/* ----------------------------------------------------------------------- */
/* =========================Profile - Related============================= */
/* ----------------------------------------------------------------------- */
GA_RESULT ga_brr_discover_service_pl
          (
              /* IN */ GA_BRR_PRF_HANDLE pid,
              /* IN */ GA_BRR_DEVICE     * device,
              /* IN */ GA_BRR_SVC_INFO   * svc_info,
              /* IN */ UCHAR             disc_type,
              /* IN */ void              * context
          );
GA_RESULT ga_brr_get_service_composition_pl
          (
              /* IN */ GA_BRR_PRF_HANDLE   pid,
              /* IN */ GA_BRR_DEVICE     * device,
              /* IN */ GA_BRR_SVC_INFO   * service,
              /* IN */ void              * context
          );
GA_RESULT ga_brr_get_characteristic_composition_pl
          (
              /* IN */ GA_BRR_PRF_HANDLE   pid,
              /* IN */ GA_BRR_DEVICE     * device,
              /* IN */ GA_BRR_CHAR_RANGE * characteristic,
              /* IN */ void              * context
          );
GA_RESULT ga_brr_read_characteristic_pl
          (
              /* IN */ GA_BRR_PRF_HANDLE pid,
              /* IN */ GA_BRR_DEVICE     * device,
              /* IN */ GA_BRR_CHR_HANDLE characteristic,
              /* IN */ void              * context
          );
GA_RESULT ga_brr_write_characteristic_pl
          (
              /* IN */ GA_BRR_PRF_HANDLE pid,
              /* IN */ GA_BRR_DEVICE     * device,
              /* IN */ GA_BRR_CHR_HANDLE characteristic,
              /* IN */ GA_BRR_CHR_VAL    * value,
              /* IN */ UINT8             wwr,
              /* IN */ void              * context
          );
GA_RESULT ga_brr_config_notification_pl
          (
              /* IN */ GA_BRR_PRF_HANDLE pid,
              /* IN */ GA_BRR_DEVICE     * device,
              /* IN */ GA_BRR_CHR_HANDLE characteristic,
              /* IN */ UINT8             state,
              /* IN */ void              * context
          );
GA_RESULT ga_brr_config_adv
          (
              GA_BRR_PRF_HANDLE pid,
              UINT8   type,
              UINT8   handle,
              UINT8   enable,
              UCHAR * data,
              UINT8   data_len,
              void  * context
          );
GA_RESULT ga_brr_config_scan
          (
              GA_BRR_PRF_HANDLE   pid,
              UCHAR               enable,
              void              * context
          );
GA_RESULT ga_brr_config_sync
          (
              GA_BRR_PRF_HANDLE pid,
              UINT16            handle,
              GA_BRR_DEVICE   * device,
              void            * context
          );
GA_RESULT ga_brr_config_sync_cancel
          (
              GA_BRR_PRF_HANDLE pid,
              void            * context
          );
GA_RESULT ga_brr_config_broadcast
          (
              GA_BRR_PRF_HANDLE    pid,
              UINT8                handle,
              UINT8                adv_handle,
              GA_BRR_BCAST_PARAM * param,
              void               * context
          );
GA_RESULT ga_brr_config_broadcast_sync
          (
              GA_BRR_PRF_HANDLE         pid,
              UINT8                     handle,
              UINT16                    sync_handle,
              GA_BRR_BCAST_SYNC_PARAM * sync_params,
              void                    * context
          );
void ga_brr_set_default_broadcast_settings(void);

void ga_brr_dispatch_event_bh
     (
         void * args,
         UINT16 args_len
     );

#ifdef GA_BRR_HANDLE_MTUXCHG
void ga_brr_gatt_xchg_mtu(UINT8 enable);
#endif /* GA_BRR_HANDLE_MTUXCHG */

/* ----------------------------------------------------------------------- */
/* =========================Service - Related============================= */
/* ----------------------------------------------------------------------- */
GA_RESULT ga_brr_add_service_pl
          (
              /* IN  */ GA_BRR_UUID     service_uuid,
              /* IN  */ UINT8           service_type,
              /* IN */  UCHAR           lkid,
              /* OUT */ GA_BRR_SVC_INST * sid
          );
GA_RESULT ga_brr_include_service_add_pl
          (
              /* IN  */ GA_BRR_SVC_INST sid,
              /* IN  */ GA_BRR_UUID     service_uuid,
              /* IN  */ UINT8           service_state,
              /* IN */  UCHAR           lkid,
              /* OUT */ GA_BRR_SVC_INST * isid
          );
GA_RESULT ga_brr_add_characteristic_pl
          (
              /* IN  */ GA_BRR_SVC_INST sid,
              /* IN  */ GA_BRR_UUID     char_uuid,
              /* IN  */ UINT16          char_property,
              /* IN  */ GA_BRR_CHR_VAL  * value,
              /* IN */  UCHAR           lkid,
              /* OUT */ GA_BRR_CHR_INST * cid
          );
GA_RESULT ga_brr_manage_service_pl
          (
              /* IN  */ UINT8 sid,
              /* IN  */ UINT8 iid,
              /* IN  */ UINT8 state
          );
GA_RESULT ga_brr_manage_characteristic_pl
          (
              /* IN  */ UINT8 sid,
              /* IN  */ UINT8 cid,
              /* IN  */ UINT8 state
          );
GA_RESULT ga_brr_update_characteristic_value_pl
          (
              /* IN */ GA_BRR_SVC_INST sid,
              /* IN */ GA_BRR_UUID     char_uuid,
              /* IN */ GA_BRR_CHR_INST cid,
              /* IN */ GA_BRR_CHR_VAL  * value
          );
GA_RESULT ga_brr_write_characteristic_rsp_pl
          (
              /* IN */ GA_BRR_DEVICE      * device,
              /* IN */ GA_BRR_CHR_CONTEXT * ctx,
              /* IN */ UINT16             status
          );
GA_RESULT ga_brr_read_characteristic_rsp_pl
          (
              /* IN */ GA_BRR_DEVICE      * device,
              /* IN */ GA_BRR_CHR_CONTEXT * ctx,
              /* IN */ UINT16             status,
              /* IN */ GA_BRR_CHR_VAL     * value
          );
GA_RESULT ga_brr_notify_characteristic_pl
          (
              /* IN */ GA_BRR_DEVICE   * device,
              /* IN */ GA_BRR_SVC_INST sid,
              /* IN */ GA_BRR_UUID     char_uuid,
              /* IN */ GA_BRR_CHR_INST cid,
              /* IN */ GA_BRR_CHR_VAL  * value,
              /* IN */ UINT8           nwr
          );
GA_RESULT ga_brr_dispatch_event_pl
          (
              /* IN */ GA_BRR_PRF_HANDLE        pid,
              /* IN */ GA_BRR_DEVICE           *device,
              /* IN */ GA_BRR_EVENT_PARAMS     *event_params,
              /* IN */ void                    *context
          );
GA_RESULT ga_brr_rpa_operate_pl
          (
              /* IN */ GA_BRR_PRF_HANDLE     pid,
              /* IN */ UCHAR               * addr,
              /* IN */ UCHAR               * irk,
              /* IN */ void                * context
          );
GA_RESULT ga_brr_crypto_pl
          (
              /* IN */ UCHAR             op,
              /* IN */ void            * info,
              /* IN */ GA_BRR_CRYPTO_CB  cb,
              /* IN */ void            * context
          );

void ga_brr_dispatch_event_handler
     (
         /* IN */ GA_BRR_PRF_HANDLE        pid,
         /* IN */ GA_BRR_DEVICE           *device,
         /* IN */ GA_BRR_EVENT_PARAMS     *event_params,
         /* IN */ void                    *context
     );

GA_RESULT ga_brr_dyn_gatt_db_init_pl
          (
              void * db_blob
          );

GA_RESULT ga_brr_setup_pl(void);

GA_RESULT ga_brr_access_eadv_params_pl
          (
              UINT8 set,
              GA_BRR_EXTENDED_ADV_PARAMS * eadv_params
          );
GA_RESULT ga_brr_access_padv_params_pl
          (
              UINT8 set,
              GA_BRR_PERIODIC_ADV_PARAMS * padv_params
          );
GA_RESULT ga_brr_set_bctest_mode_pl (UINT8 state);
GA_RESULT ga_brr_access_bctest_params_pl
          (
              UINT8 set,
              GA_BRR_BCTEST_PARAMS * bctest_params
          );

GA_RESULT ga_brr_access_escan_params_pl
          (
              UINT8 set,
              GA_BRR_EXTENDED_SCAN_PARAMS * escan_params
          );
GA_RESULT ga_brr_access_psync_params_pl
          (
              UINT8 set,
              GA_BRR_PERIODIC_SYNC_PARAMS * psync_params
          );
GA_RESULT ga_brr_access_bsync_params_pl
          (
              UINT8 set,
              GA_BRR_BROADCAST_SYNC_PARAMS * bsync_params
          );
#if (defined GATT_CLIENT || defined GATT_SERVER)
API_RESULT ga_gatt_cb_pl
           (
               ATT_HANDLE    * handle,
               UCHAR         att_event,
               API_RESULT    event_result,
               void          * eventdata,
               UINT16        event_datalen
           );
#endif /* (defined GATT_CLIENT || defined GATT_SERVER) */

#endif /* _H_GA_BRR_PL_ */


