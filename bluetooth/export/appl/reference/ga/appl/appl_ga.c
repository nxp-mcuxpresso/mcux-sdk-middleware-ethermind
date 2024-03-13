/**
 *  \file appl_ga.c
 *
 *  Reference application for GA Core interfaces
 */

/*
 *  Copyright (C) 2020. Mindtree Ltd.
 *  All rights reserved.
 */

/* --------------------------------------------- Header File Inclusion */

#include "appl_ga.h"

#include "appl_vcp.h"
#include "appl_micp.h"
#include "appl_csip.h"

#include "appl_ga_uc.h"
#include "appl_ga_bc.h"

#include "appl_mcp_ce.h"
#include "appl_mcp_se.h"

#include "appl_ccp_ce.h"
#include "appl_ccp_se.h"

#include "appl_tmap.h"
#include "appl_hap.h"

#include "appl_ga_utils_hci.h"

#include "appl_ga_utils_audio_src.h"
#include "appl_ga_utils_audio_snk.h"

#include "audio_pl.h"

#ifdef BT_GAM

#ifdef NXP_CODE
extern uint8_t local_cis_bis_feature_set;
#endif

/* Used to differentiate ongoing scan */
extern UINT8 is_scan_enabled;

/* Used to differentiate ongoing advertise */
extern UINT8 is_adv_enabled;

static const char ga_menu_options[] = " \n\
================ GA Main MENU ================ \n\
    0. Exit. \n\
    1. Refresh this Menu. \n\
\n\
================ Profile Management ~ Init ============ \n\
    2. GA Init. \n\
    3. GA Setup. \n\
\n\
================ Profile Management ~ Deinit ============ \n\
    4. GA Shutdown. \n\
\n\
================ GA PACS SERVER MENU ================ \n\
================ Service Management ~ Setup ============ \n\
    5. GA Register - PACS. \n\
\n\
================ Service Management ~ Operations(Notify) ============ \n\
    6. Update/Notify PACS - Audio Capability. \n\
    7. Update/Notify PACS - Available Audio Contexts. \n\
    8. Update/Notify PACS - Supported Audio Contexts. \n\
    9. Update/Notify PACS - Audio Locations. \n\
\n\
================ GA PACS CLIENT MENU ================ \n\
================ Context Management ~ Setup ============ \n\
   10. Setup PACS - Audio Role Discovery. \n\
\n\
================ Context Management ~ Release ============ \n\
   11. Release/Close PACS. \n\
\n\
================ Profile Management (PACS) ~ Operations(Read) ============ \n\
   12. Get PACS Capabilities - Audio Capability, Location, Supp/Avail Contexts \n\
\n\
   18. Set Local Device Address and Type for Connection \n\
\n\
================ Device Management ~ LE Advertise ============ \n\
   20. Enable/Disable LE Advertising - Legacy. [CAP - Acceptor, GAP - Peripheral] \n\
   21. Enable/Disable LE Advertising - Extended. [CAP - Acceptor, GAP - Peripheral] \n\
\n\
================ Device Management ~ LE Scan ============ \n\
   22. Enable/Disable LE Scan - Legacy. [CAP - Initiator, GAP - Central] \n\
   23. Enable/Disable LE Scan - Extended. [CAP - Initiator GAP - Central]  \n\
\n\
================ Device Management ~ LE Connection ============ \n\
   25. LE Create Connection. [CAP - Initiator GAP - Central] \n\
   26. LE Extended Create Connection. [CAP - Initiator GAP - Central]  \n\
\n\
================ Device Management ~ Authentication ============ \n\
   27. LE Legacy Authenticate and Encrypt. \n\
   28. LE LESC Authenticate and Encrypt. \n\
\n\
================ Device Management ~ Disconnection ============ \n\
   29. Disconnection. \n\
\n\
================ Device Management ~ Remote Features ============ \n\
   30. Read Remote Used Featues. \n\
\n\
================ Device Management ~ Setting ============ \n\
   31. Display all Connected Devices. \n\
   32. Set Connected Device Index. \n\
   33. Remove Device from Device Manager. \n\
   34. Reset Device Manager. \n\
\n\
================ GA Config Audio Dump MENU ================ \n\
   35. Configure Sink Audio Dump. \n\
   36. Configure Source Audio Dump. \n\
   37. Configure Sink Missed Sequence number display. \n\
   38. Configure Source Missed Sequence number display. \n\
\n\
================ GA Sub MENU ================ \n\
   40. Unicast Operations. \n\
   45. Broadcast Operations. \n\
\n\
================ Capture and Rendering Control MENU ================ \n\
   50. VCP Volume Controller Operations. \n\
   51. VCP Volume Renderer Operations. \n\
\n\
   55. MICP Microphone Controller Operations. \n\
   56. MICP Microphone Device Operations. \n\
\n\
================ GA CSIP MENU ================ \n\
   60. CSIP Set Coordinator Operations. \n\
   61. CSIP Set Member Operations. \n\
\n\
================ Content Control MENU ================ \n\
   65. MCP Media Control Client. \n\
   66. MCP Media Control Server. \n\
\n\
   70. CCP Call Control Client. \n\
   71. CCP Call Control Server. \n\
\n\
================ Device Application MENU ============= \n\
   75. GA TMAP Operations. \n\
   76. GA HAP Operations. \n\
\n\
================ Context Management ~ Persistence ============ \n\
   80. Get Context Info. \n\
   81. Set Context Info. \n\
   82. Free Saved Context Info. \n\
   83. Get Stream Context. \n\
   84. Set Stream Context. \n\
\n\
   85. Get CAP CS Context Info. \n\
   86. Set CAP CS Context Info. \n\
   88. Free Saved CAP CS Context Info. \n\
\n\
================ Configuration Management ~ Notification/Indication Settings ===== \n\
   90. Configure Notification \n\
\n\
================ CAP ~ Discovery and Setup ===== \n\
  100. Discover CAS \n\
  101. Setup CAS Member \n\
  102. Release CAS Member \n\
\n\
  105. CAP Lock Member \n\
\n\
  110. CAP Member Lock Update \n\
  111. CAP Member SIRK Update \n\
  112. CAP Member Size Update \n\
  113. CAP Member Rank Update \n\
\n\
  115. CAP Member Simulate Device Lock/Unlock \n\
\n\
  120. CAP Set Find count \n\
  121. CAP Set LockRequest \n\
  122. CAP Set LockRelease \n\
  123. CAP Set BeginOA \n\
  124. CAP Set EndOA \n\
  125. CAP Set NextOA \n\
\n\
  130. Scan/Stop Scan for CAS \n\
  131. Display Scan CAS devices \n\
  132. Verify RSI \n\
\n\
Your Option ?: ";

#ifdef BAP_SUPPORT_CONTEXT_MANAGE
DECL_STATIC GA_BRR_SVC_RANGE bap_svc_range[BAP_SERVICE_COUNT];
DECL_STATIC GA_CHAR_INFO* bap_char_info;
DECL_STATIC GA_BRR_SVC_RANGE* bap_svc_range_ptr;
DECL_STATIC GA_CHAR_INFO* bap_char_info_ptr;
DECL_STATIC UINT16 bap_total_char_count;

DECL_STATIC GA_STREAM_CONTEXT bap_stream[GA_MAX_SOURCE_STREAM_CONTEXTS + GA_MAX_SINK_STREAM_CONTEXTS];
DECL_STATIC UINT16 bap_stream_count;
#endif /* BAP_SUPPORT_CONTEXT_MANAGE */

/*
 * To Validate if we are Initializing through GA_Init() in appl_ga.c
 * or appl_ga_legacy.c
 */
extern UINT8 ga_init_status;

/* Session role selected for GA during Init */
DECL_STATIC UCHAR appl_ga_role;

#ifdef APPL_CAS_SETMEMBER
#define APPL_CAS_SM_SIRK_TYPE   CSIP_SIRK_TYPE_ENCRYPTED
#define APPL_CAS_SM_SIRK        {0xB8, 0x03, 0xEA, 0xC6, 0xAF, 0xBB, 0x65, 0xA2, 0x5A, 0x41, 0xF1, 0x53, 0x05, 0x68, 0x8E, 0x83}

/* CAS Server - Local Member */
typedef struct _CAS_MEMBER
{
    GA_SET_MEMBER member;
    UCHAR         enc_sirk[CSIP_SIRK_LEN];
}CAS_MEMBER;

CAS_MEMBER local_cas_sm;

/* Local SM Init */
void appl_ga_cs_sm_init(void);

#endif /* APPL_CAS_SETMEMBER */

#ifdef APPL_CAS_SETCOORDINATOR
/* CAS Devices DB */
extern CAS_DEVICES cas_devices[MAX_SCAN_CAS_DEVICES];

GA_BRR_EXTENDED_SCAN_PARAMS appl_ga_cas_escan_params;

#ifdef CSIP_SUPPORT_CONTEXT_MANAGE
DECL_STATIC GA_BRR_SVC_RANGE cap_cs_svc_range;
DECL_STATIC GA_CHAR_INFO* cap_cs_char_info;
DECL_STATIC GA_BRR_SVC_RANGE* cap_cs_svc_range_ptr;
DECL_STATIC GA_CHAR_INFO* cap_cs_char_info_ptr;
DECL_STATIC UINT16 cap_cs_total_char_count;
#endif /* CSIP_SUPPORT_CONTEXT_MANAGE */

#endif /* APPL_CAS_SETCOORDINATOR */

void appl_ga_module_init(int choice);
void appl_ga_brr_setup(void);

void appl_ga_uc_client_init(void);
void appl_ga_uc_client_shutdown(void);
void appl_ga_uc_server_init(void);
void appl_ga_uc_server_shutdown(void);
void appl_ga_bc_source_init(void);
void appl_ga_bc_source_shutdown(void);
void appl_ga_bc_sink_init(void);
void appl_ga_bc_sink_shutdown(void);

#ifdef APPL_CAS_SETCOORDINATOR

void appl_ga_set_default_cas_scan_settings(void);
GA_RESULT appl_ga_scan_for_cas(void);
GA_RESULT appl_ga_stop_scan_for_cas(void);
UINT8 appl_ga_is_dev_in_cas_db(UINT8* rsi);
GA_RESULT appl_ga_add_dev_into_cas_db(GA_ENDPOINT dev, UINT8* dev_rsi);
UINT8 appl_ga_utils_get_cas_dev_index(void);
void appl_ga_display_cas_db(void);
void appl_ga_reset_cas_db(void);

#endif /* APPL_CAS_SETCOORDINATOR */
/* --------------------------------------------- APIs */
GA_RESULT appl_ga_cap_callback
          (
              GA_ENDPOINT * device,
              UINT8         ga_event,
              UINT16        ga_status,
              void        * ga_data,
              UINT16        ga_datalen
          )
{
    GA_BRR_SVC_INFO  * svc;
    GA_SET_MEMBER    * csmem;
    CSIP_EVENT_INFO  * cas_csis_evt_info;
    UCHAR            * rsi;
    GA_RESULT          retval;
    UINT8              index;
    UINT8              set_handle;
    CSIP_SIRK        * cs_mem_sirk;
    UINT8              i;
    GA_SET_MEMBER      conn_dev_csmem_data;

    /* Initialize */
    svc = NULL;
    csmem = NULL;
    cas_csis_evt_info = NULL;
    rsi = NULL;
    retval = GA_FAILURE;
    index = 0U;
    set_handle = 0U;
    cs_mem_sirk = NULL;
    i = 0U;

    switch (ga_event)
    {
#ifdef APPL_CAS_SETCOORDINATOR
    case GA_CAP_DISCOVER_CNF:
        GA_CB_ENTRY("CAP Client");
        APPL_TRC("[Profile]     : CAP (0x%04X)\n", GA_SERVICE_CAS);
        APPL_TRC("[SECTION]     : CAP CLIENT EVENTS\n");
        APPL_TRC("[SUB-SECTION] : CAP COORDINATOR-SETUP\n");
        APPL_TRC("[TYPE]        : DISCOVER RESPONSE\n");
        appl_ga_utils_display_bdaddr_and_type(device);
        APPL_TRC("[Event Status]: 0x%04X\n", ga_status);
        APPL_TRC("[EVENT]       : GA_CAP_DISCOVER_CNF\n");

        if ((GA_SUCCESS != ga_status) &&
            (GA_CONTINUE != ga_status))
        {
            APPL_ERR("CAS Discovery Failed !\n");
            break;
        }

        if (GA_CONTINUE == ga_status)
        {
            svc = (GA_BRR_SVC_INFO *)ga_data;

            if (GA_SERVICE_CSIS == svc->uuid)
            {
                GA_FORMAT_DISPLAY();
                appl_ga_utils_display_svc_uuid(svc->uuid);
                GA_FORMAT_DISPLAY();
                appl_ga_utils_display_svc_range(svc->range);

                /* Update the details in Conn Device Manager */
                if (GA_SUCCESS == appl_ga_utils_get_conn_device_index(*device, &index))
                {
                    appl_ga_utils_update_cas_of_conn_dev(index, svc);
                }
            }
        }
        else
        {
            APPL_TRC("\n");
            GA_FORMAT_DISPLAY();
            APPL_TRC("Data Length: 0x%02X\n", ga_datalen);
            if (0U == ga_datalen)
            {
                APPL_TRC("Data: NULL\n");
            }
            APPL_TRC("CAS Discovery Successful\n");
        }
        break;

    case GA_CAP_SETUP_MEMBER_CNF:
        GA_CB_ENTRY("CAP Client");
        APPL_TRC("[Profile]     : CAP (0x%04X)\n", GA_SERVICE_CAS);
        APPL_TRC("[SECTION]     : CAP CLIENT EVENTS\n");
        APPL_TRC("[SUB-SECTION] : CAP COORDINATOR-SETUP\n");
        APPL_TRC("[TYPE]        : SETUP RESPONSE\n");
        appl_ga_utils_display_bdaddr_and_type(device);
        APPL_TRC("[Event Status]: 0x%04X\n", ga_status);
        APPL_TRC("[EVENT]       : GA_CAP_SETUP_MEMBER_CNF\n");

        if (GA_SUCCESS == ga_status)
        {
            csmem = (GA_SET_MEMBER *)ga_data;

            if (NULL != csmem)
            {
                APPL_TRC("\n");
                GA_FORMAT_DISPLAY();
                APPL_TRC("Data Length: 0x%02X\n", ga_datalen);
                APPL_TRC("Data:\n");

                APPL_TRC
                (
                    "Len: 0x%02X,  Set SIRK Type: ",
                    (UCHAR)sizeof(UINT8)
                );
                appl_csip_parse_and_display_sirk_type_value(csmem->sirk[0]);
                APPL_TRC
                (
                    "Len: 0x%02X,  Set SIRK Value: ",
                    CSIP_SIRK_LEN
                );
                /* 0th position holds the SIRK Type, Value starts from 1 */
                for (i = 1U; i <= CSIP_SIRK_LEN; i++)
                {
                    APPL_TRC("%02X ", csmem->sirk[i]);
                }
                APPL_TRC("\n");
                APPL_TRC
                (
                    "Len: 0x%02X,  Coordinated Set Size: 0x%02X\n",
                    (UCHAR)sizeof(UINT8),
                    csmem->size
                );
                APPL_TRC
                (
                    "Len: 0x%02X,  Set Member Lock: ",
                    (UCHAR)sizeof(UINT8)
                );
                appl_csip_parse_and_display_set_mem_lock_value(csmem->lock);
                APPL_TRC
                (
                    "Len: 0x%02X,  Set Member Rank: 0x%02X\n",
                    (UCHAR)sizeof(UINT8),
                    csmem->rank
                );

                if (csmem->size < 2)
                {
                    APPL_TRC("Not creating set for Size < 2\n");
                    break;
                }

                /* Update the details in Conn Device Manager */
                if (GA_SUCCESS == appl_ga_utils_get_conn_device_index(*device, &index))
                {
                    appl_ga_utils_update_sm_of_conn_dev
                    (
                        index,
                        *csmem
                    );
                }

                if (CSIP_SIRK_TYPE_PLAIN_TEXT == csmem->sirk[0])
                {
                    /* Create/find a set and Add the member */
                    APPL_TRC("Check if a Set handle is available... ");
                    retval = GA_cap_set_find(&csmem->sirk[1U], csmem->size, &set_handle);
                    APPL_TRC("Retval - 0x%04X\n", retval);

                    if (GA_SUCCESS != retval)
                    {
                        APPL_TRC("No, Create a Set handle... ");
                        retval = GA_cap_set_create(&csmem->sirk[1U], csmem->size, &set_handle);
                        APPL_TRC("Retval - 0x%04X\n", retval);
                        appl_ga_utils_update_set_handle_of_conn_dev(index, set_handle);
                    }
                    else
                    {
                        /* Already Set is created, Verify the SIRK */
                        /* TODO: Move it to CAP Core */

                    }

                    if (GA_SUCCESS == retval)
                    {
                        APPL_TRC("Adding member to Set... ");
                        retval = GA_cap_set_add_member(set_handle, device, csmem->rank);
                        APPL_TRC("Retval - 0x%04X\n", retval);
                    }
                }
                else if (CSIP_SIRK_TYPE_ENCRYPTED == csmem->sirk[0])
                {
                    appl_ga_process_sirk(device, CSIP_SIRK_TYPE_ENCRYPTED, &csmem->sirk[1]);
                }

                if (CSIP_SET_MEMBER_LOCK_LOCKED == csmem->lock)
                {
                    APPL_TRC("\n*** CAS Set Member LOCKED to perform further CAP proedures ***\n");
                    APPL_TRC("\n*** Please wait for UNLOCKED notification to proceed ***\n");
                }
            }
        }
        break;

    case GA_CAP_RELEASE_MEMBER_CNF:
        GA_CB_ENTRY("CAP Client");
        APPL_TRC("[Profile]     : CAP (0x%04X)\n", GA_SERVICE_CAS);
        APPL_TRC("[SECTION]     : CAP CLIENT EVENTS\n");
        APPL_TRC("[SUB-SECTION] : CAP COORDINATOR-RELEASE\n");
        APPL_TRC("[TYPE]        : RELEASE RESPONSE\n");
        appl_ga_utils_display_bdaddr_and_type(device);
        APPL_TRC("[Event Status]: 0x%04X\n", ga_status);
        APPL_TRC("[EVENT]       : GA_CAP_RELEASE_MEMBER_CNF\n");

        if ((NULL != ga_data) && (0U != ga_datalen))
        {
            cas_csis_evt_info = (CSIP_EVENT_INFO *)ga_data;
            APPL_TRC
            (
                "[Service Cntx]: 0x%02X\n",
                cas_csis_evt_info->handle
            );
            APPL_TRC("\n");
            GA_FORMAT_DISPLAY();
            APPL_TRC("Data Length: 0x%02X\n", cas_csis_evt_info->datalen);
            if (0U == cas_csis_evt_info->datalen)
            {
                APPL_TRC("Data: NULL\n");
            }
        }
        break;

    case GA_CAP_LOCK_MEMBER_CNF:
        GA_CB_ENTRY("CAP Client");
        APPL_TRC("[Profile]     : CAP (0x%04X)\n", GA_SERVICE_CAS);
        APPL_TRC("[SECTION]     : CAP CLIENT EVENTS\n");
        APPL_TRC("[SUB-SECTION] : CAP COORDINATOR-WRITE\n");
        APPL_TRC("[TYPE]        : WRITE RESPONSE\n");
        appl_ga_utils_display_bdaddr_and_type(device);
        APPL_TRC("[Event Status]: 0x%04X\n", ga_status);
        APPL_TRC("[EVENT]       : GA_CAP_LOCK_MEMBER_CNF\n");

        if ((NULL != ga_data) && (0U != ga_datalen))
        {
            cas_csis_evt_info = (CSIP_EVENT_INFO *)ga_data;
            APPL_TRC
            (
                "[Service Cntx]: 0x%02X\n",
                cas_csis_evt_info->handle
            );
            APPL_TRC("\n");
            GA_FORMAT_DISPLAY();
            APPL_TRC
            (
                "Char UUID: Set Member Lock (0x%04X)\n",
                GA_CHAR_CSIS_LOCK
            );
            GA_FORMAT_DISPLAY();
            APPL_TRC("Data Length: 0x%02X\n", cas_csis_evt_info->datalen);
            if (0U == cas_csis_evt_info->datalen)
            {
                APPL_TRC("Data: NULL\n");
            }
            if (GA_SUCCESS == appl_ga_utils_get_conn_device_index
                              (
                                  *device,
                                  &index
                              ))
            {
                if (GA_SUCCESS == ga_status)
                {
                    /* Fetch the input given for lock_req for the SetMember. */
                    appl_ga_utils_fetch_lock_req_for_sm(index, &i);

                    /*
                     * Since the status is success, update the value in
                     * device manager.
                     */
                    appl_ga_utils_update_sm_char_of_conn_dev
                    (
                        index,
                        GA_CHAR_CSIS_LOCK,
                        &i
                    );

                    /* Revert lockReqOngoing to any RFU value. */
                    appl_ga_utils_update_lock_req_for_sm(index, 0U);

                    /* Fetch the set_handle for the member */
                    appl_ga_utils_fetch_set_handle(index, &set_handle);

                    /* Update the lock value of the SetMember in the database */
                    if (GA_SUCCESS == GA_cap_set_update_member_lock
                                      (
                                          set_handle,
                                          device,
                                          &i
                                      ))
                    {
                        APPL_TRC("Successully updated the CAS SetMember\n");
                    }
                    else
                    {
                        APPL_ERR("Failed to update the CAS SetMember !\n");
                    }
                }
            }
            /* Clear the variable */
            appl_ga_utils_update_lock_req_for_sm(index, 0U);
        }
        break;

    case GA_CS_SIRK_NTF:
        GA_CB_ENTRY("CAP Client");
        APPL_TRC("[Profile]     : CAP (0x%04X)\n", GA_SERVICE_CAS);
        APPL_TRC("[SECTION]     : CAP CLIENT EVENTS\n");
        APPL_TRC("[SUB-SECTION] : CAP COORDINATOR-NOTIFICATION\n");
        APPL_TRC("[TYPE]        : NOTIFICATION\n");
        appl_ga_utils_display_bdaddr_and_type(device);
        APPL_TRC("[Event Status]: 0x%04X\n", ga_status);
        APPL_TRC("[EVENT]       : GA_CS_SIRK_NTF\n");

        if ((NULL != ga_data) && (0U != ga_datalen))
        {
            cas_csis_evt_info = (CSIP_EVENT_INFO *)ga_data;
            APPL_TRC
            (
                "[Service Cntx]: 0x%02X\n",
                cas_csis_evt_info->handle
            );
            APPL_TRC("\n");
            GA_FORMAT_DISPLAY();
            APPL_TRC
            (
                "Char UUID: Set Identity Resolving Key (0x%04X)\n",
                GA_CHAR_CSIS_SIRK
            );
            GA_FORMAT_DISPLAY();
            if (GA_SUCCESS == ga_status)
            {
                if (GA_SUCCESS == appl_ga_utils_get_conn_device_index
                                  (
                                      *device,
                                      &index
                                  ))
                {
                    APPL_TRC("Data Length: 0x%02X\n", cas_csis_evt_info->datalen);
                    if (((CSIP_SIRK_LEN + 1U) == cas_csis_evt_info->datalen)
                         &&
                         (NULL != cas_csis_evt_info->data))
                    {
                        /* Get the SIRK */
                        cs_mem_sirk = (CSIP_SIRK *)cas_csis_evt_info->data;
                        APPL_TRC("Data:\n");
                        APPL_TRC("Len: 0x%02X,  Type: ", (UCHAR)sizeof(cs_mem_sirk->type));
                        appl_csip_parse_and_display_sirk_type_value(cs_mem_sirk->type);
                        APPL_TRC("Len: 0x%02X,  Value: ", (UCHAR)sizeof(cs_mem_sirk->value));
                        for (i = 0U; i < CSIP_SIRK_LEN; i++)
                        {
                            APPL_TRC("%02X ", cs_mem_sirk->value[i]);
                        }
                        APPL_TRC("\n");

                        /* Fetch the SetMember Data for this device */
                        appl_ga_utils_fetch_sm_of_conn_dev
                        (
                            index,
                            &conn_dev_csmem_data
                        );

                        /* Check if the SIRK type or value notified is different */
                        if ((conn_dev_csmem_data.sirk[0U] != cs_mem_sirk->type) ||
                            (0U != GA_mem_cmp
                                   (
                                       &conn_dev_csmem_data.sirk[1U],
                                       cs_mem_sirk->value,
                                       CSIP_SIRK_LEN
                                   )))
                        {
                            /* Update SIRK */
                            appl_ga_utils_update_sm_char_of_conn_dev
                            (
                                index,
                                GA_CHAR_CSIS_SIRK,
                                (UINT8 *)cas_csis_evt_info->data
                            );

                            /*
                             * Since the new type is Encrypted, Perform Decryption
                             * of SIRK
                             */
                            if (CSIP_SIRK_TYPE_ENCRYPTED == cs_mem_sirk->type)
                            {
                                /*
                                 * If SIRK is notified, and the type is
                                 * encrypted, then decrypt the SIRK and update
                                 * it in CAP SM database(cap_utils_api.c). Do
                                 * not add it into the CAP SM database again.
                                 */
                                appl_ga_process_sirk
                                (
                                    device,
                                    CSIP_SIRK_TYPE_ENCRYPTED,
                                    cs_mem_sirk->value
                                );
                            }
                            else
                            {
                                /*
                                 * If SIRK is notified, and the type is plain,
                                 * then update CAP SM database here
                                 * (cap_utils_api.c). Do not add it into the
                                 * CAP SM database again.
                                 */
                                appl_ga_utils_fetch_set_handle(index, &set_handle);
                                retval = GA_cap_set_update_member_sirk
                                         (
                                             set_handle,
                                             device,
                                             cs_mem_sirk->value
                                         );
                            }
                        }
                    }
                }
                else
                {
                    APPL_ERR("Device not found !\n");
                }
            }
        }
        break;

    case GA_CS_SETSIZE_NTF:
        GA_CB_ENTRY("CAP Client");
        APPL_TRC("[Profile]     : CAP (0x%04X)\n", GA_SERVICE_CAS);
        APPL_TRC("[SECTION]     : CAP CLIENT EVENTS\n");
        APPL_TRC("[SUB-SECTION] : CAP COORDINATOR-NOTIFICATION\n");
        APPL_TRC("[TYPE]        : NOTIFICATION\n");
        appl_ga_utils_display_bdaddr_and_type(device);
        APPL_TRC("[Event Status]: 0x%04X\n", ga_status);
        APPL_TRC("[EVENT]       : GA_CS_SETSIZE_NTF\n");

        if ((NULL != ga_data) && (0U != ga_datalen))
        {
            cas_csis_evt_info = (CSIP_EVENT_INFO *)ga_data;
            APPL_TRC
            (
                "[Service Cntx]: 0x%02X\n",
                cas_csis_evt_info->handle
            );
            APPL_TRC("\n");
            GA_FORMAT_DISPLAY();
            APPL_TRC
            (
                "Char UUID: Coordinated Set Size (0x%04X)\n",
                GA_CHAR_CSIS_SIZE
            );
            GA_FORMAT_DISPLAY();
            if (GA_SUCCESS == ga_status)
            {
                if (GA_SUCCESS == appl_ga_utils_get_conn_device_index
                                  (
                                      *device,
                                      &index
                                  ))
                {
                    APPL_TRC("Data Length: 0x%02X\n", cas_csis_evt_info->datalen);
                    if (CSIP_SET_SIZE_MIN <= *(UINT8*)cas_csis_evt_info->data)
                    {
                        APPL_TRC("Data:\n");
                        APPL_TRC
                        (
                            "Len: 0x%02X,  Coordinated Set Size: 0x%02X\n",
                            cas_csis_evt_info->datalen,
                            *(UINT8*)cas_csis_evt_info->data
                        );

                        /* Update Set Size */
                        appl_ga_utils_update_sm_char_of_conn_dev
                        (
                            index,
                            GA_CHAR_CSIS_SIZE,
                            (UINT8 *)cas_csis_evt_info->data
                        );

                        /* Update the cap_utils_api.c */
                        appl_ga_utils_fetch_set_handle(index, &set_handle);
                        retval = GA_cap_set_update_member_size
                                 (
                                     set_handle,
                                     device,
                                     (UINT8 *)cas_csis_evt_info->data
                                 );
                    }
                    else
                    {
                        APPL_TRC("Prohibited (0x%02X)\n", *((UINT8*)ga_data));
                    }
                }
                else
                {
                    APPL_ERR("Device not found !\n");
                }
            }
        }
        break;

    case GA_CS_SETMEMBER_LOCK_STATUS_NTF:
        GA_CB_ENTRY("CAP Client");
        APPL_TRC("[Profile]     : CAP (0x%04X)\n", GA_SERVICE_CAS);
        APPL_TRC("[SECTION]     : CAP CLIENT EVENTS\n");
        APPL_TRC("[SUB-SECTION] : CAP COORDINATOR-NOTIFICATION\n");
        APPL_TRC("[TYPE]        : NOTIFICATION\n");
        appl_ga_utils_display_bdaddr_and_type(device);
        APPL_TRC("[Event Status]: 0x%04X\n", ga_status);
        APPL_TRC("[EVENT]       : GA_CS_SETMEMBER_LOCK_STATUS_NTF\n");

        if ((NULL != ga_data) && (0U != ga_datalen))
        {
            cas_csis_evt_info = (CSIP_EVENT_INFO *)ga_data;
            APPL_TRC
            (
                "[Service Cntx]: 0x%02X\n",
                cas_csis_evt_info->handle
            );
            APPL_TRC("\n");
            GA_FORMAT_DISPLAY();
            APPL_TRC
            (
                "Char UUID: Set Member Lock (0x%04X)\n",
                GA_CHAR_CSIS_LOCK
            );
            GA_FORMAT_DISPLAY();
            if (GA_SUCCESS == ga_status)
            {
                if (GA_SUCCESS == appl_ga_utils_get_conn_device_index
                                  (
                                      *device,
                                      &index
                                  ))
                {
                    APPL_TRC("Data Length: 0x%02X\n", cas_csis_evt_info->datalen);
                    APPL_TRC("Data:\n");
                    APPL_TRC
                    (
                        "Len: 0x%02X,  Set Member Lock: ",
                        cas_csis_evt_info->datalen
                    );
                    appl_csip_parse_and_display_set_mem_lock_value
                    (
                        *(UINT8*)cas_csis_evt_info->data
                    );

                    /* Check if the lock value received is valid */
                    if ((CSIP_SET_MEMBER_LOCK_UNLOCKED == *(UINT8*)cas_csis_evt_info->data)
                        ||
                        (CSIP_SET_MEMBER_LOCK_LOCKED == *(UINT8*)cas_csis_evt_info->data))
                    {
                        /* Update Set Member Lock */
                        appl_ga_utils_update_sm_char_of_conn_dev
                        (
                            index,
                            GA_CHAR_CSIS_LOCK,
                            (UINT8 *)cas_csis_evt_info->data
                        );

                        /* Fetch the set_handle for the member */
                        appl_ga_utils_fetch_set_handle(index, &set_handle);

                        /* Update the lock value of the SetMember in the database */
                        if (GA_SUCCESS == GA_cap_set_update_member_lock
                                          (
                                              set_handle,
                                              device,
                                              (UINT8 *)cas_csis_evt_info->data
                                          ))
                        {
                            APPL_TRC("Successfully updated the CAS SetMember\n");
                        }
                        else
                        {
                            APPL_ERR("Failed to update the CAS SetMember !\n");
                        }
                    }
                }
                else
                {
                    APPL_ERR("Device not found !\n");
                }
            }
        }
        break;

    case GA_CS_RSI_VERIFY_COMPLETE:
        GA_CB_ENTRY("CAP Client");
        APPL_TRC("[Profile]     : CAP (0x%04X)\n", GA_SERVICE_CAS);
        APPL_TRC("[SECTION]     : CAP CLIENT EVENTS\n");
        APPL_TRC("[SUB-SECTION] : CAP COORDINATOR-Local Procedure\n");
        APPL_TRC("[TYPE]        : RSI Procedure\n");
        appl_ga_utils_display_bdaddr_and_type(device);
        APPL_TRC("[Event Status]: 0x%04X\n", ga_status);
        APPL_TRC("[EVENT]       : GA_CS_RSI_VERIFY_COMPLETE\n");

        if (GA_SUCCESS == ga_status)
        {
            APPL_TRC("\n");
            GA_FORMAT_DISPLAY();
            APPL_TRC("Data Length: 0x%02X\n", ga_datalen);

            if ((NULL != ga_data) && (0U != ga_datalen))
            {
                rsi = (UCHAR*)ga_data;
                /* Fetch the CAS device index from the device */
                index = appl_ga_is_dev_in_cas_db(rsi);

                APPL_TRC("Data:\n");
                APPL_TRC("Len: 0x%02X,  RSI: ", ga_datalen);
                for (i = 0U; i < ga_datalen; i++)
                {
                    APPL_TRC("%02X ", rsi[i]);
                }
                APPL_TRC("\n");

                /* Validate if RSI State is Ongoing */
                if ((MAX_SCAN_CAS_DEVICES != index) &&
                    (RSI_STATE_VERIFY_ONGOING == cas_devices[index].rsi_state))
                {
                    if (GA_SUCCESS == ga_status)
                    {
                        cas_devices[index].rsi_state = RSI_STATE_VERIFY_SUCCESS;

                        /* Trigger Connection to this Device */
                    }
                    else
                    {
                        cas_devices[index].rsi_state = RSI_STATE_VERIFY_FAILED;
                    }
                }
            }
        }
        break;
#endif /* APPL_CAS_SETCOORDINATOR */

#ifdef APPL_CAS_SETMEMBER
    case GA_CAP_LOCK_MEMBER_IND:
        GA_CB_ENTRY("CAP Server");
        APPL_TRC("[Profile]     : CAS (0x%04X)\n", GA_SERVICE_CAS);
        APPL_TRC("[SECTION]     : CAS SERVER EVENTS\n");
        APPL_TRC("[SUB-SECTION] : CAP MEMBER-WRITE\n");
        APPL_TRC("[TYPE]        : WRITE REQUEST\n");
        appl_ga_utils_display_bdaddr_and_type(device);
        APPL_TRC("[Event Status]: 0x%04X\n", ga_status);
        APPL_TRC("[EVENT]       : GA_CAP_LOCK_MEMBER_IND\n");

        if ((NULL != ga_data) && (0U != ga_datalen))
        {
            cas_csis_evt_info = (CSIP_EVENT_INFO *)ga_data;
            APPL_TRC("[Service Inst]: 0x%02X\n", cas_csis_evt_info->handle);

            APPL_TRC("\n");
            GA_FORMAT_DISPLAY();
            APPL_TRC
            (
                "Char UUID: Set Member Lock (0x%04X)\n",
                GA_CHAR_CSIS_LOCK
            );
            GA_FORMAT_DISPLAY();

            APPL_TRC("\n");
            GA_FORMAT_DISPLAY();
            APPL_TRC("RECEIVED DATA\n");
            GA_FORMAT_DISPLAY();
            APPL_TRC("Datalen: 0x%02X\n", cas_csis_evt_info->datalen);
            APPL_TRC("Data:\n");
            APPL_TRC
            (
                "Len: 0x%02X,  Set Member Lock: ",
                cas_csis_evt_info->datalen
            );
            appl_csip_parse_and_display_set_mem_lock_value
            (
                *(UINT8 *)(cas_csis_evt_info->data)
            );

            /* NOTE: This event is already handled at the CAS Core Layer */
        }
        break;

#ifdef APPL_CAP_ENABLE_CSIS_READ_APP_CB
    case GA_CS_SIRK_GET_IND:
        GA_CB_ENTRY("CAP Server");
        APPL_TRC("[Profile]     : CAS (0x%04X)\n", GA_SERVICE_CAS);
        APPL_TRC("[SECTION]     : CAS SERVER EVENTS\n");
        APPL_TRC("[SUB-SECTION] : CAP MEMBER-READ\n");
        APPL_TRC("[TYPE]        : READ REQUEST\n");
        appl_ga_utils_display_bdaddr_and_type(device);
        APPL_TRC("[Event Status]: 0x%04X\n", ga_status);
        APPL_TRC("[EVENT]       : GA_CS_SIRK_GET_IND\n");

        if ((NULL != ga_data) && (0U != ga_datalen))
        {
            cas_csis_evt_info = (CSIP_EVENT_INFO *)ga_data;
            APPL_TRC("[Service Inst]: 0x%02X\n", cas_csis_evt_info->handle);

            APPL_TRC("\n");
            GA_FORMAT_DISPLAY();
            APPL_TRC
            (
                "Char UUID: Set Identity Resolving Key (0x%04X)\n",
                GA_CHAR_CSIS_SIRK
            );
            GA_FORMAT_DISPLAY();

            /* Response is already sent to the peer as part of the GA Core */
        }
        break;

    case GA_CS_SETSIZE_GET_IND:
        GA_CB_ENTRY("CAP Server");
        APPL_TRC("[Profile]     : CAS (0x%04X)\n", GA_SERVICE_CAS);
        APPL_TRC("[SECTION]     : CAS SERVER EVENTS\n");
        APPL_TRC("[SUB-SECTION] : CAP MEMBER-READ\n");
        APPL_TRC("[TYPE]        : READ REQUEST\n");
        appl_ga_utils_display_bdaddr_and_type(device);
        APPL_TRC("[Event Status]: 0x%04X\n", ga_status);
        APPL_TRC("[EVENT]       : GA_CS_SETSIZE_GET_IND\n");

        if ((NULL != ga_data) && (0U != ga_datalen))
        {
            cas_csis_evt_info = (CSIP_EVENT_INFO *)ga_data;
            APPL_TRC("[Service Inst]: 0x%02X\n", cas_csis_evt_info->handle);

            APPL_TRC("\n");
            GA_FORMAT_DISPLAY();
            APPL_TRC
            (
                "Char UUID: Coordinated Set Size (0x%04X)\n",
                GA_CHAR_CSIS_SIZE
            );
            GA_FORMAT_DISPLAY();

            /* Response is already sent to the peer as part of the GA Core */
        }
        break;

    case GA_CS_SETMEMBER_RANK_GET_IND:
        GA_CB_ENTRY("CAP Server");
        APPL_TRC("[Profile]     : CAS (0x%04X)\n", GA_SERVICE_CAS);
        APPL_TRC("[SECTION]     : CAS SERVER EVENTS\n");
        APPL_TRC("[SUB-SECTION] : CAP MEMBER-READ\n");
        APPL_TRC("[TYPE]        : READ REQUEST\n");
        appl_ga_utils_display_bdaddr_and_type(device);
        APPL_TRC("[Event Status]: 0x%04X\n", ga_status);
        APPL_TRC("[EVENT]       : GA_CS_SETMEMBER_RANK_GET_IND\n");

        if ((NULL != ga_data) && (0U != ga_datalen))
        {
            cas_csis_evt_info = (CSIP_EVENT_INFO *)ga_data;
            APPL_TRC("[Service Inst]: 0x%02X\n", cas_csis_evt_info->handle);

            APPL_TRC("\n");
            GA_FORMAT_DISPLAY();
            APPL_TRC
            (
                "Char UUID: Set Member Rank (0x%04X)\n",
                GA_CHAR_CSIS_RANK
            );
            GA_FORMAT_DISPLAY();

            /* Response is already sent to the peer as part of the GA Core */
        }
        break;

    case GA_CS_SETMEMBER_LOCK_GET_IND:
        GA_CB_ENTRY("CAP Server");
        APPL_TRC("[Profile]     : CAS (0x%04X)\n", GA_SERVICE_CAS);
        APPL_TRC("[SECTION]     : CAS SERVER EVENTS\n");
        APPL_TRC("[SUB-SECTION] : CAP MEMBER-READ\n");
        APPL_TRC("[TYPE]        : READ REQUEST\n");
        appl_ga_utils_display_bdaddr_and_type(device);
        APPL_TRC("[Event Status]: 0x%04X\n", ga_status);
        APPL_TRC("[EVENT]       : GA_CS_SETMEMBER_LOCK_GET_IND\n");

        if ((NULL != ga_data) && (0U != ga_datalen))
        {
            cas_csis_evt_info = (CSIP_EVENT_INFO *)ga_data;
            APPL_TRC("[Service Inst]: 0x%02X\n", cas_csis_evt_info->handle);

            APPL_TRC("\n");
            GA_FORMAT_DISPLAY();
            APPL_TRC
            (
                "Char UUID: Set Member Lock (0x%04X)\n",
                GA_CHAR_CSIS_LOCK
            );
            GA_FORMAT_DISPLAY();

            /* Response is already sent to the peer as part of the GA Core */
        }
        break;
#endif /* APPL_CAP_ENABLE_CSIS_READ_APP_CB */

    case GA_CS_RSI_CREATE_COMPLETE:
        GA_CB_ENTRY("CAP Server");
        APPL_TRC("[Profile]     : CAS (0x%04X)\n", GA_SERVICE_CAS);
        APPL_TRC("[SECTION]     : CAS SERVER EVENTS\n");
        APPL_TRC("[SUB-SECTION] : CAP MEMBER-Local Procedure\n");
        APPL_TRC("[TYPE]        : RSI Procedure\n");
        appl_ga_utils_display_bdaddr_and_type(device);
        APPL_TRC("[Event Status]: 0x%04X\n", ga_status);
        APPL_TRC("[EVENT]       : GA_CS_RSI_CREATE_COMPLETE\n");

        if (GA_SUCCESS == ga_status)
        {
            APPL_TRC("\n");
            GA_FORMAT_DISPLAY();
            APPL_TRC("Data Length: 0x%02X\n", ga_datalen);

            if ((NULL != ga_data) && (0U != ga_datalen))
            {
                rsi = (UCHAR *)ga_data;
                APPL_TRC("Data:\n");
                APPL_TRC("Len: 0x%02X,  RSI: ", ga_datalen);
                for (i = 0U; i < ga_datalen; i++)
                {
                    APPL_TRC("%02X ", rsi[i]);
                }
                APPL_TRC("\n");

                /* Update AD Type information */
                appl_ga_utils_set_cs_rsi(rsi, ga_datalen);
                appl_ga_utils_add_cs_info_to_advdata();
            }
        }

        break;
#endif /* APPL_CAS_SETMEMBER */

    default:
        break;
    }

#if defined(LE_AUDIO_ENABLE_PRINTS_FOR_STREAMING) && (LE_AUDIO_ENABLE_PRINTS_FOR_STREAMING == 1)
    GA_CB_EXIT();
#endif

    return GA_SUCCESS;
}

GA_RESULT appl_ga_cap_uc_client_callback
          (
              GA_ENDPOINT * device,
              UINT8         ga_event,
              UINT16        ga_status,
              void        * ga_data,
              UINT16        ga_datalen
          )
{
    GA_RESULT          retval;
    UINT8              role;
    GA_CAP_ENDPOINT  * capab;
    UINT8 to_update;

    /* Initialize */
    retval = GA_SUCCESS;
    role = 0U;
    to_update = GA_FALSE;

    if (NULL == device)
    {
        APPL_ERR("NULL Device Unexpected !\n");
        return GA_FAILURE;
    }

#if defined(LE_AUDIO_ENABLE_PRINTS_FOR_STREAMING) && (LE_AUDIO_ENABLE_PRINTS_FOR_STREAMING == 1)
    GA_CB_ENTRY("Client");
#endif

    APPL_DBG("[APPL][GA]: >> appl_ga_cap_uc_client_callback\n");

    switch (ga_event)
    {
    case GA_SETUP_CNF:
        APPL_TRC("[Profile]     : PACS (0x%04X)\n", GA_SERVICE_PACS);
        APPL_TRC("[SECTION]     : PACS CLIENT EVENTS\n");
        APPL_TRC("[SUB-SECTION] : PACS CLIENT-SETUP\n");
        APPL_TRC("[TYPE]        : SETUP RESPONSE\n");
        appl_ga_utils_display_bdaddr_and_type(device);
        APPL_TRC("[Event Status]: ");
        appl_ga_utils_display_ga_result(ga_status);
        APPL_TRC
        (
            "[Event]       : GA_SETUP_CNF (0x%02X)\n",
            ga_event
        );
        if (GA_SUCCESS == ga_status)
        {
            role = *((UINT8*)ga_data);
            APPL_TRC("\n");
            GA_FORMAT_DISPLAY();
            APPL_TRC("Data Length: 0x%02X\n", ga_datalen);
            APPL_TRC("Data:\n");
            APPL_TRC("Len: 0x%02X,  Supported ", (UCHAR)sizeof(UINT8));
            appl_ga_utils_bap_display_role(role);
        }
        break;

    case GA_RELEASE_CNF:
        APPL_TRC("[Profile]     : PACS (0x%04X)\n", GA_SERVICE_PACS);
        APPL_TRC("[SECTION]     : PACS CLIENT EVENTS\n");
        APPL_TRC("[SUB-SECTION] : PACS CLIENT-RELEASE\n");
        APPL_TRC("[TYPE]        : RELEASE RESPONSE\n");
        appl_ga_utils_display_bdaddr_and_type(device);
        APPL_TRC("[Event Status]: ");
        appl_ga_utils_display_ga_result(ga_status);
        APPL_TRC
        (
            "[Event]       : GA_RELEASE_CNF (0x%02X)\n",
            ga_event
        );
        APPL_TRC("\n");
        GA_FORMAT_DISPLAY();
        APPL_TRC("Data Length: 0x%02X\n", ga_datalen);
        if (0U == ga_datalen)
        {
            APPL_TRC("Data: NULL\n");
        }
        break;

    case GA_CAPABILITIES_CHANGE_NTF: /* Fall-through */
    case GA_GET_CAPABILITIES_CNF:
        APPL_TRC("[Profile]     : PACS (0x%04X)\n", GA_SERVICE_PACS);
        APPL_TRC("[SECTION]     : PACS CLIENT EVENTS\n");
        APPL_TRC("[SUB-SECTION] : PACS CLIENT-SETUP\n");
        APPL_TRC("[TYPE]        : SETUP RESPONSE\n");
        appl_ga_utils_display_bdaddr_and_type(device);
        APPL_TRC("[Event Status]: ");
        appl_ga_utils_display_ga_result(ga_status);
        if (GA_GET_CAPABILITIES_CNF == ga_event)
        {
            APPL_TRC
            (
                "[Event]       : GA_GET_CAPABILITIES_CNF (0x%02X)\n",
                ga_event
            );
        }
        else
        {
            APPL_TRC
            (
                "[Event]       : GA_CAPABILITIES_CHANGE_NTF (0x%02X)\n",
                ga_event
            );
            to_update = GA_TRUE;
        }

        capab = (GA_CAP_ENDPOINT *)ga_data;
        /*
         * Add Remote PACS data: Context can be passed as NULL here since it is
         * already added during GA_Setup() .
         */
        retval = appl_ga_utils_bap_add_remote_pacs_for_dev
                 (
                     device,
                     capab,
                     to_update
                 );
        break;

    default:
        retval = appl_ga_uc_client_cb_handler
                 (
                     device,
                     ga_event,
                     ga_status,
                     ga_data,
                     ga_datalen
                 );
        break;
    }

#if defined(LE_AUDIO_ENABLE_PRINTS_FOR_STREAMING) && (LE_AUDIO_ENABLE_PRINTS_FOR_STREAMING == 1)
    GA_CB_EXIT();
#endif

    APPL_DBG("[APPL][GA]: << appl_ga_cap_uc_client_callback\n");

    return retval;
}

GA_RESULT appl_ga_cap_uc_server_callback
          (
              GA_ENDPOINT * device,
              UINT8         ga_event,
              UINT16        ga_status,
              void        * ga_data,
              UINT16        ga_datalen
          )
{
    GA_RESULT retval;

    APPL_DBG("[APPL][GA]: >> appl_ga_cap_uc_server_callback\n");

    retval = appl_ga_uc_server_cb_handler
             (
                 device,
                 ga_event,
                 ga_status,
                 ga_data,
                 ga_datalen
             );

    APPL_DBG("[APPL][GA]: << appl_ga_cap_uc_server_callback\n");

    return retval;
}

GA_RESULT appl_ga_cap_bc_src_callback
          (
              GA_ENDPOINT * device,
              UINT8         ga_event,
              UINT16        ga_status,
              void        * ga_data,
              UINT16        ga_datalen
          )
{
    GA_RESULT retval;

    APPL_DBG("[APPL][GA]: >> appl_ga_cap_bc_src_callback\n");

    retval = appl_ga_bc_src_cb_handler
             (
                 device,
                 ga_event,
                 ga_status,
                 ga_data,
                 ga_datalen
             );

    APPL_DBG("[APPL][GA]: << appl_ga_cap_bc_src_callback\n");

    return retval;
}

GA_RESULT appl_ga_cap_bc_sink_callback
          (
              GA_ENDPOINT * device,
              UINT8         ga_event,
              UINT16        ga_status,
              void        * ga_data,
              UINT16        ga_datalen
          )
{
    GA_RESULT retval;

    APPL_DBG("[APPL][GA]: >> appl_ga_cap_bc_sink_callback\n");

    retval = appl_ga_bc_sink_cb_handler
             (
                 device,
                 ga_event,
                 ga_status,
                 ga_data,
                 ga_datalen
             );

    APPL_DBG("[APPL][GA]: << appl_ga_cap_bc_sink_callback\n");

    return retval;
}

void appl_ga_init(void)
{
    GA_RESULT retval;
#ifdef GA_HAVE_DYNAMIC_CONFIG
    GA_CONFIG    appl_ga_config;
#endif /* GA_HAVE_DYNAMIC_CONFIG */

    /* Register with the bearer interface */
    ga_brr_register();

#ifdef GA_HAVE_DYNAMIC_CONFIG
    APPL_TRC("GA_configure: \n");
    GA_INIT_CONFIG(appl_ga_config);

    GA_configure(&appl_ga_config);
#endif /* GA_HAVE_DYNAMIC_CONFIG */

    APPL_TRC("GA_init\n");
    retval = GA_init();
    APPL_TRC("Retval - ");
    if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
    {
        APPL_TRC("0x%04X\n", retval);
    }
}

int main_ga_operations(void)
{
    GA_RESULT    retval;
    int          choice;
    UINT8        menu_choice;
    GA_ENDPOINT  device, *pdevice;
    UINT8        index;
    UINT16       acl_conn_handle;
    GA_CONTEXT   context;
    GA_BRR_EXTENDED_SCAN_PARAMS escan_params;
    APPL_GA_LE_CONN_PARAMS local_le_conn_params;
    APPL_GA_LE_EXT_CONN_PARAMS local_le_ext_conn_params;
    UINT8        set_handle;
    GA_BRR_SVC_INFO cas_svc_info;

#ifdef APPL_CAS_SETMEMBER
    GA_SET_MEMBER *pmember;
#endif /* APPL_CAS_SETMEMBER */

    UINT16 ctx, *pctx;
    UINT32 loc, *ploc;
    UINT8 role;
    UINT8 record_id;

    /* Initialize */
    retval = GA_FAILURE;
    index = 0U;
    pctx = NULL;
    ploc = NULL;
    pdevice = NULL;

    GA_LOOP_FOREVER()
    {
        CONSOLE_OUT("\n");
        CONSOLE_OUT("%s", ga_menu_options);
        CONSOLE_IN("%d", &choice);

        menu_choice = (UINT8)choice;

        switch (choice)
        {
        case 0:
            break; /* return 0; */

        case 1:
            break;

        case 2:
            if (APPL_GA_INIT_STATUS_LEGACY == ga_init_status)
            {
                APPL_ERR("GA is already initialized with Reference application - Legacy !\n");
            }
            else if (APPL_GA_INIT_STATUS_GA == ga_init_status)
            {
                APPL_ERR("GA is already initialized with Reference application - New !\n");
            }
            else
            {
#ifdef NXP_CODE
               	appl_hci_le_read_local_supported_features();//TODO how to wait till command complete event comes
#endif
                CONSOLE_OUT("Enter the Role (1-Client, 2-Server, 3-Both, 4-None): ");
                CONSOLE_IN("%d", &choice);

                appl_ga_module_init(choice);
            }

#ifdef APPL_CAS_SETCOORDINATOR
            appl_ga_set_default_cas_scan_settings();
#endif /* APPL_CAS_SETCOORDINATOR */

            /* Initialize the own_addr_info */
            appl_ga_utils_set_default_values_own_addr_info();
            if (GA_SUCCESS == BT_hci_get_local_bd_addr(device.bd_addr))
            {
                /* Update own_addr_info for Connection */
                device.bd_type = BD_ADDR_TYPE_PUBLIC;
                appl_ga_utils_update_own_address_and_type(device, SET_HANDLE_CONNECTION);
                /* Update own_addr_info for Broadcast */
                appl_ga_utils_update_own_address_and_type(device, SET_HANDLE_BROADCAST);
            }
            break;

        case 3:
            appl_ga_brr_setup();
            break;

        case 4:
            if (APPL_GA_INIT_STATUS_GA == ga_init_status)
            {
                if (1U == appl_ga_role)
                {
                    appl_ga_uc_client_shutdown();
                    appl_ga_bc_source_shutdown();

                    appl_ga_vcp_client_shutdown();

                    appl_ga_micp_client_shutdown();

                    appl_ga_csip_sc_shutdown();
                }
                else if (2U == appl_ga_role)
                {
                    appl_ga_uc_server_shutdown();
                    appl_ga_bc_sink_shutdown();

                    appl_ga_vcp_server_shutdown();

                    appl_ga_micp_server_shutdown();

                    appl_ga_csip_sm_shutdown();
                }
                else if (3U == appl_ga_role)
                {
                    appl_ga_uc_client_shutdown();
                    appl_ga_uc_server_shutdown();

                    appl_ga_bc_source_shutdown();
                    appl_ga_bc_sink_shutdown();

                    appl_ga_vcp_client_shutdown();
                    appl_ga_vcp_server_shutdown();

                    appl_ga_micp_client_shutdown();
                    appl_ga_micp_server_shutdown();

                    appl_ga_csip_sc_shutdown();
                    appl_ga_csip_sm_shutdown();
                }

                APPL_TRC("GA Shutdown...\n");
                retval = GA_shutdown();
                APPL_TRC("Retval - ");
                if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
                {
                    APPL_TRC("0x%04X\n", retval);
                }
                if (GA_SUCCESS == retval)
                {
                    ga_init_status = APPL_GA_INIT_STATUS_NONE;
                    /* Fetch the connected device index and info */
                    appl_ga_utils_get_conn_device_in_use
                    (
                        &index,
                        NULL,
                        NULL
                    );
                    /* Reset the context in device manager */
                    appl_ga_utils_update_context_of_conn_dev(0xFFU, index);

                    retval = appl_ga_utils_hci_unregister_callback();
                    if (GA_SUCCESS == retval)
                    {
                        APPL_TRC("HCI Callback UnRegistered\n");
                    }
                    else
                    {
                        APPL_ERR
                        (
                            "FAILED to unregister HCI Callback !!! Error code = %04X\n",
                            retval
                        );
                    }
                }

                /* De-Initialize ISO Module */
                /* De-Initialize Audio PL Module */
                /* De-Initialize LC3 Module */
            }
            else
            {
                APPL_ERR("Invalid status for GA_shutdown() %d!\n",
                ga_init_status);
            }
            break;

        case 5:
            retval = appl_ga_register_pacs(APPL_GA_ROLE_NONE);
            break;

        case 6:
            pdevice = NULL;
            record_id = 0U;
            role = appl_ga_utils_bap_get_role();

            /* Take Input if we want to Update/Notify/Both */
            choice = appl_ga_utils_bap_get_choice_for_update_notify();

            /* Fetch the Record ID */
            record_id = appl_ga_utils_bap_get_cap_record_id();

            if (0x01 == (UINT8)choice)
            {
                pdevice = NULL;
            }
            else
            {
                /* Fetch the connected device index and info */
                appl_ga_utils_get_conn_device_in_use
                (
                    &index,
                    &device,
                    NULL
                );
                pdevice = &device;
            }

            if ((0x01 == (UINT8)choice) ||
                (0x03 == (UINT8)choice))
            {
                if (GA_SUCCESS != appl_ga_utils_bap_get_updated_cap
                                  (
                                      role,
                                      record_id,
                                      pdevice
                                  ))
                {
                    break;
                }
            }
            else
            {

                if (GA_ROLE_SINK == role)
                {
                    retval = GA_update_sink_audio_capability
                             (
                                 pdevice,
                                 record_id,
                                 NULL,
                                 0U
                             );
                }
                else
                {
                    retval = GA_update_source_audio_capability
                             (
                                 pdevice,
                                 record_id,
                                 NULL,
                                 0U
                             );
                }
                APPL_TRC("Retval - ");
                if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
                {
                    APPL_TRC("0x%04X\n", retval);
                }
            }
            break;

        case 7:
            pctx = NULL;
            pdevice = NULL;
            role = appl_ga_utils_bap_get_role();

            /* Take Input if we want to Update/Notify/Both */
            choice = appl_ga_utils_bap_get_choice_for_update_notify();
            if ((0x01 == (UINT8)choice) ||
                (0x03 == (UINT8)choice))
            {
                ctx = appl_ga_utils_bap_get_available_ctx();
                pctx = &ctx;
                /* Update Local Record Info */
                appl_ga_utils_bap_fetch_update_local_pacs_avail_audio_cntx
                (
                    role,
                    *pctx
                );
            }
            if ((0x02 == (UINT8)choice) ||
                (0x03 == (UINT8)choice))
            {
                /* Fetch the connected device index and info */
                appl_ga_utils_get_conn_device_in_use
                (
                    &index,
                    &device,
                    NULL
                );
                pdevice = &device;
            }

            if (GA_ROLE_SOURCE == role)
            {
                retval = GA_update_source_available_audio_contexts(pdevice, pctx);
            }
            else if (GA_ROLE_SINK == role)
            {
                retval = GA_update_sink_available_audio_contexts(pdevice, pctx);
            }
            else
            {
                APPL_ERR("Invalid Role - 0x%02X\n", role);
            }

            APPL_TRC("Retval - ");
            if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
            {
                APPL_TRC("0x%04X\n", retval);
            }
            break;

        case 8:
            pctx = NULL;
            pdevice = NULL;
            role = appl_ga_utils_bap_get_role();

            /* Take Input if we want to Update/Notify/Both */
            choice = appl_ga_utils_bap_get_choice_for_update_notify();
            if ((0x01 == (UINT8)choice) ||
                (0x03 == (UINT8)choice))
            {
                ctx = appl_ga_utils_bap_get_supp_ctx();
                pctx = &ctx;
                /* Update Local Record Info */
                appl_ga_utils_bap_fetch_update_local_pacs_supp_audio_cntx
                (
                    role,
                    *pctx
                );
            }
            if ((0x02 == (UINT8)choice) ||
                (0x03 == (UINT8)choice))
            {
                /* Fetch the connected device index and info */
                appl_ga_utils_get_conn_device_in_use
                (
                    &index,
                    &device,
                    NULL
                );
                pdevice = &device;
            }

            if (GA_ROLE_SOURCE == role)
            {
                retval = GA_update_source_supported_audio_contexts(pdevice, pctx);
            }
            else if (GA_ROLE_SINK == role)
            {
                retval = GA_update_sink_supported_audio_contexts(pdevice, pctx);
            }
            else
            {
                APPL_ERR("Invalid Role - 0x%02X\n", role);
            }

            APPL_TRC("Retval - ");
            if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
            {
                APPL_TRC("0x%04X\n", retval);
            }
            break;

        case 9:
            ploc = NULL;
            pdevice = NULL;
            role = appl_ga_utils_bap_get_role();

            /* Take Input if we want to Update/Notify/Both */
            choice = appl_ga_utils_bap_get_choice_for_update_notify();
            if ((0x01 == (UINT8)choice) ||
                (0x03 == (UINT8)choice))
            {
                loc = appl_ga_utils_bap_get_audio_channel_alloc();
                ploc = &loc;
                /* Update Local Record Info */
                appl_ga_utils_bap_fetch_update_local_pacs_audio_locations
                (
                    role,
                    *ploc
                );
            }
            if ((0x02 == (UINT8)choice) ||
                (0x03 == (UINT8)choice))
            {
                /* Fetch the connected device index and info */
                appl_ga_utils_get_conn_device_in_use
                (
                    &index,
                    &device,
                    NULL
                );
                pdevice = &device;
            }

            if (GA_ROLE_SOURCE == role)
            {
                retval = GA_update_source_audio_locations(pdevice, ploc);
            }
            else if (GA_ROLE_SINK == role)
            {
                retval = GA_update_sink_audio_locations(pdevice, ploc);
            }
            else
            {
                APPL_ERR("Invalid Role - 0x%02X\n", role);
            }

            APPL_TRC("Retval - ");
            if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
            {
                APPL_TRC("0x%04X\n", retval);
            }
            break;

        case 10:
            /* Fetch the connected device index and info */
            appl_ga_utils_get_conn_device_in_use
            (
                &index,
                &device,
                NULL
            );

            /* Remove reference to old records */
            retval = appl_ga_utils_bap_remove_remote_pacs_for_dev(index);

            APPL_TRC("Setup Endpoint\n");
            APPL_TRC("Setup PACS: Audio Role Discovery - PACS Discovery\n");
            retval = GA_setup(&device, &context);
            APPL_TRC("Retval - ");
            if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
            {
                APPL_TRC("0x%04X\n", retval);
            }
            APPL_TRC("Context: %d\n", context);

            if (GA_SUCCESS == retval)
            {
                /* Set the context in device manager */
                appl_ga_utils_update_context_of_conn_dev
                (
                    context,
                    index
                );
            }
            break;

        case 11:
        {
            /* Fetch the connected device index, context and info */
            appl_ga_utils_get_conn_device_in_use
            (
                &index,
                &device,
                &context
            );
            appl_ga_utils_bap_remove_remote_pacs_for_dev(index);
            CONSOLE_OUT("\n1. Release\n2. Close\n");
            CONSOLE_OUT("Enter your choice: ");
            CONSOLE_IN("%d", &choice);
            if (1 == choice)
            {
                APPL_TRC("GA_release\n");
                retval = GA_release(&context);
                APPL_TRC("Retval - ");
                if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
                {
                    APPL_TRC("0x%04X\n", retval);
                }
                if (GA_SUCCESS == retval)
                {
                    /* Reset the context in device manager */
                    appl_ga_utils_update_context_of_conn_dev(0xFFU, index);
                }
            }
            else if (2 == choice)
            {
                APPL_TRC("GA_close\n");
                retval = GA_close(&context);
                APPL_TRC("Retval - ");
                if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
                {
                    APPL_TRC("0x%04X\n", retval);
                }
                if (GA_SUCCESS == retval)
                {
                    /* Reset the context in device manager */
                    appl_ga_utils_update_context_of_conn_dev(0xFFU, index);
                }
            }
            else
            {
                APPL_ERR("Invalid choice !\n");
            }
        }
            break;

        case 12:
            /* Fetch the connected device index, context and info */
            appl_ga_utils_get_conn_device_in_use
            (
                &index,
                &device,
                &context
            );

            role = appl_ga_utils_bap_get_role();
            APPL_TRC
            (
                "Get PACS Capabilities - Read Audio Capability, Location, "
                "Supp/Avail Contexts\n"
            );
            retval = GA_get_capabilities(&context, role);
            APPL_TRC("Retval - ");
            if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
            {
                APPL_TRC("0x%04X\n", retval);
            }
            break;

        case 18:
            CONSOLE_OUT("Enter own address type\n");
            CONSOLE_OUT("1. Public\n2. Random\n");
            CONSOLE_IN("%d", &choice);
            if (1U == (UINT8)choice)
            {
                /*
                 * If the addr_type is public, then get the local BD_Address
                 */
                device.bd_type = BD_ADDR_TYPE_PUBLIC;

                /* This always returns Public Address */
                retval = BT_hci_get_local_bd_addr(&device.bd_addr[0U]);
            }
            else if (2U == (UINT8)choice)
            {
                /*
                 * If the addr_type is random, then take input for Random Address
                 */
                device.bd_type = BD_ADDR_TYPE_RANDOM;

                CONSOLE_OUT("Enter the Random BD_Address: ");
                appl_get_bd_addr(&device.bd_addr[0]);
                /* Set the random address with the HCI */
                retval = BT_hci_le_set_random_address(&device.bd_addr[0]);
            }
            else
            {
                APPL_ERR("Invalid Option !\n");
            }
            if (((1U == (UINT8)choice) || (2U == (UINT8)choice)) &&
                (GA_SUCCESS == retval))
            {
                appl_ga_utils_update_own_address_and_type
                (
                    device,
                    SET_HANDLE_CONNECTION
                );
            }
            break;

        case 20:
            CONSOLE_OUT("1. Enable 2. Disable\n");
            CONSOLE_IN("%d", &choice);
            index = (UINT8)choice;
            if (1U == index)
            {
                /* Reusing index to indicate enable */
                retval = appl_ga_utils_enable_legacy_advertise(GA_TRUE);
                if (GA_SUCCESS == retval)
                {
                    is_adv_enabled = APPL_GA_ADV_UCS;
                }
                else
                {
                    APPL_ERR("Legacy Advertise Already initiated by Other Module !\n");
                }
            }
            else if (2U == index)
            {
                /* Reusing index to indicate disable */
                retval = appl_ga_utils_enable_legacy_advertise(GA_FALSE);
                if (GA_SUCCESS == retval)
                {
                    is_adv_enabled = APPL_GA_ADV_INVALID;
                }
                else
                {
                    APPL_ERR("Failed to Disable Legacy Advertise Or Advertise Already Stopped"
                        " by Other Module !\n");
                }
            }
            else
            {

            }
            break;

        case 21:
            CONSOLE_OUT("1. Enable 2. Disable\n");
            CONSOLE_IN("%d", &choice);
            index = (UINT8)choice;
            if (1U == index)
            {
                /* Reusing index to indicate enable */
                retval = appl_ga_utils_enable_extended_advertise(GA_TRUE);
                if (GA_SUCCESS == retval)
                {
                    is_adv_enabled = APPL_GA_ADV_UCS;
                }
                else
                {
                    APPL_ERR("Extended Advertise Already initiated by Other Module !\n");
                }
            }
            else if (2U == index)
            {
                /* Reusing index to indicate disable */
                retval = appl_ga_utils_enable_extended_advertise(GA_FALSE);
                if (GA_SUCCESS == retval)
                {
                    is_adv_enabled = APPL_GA_ADV_INVALID;
                }
                else
                {
                    APPL_ERR("Failed to Disable Extended Advertise Or Advertise Already Stopped"
                        " by Other Module !\n");
                }
            }
            else
            {

            }
            break;

        case 22:
            CONSOLE_OUT("1. Enable 2. Disable\n");
            CONSOLE_IN("%d", &choice);
            index = (UINT8)choice;
            if (0x01U == index)
            {
                retval = appl_ga_utils_enable_legacy_scan(GA_TRUE);
                if (GA_SUCCESS == retval)
                {
                    is_scan_enabled = APPL_GA_SCAN_FOR_UCS;
                }
                else
                {
                    APPL_ERR("Failed to set Legacy Scan Params Or Scan Already initiated"
                        " by Other Module !\n");
                }
            }
            else
            {
                retval = appl_ga_utils_enable_legacy_scan(GA_FALSE);
                if (GA_SUCCESS == retval)
                {
                    is_scan_enabled = APPL_GA_SCAN_INVALID;
                }
                else
                {
                    APPL_ERR("Failed to Disable Extended Scan Or Scan Already Stopped"
                        " by Other Module !\n");
                }
            }
            break;

        case 23:
            CONSOLE_OUT("1. Enable 2. Disable\n");
            CONSOLE_IN("%d", &choice);
            index = (UINT8)choice;
            escan_params.duration = 0x00;
            escan_params.filter_duplicates = 0x01;
            escan_params.period = 0x00;
            escan_params.scan_filter_policy = 0x00;
            escan_params.scan_interval = 0x00A0;
            escan_params.scan_phy = 0x01;
            escan_params.scan_type = 0x00;
            escan_params.scan_window = 0x00A0;

            /* Fetch own_addr_info for scanning */
            appl_ga_utils_fetch_own_address_and_type(&device, SET_HANDLE_CONNECTION);
            /* Update own address type for ESCAN params */
            escan_params.own_addr_type = device.bd_type;

            if (0x01U == index)
            {
                retval = appl_ga_utils_enable_extended_scan(escan_params);
                if (GA_SUCCESS == retval)
                {
                    is_scan_enabled = APPL_GA_SCAN_FOR_UCS;
                }
                else
                {
                    APPL_ERR("Failed to set Extended Scan Params Or Scan Already initiated"
                        " by Other Module !\n");
                }
            }
            else
            {
                retval = appl_ga_utils_disable_extended_scan(escan_params);
                if (GA_SUCCESS == retval)
                {
                    is_scan_enabled = APPL_GA_SCAN_INVALID;
                }
                else
                {
                    APPL_ERR("Failed to Disable Extended Scan Or Scan Already Stopped"
                        " by Other Module !\n");
                }
            }
            break;

        case 25:
            /* Get LE connection parameters */
            appl_ga_utils_get_le_conn_params(&local_le_conn_params);
            CONSOLE_OUT("Enter endpoint address: ");
            appl_get_bd_addr(local_le_conn_params.peer_addr);
            BT_COPY_BD_ADDR
            (
                &device.bd_addr[0U],
                &local_le_conn_params.peer_addr[0U]
            );

            CONSOLE_OUT("Enter endpoint type: ");
            CONSOLE_IN("%d", &choice);
            local_le_conn_params.peer_addr_type = (UINT8)choice;
            device.bd_type = local_le_conn_params.peer_addr_type;

            /* Update peer address in device manager */
            retval = appl_ga_utils_add_conn_device_as_a_initiator(device);

            /* Fetch own address type */
            appl_ga_utils_fetch_own_address_and_type(&device, SET_HANDLE_CONNECTION);
            /* Update own address type for connection */
            local_le_conn_params.own_addr_type = device.bd_type;

            /* Update LE Connection Parameters */
            appl_ga_utils_update_le_conn_params(local_le_conn_params);

            if (GA_SUCCESS == retval)
            {
                appl_ga_utils_connect
                (
                    GA_CONNECTION_MODE_NORMAL,
                    (void *)&local_le_conn_params
                );
            }
            else
            {
                APPL_ERR("Device already registered !\n");
            }
            break;

        case 26:
            CONSOLE_OUT("Connection via EA Device Index OR Device\n");
            CONSOLE_OUT("1. EA Device Index\n");
            CONSOLE_OUT("2. Device\n");
            CONSOLE_IN("%d", &choice);

            /* Get LE Extended connection parameters */
            appl_ga_utils_get_le_ext_conn_params(&local_le_ext_conn_params);

            if (1U == (UINT8)choice)
            {
                CONSOLE_OUT("Enter EA Device Index\n");
                CONSOLE_IN("%d", &choice);
                appl_ga_utils_hci_get_ea_device_from_index((UINT16)choice, &device);
                local_le_ext_conn_params.peer_addr_type = device.bd_type;
                BT_COPY_BD_ADDR(&local_le_ext_conn_params.peer_addr, device.bd_addr);
            }
            else
            {
                CONSOLE_OUT("Enter endpoint address: ");
                appl_get_bd_addr(local_le_ext_conn_params.peer_addr);
                BT_COPY_BD_ADDR
                (
                    &device.bd_addr[0U],
                    &local_le_ext_conn_params.peer_addr[0U]
                );

                CONSOLE_OUT("Enter endpoint type: ");
                CONSOLE_IN("%d", &choice);
                local_le_ext_conn_params.peer_addr_type = (UINT8)choice;
                device.bd_type = local_le_ext_conn_params.peer_addr_type;
            }

            /* Update peer address in device manager */
            retval = appl_ga_utils_add_conn_device_as_a_initiator(device);

            /* Fetch own address type */
            appl_ga_utils_fetch_own_address_and_type(&device, SET_HANDLE_CONNECTION);
            /* Update own address type for connection */
            local_le_ext_conn_params.own_addr_type = device.bd_type;

            /* Update LE Extended Connection Parameters */
            appl_ga_utils_update_le_ext_conn_params(local_le_ext_conn_params);

            if (GA_SUCCESS == retval)
            {
                appl_ga_utils_connect
                (
                    GA_CONNECTION_MODE_EXTENDED,
                    (void *)&local_le_ext_conn_params
                );
            }
            else
            {
                APPL_ERR("Device already registered !\n");
            }
            break;

        case 27:
            retval = appl_ga_authenticate(SMP_LEGACY_MODE);
            APPL_TRC("Retval - ");
            if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
            {
                APPL_TRC("0x%04X\n", retval);
            }
            break;

        case 28:
            retval = appl_ga_authenticate(SMP_LESC_MODE);
            APPL_TRC("Retval - ");
            if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
            {
                APPL_TRC("0x%04X\n", retval);
            }
            break;

        case 29:
            retval = appl_ga_disconnect();
            APPL_TRC("Retval - ");
            if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
            {
                APPL_TRC("0x%04X\n", retval);
            }
            break;

        case 30:
            /* Fetch Conn Device Index */
            index = appl_ga_utils_bap_get_input_conn_dev_index();

            if (GA_SUCCESS == appl_ga_utils_get_conn_handle_from_index
                              (
                                  index,
                                  &acl_conn_handle
                              ))
            {
                APPL_TRC("Reading Remote Used Features...\n");
                retval = BT_hci_le_read_remote_used_features
                         (
                             acl_conn_handle
                         );
                APPL_TRC("Retval - 0x%04X\n", retval);
            }
            break;

        case 31:
            appl_ga_utils_display_all_conn_device();
            break;

        case 32:
            index = appl_ga_utils_bap_get_input_conn_dev_index();
            retval = appl_ga_utils_set_conn_device_in_use(index);
            APPL_TRC("Retval - ");
            if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
            {
                APPL_TRC("0x%04X\n", retval);
            }
            break;

        case 33:
            index = appl_ga_utils_bap_get_input_conn_dev_index();
            retval = appl_ga_utils_remove_conn_device(index);
            APPL_TRC("Retval - ");
            if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
            {
                APPL_TRC("0x%04X\n", retval);
            }
            break;

        case 34:
            appl_ga_utils_reset_dev_manager();
            break;

        case 35:
#if ((defined SNK_DUMP_AUDIO_PREDECODED) || (defined SNK_DUMP_AUDIO_DECODED))
            CONSOLE_OUT("Configure Sink Audio Dump:\n");
            CONSOLE_OUT("1. Enable\n2. Disable\n");
            CONSOLE_IN("%d", &choice);
            int config_snk_audio_dump = (UINT8)choice;
            CONSOLE_OUT("Configure:\n1. All\n2. Pre-Decoded\n3. Post-Decoded\n");
            CONSOLE_IN("%d", &choice);
            retval = appl_ga_utils_audio_snk_config_audio_dump_files
                     (
                         config_snk_audio_dump,
                         (UINT8)choice
                     );
            APPL_TRC("Retval - ");
            if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
            {
                APPL_TRC("0x%04X\n", retval);
            }
#else /* ((defined SNK_DUMP_AUDIO_PREDECODED) || (defined SNK_DUMP_AUDIO_DECODED)) */
            APPL_ERR("SNK_DUMP_AUDIO_PREDECODED or SNK_DUMP_AUDIO_DECODED is not enabled !\n");
#endif /* ((defined SNK_DUMP_AUDIO_PREDECODED) || (defined SNK_DUMP_AUDIO_DECODED)) */
            break;

        case 36:
#if ((defined SRC_DUMP_AUDIO_PREENCODED) || (defined SRC_DUMP_AUDIO_ENCODED))
            CONSOLE_OUT("Configure Source Audio Dump:\n");
            CONSOLE_OUT("1. Enable\n2. Disable\n");
            CONSOLE_IN("%d", &choice);
            int config_audio_dump = (UINT8)choice;
            CONSOLE_OUT("Configure:\n1. All\n2. Pre-Encoded\n3. Post-Encoded\n");
            CONSOLE_IN("%d", &choice);
            retval = appl_ga_utils_audio_src_config_audio_dump_files
                     (
                         config_audio_dump,
                         (UINT8)choice
                     );
            APPL_TRC("Retval - ");
            if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
            {
                APPL_TRC("0x%04X\n", retval);
            }
#else /* ((defined SRC_DUMP_AUDIO_PREENCODED) || (defined SRC_DUMP_AUDIO_ENCODED)) */
            APPL_ERR("SRC_DUMP_AUDIO_PREENCODED or SRC_DUMP_AUDIO_ENCODED is not enabled !\n");
#endif /* ((defined SRC_DUMP_AUDIO_PREENCODED) || (defined SRC_DUMP_AUDIO_ENCODED)) */
            break;

        case 37:
#ifdef SNK_DISPLAY_MISSED_SEQ_NUM
            CONSOLE_OUT("Configure Sink Missed Sequence number display:\n");
            CONSOLE_OUT("1. Enable\n2. Disable\n");
            CONSOLE_IN("%d", &choice);
            appl_ga_utils_audio_snk_config_missed_seq_num_display((UINT8)choice);
#else /* SNK_DISPLAY_MISSED_SEQ_NUM */
            APPL_ERR("SNK_DISPLAY_MISSED_SEQ_NUM is not enabled !\n");
#endif /* SNK_DISPLAY_MISSED_SEQ_NUM */
            break;

        case 38:
#ifdef SRC_DISPLAY_MISSED_SEQ_NUM
            CONSOLE_OUT("Configure Source Missed Sequence number display:\n");
            CONSOLE_OUT("1. Enable\n2. Disable\n");
            CONSOLE_IN("%d", &choice);
            appl_ga_utils_audio_src_config_missed_seq_num_display((UINT8)choice);
#else /* SRC_DISPLAY_MISSED_SEQ_NUM */
            APPL_ERR("SRC_DISPLAY_MISSED_SEQ_NUM is not enabled !\n");
#endif /* SRC_DISPLAY_MISSED_SEQ_NUM */
            break;

        case 40:
#if ((defined APPL_UCC) || (defined APPL_UCS))
            main_unicast_operations();
#else /* ((defined APPL_UCC) || (defined APPL_UCS)) */
            APPL_ERR("APPL_UCC or APPL_UCS NOT defined !\n");
#endif /* ((defined APPL_UCC) || (defined APPL_UCS)) */
            break;

        case 45:
#if ((defined APPL_BAP_BROADCAST_SOURCE) || (defined APPL_BAP_BROADCAST_SINK) || (defined APPL_BAP_BROADCAST_ASSISTANT) || (defined APPL_BAP_BROADCAST_SCAN_DELEGATOR))
            main_broadcast_operations();
#else /* ((defined APPL_BAP_BROADCAST_SOURCE) || (defined APPL_BAP_BROADCAST_SINK) || (defined APPL_BAP_BROADCAST_ASSISTANT) || (defined APPL_BAP_BROADCAST_SCAN_DELEGATOR)) */
            APPL_ERR("APPL_BAP_BROADCAST_SOURCE or APPL_BAP_BROADCAST_SINK or APPL_BAP_BROADCAST_ASSISTANT or APPL_BAP_BROADCAST_SCAN_DELEGATOR NOT defined !\n");
#endif /* ((defined APPL_BAP_BROADCAST_SOURCE) || (defined APPL_BAP_BROADCAST_SINK) || (defined APPL_BAP_BROADCAST_ASSISTANT) || (defined APPL_BAP_BROADCAST_SCAN_DELEGATOR)) */
            break;

        case 50:
#ifdef APPL_VCP_CONTROLLER
            appl_vcp_ct_operations();
#else /* APPL_VCP_CONTROLLER */
            APPL_ERR("APPL_VCP_CONTROLLER NOT defined !\n");
#endif /* APPL_VCP_CONTROLLER */
            break;

        case 51:
#ifdef APPL_VCP_RENDERER
            appl_vcp_rd_operations();
#else /* APPL_VCP_RENDERER */
            APPL_ERR("APPL_VCP_RENDERER NOT defined !\n");
#endif /* APPL_VCP_RENDERER */
            break;

        case 55:
#ifdef APPL_MICP_CONTROLLER
            appl_micp_ct_operations();
#else /* APPL_MICP_CONTROLLER */
            APPL_ERR("APPL_MICP_CONTROLLER NOT defined !\n");
#endif /* APPL_MICP_CONTROLLER */
            break;

        case 56:
#ifdef APPL_MICP_DEVICE
            appl_micp_dev_operations();
#else /* APPL_MICP_DEVICE */
            APPL_ERR("APPL_MICP_DEVICE NOT defined !\n");
#endif /* APPL_MICP_DEVICE */
            break;

        case 60:
#ifdef APPL_CSIP_SETCOORDINATOR
            appl_csip_sc_operations();
#else /* APPL_CSIP_SETCOORDINATOR */
            APPL_ERR("APPL_CSIP_SETCOORDINATOR NOT defined !\n");
#endif /* APPL_CSIP_SETCOORDINATOR */
            break;

        case 61:
#ifdef APPL_CSIP_SETMEMBER
            appl_csip_sm_operations();
#else /* APPL_CSIP_SETMEMBER */
            APPL_ERR("APPL_CSIP_SETMEMBER NOT defined !\n");
#endif /* APPL_CSIP_SETMEMBER */
            break;

        case 65:
#ifdef APPL_MCP_CLIENT
            main_mcp_ce_menu_operations();
#else /* APPL_MCP_CLIENT */
            APPL_ERR("APPL_MCP_CLIENT NOT defined !\n");
#endif /* APPL_MCP_CLIENT */
            break;

        case 66:
#ifdef APPL_MCP_SERVER
            main_mcp_se_menu_operations();
#else /* APPL_MCP_SERVER */
            APPL_ERR("APPL_MCP_SERVER NOT defined !\n");
#endif /* APPL_MCP_SERVER */
            break;

        case 70:
#ifdef APPL_CCP_CLIENT
            main_ccp_ce_menu_operations();
#else /* APPL_CCP_CLIENT */
            APPL_ERR("APPL_CCP_CLIENT NOT defined !\n");
#endif /* APPL_CCP_CLIENT */
            break;

        case 71:
#ifdef APPL_CCP_SERVER
            main_ccp_se_menu_operations();
#else /* APPL_CCP_SERVER */
            APPL_ERR("APPL_CCP_SERVER NOT defined !\n");
#endif /* APPL_CCP_SERVER */
            break;

        case 75:
#if ((defined APPL_TMAP_CLIENT) || (defined APPL_TMAP_SERVER))
            main_tmap_menu_operations();
#else /* ((defined APPL_TMAP_CLIENT) || (defined APPL_TMAP_SERVER)) */
            APPL_ERR("APPL_TMAP_CLIENT or APPL_TMAP_SERVER NOT defined !\n");
#endif /* ((defined APPL_TMAP_CLIENT) || (defined APPL_TMAP_SERVER)) */
            break;

        case 76:
#if ((defined APPL_HAP_CLIENT) || (defined APPL_HAP_SERVER))
            main_hap_menu_operations();
#else /* ((defined APPL_HAP_CLIENT) || (defined APPL_HAP_SERVER)) */
            APPL_ERR("APPL_HAP_CLIENT or APPL_HAP_SERVER NOT defined !\n");
#endif /* ((defined APPL_HAP_CLIENT) || (defined APPL_HAP_SERVER)) */
            break;

        case 80:
#ifdef BAP_SUPPORT_CONTEXT_MANAGE
            APPL_TRC("GA_get_context_info...\n");
            /* Fetch the connected device index, context and info */
            appl_ga_utils_get_conn_device_in_use
            (
                &index,
                &device,
                &context
            );

            retval = GA_get_context_info
                     (
                         &device,
                         &context,
                         &bap_svc_range_ptr,
                         &bap_char_info_ptr,
                         &bap_total_char_count
                     );
            APPL_TRC("Retval - ");
            if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
            {
                APPL_TRC("0x%04X\n", retval);
            }

            if (GA_SUCCESS == retval)
            {
                GA_mem_copy
                (
                    bap_svc_range,
                    bap_svc_range_ptr,
                    (BAP_SERVICE_COUNT * sizeof(GA_BRR_SVC_RANGE))
                );

                /**
                 *  Reference to allocate to save locally.
                 *  This can be written to persistent and retrieved
                 *  upon the next connection if bonded device.
                 */
                bap_char_info = GA_alloc_mem(bap_total_char_count * sizeof(GA_CHAR_INFO));
                if (NULL != bap_char_info)
                {
                    GA_mem_copy(bap_char_info, bap_char_info_ptr, (bap_total_char_count * sizeof(GA_CHAR_INFO)));
                }
            }
#else /* BAP_SUPPORT_CONTEXT_MANAGE */
            APPL_ERR("BAP_SUPPORT_CONTEXT_MANAGE NOT defined !\n");
#endif /* BAP_SUPPORT_CONTEXT_MANAGE */
            break;

        case 81:
#ifdef BAP_SUPPORT_CONTEXT_MANAGE
            APPL_TRC("GA_set_context_info...\n");
            /* Fetch the connected device index, context and info */
            appl_ga_utils_get_conn_device_in_use
            (
                &index,
                &device,
                &context
            );

            bap_svc_range_ptr = bap_svc_range;
            bap_char_info_ptr = bap_char_info;

            retval = GA_set_context_info
                     (
                         &device,
                         &context,
                         &bap_svc_range_ptr,
                         &bap_char_info_ptr,
                         &bap_total_char_count
                     );
            APPL_TRC("Retval - ");
            appl_ga_utils_display_ga_result(retval);

            if (GA_SUCCESS == retval)
            {
                /* Set the context in device manager */
                appl_ga_utils_update_context_of_conn_dev(context, index);
                if (NULL != bap_char_info)
                {
                    GA_free_mem(bap_char_info);
                    bap_char_info = NULL;
                }
            }
#else /* BAP_SUPPORT_CONTEXT_MANAGE */
            APPL_ERR("BAP_SUPPORT_CONTEXT_MANAGE NOT defined !\n");
#endif /* BAP_SUPPORT_CONTEXT_MANAGE */
            break;

        case 82:
#ifdef BAP_SUPPORT_CONTEXT_MANAGE
            /**
             * This is to free up the allocated char. info. memory
             * If incase GA_set_context_info() is NOT called after
             * GA_get_context_info().
             */

            /* Free the allocated memory for PACS + ASCS char. info. */
            if (NULL != bap_char_info)
            {
                APPL_TRC("Freeing bap_char_info ...\n");
                GA_free_mem(bap_char_info);
                bap_char_info = NULL;
            }
#else /* BAP_SUPPORT_CONTEXT_MANAGE */
            APPL_ERR("BAP_SUPPORT_CONTEXT_MANAGE NOT defined !\n");
#endif /* BAP_SUPPORT_CONTEXT_MANAGE */
            break;

        case 83:
#ifdef BAP_SUPPORT_CONTEXT_MANAGE
            APPL_TRC("GA_get_stream_context...\n");
            /* Fetch the connected device index, context and info */
            appl_ga_utils_get_conn_device_in_use
            (
                &index,
                &device,
                &context
            );

            bap_stream_count = sizeof(bap_stream) / sizeof(GA_STREAM_CONTEXT);
            retval = GA_get_stream_context
                     (
                         &context,
                         (GA_STREAM_CONTEXT *)&bap_stream,
                         &bap_stream_count
                   );
            APPL_TRC("Retval - ");
            appl_ga_utils_display_ga_result(retval);
            APPL_TRC("bap_stream_count: 0x%04X\n", bap_stream_count);
#else /* BAP_SUPPORT_CONTEXT_MANAGE */
            APPL_ERR("BAP_SUPPORT_CONTEXT_MANAGE NOT defined !\n");
#endif /* BAP_SUPPORT_CONTEXT_MANAGE */
            break;

        case 84:
#ifdef BAP_SUPPORT_CONTEXT_MANAGE
            APPL_TRC("GA_set_stream_context...\n");
            /* Fetch the connected device index, context and info */
            appl_ga_utils_get_conn_device_in_use
            (
                &index,
                &device,
                &context
            );

            retval = GA_set_stream_context
                     (
                         &context,
                         (GA_STREAM_CONTEXT *)&bap_stream,
                         &bap_stream_count
                     );
            APPL_TRC("Retval - ");
            appl_ga_utils_display_ga_result(retval);
#else /* BAP_SUPPORT_CONTEXT_MANAGE */
            APPL_ERR("BAP_SUPPORT_CONTEXT_MANAGE NOT defined !\n");
#endif /* BAP_SUPPORT_CONTEXT_MANAGE */
            break;

        case 85:
#ifdef APPL_CAS_SETCOORDINATOR
#ifdef CSIP_SUPPORT_CONTEXT_MANAGE
            APPL_TRC("GA_get_cs_context_info...\n");
            /* Fetch the connected device index, context and info */
            appl_ga_utils_get_conn_device_in_use
            (
                &index,
                &device,
                &context
            );

            retval = GA_get_cs_context_info
                     (
                         &device,
                         &context,
                         &cap_cs_svc_range_ptr,
                         &cap_cs_char_info_ptr,
                         &cap_cs_total_char_count
                     );
            APPL_TRC("Retval - ");
            if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
            {
                APPL_TRC("0x%04X\n", retval);
            }

            if (GA_SUCCESS == retval)
            {
                GA_mem_copy
                (
                    &cap_cs_svc_range,
                    cap_cs_svc_range_ptr,
                    sizeof(GA_BRR_SVC_RANGE)
                );

                /**
                 *  Reference to allocate to save locally.
                 *  This can be written to persistent and retrieved
                 *  upon the next connection if bonded device.
                 */
                cap_cs_char_info = GA_alloc_mem(cap_cs_total_char_count * sizeof(GA_CHAR_INFO));
                if (NULL != cap_cs_char_info)
                {
                    GA_mem_copy(cap_cs_char_info, cap_cs_char_info_ptr, (cap_cs_total_char_count * sizeof(GA_CHAR_INFO)));
                }
            }
#else /* CSIP_SUPPORT_CONTEXT_MANAGE */
            APPL_ERR("CSIP_SUPPORT_CONTEXT_MANAGE NOT defined !\n");
#endif /* CSIP_SUPPORT_CONTEXT_MANAGE */
#else /* APPL_CAS_SETCOORDINATOR */
            APPL_ERR("APPL_CAS_SETCOORDINATOR NOT defined !\n");
#endif /* APPL_CAS_SETCOORDINATOR */
            break;

        case 86:
#ifdef APPL_CAS_SETCOORDINATOR
#ifdef CSIP_SUPPORT_CONTEXT_MANAGE
            APPL_TRC("GA_set_cs_context_info...\n");
            /* Fetch the connected device index, context and info */
            appl_ga_utils_get_conn_device_in_use
            (
                &index,
                &device,
                &context
            );

            cap_cs_svc_range_ptr = &cap_cs_svc_range;
            cap_cs_char_info_ptr = cap_cs_char_info;

            retval = GA_set_cs_context_info
                     (
                         &device,
                         &context,
                         &cap_cs_svc_range_ptr,
                         &cap_cs_char_info_ptr,
                         &cap_cs_total_char_count
                     );
            APPL_TRC("Retval - ");
            appl_ga_utils_display_ga_result(retval);

            if (GA_SUCCESS == retval)
            {
                /* Set the context in device manager */
                appl_ga_utils_update_context_of_conn_dev(context, index);
                if (NULL != bap_char_info)
                {
                    GA_free_mem(cap_cs_char_info);
                    cap_cs_char_info = NULL;
                }
            }
#else /* CSIP_SUPPORT_CONTEXT_MANAGE */
            APPL_ERR("CSIP_SUPPORT_CONTEXT_MANAGE NOT defined !\n");
#endif /* CSIP_SUPPORT_CONTEXT_MANAGE */
#else /* APPL_CAS_SETCOORDINATOR */
            APPL_ERR("APPL_CAS_SETCOORDINATOR NOT defined !\n");
#endif /* APPL_CAS_SETCOORDINATOR */
            break;

        case 88:
#ifdef APPL_CAS_SETCOORDINATOR
#ifdef CSIP_SUPPORT_CONTEXT_MANAGE
            /**
            * This is to free up the allocated char. info. memory
            * If incase GA_set_context_info() is NOT called after
            * GA_get_context_info().
            */

            /* Free the allocated memory for PACS + ASCS char. info. */
            if (NULL != cap_cs_char_info)
            {
                APPL_TRC("Freeing bap_char_info ...\n");
                GA_free_mem(cap_cs_char_info);
                cap_cs_char_info = NULL;
            }
#else /* CSIP_SUPPORT_CONTEXT_MANAGE */
            APPL_ERR("CSIP_SUPPORT_CONTEXT_MANAGE NOT defined !\n");
#endif /* CSIP_SUPPORT_CONTEXT_MANAGE */
#else /* APPL_CAS_SETCOORDINATOR */
            APPL_ERR("APPL_CAS_SETCOORDINATOR NOT defined !\n");
#endif /* APPL_CAS_SETCOORDINATOR */
            break;

        case 90:
#ifdef BAP_SUPPORT_CONFIG_SELECTION
            APPL_TRC("GA_update_ntf_configuration...\n");
            retval = GA_update_ntf_configuration
                     (
                         (/* BAP_CHAR_CONFIG(BAP_CHAR_ID_SOURCE_PAC) |
                          BAP_CHAR_CONFIG(BAP_CHAR_ID_SOURCE_AUDIO_LOCATIONS) |
                          BAP_CHAR_CONFIG(BAP_CHAR_ID_SINK_PAC) |
                          BAP_CHAR_CONFIG(BAP_CHAR_ID_SINK_AUDIO_LOCATIONS) |
                          BAP_CHAR_CONFIG(BAP_CHAR_ID_AVAILABLE_AUDIO_CONTEXTS) |
                          BAP_CHAR_CONFIG(BAP_CHAR_ID_SUPPORTED_AUDIO_CONTEXTS) | */
                          BAP_CHAR_CONFIG(BAP_CHAR_ID_ASE_CP) |
                          BAP_CHAR_CONFIG(BAP_CHAR_ID_ASE_SOURCE) |
                          BAP_CHAR_CONFIG(BAP_CHAR_ID_ASE_SINK))
                     );
            APPL_TRC("Retval - 0x%04X\n", retval);
#else /* BAP_SUPPORT_CONFIG_SELECTION */
            APPL_ERR("BAP_SUPPORT_CONFIG_SELECTION NOT defined !\n");
#endif /* BAP_SUPPORT_CONFIG_SELECTION */
            break;

        case 100:
#ifdef APPL_CAS_SETCOORDINATOR
            /* Fetch the connected device index and info */
            appl_ga_utils_get_conn_device_in_use
            (
                &index,
                &device,
                NULL
            );

            APPL_TRC("Discover CAS\n");
            retval = GA_cap_discover(&device);
            APPL_TRC("Retval - ");
            if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
            {
                APPL_TRC("0x%04X\n", retval);
            }
#else /* APPL_CAS_SETCOORDINATOR */
            APPL_ERR("APPL_CAS_SETCOORDINATOR NOT defined !\n");
#endif /* APPL_CAS_SETCOORDINATOR */
            break;

        case 101:
#ifdef APPL_CAS_SETCOORDINATOR
            /* Fetch the connected device index and info */
            appl_ga_utils_get_conn_device_in_use
            (
                &index,
                &device,
                NULL
            );

            appl_ga_utils_fetch_cas_of_conn_dev(index, &cas_svc_info);

            APPL_TRC("Setup CAS Member\n");
            retval = GA_cap_setup_member(&device, &cas_svc_info, &context);
            APPL_TRC("Retval - ");
            if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
            {
                APPL_TRC("0x%04X\n", retval);
            }
            APPL_TRC("Context: %d\n", context);

            if (GA_SUCCESS == retval)
            {
                /* Set the context in device manager */
                appl_ga_utils_update_context_of_conn_dev
                (
                    context,
                    index
                );
            }
#else /* APPL_CAS_SETCOORDINATOR */
            APPL_ERR("APPL_CAS_SETCOORDINATOR NOT defined !\n");
#endif /* APPL_CAS_SETCOORDINATOR */
            break;

        case 102:
#ifdef APPL_CAS_SETCOORDINATOR
        {
            /* Fetch the connected device index, context and info */
            appl_ga_utils_get_conn_device_in_use
            (
                &index,
                &device,
                &context
            );
            CONSOLE_OUT("\n1. Release\n2. Close\n");
            CONSOLE_OUT("Enter your choice: ");
            CONSOLE_IN("%d", &choice);
            if (1 == choice)
            {
                APPL_TRC("GA_release\n");
                retval = GA_cap_release_member(&context);
                APPL_TRC("Retval - ");
                if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
                {
                    APPL_TRC("0x%04X\n", retval);
                }
                if (GA_SUCCESS == retval)
                {
                    /* Reset the context in device manager */
                    appl_ga_utils_update_context_of_conn_dev(0U, index);
                }
            }
            else if (2 == choice)
            {
                APPL_TRC("GA_close\n");
                retval = GA_cap_close_member(&context);
                APPL_TRC("Retval - ");
                if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
                {
                    APPL_TRC("0x%04X\n", retval);
                }
                if (GA_SUCCESS == retval)
                {
                    /* Reset the context in device manager */
                    appl_ga_utils_update_context_of_conn_dev(0U, index);
                }
            }
            else
            {
                APPL_ERR("Invalid choice !\n");
            }
        }
#else /* APPL_CAS_SETCOORDINATOR */
            APPL_ERR("APPL_CAS_SETCOORDINATOR NOT defined !\n");
#endif /* APPL_CAS_SETCOORDINATOR */
        break;

        case 105:
#ifdef APPL_CAS_SETCOORDINATOR
            /* Fetch the connected device index, context and info */
            appl_ga_utils_get_conn_device_in_use
            (
                &index,
                &device,
                &context
            );
            CONSOLE_OUT("\n1. Unlock\n2. Lock\n");
            CONSOLE_OUT("Enter your choice: ");
            CONSOLE_IN("%d", &choice);

            retval = GA_cap_lock_member(&context, (UINT8)choice);
            APPL_TRC("0x%04X\n", retval);

            if (GA_SUCCESS == retval)
            {
                /* If success, update the value in the DB */
                appl_ga_utils_update_lock_req_for_sm(index, (UINT8)choice);
            }
#else /* APPL_CAS_SETCOORDINATOR */
            APPL_ERR("APPL_CAS_SETCOORDINATOR NOT defined !\n");
#endif /* APPL_CAS_SETCOORDINATOR */
            break;

        case 110:
#ifdef APPL_CAS_SETMEMBER
            /* Fetch the connected device index, context and info */
            appl_ga_utils_get_conn_device_in_use
            (
                &index,
                &device,
                &context
            );

            retval = GA_cap_member_lock_update(&device);
            APPL_TRC("0x%04X\n", retval);
#else /* APPL_CAS_SETMEMBER */
            APPL_TRC("APPL_CAS_SETMEMBER not defined\n");
#endif /* APPL_CAS_SETMEMBER */
            break;

        case 111:
#ifdef APPL_CAS_SETMEMBER
            pmember = NULL;
            pdevice = NULL;

            /* Take Input if we want to Update/Notify/Both */
            choice = appl_ga_utils_bap_get_choice_for_update_notify();
            index = (UINT8)choice;

            if ((0x01 == index) ||
                (0x03 == index))
            {
                CONSOLE_OUT("\n0. Encrypted\n1. Plain\n2. OOB\n");
                CONSOLE_OUT("Enter your choice: ");
                CONSOLE_IN("%d", &choice);

                local_cas_sm.member.sirk[0U] = (UINT8)choice;
                if (0U == choice)
                {
                    GA_mem_copy(&local_cas_sm.member.sirk[1U], &local_cas_sm.enc_sirk[0U], CSIP_SIRK_LEN);
                }
                else
                {
                    UINT8 sirk[16] = APPL_CAS_SM_SIRK;
                    GA_mem_copy(&local_cas_sm.member.sirk[1U], &sirk[0U], CSIP_SIRK_LEN) ;
                }

                pmember = &local_cas_sm.member;
            }
            if ((0x02 == index) ||
                (0x03 == index))
            {
                /* Fetch the connected device index and info */
                appl_ga_utils_get_conn_device_in_use
                (
                    &index,
                    &device,
                    NULL
                );

                pdevice = &device;
            }

            retval = GA_cap_member_sirk_update(pdevice, pmember);
            APPL_TRC("0x%04X\n", retval);
#else /* APPL_CAS_SETMEMBER */
            APPL_TRC("APPL_CAS_SETMEMBER not defined\n");
#endif /* APPL_CAS_SETMEMBER */
            break;

        case 112:
#ifdef APPL_CAS_SETMEMBER
            pmember = NULL;
            pdevice = NULL;

            /* Take Input if we want to Update/Notify/Both */
            choice = appl_ga_utils_bap_get_choice_for_update_notify();
            index = (UINT8)choice;

            if ((0x01 == index) ||
                (0x03 == index))
            {
                CONSOLE_OUT("Enter Size: ");
                CONSOLE_IN("%d", &choice);

                local_cas_sm.member.size = (UINT8)choice;
                pmember = &local_cas_sm.member;
            }
            if ((0x02 == index) ||
                (0x03 == index))
            {
                /* Fetch the connected device index and info */
                appl_ga_utils_get_conn_device_in_use
                (
                    &index,
                    &device,
                    NULL
                );
                pdevice = &device;
            }

            retval = GA_cap_member_size_update(pdevice, pmember);
            APPL_TRC("0x%04X\n", retval);
#else /* APPL_CAS_SETMEMBER */
            APPL_TRC("APPL_CAS_SETMEMBER not defined\n");
#endif /* APPL_CAS_SETMEMBER */
            break;

        case 113:
#ifdef APPL_CAS_SETMEMBER
            pmember = NULL;
            pdevice = NULL;

            /* Take Input if we want to Update/Notify/Both */
            choice = appl_ga_utils_bap_get_choice_for_update_notify();
            index = (UINT8)choice;

            if ((0x01 == index) ||
                (0x03 == index))
            {
                CONSOLE_OUT("Enter Rank: ");
                CONSOLE_IN("%d", &choice);

                local_cas_sm.member.rank = (UINT8)choice;
                pmember = &local_cas_sm.member;
            }
            else
            {
                CONSOLE_OUT("Rank cannot be notified\n");
            }

            retval = GA_cap_member_rank_update(pmember);
            APPL_TRC("0x%04X\n", retval);
#else /* APPL_CAS_SETMEMBER */
            APPL_TRC("APPL_CAS_SETMEMBER not defined\n");
#endif /* APPL_CAS_SETMEMBER */
            break;

        case 115:
#ifdef APPL_CAS_SETMEMBER
#ifdef CAP_SIMULATE_RANDOM_DEVICE_LOCKING
            CONSOLE_OUT("Enter endpoint address: ");
            appl_get_bd_addr(device.bd_addr);
            CONSOLE_OUT("Enter endpoint type: ");
            CONSOLE_IN("%d", &choice);
            device.bd_type = (UINT8)choice;

            CONSOLE_OUT("Enter Lock Status (1: Unlock, 2: Lock): ");
            CONSOLE_IN("%d", &choice);
            local_cas_sm.member.lock = (UINT8)choice;

            retval = GA_cap_member_device_lock(&device, &local_cas_sm.member);
            APPL_TRC("0x%04X\n", retval);
#else /* CAP_SIMULATE_RANDOM_DEVICE_LOCKING */
            APPL_TRC("CAP_SIMULATE_RANDOM_DEVICE_LOCKING not defined\n");
#endif /* CAP_SIMULATE_RANDOM_DEVICE_LOCKING */
#else /* APPL_CAS_SETMEMBER */
            APPL_TRC("APPL_CAS_SETMEMBER not defined\n");
#endif /* APPL_CAS_SETMEMBER */
            break;

        case 120:
#ifdef APPL_CAS_SETCOORDINATOR
            {
                UINT8 size, actual;

                APPL_TRC("Find the Set count\n");
                appl_ga_utils_get_conn_device_in_use(&index, NULL, NULL);
                appl_ga_utils_fetch_set_handle(index, &set_handle);
                retval = GA_cap_set_find_count(set_handle, &size, &actual);
                APPL_TRC("Retval - 0x%04X\n", retval);

                if (GA_SUCCESS == retval)
                {
                    APPL_TRC("Set Size - %d, Actual - %d\n", size, actual);
                }
            }
#else /* APPL_CAS_SETCOORDINATOR */
            APPL_TRC("APPL_CAS_SETCOORDINATOR not defined\n");
#endif /* APPL_CAS_SETCOORDINATOR */
            break;

        case 121:
#ifdef APPL_CAS_SETCOORDINATOR
            APPL_TRC("Initiate LockRequest\n");
            appl_ga_utils_get_conn_device_in_use(&index, NULL, NULL);
            appl_ga_utils_fetch_set_handle(index, &set_handle);
            retval = GA_cap_set_lockrequest(set_handle);
            APPL_TRC("Retval - 0x%04X\n", retval);
#else /* APPL_CAS_SETCOORDINATOR */
            APPL_TRC("APPL_CAS_SETCOORDINATOR not defined\n");
#endif /* APPL_CAS_SETCOORDINATOR */
            break;

        case 122:
#ifdef APPL_CAS_SETCOORDINATOR
            APPL_TRC("Initiate LockRelease\n");
            appl_ga_utils_get_conn_device_in_use(&index, NULL, NULL);
            appl_ga_utils_fetch_set_handle(index, &set_handle);
            retval = GA_cap_set_lockrelease(set_handle);
            APPL_TRC("Retval - 0x%04X\n", retval);
#else /* APPL_CAS_SETCOORDINATOR */
            APPL_TRC("APPL_CAS_SETCOORDINATOR not defined\n");
#endif /* APPL_CAS_SETCOORDINATOR */
            break;

        case 123:
#ifdef APPL_CAS_SETCOORDINATOR
            APPL_TRC("OrdAccess Begin\n");
            appl_ga_utils_get_conn_device_in_use(&index, NULL, NULL);
            appl_ga_utils_fetch_set_handle(index, &set_handle);
            retval = GA_cap_set_orderedaccess_begin(set_handle);
            APPL_TRC("Retval - 0x%04X\n", retval);
#else /* APPL_CAS_SETCOORDINATOR */
            APPL_TRC("APPL_CAS_SETCOORDINATOR not defined\n");
#endif /* APPL_CAS_SETCOORDINATOR */
            break;

        case 124:
#ifdef APPL_CAS_SETCOORDINATOR
            APPL_TRC("OrdAccess End\n");
            appl_ga_utils_get_conn_device_in_use(&index, NULL, NULL);
            appl_ga_utils_fetch_set_handle(index, &set_handle);
            retval = GA_cap_set_orderedaccess_end(set_handle);
            APPL_TRC("Retval - 0x%04X\n", retval);
#else /* APPL_CAS_SETCOORDINATOR */
            APPL_TRC("APPL_CAS_SETCOORDINATOR not defined\n");
#endif /* APPL_CAS_SETCOORDINATOR */
            break;

        case 125:
#ifdef APPL_CAS_SETCOORDINATOR
            APPL_TRC("OrdAccess Next Endpoint\n");
            appl_ga_utils_get_conn_device_in_use(&index, NULL, NULL);
            appl_ga_utils_fetch_set_handle(index, &set_handle);
            retval = GA_cap_set_access_next_member(set_handle, &device);
            APPL_TRC("Retval - 0x%04X\n", retval);

            if (GA_SUCCESS == retval)
            {
                APPL_TRC("Access Endpoint Type: %02X\n", device.bd_type);
                APPL_TRC("Access Endpoint Addr: %02X %02X %02X %02X %02X %02X\n",
                    device.bd_addr[0], device.bd_addr[1], device.bd_addr[2],
                    device.bd_addr[3], device.bd_addr[4], device.bd_addr[5]);
            }
#else /* APPL_CAS_SETCOORDINATOR */
            APPL_TRC("APPL_CAS_SETCOORDINATOR not defined\n");
#endif /* APPL_CAS_SETCOORDINATOR */
            break;

        case 130:
#ifdef APPL_CAS_SETCOORDINATOR
            CONSOLE_OUT("1. Scan for CAS Devices\n2. Stop Scan for CAS Devices\n");
            CONSOLE_IN("%x", &choice);

            if (1 == (UINT8)choice)
            {
                APPL_TRC("Scan for CAS Discovery\n");
                retval = appl_ga_scan_for_cas();
                APPL_TRC("Retval - ");
                appl_ga_utils_display_ga_result(retval);
            }
            else if (2 == (UINT8)choice)
            {
                if (APPL_GA_SCAN_FOR_CAS == is_scan_enabled)
                {
                    APPL_TRC("Stop Scan for CAS Discovery\n");
                    retval = appl_ga_stop_scan_for_cas();
                    APPL_TRC("Retval - ");
                    if (GA_SUCCESS == retval)
                    {
                        appl_ga_reset_cas_db();
                    }
                    appl_ga_utils_display_ga_result(retval);
                }
                else
                {
                    /* TODO */
                }
            }
#else /* APPL_CAS_SETCOORDINATOR */
            APPL_TRC("APPL_CAS_SETCOORDINATOR not defined\n");
#endif /* APPL_CAS_SETCOORDINATOR */
            break;

        case 131:
#ifdef APPL_CAS_SETCOORDINATOR
            appl_ga_display_cas_db();
#else /* APPL_CAS_SETCOORDINATOR */
            APPL_TRC("APPL_CAS_SETCOORDINATOR not defined\n");
#endif /* APPL_CAS_SETCOORDINATOR */
            break;

        case 132:
#ifdef APPL_CAS_SETCOORDINATOR
            /* Input CAS Device for RSI Verification */
            index = appl_ga_utils_get_cas_dev_index();

            appl_ga_utils_verify_rsi(index);
#else /* APPL_CAS_SETCOORDINATOR */
            APPL_TRC("APPL_CAS_SETCOORDINATOR not defined\n");
#endif /* APPL_CAS_SETCOORDINATOR */
            break;

        default:
            APPL_INF("Invalid Choice\n");
            break;

        }
        if (0U == menu_choice)
        {
            /* return */
            break;
        }
    }

    return 0;
}

GA_RESULT appl_ga_authenticate(UCHAR security_mode)
{
    GA_RESULT      retval;
    SMP_AUTH_INFO  auth;
    SMP_BD_HANDLE  bd_handle;
    GA_ENDPOINT    device;
    UINT8          dev_index;

    /* Initialize */
    retval = GA_FAILURE;
    /* Security Mode - SMP_LEGACY_MODE or SMP_LESC_MODE */
    auth.pair_mode = security_mode;
    auth.security = SMP_SEC_LEVEL_1;
    auth.bonding = BT_TRUE;
    auth.ekey_size = 16U;
    dev_index = 0U;

    /* Fetch Conn Device Index */
    dev_index = appl_ga_utils_bap_get_input_conn_dev_index();

    /* Fetch device from conn_dev_index */
    appl_ga_utils_get_conn_device(dev_index, &device);

#ifdef SMP_LESC_CROSS_TXP_KEY_GEN
    auth.transport = SMP_LINK_LE;
    auth.xtx_info = SMP_XTX_DISABLE;
    BT_smp_get_link_handle
    (
        (BT_DEVICE_ADDR *)&device,
        &bd_handle,
        auth.transport
    );
#else /* SMP_LESC_CROSS_TXP_KEY_GEN */
    BT_smp_get_bd_handle
    (
        (BT_DEVICE_ADDR *)&device,
        &bd_handle
    );
#endif /* SMP_LESC_CROSS_TXP_KEY_GEN */

    retval = BT_smp_authenticate
             (
                 &bd_handle,
                 &auth
             );

    return retval;
}

void appl_ga_encsirk_callback(UCHAR * data, UINT16 datalen)
{
    GA_IGNORE_UNUSED_PARAM(datalen);
#ifdef APPL_CAS_SETMEMBER
    APPL_TRC("\n============================\n");
    APPL_TRC("Encrypted SIRK generated:\n");

    GA_mem_copy(&local_cas_sm.enc_sirk[0U], data, CSIP_SIRK_LEN);
    appl_dump_bytes(&local_cas_sm.enc_sirk[0U], CSIP_SIRK_LEN);
    APPL_TRC("============================\n");

    /* Update member if set */
    if (CSIP_SIRK_TYPE_ENCRYPTED == local_cas_sm.member.sirk[0])
    {
        GA_mem_copy(&local_cas_sm.member.sirk[1], &local_cas_sm.enc_sirk[0U], CSIP_SIRK_LEN);
        GA_cap_member_sirk_update(NULL, &local_cas_sm.member);
    }
#endif /* APPL_CAS_SETMEMBER */
}

void appl_ga_decsirk_callback(UCHAR * data, UINT16 datalen)
{
    GA_IGNORE_UNUSED_PARAM(datalen);

    UINT8          conn_dev_index;
    GA_SET_MEMBER  sm;
    UINT8          set_handle;
    GA_ENDPOINT    device;

#ifdef APPL_CAS_SETMEMBER
    GA_RESULT retval;

    APPL_TRC("\n============================\n");
    APPL_TRC("Decrypted SIRK generated:\n");

    appl_dump_bytes(data, CSIP_SIRK_LEN);
    APPL_TRC("============================\n");

    /* Fetch the SM for which decSirkOngoing is set */
    appl_ga_utils_fetch_sm_device_sirk_decrypting(&conn_dev_index);
    /* Update decrypted SIRK for the SM */
    appl_ga_utils_update_sm_decsirk(conn_dev_index, data);

    /* Fetch the SM data */
    appl_ga_utils_fetch_sm_of_conn_dev
    (
        conn_dev_index,
        &sm
    );

    /*
     * TODO:
     * Do not add the device to the SM Database if triggered as part of
     * notification. Only update it. (cap_utils_api.c)
     */

    /* Further process */
    /* Create/find a set and Add the member */
    APPL_TRC("Check if a Set handle is available... ");
    retval = GA_cap_set_find(&data[0U], sm.size, &set_handle);
    APPL_TRC("Retval - 0x%04X\n", retval);

    if (GA_SUCCESS != retval)
    {
        APPL_TRC("No, Create a Set handle... ");
        retval = GA_cap_set_create(&data[0U], sm.size, &set_handle);
        APPL_TRC("Retval - 0x%04X\n", retval);

        appl_ga_utils_update_set_handle_of_conn_dev(conn_dev_index, set_handle);
    }

    if (GA_SUCCESS == retval)
    {
        if (GA_SUCCESS == appl_ga_utils_get_conn_device(conn_dev_index, &device))
        {
            if (GA_SUCCESS == GA_cap_fetch_member_from_device(set_handle, &device, NULL))
            {
                /* TODO: If already updated once, need no do for all members of the set */
                /* Update the Member */
                APPL_TRC("Update member to Set...\n");
                retval = GA_cap_set_update_member_sirk(set_handle, &device, &data[0U]);
            }
            else
            {
                APPL_TRC("Adding member to Set...\n");
                retval = GA_cap_set_add_member(set_handle, &device, sm.rank);
                APPL_TRC("Retval - 0x%04X\n", retval);
            }
        }
        else
        {
            APPL_TRC("Device not found!!!\n");
        }
    }

    appl_ga_utils_update_sm_decsirk_ongoing_status
    (
        conn_dev_index,
        GA_FALSE
    );
#endif /* APPL_CAS_SETMEMBER */
}

void appl_ga_bonded_connection(BT_DEVICE_ADDR * bdaddr, UCHAR * key)
{
#if ((defined APPL_CAS_SETMEMBER) || (defined APPL_CAS_SETCOORDINATOR))
    GA_RESULT retval;
    UINT8     conn_index;

    if (APPL_GA_INIT_STATUS_GA != ga_init_status)
    {
        return;
    }

#ifdef APPL_CAS_SETMEMBER
    if ((2U <= local_cas_sm.member.size) && (CSIP_SIRK_TYPE_ENCRYPTED == local_cas_sm.member.sirk[0]))
    {
        /*
         * This encryption of SIRK to be done only on Server side for a Set Member.
         * Also, Perform only for Encrypted Key Type.
         */
        APPL_TRC("Generating Encrypted SIRK for the bonded device...\n");
        retval = CSIP_sirk_process(&local_cas_sm.member.sirk[1U], key, 0x01, appl_ga_encsirk_callback);
        APPL_TRC("Retval - 0x%04X\n", retval);
    }
#endif /* APPL_CAS_SETMEMBER */

    if (GA_SUCCESS == appl_ga_utils_get_conn_device_index
                      (
                          *(GA_ENDPOINT*)bdaddr,
                          &conn_index
                      ))
    {
        /* Update the Key only for the Client Device */
        appl_ga_utils_update_key_of_conn_dev(conn_index, key);
    }

#ifdef APPL_CSIP_SETMEMBER
    appl_csip_encrypt_sirk((GA_ENDPOINT*)bdaddr);
#endif /* APPL_CSIP_SETMEMBER */
#endif /* ((defined APPL_CAS_SETMEMBER) || (defined APPL_CAS_SETCOORDINATOR)) */
}

void appl_ga_process_sirk(GA_ENDPOINT * device, UCHAR type, UCHAR * sirk)
{
#ifdef APPL_CAS_SETCOORDINATOR
    GA_RESULT retval;
    UINT8 conn_dev_index;
    UINT8 key[16U];

    /* Decrypt if encrypted */
    if (CSIP_SIRK_TYPE_ENCRYPTED == type)
    {
        if (GA_SUCCESS == appl_ga_utils_get_conn_device_index(*device, &conn_dev_index))
        {
            appl_ga_utils_fetch_key_of_conn_dev(conn_dev_index, key);
            APPL_TRC("Decrypting SIRK for the bonded device...\n");
            retval = CSIP_sirk_process(sirk, key, 0x00, appl_ga_decsirk_callback);
            APPL_TRC("Retval - 0x%04X\n", retval);

            if (GA_SUCCESS == retval)
            {
                appl_ga_utils_update_sm_decsirk_ongoing_status
                (
                    conn_dev_index,
                    GA_TRUE
                );
            }
        }
    }
#endif /* APPL_CAS_SETCOORDINATOR */
}

GA_RESULT appl_ga_disconnect(void)
{
    UINT32     read;
    GA_RESULT  retval;
    UCHAR      reason;
    UINT16     handle;

    /* Initialize */
    retval = GA_FAILURE;
    reason = 0U;
    handle = 0U;
    read = 0U;

    CONSOLE_OUT("ACL/SCO Connection Handle (in Hex) = ");
    CONSOLE_IN("%x", &read);
    handle = (UINT16)read;
    CONSOLE_OUT("Reason for Disconnection (in Hex) = ");
    CONSOLE_IN("%x", &read);
    reason = (UCHAR)read;
    APPL_TRC("\nStarting ACL/SCO Disconnection... ");
    retval = appl_ga_utils_disconnect(handle, reason);

    return retval;
}

void appl_ga_module_init(int choice)
{
    GA_RESULT retval;

    /* Save the GA role chosen */
    appl_ga_role = (UCHAR)choice;

    retval = appl_ga_utils_hci_register_callback();
    if (GA_SUCCESS == retval)
    {
        APPL_TRC("HCI Callback Registered\n");
    }
    else
    {
        APPL_ERR
        (
            "FAILED to register HCI Callback !!! Error code = %04X\n",
            retval
        );
    }

    /* Register CAP callback */
    retval = GA_register_callback(appl_ga_cap_callback);
    APPL_TRC("GA_register_callback. Retval - 0x%04X\n", retval);

    ga_init_status = APPL_GA_INIT_STATUS_GA;

    /* Initialize Device Manager */
    appl_ga_utils_dev_manager_init();

    /* Initialize Legacy LE Connection Parameters */
    appl_ga_utils_set_default_values_le_conn_params();
    /* Initialize Extended LE Connection Parameters */
    appl_ga_utils_set_default_values_le_ext_conn_params();

    if (1U == appl_ga_role)
    {
        /* Initialize Unicast Module - Client */
        appl_ga_uc_client_init();

        /* Initialize Broadcast Module - Source */
        appl_ga_bc_source_init();

        /* Initialize Volume Control Module - Client(Controller) */
        appl_ga_vcp_client_init();

        /* Initialize Microphone Control Module - Client(Controller) */
        appl_ga_micp_client_init();

        /* Initialize Microphone Control Module - Client(Controller) */
        appl_ga_csip_sc_init();

        /* Prepare the CAP role and CS Member if required */
        retval = GA_prepare((CAP_ROLE_INITIATOR | CAP_ROLE_COMMANDER), NULL);
        APPL_TRC("GA_prepare. Retval - 0x%04X\n", retval);

        appl_ga_utils_pacs_init();

        /* Initialize ISO Module - Source */
        appl_ga_utils_audio_src_init();

        /* Initialize ISO Module - Sink */
        appl_ga_utils_audio_snk_init();
    }
    else if (2U == appl_ga_role)
    {
        /* Initialize Unicast Module - Server */
        appl_ga_uc_server_init();

        /* Initialize Broadcast Module - Sink */
        appl_ga_bc_sink_init();

        /* Initialize Volume Control Module - Server(Renderer) */
        appl_ga_vcp_server_init();

        /* Initialize Microphone Control Module - Server(Device) */
        appl_ga_micp_server_init();

        /* Initialize Coordinated Set Module - Server(Set Member) */
        appl_ga_csip_sm_init();

        /* Prepare the CAP role and CS Member if required */
        retval = GA_prepare(CAP_ROLE_ACCEPTOR, NULL);
        APPL_TRC("GA_prepare. Retval - 0x%04X\n", retval);

        /* Initialize ISO Module - Source */
        appl_ga_utils_audio_src_init();

        /* Initialize ISO Module - Sink */
        appl_ga_utils_audio_snk_init();

        /* Get the CAP Annoucement Type */
        appl_ga_utils_update_cap_announcement_type_in_adv();
    }
    else if (3U == appl_ga_role)
    {
        /* Initialize Unicast Module - Client */
        appl_ga_uc_client_init();
        /* Initialize Unicast Module - Server */
        appl_ga_uc_server_init();

        /* Initialize Broadcast Module - Source */
        appl_ga_bc_source_init();
        /* Initialize Broadcast Module - Sink */
        appl_ga_bc_sink_init();

        /* Initialize Volume Control Module - Client(Controller) */
        appl_ga_vcp_client_init();
        /* Initialize Volume Control Module - Server(Renderer) */
        appl_ga_vcp_server_init();

        /* Initialize Microphone Control Module - Client(Controller) */
        appl_ga_micp_client_init();
        /* Initialize Microphone Control Module - Server(Device) */
        appl_ga_micp_server_init();

        /* Initialize Coordinated Set Module - Client(Set Coordinator) */
        appl_ga_csip_sc_init();
        /* Initialize Coordinated Set Module - Server(Set Member) */
        appl_ga_csip_sm_init();

#ifndef APPL_CAS_SETMEMBER
        /* Prepare the CAP role and CS Member if required */
        (GA_IGNORE_RETURN_VALUE) GA_prepare
        (
            (CAP_ROLE_INITIATOR | CAP_ROLE_ACCEPTOR | CAP_ROLE_COMMANDER),
            NULL
        );
#else /* APPL_CAS_SETMEMBER */
        appl_ga_cs_sm_init();

        /* Prepare the CAP role and CS Member if required */
        (GA_IGNORE_RETURN_VALUE)GA_prepare
        (
            (CAP_ROLE_INITIATOR | CAP_ROLE_ACCEPTOR | CAP_ROLE_COMMANDER),
            &local_cas_sm.member
        );
#endif /* APPL_CAS_SETMEMBER */

        /* Get the CAP Annoucement Type */
        appl_ga_utils_update_cap_announcement_type_in_adv();

        /* Initialize ISO Module - Source */
        appl_ga_utils_audio_src_init();

        /* Initialize ISO Module - Sink */
        appl_ga_utils_audio_snk_init();

        /* Initialize PACS Module - Client */
        appl_ga_utils_pacs_init();

        /* Initialize Audio PL Module */
        /* Initialize LC3 Module */
    }
    else if (4U == appl_ga_role)
    {
        /* Other Initialization will be done as part of TMAP/HAP/PBP */
    }
    else
    {
        /* No action */
    }

    /*
     * Initialize Host Features - Connected Isochronous Stream
     * (Host Support) - Bit 32
     */
    appl_ga_utils_hci_set_host_feature(0x20U, 0x01U);

    /* TODO:
     * LE 2M PHY - Bit 8
     * appl_ga_utils_hci_set_host_feature(0x08U, 0x01U);
     *
     * LE Coded PHY - Bit 11
     * appl_ga_utils_hci_set_host_feature(0x0BU, 0x01U);
     *
     * PAST Sender - Bit 24
     * appl_ga_utils_hci_set_host_feature(0x18U, 0x01U);
     *
     * PAST Recipient - Bit 25
     * appl_ga_utils_hci_set_host_feature(0x19U, 0x01U);
     *
     * CIS Central - Bit 28
     * appl_ga_utils_hci_set_host_feature(0x1CU, 0x01U);
     *
     * CIS Peripheral - Bit 29
     * appl_ga_utils_hci_set_host_feature(0x1DU, 0x01U);
     *
     * ISO Broadcaster - Bit 30
     * appl_ga_utils_hci_set_host_feature(0x1EU, 0x01U);
     *
     * CIS Host Support - Bit 32
     * appl_ga_utils_hci_set_host_feature(0x20U, 0x01U);
     *
     */
}

void appl_ga_brr_setup(void)
{
    GA_RESULT retval;

    APPL_TRC("GA Setup... ");
    retval = ga_brr_setup_pl();
    APPL_TRC("Retval - ");
    if (GA_SUCCESS != appl_ga_utils_display_ga_result(retval))
    {
        APPL_TRC("0x%04X\n", retval);
    }

    return;
}

void appl_ga_automate_server_sink_init(void)
{
#ifdef APPL_INIT_AUTOMATE_SERVER_SINK
    GA_RESULT retval;
    GA_ENDPOINT device;

    /* 2U refers to GA Server */
    appl_ga_module_init(2U);
    appl_tmap_automate_init();

    /* Init TMAP role and PACS/ASCS associated with it */
    appl_ga_brr_setup();

    /* Initialize the own_addr_info */
    appl_ga_utils_set_default_values_own_addr_info();
    if (GA_SUCCESS == BT_hci_get_local_bd_addr(device.bd_addr))
    {
        /* Update own_addr_info for Connection */
        device.bd_type = BD_ADDR_TYPE_PUBLIC;
        appl_ga_utils_update_own_address_and_type(device, SET_HANDLE_CONNECTION);
        /* Update own_addr_info for Broadcast */
        appl_ga_utils_update_own_address_and_type(device, SET_HANDLE_BROADCAST);
    }

    retval = appl_ga_utils_enable_extended_advertise(GA_TRUE);
    if (GA_SUCCESS == retval)
    {
        is_adv_enabled = APPL_GA_ADV_UCS;
    }
    else
    {
        APPL_ERR("Extended Advertise Already initiated by Other Module !\n");
    }
#endif /* APPL_INIT_AUTOMATE_SERVER_SINK */

    return;
}

#ifdef APPL_CAS_SETMEMBER

void appl_ga_cs_sm_init(void)
{
    int input;
    UINT8 sirk[16U] = APPL_CAS_SM_SIRK;

    /* Set the SIRK Type and Value */
    local_cas_sm.member.sirk[0] = APPL_CAS_SM_SIRK_TYPE;
    GA_mem_copy(&local_cas_sm.member.sirk[1], &sirk[0U], CSIP_SIRK_LEN);

    /* Get the Set Size */
    CONSOLE_OUT("Enter the Coordinated Set Size: ");
    CONSOLE_IN("%d", &input);
    local_cas_sm.member.size = (UINT8)input;

    /* Get the Member Rank */
    CONSOLE_OUT("Enter the Coordinated Set Rank for this member: ");
    CONSOLE_IN("%d", &input);
    local_cas_sm.member.rank = (UINT8)input;

    /* Update the Advertising data with RSI AD Type */
    GA_cs_rsi_create(&local_cas_sm.member.sirk[1U]);

    return;
}

#endif /* APPL_CAS_SETMEMBER*/

void appl_ga_uc_client_init(void)
{
    GA_RESULT retval;

#ifdef APPL_UCC
    retval = GA_uc_client_init(appl_ga_cap_uc_client_callback);
    APPL_TRC("GA_uc_client_init. Retval - 0x%04X\n", retval);

    /* Initialize Unicast App Client Module */
    appl_ga_uc_init(APPL_GA_UNICAST_CLIENT);
#else /* APPL_UCC */
    APPL_TRC("APPL_UCC not defined!");
#endif /* APPL_UCC */

    return;
}

void appl_ga_uc_client_shutdown(void)
{
    GA_RESULT retval;

#ifdef APPL_UCC
    /* De-Initialize Unicast core */
    retval = GA_uc_client_shutdown();
    APPL_TRC("GA_uc_client_shutdown. Retval - 0x%04X\n", retval);
#else /* APPL_UCC */
    APPL_TRC("APPL_UCC not defined!");
#endif /* APPL_UCC */

    return;
}

void appl_ga_uc_server_init(void)
{
    GA_RESULT retval;

#ifdef APPL_UCS
    retval = GA_uc_server_init(appl_ga_cap_uc_server_callback);
    APPL_TRC("GA_uc_server_init. Retval - 0x%04X\n", retval);

    /* Initialize Unicast App Server Module */
    appl_ga_uc_init(APPL_GA_UNICAST_SERVER);
#else /* APPL_UCS */
    APPL_TRC("APPL_UCS not defined!");
#endif /* APPL_UCS */

    return;
}

void appl_ga_uc_server_shutdown(void)
{
    GA_RESULT retval;

#ifdef APPL_UCS
    /* De-Initialize Unicast core */
    retval = GA_uc_server_shutdown();
    APPL_TRC("GA_uc_server_shutdown. Retval - 0x%04X\n", retval);
#else /* APPL_UCS */
    APPL_TRC("APPL_UCS not defined!");
#endif /* APPL_UCS */

    return;
}

void appl_ga_bc_source_init(void)
{
    GA_RESULT retval;

#ifdef APPL_BAP_BROADCAST_SOURCE
    retval = GA_bc_source_init(appl_ga_cap_bc_src_callback);
    APPL_TRC("GA_bc_source_init. Retval - 0x%04X\n", retval);
#else /* APPL_BAP_BROADCAST_SOURCE */
    APPL_TRC("APPL_BAP_BROADCAST_SOURCE not defined!");
#endif /* APPL_BAP_BROADCAST_SOURCE */

    return;
}

void appl_ga_bc_source_shutdown(void)
{
    GA_RESULT retval;
#ifdef APPL_BAP_BROADCAST_SOURCE
    retval = GA_bc_source_shutdown();
    APPL_TRC("GA_bc_source_shutdown. Retval - 0x%04X\n", retval);
#else /* APPL_BAP_BROADCAST_SOURCE */
    APPL_TRC("APPL_BAP_BROADCAST_SOURCE not defined!");
#endif /* APPL_BAP_BROADCAST_SOURCE */

    return;
}

void appl_ga_bc_sink_init(void)
{
    GA_RESULT retval;

#ifdef APPL_BAP_BROADCAST_SINK
    retval = GA_bc_sink_init(appl_ga_cap_bc_sink_callback);
    APPL_TRC("GA_bc_sink_init. Retval - 0x%04X\n", retval);

    appl_ga_bc_init();
#else /* APPL_BAP_BROADCAST_SINK */
    APPL_TRC("APPL_BAP_BROADCAST_SINK not defined!");
#endif /* APPL_BAP_BROADCAST_SINK */

    return;
}

void appl_ga_bc_sink_shutdown(void)
{
    GA_RESULT retval;

#ifdef APPL_BAP_BROADCAST_SINK
    retval = GA_bc_sink_shutdown();
    APPL_TRC("GA_bc_source_shutdown. Retval - 0x%04X\n", retval);
#else /* APPL_BAP_BROADCAST_SINK */
    APPL_TRC("APPL_BAP_BROADCAST_SINK not defined!");
#endif /* APPL_BAP_BROADCAST_SINK */

    return;
}

#ifdef APPL_CAS_SETCOORDINATOR

void appl_ga_set_default_cas_scan_settings(void)
{
    APPL_DBG("[APPL][GA]: >> appl_ga_set_default_cas_scan_settings\n");

    /* Initialize default CAS scan parameters */
    appl_ga_cas_escan_params.duration = 0x00;
    appl_ga_cas_escan_params.filter_duplicates = 0x01;
    appl_ga_cas_escan_params.own_addr_type = 0x00;
    appl_ga_cas_escan_params.period = 0x00;
    appl_ga_cas_escan_params.scan_filter_policy = 0x00;
    appl_ga_cas_escan_params.scan_interval = 0x00A0;
    appl_ga_cas_escan_params.scan_phy = 0x01;
    appl_ga_cas_escan_params.scan_type = 0x00;
    appl_ga_cas_escan_params.scan_window = 0x00A0;

    APPL_DBG("[APPL][GA]: << appl_ga_set_default_cas_scan_settings\n");
    return;
}

GA_RESULT appl_ga_scan_for_cas(void)
{
    GA_RESULT retval;

    APPL_DBG("[APPL][GA]: >> appl_ga_scan_for_cas\n");

    /* TODO: Move it to init */
    /* Setting of default Scan parameters */

    retval = appl_ga_utils_enable_extended_scan(appl_ga_cas_escan_params);
    if (GA_SUCCESS == retval)
    {
        is_scan_enabled = APPL_GA_SCAN_FOR_CAS;
    }
    else
    {
        APPL_ERR("Failed to set Extended Scan Params Or Scan Already initiated"
                 " by Other Module !\n");
    }

    APPL_DBG("[APPL][GA]: << appl_ga_scan_for_cas\n");
    return retval;
}

GA_RESULT appl_ga_stop_scan_for_cas(void)
{
    GA_RESULT retval;

    retval = GA_FAILURE;

    APPL_DBG("[APPL][GA]: >> appl_ga_stop_scan_for_cas\n");

    retval = appl_ga_utils_disable_extended_scan(appl_ga_cas_escan_params);
    if (GA_SUCCESS == retval)
    {
        is_scan_enabled = APPL_GA_SCAN_INVALID;
    }
    else
    {
        APPL_ERR("Failed to Disable Extended Scan Or Scan Already Stopped"
            " by Other Module !\n");
    }

    APPL_DBG("[APPL][GA][CSIP]: << appl_ga_stop_scan_for_cas\n");
    return retval;
}

UINT8 appl_ga_is_dev_in_cas_db(UINT8 * rsi)
{
    UINT8 retval;
    UINT8 index;

    retval = MAX_SCAN_CAS_DEVICES;

    /* Validate if Dev already added */
    for (index = 0U; index < MAX_SCAN_CAS_DEVICES; index++)
    {
        /* Check if this RSI is the same as any of the CAS Device RSI */
        if (0U == GA_mem_cmp(&cas_devices[index].rsi[0], rsi, 6U))
        {
            /* Device is already present */
            retval = index;
            break;
        }
    }

    return retval;
}

GA_RESULT appl_ga_add_dev_into_cas_db(GA_ENDPOINT dev, UINT8* dev_rsi)
{
    GA_RESULT retval;
    UINT8 index;

    retval = GA_FAILURE;

    /* Validate if Dev already added */
    for (index = 0U; index < MAX_SCAN_CAS_DEVICES; index++)
    {
        if (!GA_BRR_DEV_ADDR_IS_NON_ZERO(&cas_devices[index].device.bd_addr[0U]))
        {
            GA_mem_copy
            (
                &cas_devices[index].rsi[0U],
                &dev_rsi[0U],
                6U
            );

            /* Copy the device */
            GA_COPY_BRR_DEVICE
            (
                &cas_devices[index].device,
                &dev
            );
            retval = GA_SUCCESS;
            break;
        }
    }

    return retval;
}

UINT8 appl_ga_utils_get_cas_dev_index(void)
{
    int choice;

    appl_ga_display_cas_db();

    CONSOLE_OUT("Enter the CAS device index: ");
    CONSOLE_IN("%d", &choice);
    /* Decrementing input by as cas_dev_index will start from 0 */
    choice -= 1;

    return ((UINT8)choice);
}

void appl_ga_display_cas_db(void)
{
    UINT8 index;

    for (index = 0U; index < MAX_SCAN_CAS_DEVICES; index++)
    {
        /* Display Devices */
        if (GA_BRR_DEV_ADDR_IS_NON_ZERO(&cas_devices[index].device.bd_addr[0U]))
        {
            appl_ga_utils_display_bdaddr_and_type(&cas_devices[index].device);
            APPL_TRC("\n");

            /* Display RSI */
            APPL_TRC("RSI: ");
            appl_dump_bytes(&cas_devices[index].rsi[0], 6U);

            APPL_TRC("Index: 0x%02X\n", (index + 1U));
        }
    }
}

void appl_ga_reset_cas_db(void)
{
    UINT8 index;

    for (index = 0U; index < MAX_SCAN_CAS_DEVICES; index++)
    {
        GA_mem_set(&cas_devices[index], 0x00U, sizeof(CAS_DEVICES));
    }
}

#endif /* APPL_CAS_SETCOORDINATOR */

GA_RESULT appl_ga_cas_hci_cb_handler
          (
              UINT8   event_code,
              UINT8* event_data,
              UINT8   event_datalen
          )
{
    UCHAR        i;
    UINT8        value_1;
    UCHAR        num_report;
    UINT8        marker;
    UINT8        sub_event;
    UINT8        adtype;
    UINT8        adlength;
    GA_ENDPOINT  dev;
    UINT8        dev_rsi[6U];
    UINT16       svc_uuid;
    UINT8        is_CAS_found;
    UINT8        is_RSI_found;
    UINT16       ea_index;

    ea_index = 0U;
    adtype = 0U;
    is_CAS_found = GA_FALSE;
    is_RSI_found = GA_FALSE;
    GA_INIT_ENDPOINT(&dev);

    /* Switch on the Event Code */
    switch (event_code)
    {
    case HCI_LE_META_EVENT:
        marker = 0U;
        /* Extract the subevent code */
        GA_UNPACK_LE_1_BYTE(&sub_event, &event_data[marker]);
        marker++;

        switch (sub_event)
        {
        case HCI_LE_EXTENDED_ADVERTISING_REPORT_SUBEVENT:
            if (APPL_GA_SCAN_FOR_CAS == is_scan_enabled)
            {
                /* Num_Reports Length: 1 Octet */
                num_report = event_data[marker];
                marker++;

                for (i = 0U; i < num_report; i++)
                {
                    /* Skip Event Type */
                    marker += 2U;

                    /* Address Type: 1 Octet */
                    value_1 = event_data[marker];
                    dev.bd_type = value_1;
                    marker++;

                    /* Address: 6 Octet */
                    for (i = 0U; i < GA_BD_ADDR_SIZE; i++)
                    {
                        dev.bd_addr[i] = event_data[marker];
                        marker++;
                    }

                    marker += 14U;

                    /* Data Length: 1 Octet */
                    value_1 = event_data[marker];
                    marker++;

                    while (0x00U < value_1)
                    {
                        /* Extract the Length from the event data */
                        GA_UNPACK_LE_1_BYTE(&adlength, &event_data[marker]);
                        marker++;
                        value_1 -= 1U;

                        /* TODO: Check Length for each param? */

                        if (0x000 != adlength)
                        {
                            /* Extract the Ad type from the event data */
                            GA_UNPACK_LE_1_BYTE(&adtype, &event_data[marker]);
                            marker++;
                            value_1 -= 1U;

                            /*
                             * To inform an unconnected Central that the
                             * Peripheral is connectable, the Peripheral
                             * shall transmit connectable extended advertising
                             * PDUs that contain the Service Data AD data type
                             * (see [3]), including additional service data
                             * defined in Table 8.1.
                             *
                             * CAP Spec, Version 1.0, Page: 44, Section 8.1.1(CAP Announcement)
                             */
                            if ((GA_ADTYPE_SERVICE_DATA == adtype) && (!is_CAS_found))
                            {
                                /* Extract the Value - Service UUID from the event data */
                                GA_UNPACK_LE_2_BYTE(&svc_uuid, &event_data[marker]);
                                marker += 2U;
                                value_1 -= 2U;

                                if (GA_SERVICE_CAS == svc_uuid)
                                {
                                    is_CAS_found = GA_TRUE;

                                    marker += (adlength - 3U);
                                    value_1 -= (adlength - 3U);
                                }
                                else
                                {
                                    /* Service UUID not interested, Validate further */
                                    svc_uuid = 0x0000U;
                                    marker += (adlength - 3U);
                                    value_1 -= (adlength - 3U);
                                }
                            }
                            else if ((GA_ADTYPE_RSI == adtype) && (!is_RSI_found))
                            {
                                /* Extract RSI, Add it into the DB */
                                BT_UNPACK_LE_N_BYTE
                                (
                                    &dev_rsi[0U],
                                    &event_data[marker],
                                    6U
                                );

                                is_RSI_found = GA_TRUE;
                                if (GA_TRUE == is_CAS_found)
                                {
                                    break;
                                }
                                else
                                {
                                    marker += (adlength - 1U);
                                    value_1 -= (adlength - 1U);
                                }
                            }
                            else
                            {
                                /* Interested AD Type - Not found yet! */
                                marker += (adlength - 1U);
                                value_1 -= (adlength - 1U);
                            }
                        }
                        else
                        {
                            /* AdLength is 0 */
                            break;
                        }
                    }
                }
                if ((GA_TRUE == is_CAS_found) && (GA_TRUE == is_RSI_found))
                {
#ifdef APPL_CAS_SETCOORDINATOR
                    if (MAX_SCAN_CAS_DEVICES == appl_ga_is_dev_in_cas_db(&dev_rsi[0U]))
                    {
                        /*
                         * Device to be added into DB,
                         * Add this if less than Max allowed.
                         */
                         /* It is a new Entry, Add RSI and Device to DB */
                        if (GA_SUCCESS !=
                            appl_ga_add_dev_into_cas_db(dev, &dev_rsi[0U]))
                        {
                            /* Device is beyond Max, Skip this! */
                            APPL_TRC("Skipping this device, Reached Max Size!\n");
                        }
                        else
                        {
                            /* Device is added into DB */
                            appl_ga_utils_hci_fetch_current_ea_index(&ea_index);

                            GA_FORMAT_DISPLAY();
                            APPL_TRC("Index: %d\n", ea_index);

                            /* Display the CAS Device */
                            appl_ga_utils_parse_and_display_ea_report_subevent(event_data, event_datalen);
                            GA_FORMAT_DISPLAY();
                        }
                    }
#endif /* APPL_CAS_SETCOORDINATOR */
                }
                else
                {
                    /* Device not Interested! */
#ifdef APPL_DISPLAY_ALL_EA_DEVICE
                    GA_FORMAT_DISPLAY();
                    appl_ga_utils_hci_fetch_current_ea_index(&ea_index);
                    APPL_TRC("Index: %d\n", ea_index);

                    /* Address Type: 1 Octet */
                    APPL_TRC("Address type: 0x%04X\n", dev.bd_type);

                    /* Address: 6 Octet */
                    APPL_TRC("Address: ");
                    for (i = 0U; i < GA_BD_ADDR_SIZE; i++)
                    {
                        APPL_TRC("0x%02X ", dev.bd_addr[i]);
                    }
                    APPL_TRC("\n");
                    APPL_TRC("Device not Interested!\n");

                    GA_FORMAT_DISPLAY();
#endif /* APPL_DISPLAY_ALL_EA_DEVICE */
                }
            }
            break;

        default:
            /* Do Nothing */
            break;
        }
        break;

    default:
        /* Do Nothing */
        break;
    }

    return GA_SUCCESS;
}

#endif /* BT_GAM */
