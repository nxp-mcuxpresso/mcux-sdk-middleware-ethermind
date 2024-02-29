/**
 *  \file appl_bass.c
 *
 *  \brief This file is a generic application example that demonstrates the
 *  usage of BASS - Client role interfaces exposed by BASS Client library
 *  and Server role interfaces exposed by BASS Server library.
 *  BASS CE discovers all the instances of BASS Server on a particular
 *  peer device. Based on the Service Instance and the Context provided by BASS
 *  Client module, the procedures of BASS on a particular instance
 *  can be carried out.
 *  By default during init, single instance of BASS Server BAS Rx State is
 *  registered. Multiple instances can be added. The Service and Char Handles
 *  are provided for further procedure usage.
 */

/*
*  Copyright (C) 2020. Mindtree Ltd.
*  All rights reserved.
*/

/* --------------------------------------------- Header File Inclusion */
#include "appl_bass.h"
#include "appl_utils.h"
#include "BT_hci_api.h"

#ifdef GA_BAP
/* --------------------------------------------- Global Definitions */

static UCHAR ga_bass_appl_menu[] =
"\n\
    0.  Exit\n\
    1.  Refresh\n\n\
    -- GA BASS Client Entity Menu Operations --\n\
    5.  GA BASS CE Init \n\
    6.  GA BASS CE Shutdown \n\
   \n\
   10. Setup BASS session with Peer Device \n\
   11. Read Broadcast Receive State \n\
   12. Write BAS CP - Remote Scan Stopped \n\
   13. Write BAS CP - Remote Scan Started \n\
   14. Write BAS CP - Add Source \n\
   15. Write BAS CP - Modify Source \n\
   16. Write BAS CP - Set Broadcast Code \n\
   17. Write BAS CP - Remove Source \n\
   18. Send Sync Info to BA SD. \n\
\n\
    -- GA BASS Server Entity Menu Operations --\n\
   20. GA BASS SE Init \n\
   21. GA BASS SE Shutdown \n\
   22. GA BASS SE - Add Broadcast Receive State Char Instance \n\
   \n\
   25. Notify Broadcast Receive State \n\
   26. Request Sync Info (PAST - Available). \n\
\n\
Your Option?\n\
";

/* --------------------------------------------- Data types /Structures */

/* --------------------------------------------- External Global Variables */

/* --------------------------------------------- Exported Global Variables */

/* --------------------------------------------- Static Global Variables */
DECL_STATIC GA_ENDPOINT appl_ga_bass_device;
DECL_STATIC BASS_HANDLE appl_ga_bass_ce_handle;

/* Server */
typedef struct _APPL_BASS_SE_RX_STATE_INST
{
    /*
     * This maintaining of status of Src Add is required since the DB wont know
     * how many Char instances are added.
     * Solution is during Char Add, Create a DB Entry by marking a variable.
     */
    UINT8 isSrcAdded;
    UINT8 db_index;
    BASS_BC_RX_STATE_INST inst;
}APPL_BASS_SE_RX_STATE_INST;

APPL_BASS_SE_RX_STATE_INST bass_se_rx_state_inst[BASS_SE_MAX_BC_RX_STATE_ENTITIES];
UINT8 bass_se_num_bc_rx_state_inst;

/*
 * This is used during CP Add handling. It is made global since it's updated
 * at couple of places.
 * Eg: Receive CP Add, Sync to PA, Sync to BIS
 */
GA_BASS_BC_RX_STATE  bass_bc_rx_state = { 0U };

/* Add Source Opcode */
UCHAR add_src_cp_past_avail[30U] =
{
    BASS_CP_OPCODE_ADD_SOURCE,
    0x00U, /* Src Addr Type */
    0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, /* Src Address */
    0x01U, /* Adv SID */
    0xEFU, 0xBEU, 0xADU, /* Broacast ID */
    BASS_PA_SYNC_SYNC_TO_PA_PAST_AVL, /* BASS_PA_SYNC_DO_NOT_SYNC_TO_PA(0x00), BASS_PA_SYNC_SYNC_TO_PA_PAST_AVL(0x01), BASS_PA_SYNC_SYNC_TO_PA_PAST_NOT_AVL(0x02) */
    0x10U, 0x00U, /* PA_Interval - 0x0010 */
    0x01U, /* Number_of_Subgroups */
    0x01U, 0x00U, 0x00U, 0x00, /* BIS_Sync[i]: 0x00000001 */
    0x09U, /* Metadata Len */
    0x03U, 0x02U, 0x04U, 0x00U, 0x04U, 0x04U, 0x65U, 0x6EU, 0x67U
    /*
     * Length: 0x03
     * Type: 0x02
     * Value: Streaming Audio Contexts:  - Media (0x0004)
     *
     * Length: 0x04
     * Type: 0x04
     * Value: Language: eng
     */
};

/* Add Source Opcode */
UCHAR add_src_cp_past_not_avail[30U] =
{
    BASS_CP_OPCODE_ADD_SOURCE,
    0x00U, /* Src Addr Type */
    0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, /* Src Address */
    0x01U, /* Adv SID */
    0xEFU, 0xBEU, 0xADU, /* Broacast ID */
    BASS_PA_SYNC_SYNC_TO_PA_PAST_NOT_AVL, /* BASS_PA_SYNC_DO_NOT_SYNC_TO_PA(0x00), BASS_PA_SYNC_SYNC_TO_PA_PAST_AVL(0x01), BASS_PA_SYNC_SYNC_TO_PA_PAST_NOT_AVL(0x02) */
    0x10U, 0x00U, /* PA_Interval - 0x0010 */
    0x01U, /* Number_of_Subgroups */
    0x01U, 0x00U, 0x00U, 0x00, /* BIS_Sync[i]: 0x00000001 */
    0x09U, /* Metadata Len */
    0x03U, 0x02U, 0x04U, 0x00U, 0x04U, 0x04U, 0x65U, 0x6EU, 0x67U
    /*
     * Length: 0x03
     * Type: 0x02
     * Value: Streaming Audio Contexts:  - Media (0x0004)
     *
     * Length: 0x04
     * Type: 0x04
     * Value: Language: eng
     */
};

/* Modify Source Opcode */
UCHAR modify_src_cp[20U] =
{
    BASS_CP_OPCODE_MODIFY_SOURCE,
    0x00U, /* source_id */
    BASS_PA_SYNC_SYNC_TO_PA_PAST_AVL, /* PA_Sync, BASS_PA_SYNC_DO_NOT_SYNC_TO_PA(0x00), BASS_PA_SYNC_SYNC_TO_PA_PAST_AVL(0x01), BASS_PA_SYNC_SYNC_TO_PA_PAST_NOT_AVL(0x02)*/
    0x10U, 0x00U, /* PA_Interval - 0x0010 */
    0x01U, /* Number_of_Subgroups */
    0x01U, 0x00U, 0x00U, 0x00, /* BIS_Sync[i]: 0x00000001 */
    0x09U, /* Metadata Len */
    0x03U, 0x02U, 0x02U, 0x00U, 0x04U, 0x04U, 0x65U, 0x6EU, 0x67U
    /*
     * Length: 0x03
     * Type: 0x02
     * Value: Streaming Audio Contexts:  - Conversational (0x0002)
     *
     * Length: 0x04
     * Type: 0x04
     * Value: Language: eng
     */
};

/* Remove Source Opcode */
UCHAR remove_src_cp[2U] =
{
    BASS_CP_OPCODE_REMOVE_SOURCE,
    0x00U /* source_id */
};

/* Set BC Code Opcode */
UCHAR set_bc_code_src_cp[18U] =
{
    BASS_CP_OPCODE_SET_BC_CODE,
    0x00U, /* source_id */
    0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U, 0x0AU, 0x0BU, 0x0CU, 0x0DU, 0x0EU, 0x0FU /* BC Code */
};

UCHAR bc_rx_state_inst_post_add_src[29U] =
{
    0x00U, /* source_id */
    0x00U, /* Src Addr Type */
    0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, /* Src Address */
    0x01U, /* Adv SID */
    0xEFU, 0xBEU, 0xADU, /* Broacast ID */
    BASS_PA_SYNC_STATE_SYNC_INFO_REQUEST,
    BASS_BIG_ENCRYPTION_NOT_ENCRYPTED,
    0x01U, /* Number_of_Subgroups */
    0x00U, 0x00U, 0x00U, 0x00U, /* BIS_Sync_state[i]: 0x00000000 */
    0x09U, /* Metadata Len */
    0x03U, 0x02U, 0x04U, 0x00U, 0x04U, 0x04U, 0x65U, 0x6EU, 0x67U
    /*
     * Length: 0x03
     * Type: 0x02
     * Value: Streaming Audio Contexts:  - Media (0x0004)
     *
     * Length: 0x04
     * Type: 0x04
     * Value: Language: eng
     */
};

UCHAR bc_rx_state_inst_post_src_synced[29U] =
{
    0x00U, /* source_id */
    0x00U, /* Src Addr Type */
    0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, /* Src Address */
    0x01U, /* Adv SID */
    0xEFU, 0xBEU, 0xADU, /* Broacast ID */
    BASS_PA_SYNC_STATE_SYNCHRONIZED_TO_PA,
    BASS_BIG_ENCRYPTION_NOT_ENCRYPTED,
    0x01U, /* Number_of_Subgroups */
    0x00U, 0x00U, 0x00U, 0x00U, /* BIS_Sync_state[i]: 0x00000000 */
    0x09U, /* Metadata Len */
    0x03U, 0x02U, 0x04U, 0x00U, 0x04U, 0x04U, 0x65U, 0x6EU, 0x67U
    /*
     * Length: 0x03
     * Type: 0x02
     * Value: Streaming Audio Contexts:  - Media (0x0004)
     *
     * Length: 0x04
     * Type: 0x04
     * Value: Language: eng
     */
};

UCHAR bc_rx_state_inst_post_src_modify[29U] =
{
    0x00U, /* source_id */
    0x00U, /* Src Addr Type */
    0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, /* Src Address */
    0x01U, /* Adv SID */
    0xEFU, 0xBEU, 0xADU, /* Broacast ID */
    BASS_PA_SYNC_STATE_SYNCHRONIZED_TO_PA,
    BASS_BIG_ENCRYPTION_NOT_ENCRYPTED,
    0x01U, /* Number_of_Subgroups */
    0x00U, 0x00U, 0x00U, 0x00U, /* BIS_Sync_state[i]: 0x00000000 */
    0x09U, /* Metadata Len */
    0x03U, 0x02U, 0x02U, 0x00U, 0x04U, 0x04U, 0x65U, 0x6EU, 0x67U
    /*
     * Length: 0x03
     * Type: 0x02
     * Value: Streaming Audio Contexts:  - Conversational (0x0002)
     *
     * Length: 0x04
     * Type: 0x04
     * Value: Language: eng
     */
};

UCHAR bc_rx_state_inst_post_src_rx_bc_code[29U] =
{
    0x00U, /* source_id */
    0x00U, /* Src Addr Type */
    0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, /* Src Address */
    0x01U, /* Adv SID */
    0xEFU, 0xBEU, 0xADU, /* Broacast ID */
    BASS_PA_SYNC_STATE_SYNCHRONIZED_TO_PA,
    BASS_BIG_ENCRYPTION_DECRYPTING,
    0x01U, /* Number_of_Subgroups */
    0x00U, 0x00U, 0x00U, 0x00U, /* BIS_Sync_state[i]: 0x00000000 */
    0x09U, /* Metadata Len */
    0x03U, 0x02U, 0x02U, 0x00U, 0x04U, 0x04U, 0x65U, 0x6EU, 0x67U
    /*
     * Length: 0x03
     * Type: 0x02
     * Value: Streaming Audio Contexts:  - Conversational (0x0002)
     *
     * Length: 0x04
     * Type: 0x04
     * Value: Language: eng
     */
};

GA_RESULT appl_ga_bass_bc_sd_req_sync_info_past(void);
GA_RESULT appl_ga_bass_bc_ba_send_pa_sync_info(void);
void appl_ga_bass_bc_sd_parse_and_display_add_src_data
     (
         /* IN */    GA_BASS_BAS_CP_ADD_SRC* add_src,
         /* IN */    UINT8* bas_cp,
         /* INOUT */ UINT32* bis_sync,
         /* INOUT */ UINT8* metadata_len,
         /* INOUT */ UINT8* metadata
     );
void appl_ga_bass_bc_sd_parse_and_display_modify_src_data
     (
         /* IN */    UINT8                     * bas_cp,
         /* INOUT */ GA_BASS_BAS_CP_MODIFY_SRC * modify_src,
         /* INOUT */ UINT32                    * bis_sync,
         /* INOUT */ UINT8                     * metadata_len,
         /* INOUT */ UINT8                     * metadata
     );

void appl_ga_bass_bc_sd_parse_and_display_addr_type(/* IN */ UINT8 addr_type);
void appl_ga_bass_bc_sd_parse_and_display_PA_Sync_State
     (
        /* IN */ UINT8 pa_sync_state
     );
void appl_ga_bass_bc_sd_parse_and_display_BIG_encryption
     (
        /* IN */ UINT8 big_encryption
     );
void appl_ga_bass_bc_sd_parse_and_display_PA_Sync(/* IN */ UINT8 pa_sync);
void appl_ga_bass_utils_bap_parse_and_display_metadata_ltv
     (
         /* IN */    UCHAR  * ltvarray,
         /* IN */    UINT8    ltvarray_len,
         /* INOUT */ UINT16 * pref_audio_ctx,
         /* INOUT */ UINT16 * streaming_audio_ctx
     );
/* --------------------------------------------- Functions */
void main_bass_menu_operations(void)
{
    GA_RESULT retval;
    UCHAR addr[GA_BD_ADDR_SIZE];
    int     choice, input;

    /* Client */
    UCHAR i;
    UINT8 instance;
    i = 0U;

    GA_BASS_CE_WRITE_REQ req;
    GA_BASS_BAS_CP_OP bass_bas_cp = { 0U };
    BASS_BC_RX_STATE_INST bass_ce_bc_rx_state_inst;
    GA_BASS_BC_RX_STATE rx_state = { 0U };

    /* Initialize */
    bass_bas_cp.param = NULL;
    bass_bas_cp.param_len = 0U;
    instance = 0U;
    retval = GA_FAILURE;

    while(1)
    {
        CONSOLE_OUT("%s", ga_bass_appl_menu);
        CONSOLE_IN("%d", &choice);

        switch (choice)
        {
        case 0:
            return;

        case 1:
            break;

        case 5:
            APPL_TRC("GA_bass_ce_init...\n");
            retval = GA_bass_ce_init(appl_bass_ce_cb);
            APPL_TRC("Retval - 0x%04X\n", retval);
            break;

        case 6:
            APPL_TRC("GA_bass_ce_shutdown...\n");
            retval = GA_bass_ce_shutdown();
            APPL_TRC("Retval - 0x%04X\n", retval);
            break;

        case 10:
            CONSOLE_OUT("Enter endpoint address: ");
            appl_get_bd_addr(appl_ga_bass_device.bd_addr);
            CONSOLE_OUT("Enter endpoint type: ");
            CONSOLE_IN("%d", &input);
            appl_ga_bass_device.bd_type = (UINT8)input;

            APPL_TRC("GA_bass_ce_setup_context: \n");
            retval = GA_bass_ce_setup_context
                     (
                         &appl_ga_bass_device,
                         &appl_ga_bass_ce_handle
                     );

            APPL_TRC("Retval - 0x%04X\n", retval);
            APPL_TRC("BASS Remote Handle: 0x%04X\n", appl_ga_bass_ce_handle);
            break;

        case 11:
            CONSOLE_OUT("Enter BASS Handle: ");
            CONSOLE_IN("%d", &input);
            appl_ga_bass_ce_handle = (UCHAR)input;

            CONSOLE_OUT("Enter BASS Char Broadcast Rx State Handle: ");
            CONSOLE_IN("%d", &input);
            bass_ce_bc_rx_state_inst = (UCHAR)input;

            APPL_TRC("GA_bass_ce_read_bc_rx_state: \n");
            retval = GA_bass_ce_read_bc_rx_state
                     (
                         appl_ga_bass_ce_handle,
                         bass_ce_bc_rx_state_inst
                     );
            APPL_TRC("Retval - 0x%04X\n", retval);
            break;

        case 12:
            CONSOLE_OUT("Enter BASS Handle: ");
            CONSOLE_IN("%d", &input);
            appl_ga_bass_ce_handle = (UCHAR)input;

            bass_bas_cp.opcode = BASS_CP_OPCODE_REMOTE_SCAN_STOPPED;
            bass_bas_cp.param = NULL;
            bass_bas_cp.param_len = 0U;

            req.req_data.val = (UCHAR*)&bass_bas_cp;
            /* Adding 1U to req.req_data.len for Opcode Byte */
            req.req_data.len = 1U + bass_bas_cp.param_len;

            APPL_TRC("Enter the Write Type:  [Write Req: 0], [WWR: 1]\n");
            CONSOLE_IN("%d", &input);
            req.write_type = (UINT8)input;

            APPL_TRC("GA_bass_ce_inform_remote_scan_status: \n");
            retval = GA_bass_ce_inform_remote_scan_status
                     (
                         appl_ga_bass_ce_handle,
                         &req
                     );
            APPL_TRC("Retval - 0x%04X\n", retval);
            break;

        case 13:
            CONSOLE_OUT("Enter BASS Handle: ");
            CONSOLE_IN("%d", &input);
            appl_ga_bass_ce_handle = (UCHAR)input;

            bass_bas_cp.opcode = BASS_CP_OPCODE_REMOTE_SCAN_STARTED;
            bass_bas_cp.param = NULL;
            bass_bas_cp.param_len = 0U;

            req.req_data.val = (UCHAR*)&bass_bas_cp;
            /* Adding 1U to req.req_data.len for Opcode Byte */
            req.req_data.len = 1U + bass_bas_cp.param_len;

            APPL_TRC("Enter the Write Type:  [Write Req: 0], [WWR: 1]\n");
            CONSOLE_IN("%d", &input);
            req.write_type = (UINT8)input;

            APPL_TRC("GA_bass_ce_inform_remote_scan_status: \n");
            retval = GA_bass_ce_inform_remote_scan_status
                     (
                         appl_ga_bass_ce_handle,
                         &req
                     );
            APPL_TRC("Retval - 0x%04X\n", retval);
            break;

        case 14:
            CONSOLE_OUT("Enter BASS Handle: ");
            CONSOLE_IN("%d", &input);
            appl_ga_bass_ce_handle = (UCHAR)input;

            CONSOLE_OUT("Enter PAST Status:\n");
            CONSOLE_OUT("1. PAST Available\n");
            CONSOLE_OUT("2. PAST Not Available\n");
            CONSOLE_IN("%d", &input);
            i = (UCHAR)input;

            /* Take input for Address and Adv_SID, Refer GA_BC_SOURCE_ANNOUNCEMENT_IND */
            CONSOLE_OUT("Enter the Src Address Type\n");
            CONSOLE_OUT("1. Public Address\n2. Random Address\n");
            CONSOLE_IN("%d", &choice);

            CONSOLE_OUT("Enter the BD Address of BC Src: ");
            appl_get_bd_addr(addr);

            if (1 == i)
            {
                /* Address_Type */
                if (1 == (UINT8)choice)
                {
                    add_src_cp_past_avail[1U] = BASS_ADDR_TYPE_PUBLIC;
                }
                else
                {
                    add_src_cp_past_avail[1U] = BASS_ADDR_TYPE_RANDOM;
                }

                /* Address */
                GA_mem_copy
                (
                    &add_src_cp_past_avail[2U],
                    &addr[0U],
                    GA_BD_ADDR_SIZE
                );

                CONSOLE_OUT("Enter the Src Adv_SID\n");
                CONSOLE_IN("%d", &choice);

                /* Adv_SID */
                add_src_cp_past_avail[8U] = (UINT8)choice;

                req.req_data.val = &add_src_cp_past_avail[0U];
                req.req_data.len = 30U;
            }
            else if (2 == i)
            {
                /* Address_Type */
                if (1 == (UINT8)choice)
                {
                    add_src_cp_past_not_avail[1U] = BASS_ADDR_TYPE_PUBLIC;
                }
                else
                {
                    add_src_cp_past_not_avail[1U] = BASS_ADDR_TYPE_RANDOM;
                }

                /* Address */
                GA_mem_copy
                (
                    &add_src_cp_past_not_avail[2U],
                    &addr[0U],
                    GA_BD_ADDR_SIZE
                );

                CONSOLE_OUT("Enter the Src Adv_SID\n");
                CONSOLE_IN("%d", &choice);

                /* Adv_SID */
                add_src_cp_past_not_avail[8U] = (UINT8)choice;

                req.req_data.val = &add_src_cp_past_not_avail[0U];
                req.req_data.len = 30U;
            }

            APPL_TRC("Enter the Write Type:  [Write Req: 0], [WWR: 1]\n");
            CONSOLE_IN("%d", &input);
            req.write_type = (UINT8)input;

            APPL_TRC("GA_bass_ce_request_to_add_source: \n");
            retval = GA_bass_ce_request_to_add_source
                     (
                         appl_ga_bass_ce_handle,
                         &req
                     );
            APPL_TRC("Retval - 0x%04X\n", retval);
            break;

        case 15:
            CONSOLE_OUT("Enter BASS Handle: ");
            CONSOLE_IN("%d", &input);
            appl_ga_bass_ce_handle = (UCHAR)input;

            req.req_data.val = (UCHAR *)&modify_src_cp[0U];
            req.req_data.len = 20U;

            APPL_TRC("Enter the Write Type:  [Write Req: 0], [WWR: 1]\n");
            CONSOLE_IN("%d", &input);
            req.write_type = (UINT8)input;

            APPL_TRC("GA_bass_ce_request_to_modify_source: \n");
            retval = GA_bass_ce_request_to_modify_source
                     (
                         appl_ga_bass_ce_handle,
                         &req
                     );
            APPL_TRC("Retval - 0x%04X\n", retval);
            break;

        case 16:
            CONSOLE_OUT("Enter BASS Handle: ");
            CONSOLE_IN("%d", &input);
            appl_ga_bass_ce_handle = (UCHAR)input;

            req.req_data.val = (UCHAR *)&set_bc_code_src_cp[0U];
            req.req_data.len = 18U;

            APPL_TRC("Enter the Write Type:  [Write Req: 0], [WWR: 1]\n");
            CONSOLE_IN("%d", &input);
            req.write_type = (UINT8)input;

            APPL_TRC("GA_bass_ce_set_bc_code: \n");
            retval = GA_bass_ce_set_bc_code
                     (
                         appl_ga_bass_ce_handle,
                         &req
                     );
            APPL_TRC("Retval - 0x%04X\n", retval);
            break;

        case 17:
            CONSOLE_OUT("Enter BASS Handle: ");
            CONSOLE_IN("%d", &input);
            appl_ga_bass_ce_handle = (UCHAR)input;

            req.req_data.val = (UCHAR *)&remove_src_cp[0U];
            req.req_data.len = 2U;

            APPL_TRC("Enter the Write Type:  [Write Req: 0], [WWR: 1]\n");
            CONSOLE_IN("%d", &input);
            req.write_type = (UINT8)input;

            APPL_TRC("GA_bass_ce_request_to_remove_source: \n");
            retval = GA_bass_ce_request_to_remove_source
                     (
                         appl_ga_bass_ce_handle,
                         &req
                     );
            APPL_TRC("Retval - 0x%04X\n", retval);
            break;

        case 18:
            APPL_TRC("appl_ga_bass_bc_ba_send_pa_sync_info...\n");
            retval = appl_ga_bass_bc_ba_send_pa_sync_info();
            APPL_TRC("Retval - 0x%04X\n", retval);
            break;

        case 20:
            APPL_TRC("GA_bass_se_init...\n");
            retval = GA_bass_se_init(appl_bass_se_cb);
            APPL_TRC("Retval - 0x%04X\n", retval);
            break;

        case 21:
            APPL_TRC("GA_bass_se_shutdown...\n");
            retval = GA_bass_se_shutdown();
            APPL_TRC("Retval - 0x%04X\n", retval);
            break;

        case 22:
            APPL_TRC("GA_bass_se_add_bc_rx_state_inst...\n");
            retval = GA_bass_se_add_bc_rx_state_inst
                     (
                         &bass_se_rx_state_inst[bass_se_num_bc_rx_state_inst].inst
                     );
            APPL_TRC("Retval - 0x%04X\n", retval);
            if (GA_SUCCESS == retval)
            {
                APPL_TRC("GA_bass_se_add_bc_rx_state_inst Instance: %d \n",
                    bass_se_rx_state_inst[bass_se_num_bc_rx_state_inst].inst);
                bass_se_num_bc_rx_state_inst++;

                bass_se_rx_state_inst[bass_se_num_bc_rx_state_inst].isSrcAdded
                    = GA_FALSE;
            }
            break;

        case 25:
            CONSOLE_OUT("Enter endpoint address: ");
            appl_get_bd_addr(appl_ga_bass_device.bd_addr);
            CONSOLE_OUT("Enter endpoint type: ");
            CONSOLE_IN("%d", &input);
            appl_ga_bass_device.bd_type = (UINT8)input;

            CONSOLE_OUT("Enter BASS Broadcast Rx State Instance: ");
            CONSOLE_IN("%d", &input);
            instance = (UCHAR)input;

            CONSOLE_OUT("Enter the Notification for\n");
            CONSOLE_OUT("1. Sync Info Request\n");
            CONSOLE_OUT("2. Post Src Synced\n");
            CONSOLE_OUT("3. Post Set BC Code\n");
            CONSOLE_OUT("4. Post Modify Src\n");
            CONSOLE_OUT("5. Post Remove Src\n");
            CONSOLE_IN("%d", &input);
            i = (UINT8)input;

            if (0x01 == i)
            {
                GA_mem_copy
                (
                    &rx_state.info,
                    &bc_rx_state_inst_post_add_src[0U],
                    29U
                );
                rx_state.info_len = 29U;
            }
            else if (0x02 == i)
            {
                GA_mem_copy
                (
                    &rx_state.info,
                    &bc_rx_state_inst_post_src_synced[0U],
                    29U
                );
                rx_state.info_len = 29U;
            }
            else if (0x03 == i)
            {
                GA_mem_copy
                (
                    &rx_state.info,
                    &bc_rx_state_inst_post_src_rx_bc_code[0U],
                    29U
                );
                rx_state.info_len = 29U;
            }
            else if (0x04 == i)
            {
                GA_mem_copy
                (
                    &rx_state.info,
                    &bc_rx_state_inst_post_src_modify[0U],
                    29U
                );
                rx_state.info_len = 29U;
            }
            else if (0x05 == i)
            {
                GA_mem_set
                (
                    &rx_state.info,
                    0U,
                    sizeof(rx_state.info)
                );
                rx_state.info_len = 0U;
            }

            APPL_TRC("GA_bass_se_notify_bc_rx_state...\n");
            retval = GA_bass_se_notify_bc_rx_state
                     (
                         &appl_ga_bass_device,
                         instance,
                         (void*)&rx_state.info,
                         (UINT8)rx_state.info_len
                     );
            break;

        case 26:
            appl_ga_bass_bc_sd_req_sync_info_past();
            break;

        default:
            APPL_TRC("Invalid Choice\n");
            break;
        }
    }
}

GA_RESULT appl_bass_ce_cb
          (
              /* IN */ GA_ENDPOINT    * device,
              /* IN */ BASS_CE_EVT_ID   evt_id,
              /* IN */ UINT16           evt_status,
              /* IN */ BASS_EVT       * evt_data
          )
{
    GA_RESULT retval;
    UINT8 index;
    UINT8* rx_state_src_info_ptr;

    retval = GA_SUCCESS;
    index = 0U;
    rx_state_src_info_ptr = NULL;

    APPL_TRC("[GA][BASS]: >> appl_bass_ce_cb\n");

    if (NULL != device)
    {
        APPL_TRC(
            "\n[GA][BASS]: Event 0x%02X From Peer " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER " Type : 0x%02X\n",
            evt_id, BT_DEVICE_ADDR_ONLY_PRINT_STR(device->bd_addr), device->bd_type);

        APPL_TRC("Event Status: 0x%04x\n", evt_status);
        APPL_TRC("[GA][BASS]: BASS Handle: 0x%02x\n", evt_data->bass_handle);

        switch (evt_id)
        {

        case BASS_CE_SETUP_CNF:
            if (GA_SUCCESS == evt_status)
            {
                APPL_TRC("[GA][BASS]: Context Setup Complete\n");
                APPL_TRC
                (
                    "[GA][BASS]: Broadcast Receive State Instance: 0x%02X\n",
                    evt_data->rx_state_inst
                );

                UINT8* id;

                id = (UINT8 *)evt_data->data;

                if (evt_data->len != 0U)
                {
                    for (index = 0U; index < evt_data->len; index++)
                    {
                        APPL_TRC("0x%02X ", *id);
                        id++;
                    }
                    APPL_TRC("\n");
                }
            }
            else
            {
                APPL_ERR("[GA][BASS]: Context Setup Complete Failed !\n");
            }
            break;

        case BASS_CE_BC_RX_STATE_IND:
            if (GA_SUCCESS == evt_status)
            {
                APPL_TRC("[GA][BASS]: Notification received on Broadcast Receive State\n");
                APPL_TRC("[GA][BASS]: BASS Broadcast Receive State Handle: 0x%02x\n",
                    evt_data->bass_handle);
                APPL_TRC("[GA][BASS]: BASS Broadcast Receive State Instance: 0x%02x\n",
                    evt_data->rx_state_inst);

                if ((evt_data->len != 0U) && (NULL != evt_data->data))
                {
                    rx_state_src_info_ptr = (UINT8 *)evt_data->data;
                    appl_bass_ce_parse_and_handle_bc_rx_state
                    (
                        rx_state_src_info_ptr,
                        evt_data->len
                    );
                }
            }
            break;

        case BASS_CE_READ_BC_RX_STATE_CNF:
            if (GA_SUCCESS == evt_status)
            {
                APPL_TRC("[GA][BASS]: Read Rsp received on Broadcast Receive State\n");
                APPL_TRC("[GA][BASS]: BASS Broadcast Receive State Handle: 0x%02x\n",
                    evt_data->bass_handle);
                APPL_TRC("[GA][BASS]: BASS Broadcast Receive State Instance: 0x%02x\n",
                    evt_data->rx_state_inst);

                if ((evt_data->len != 0U) && (NULL != evt_data->data))
                {
                    rx_state_src_info_ptr = (UINT8*)evt_data->data;
                    appl_bass_ce_parse_and_handle_bc_rx_state
                    (
                        rx_state_src_info_ptr,
                        evt_data->len
                    );
                }
            }
            break;

        case BASS_CE_BAS_CP_CNF:
            if (GA_SUCCESS == evt_status)
            {
                APPL_TRC("[GA][BASS]: Write Rsp received on BAS CP\n");
            }
            break;

        default:
            APPL_ERR("[GA][BASS]: Unknown Event ID !\n");
            break;
        }

        APPL_TRC("\n[GA][BASS]: << appl_bass_ce_cb\n\n");
    }
    else
    {
        retval = GA_FAILURE;
    }

    return retval;
}

GA_RESULT appl_bass_se_cb
          (
              /* IN */ GA_ENDPOINT            * device,
              /* IN */ GA_BASS_SE_RSP_CONTEXT * ctx,
              /* IN */ BASS_SE_EVT_ID           evt_id,
              /* IN */ UINT16                   evt_status,
              /* IN */ BASS_EVT               * evt_data
          )
{
    GA_RESULT retval;
    UINT8 send_rsp;
    void* rsp;
    UINT16 rsp_len;
    UINT8 i;

    send_rsp = GA_FALSE;
    retval = GA_SUCCESS;
    rsp = NULL;
    i = 0U;
    rsp_len = 0U;

    APPL_TRC("[GA][BASS]: >> appl_bass_se_cb\n");

    if ((NULL != device) && (NULL != evt_data))
    {
        APPL_TRC(
            "\n[GA][BASS]: Event 0x%02X From Peer " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER " Type : 0x%02X\n",
            evt_id, BT_DEVICE_ADDR_ONLY_PRINT_STR(device->bd_addr), device->bd_type);

        APPL_TRC("[GA][BASS]: Event Status: 0x%04x\n", evt_status);

        send_rsp = GA_TRUE;

        switch (evt_id)
        {
        case BASS_SE_READ_BC_RX_STATE_IND:
            APPL_TRC("[GA][BASS]: BASS_SE_READ_BC_RX_STATE_IND\n");
            APPL_TRC("[GA][BASS]: BASS Broadcast Receive State Instance: 0x%02x\n",
                evt_data->rx_state_inst);

            for (i = 0U; i < GA_CONFIG_LIMITS(BASS_SE_MAX_BC_RX_STATE_ENTITIES); i++)
            {
                if (bass_se_rx_state_inst[i].inst == evt_data->rx_state_inst)
                {
                    retval = GA_SUCCESS;
                    break;
                }
            }
            if ((GA_SUCCESS != retval) || (BASS_SE_MAX_BC_RX_STATE_ENTITIES == i))
            {
                APPL_ERR(" Unknown Instance!\n");
            }
            break;

        case BASS_SE_WRITE_BAS_CP_IND:
            APPL_TRC("BASS_SE_WRITE_BAS_CP_IND\n");
            if ((NULL != ctx) && (!ctx->to_rsp))
            {
                send_rsp = GA_FALSE;
            }
            /* Parse the BAS CP */
            if ((NULL != evt_data->data) && (0U != evt_data->len))
            {
                retval = appl_bass_se_parse_and_handle_bas_cp
                         (
                             evt_data->data,
                             evt_data->len
                         );

                /* As per BASS Spec, there is no response sent for BAS CP Proc */
            }
            else
            {
                retval = GA_FAILURE;
                APPL_ERR("[GA][BASS]: BAS CP Param is NULL !\n");
            }
            break;

        default:
            APPL_ERR("[GA][BASS]: Unknown Event ID !\n");
            send_rsp = GA_FALSE;
            break;
        }

        APPL_TRC("\n[GA][BASS]: << appl_bass_se_cb\n\n");
    }
    else
    {
        retval = GA_FAILURE;
        APPL_ERR("[GA][BASS]: device is NULL !\n");
    }

    if (GA_TRUE == send_rsp)
    {
        retval = GA_bass_se_send_rsp
                 (
                     device,
                     ctx,
                     evt_id,
                     retval,
                     rsp,
                     rsp_len
                 );
    }

    return retval;
}

GA_RESULT appl_bass_se_parse_and_handle_bas_cp(UINT8* bas_cp, UINT16 len)
{
    GA_RESULT  retval;

    UINT8  opcode;
    UCHAR  i;
    UINT8  marker;

    GA_BASS_BAS_CP_ADD_SRC  add_src;
    GA_BASS_BAS_CP_MODIFY_SRC  modify_src;
    UINT32 bis_sync[APPL_BASS_MAX_NUM_OF_SUB_GROUPS];
    UINT8  metadata_len[APPL_BASS_MAX_NUM_OF_SUB_GROUPS];
    UINT8  metadata[APPL_BASS_MAX_NUM_OF_SUB_GROUPS * GA_METADATA_LEN];

    GA_BASS_BAS_CP_REMOVE_SRC rem_src;
    GA_BASS_BAS_CP_SET_BC_CODE set_bc_code;

    /* Initialize */
    retval = GA_SUCCESS;
    marker = 0U;

    /* Assign the Opcode and increment the Marker by 1U */
    opcode = bas_cp[marker];
    marker++;
    /* Excluding the Length 1B of the Opcode */
    len -= 1U;
    APPL_TRC("[GA][BASS]: appl_bass_se_parse_bas_cp()\n");

    switch (opcode)
    {
    case BASS_CP_OPCODE_REMOTE_SCAN_STOPPED:
        if (0U != len)
        {
            APPL_ERR
            (
                "[GA][BASS]: BASS_CP_OPCODE_REMOTE_SCAN_STOPPED Invalid Param or Length !\n"
            );
            retval = GA_FAILURE;
        }
        break;

    case BASS_CP_OPCODE_REMOTE_SCAN_STARTED:
        if (0U != len)
        {
            APPL_ERR("[GA][BASS]: BASS_CP_OPCODE_REMOTE_SCAN_STARTED Invalid Param or Length !\n");
            retval = GA_FAILURE;
        }
        break;

    case BASS_CP_OPCODE_ADD_SOURCE:
        if (15U > len)
        {
            APPL_ERR("[GA][BASS]: BASS_CP_OPCODE_ADD_SOURCE Invalid Param or Length !\n");
            retval = GA_FAILURE;
        }
        else
        {
            appl_ga_bass_bc_sd_parse_and_display_add_src_data
            (
                &add_src,
                &bas_cp[marker],
                bis_sync,
                metadata_len,
                metadata
            );
        }
        break;

    case BASS_CP_OPCODE_MODIFY_SOURCE:
        if (5U > len)
        {
            APPL_ERR
            (
                "[GA][BASS]: BASS_CP_OPCODE_MODIFY_SOURCE Invalid Param or Length !\n"
            );
            retval = GA_FAILURE;
        }
        else
        {
            appl_ga_bass_bc_sd_parse_and_display_modify_src_data
            (
                &bas_cp[marker],
                &modify_src,
                bis_sync,
                metadata_len,
                metadata
            );
        }
        break;

    case BASS_CP_OPCODE_SET_BC_CODE:
        if (17U != len)
        {
            APPL_ERR
            (
                "[GA][BASS]: BASS_CP_OPCODE_SET_BC_CODE Invalid Param or Length !\n"
            );
            retval = GA_FAILURE;
        }
        else
        {
            /*
             * Fetch the appl_ga_bass_se_bc_rx_state based on the Source_ID
             * provided by the client here and remove the complete entry.
             */
            set_bc_code.src_id = bas_cp[marker];
            /* Increment marker by 1B for src_id */
            marker++;
            APPL_TRC("src_id: 0x%02X\n", set_bc_code.src_id);

            BT_UNPACK_LE_16_BYTE
            (
                &set_bc_code.br_code[0U],
                &bas_cp[marker]
            );
            marker+= 16U;
            APPL_TRC("br_code: ");
            for (i = 0U; i < 16U; i++)
            {
                APPL_TRC("0x%02X ", set_bc_code.br_code[i]);
            }
            APPL_TRC("\n");
        }
        break;

    case BASS_CP_OPCODE_REMOVE_SOURCE:
        if (1U != len)
        {
            APPL_ERR
            (
                "[GA][BASS]: BASS_CP_OPCODE_REMOVE_SOURCE Invalid Param or Length !\n"
            );
            retval = GA_FAILURE;
        }
        else
        {
            /*
             * Fetch the appl_ga_bass_se_bc_rx_state based on the Source_ID
             * provided by the client here and remove the complete entry.
             */
            rem_src.src_id = bas_cp[1U];
            marker++;
            APPL_TRC("src_id: 0x%02X\n", rem_src.src_id);
        }
        break;

    default:
        APPL_ERR("[GA][BASS]: Unknown Opcode %d !\n", opcode);
        retval = BASS_APPL_ERR_CODE_OPCODE_NOT_SUPP;
        break;
    }

    return retval;
}
GA_RESULT appl_bass_se_parse_and_display_bc_rx_state(GA_BASS_BC_RX_STATE br_rx_state)
{
    GA_RESULT  retval;
    UCHAR      i;
    UCHAR      j;
    UINT8      prev_metadata_len;

    prev_metadata_len = 0U;
    retval = GA_FAILURE;

    if (0U != br_rx_state.info_len)
    {
        APPL_TRC("id: 0x%02X\n", br_rx_state.info.id);
        APPL_TRC("addr_type: 0x%02X\n", br_rx_state.info.addr_type);
        APPL_TRC
        (
            "addr: %02X %02X %02X %02X %02X %02X\n",
            br_rx_state.info.addr[0U],
            br_rx_state.info.addr[1U],
            br_rx_state.info.addr[2U],
            br_rx_state.info.addr[3U],
            br_rx_state.info.addr[4U],
            br_rx_state.info.addr[5U]
        );
        APPL_TRC("adv_sid: 0x%02X\n", br_rx_state.info.adv_sid);
        APPL_TRC
        (
            "broadcast_ID: %02X %02X %02X\n",
            br_rx_state.info.broadcast_ID[0U],
            br_rx_state.info.broadcast_ID[1U],
            br_rx_state.info.broadcast_ID[2U]
        );
        APPL_TRC("pa_sync_state: 0x%02X\n", br_rx_state.info.pa_sync_state);
        APPL_TRC("big_encryption: 0x%02X\n", br_rx_state.info.big_encryption);
        if (BASS_BIG_ENCRYPTION_BAD_CODE == br_rx_state.info.big_encryption)
        {
            /*
             * Bad_Code shall be set to the value of the incorrect 16-octet
             * Broadcast_Code that fails to decrypt the BIG
             */
            appl_dump_bytes(br_rx_state.info.bad_code, BASS_BC_CODE_MAX_LEN);
        }
        APPL_TRC("num_subgroups: 0x%02X\n", br_rx_state.info.num_subgroups);
        for (i = 0U; i < br_rx_state.info.num_subgroups; i++)
        {
            APPL_TRC("bis_sync_state[%d]:\n", i);
            APPL_TRC
            (
                "- \t0x%08X\n",
                br_rx_state.info.bis_sync_state[i]
            );
            APPL_TRC("metadata_len[%d]:\n", i);
            APPL_TRC
            (
                "\t- 0x%02X\n",
                br_rx_state.info.metadata_len[i]
            );
            APPL_TRC("metadata[%d]:\n", i);
            for (j = prev_metadata_len; j < ( prev_metadata_len + br_rx_state.info.metadata_len[i]); j++)
            {
                APPL_TRC("0x%02X ", br_rx_state.info.metadata[j]);
            }
            APPL_TRC("\n");
            prev_metadata_len += br_rx_state.info.metadata_len[i];
        }
        retval = GA_SUCCESS;
    }
    return retval;
}

GA_RESULT appl_bass_se_is_src_add_allowed(UINT8 * id)
{
    UINT8 index;
    GA_RESULT retval;

    /* Initialize */
    retval = GA_FAILURE;

    for (index = 0U; index < BASS_SE_MAX_BC_RX_STATE_ENTITIES; index++)
    {
        if (!bass_se_rx_state_inst[index].isSrcAdded)
        {
            retval = GA_SUCCESS;
            *id = index;
            break;
        }
    }

    return retval;
}

GA_RESULT appl_bass_ce_parse_and_handle_bc_rx_state(UINT8 * rx_state_src_info_ptr, UINT16 len)
{
    GA_BASS_BC_RX_STATE_SRC_INFO rx_state_src_info;
    UINT32 bc_rx_state_bis_sync[APPL_BASS_MAX_NUM_OF_SUB_GROUPS];
    UINT8 bc_rx_state_metadata_len[APPL_BASS_MAX_NUM_OF_SUB_GROUPS];
    UINT8 bc_rx_state_metadata[APPL_BASS_MAX_NUM_OF_SUB_GROUPS * GA_METADATA_LEN];
    UINT8 marker;
    UINT8 index;
    GA_RESULT retval;

    /* Initialize */
    marker = 0U;
    index = 0U;
    retval = GA_FAILURE;

    APPL_TRC("[GA][BASS]: Rx State Info:\n");

    if (len != 0U)
    {
        rx_state_src_info.id = rx_state_src_info_ptr[marker++];
        APPL_TRC("Source_ID: 0x%02X\n", rx_state_src_info.id);

        rx_state_src_info.addr_type = rx_state_src_info_ptr[marker++];
        APPL_TRC("Source_Address_Type: 0x%02X\n", rx_state_src_info.addr_type);

        GA_mem_copy
        (
            rx_state_src_info.addr,
            &rx_state_src_info_ptr[marker],
            GA_BD_ADDR_SIZE
        );
        marker += GA_BD_ADDR_SIZE;
        APPL_TRC("Source_Address:\n");
        appl_dump_bytes(rx_state_src_info.addr, GA_BD_ADDR_SIZE);

        rx_state_src_info.adv_sid = rx_state_src_info_ptr[marker++];
        APPL_TRC("Source_Adv_SID: 0x%02X\n", rx_state_src_info.adv_sid);

        BT_UNPACK_LE_3_BYTE
        (
            rx_state_src_info.broadcast_ID,
            &rx_state_src_info_ptr[marker]
        );
        marker += BASS_BC_ID_LEN;
        APPL_TRC("Broadcast_ID: \n");
        appl_dump_bytes(rx_state_src_info.broadcast_ID, BASS_BC_ID_LEN);

        rx_state_src_info.pa_sync_state = rx_state_src_info_ptr[marker++];
        APPL_TRC("PA_Sync_State: 0x%02X\n", rx_state_src_info.pa_sync_state);

        rx_state_src_info.big_encryption = rx_state_src_info_ptr[marker++];
        APPL_TRC("BIG_Encryption: 0x%02X\n", rx_state_src_info.big_encryption);

        if (BASS_BIG_ENCRYPTION_BAD_CODE == rx_state_src_info.big_encryption)
        {
            /*
             * Bad_Code shall be set to the value of the incorrect 16-octet
             * Broadcast_Code that fails to decrypt the BIG
             */
            GA_mem_copy
            (
                rx_state_src_info.bad_code,
                &rx_state_src_info_ptr[marker],
                BASS_BC_CODE_MAX_LEN
            );
            appl_dump_bytes(rx_state_src_info.bad_code, BASS_BC_CODE_MAX_LEN);
            marker += BASS_BC_CODE_MAX_LEN;
        }

        rx_state_src_info.num_subgroups = rx_state_src_info_ptr[marker++];
        APPL_TRC("Num_Subgroups: 0x%02X\n", rx_state_src_info.num_subgroups);

        /* Give reference to the pointers */
        rx_state_src_info.bis_sync_state = &bc_rx_state_bis_sync[0U];
        rx_state_src_info.metadata_len = &bc_rx_state_metadata_len[0U];
        rx_state_src_info.metadata = &bc_rx_state_metadata[0U];

        for (index = 0U; index < rx_state_src_info.num_subgroups; index++)
        {
            BT_UNPACK_LE_4_BYTE
            (
                &rx_state_src_info.bis_sync_state[index],
                &rx_state_src_info_ptr[marker]
            );
            marker += 4U;
            APPL_TRC("BIS_Sync State: 0x%08X\n", rx_state_src_info.bis_sync_state[index]);

            rx_state_src_info.metadata_len[index] = rx_state_src_info_ptr[marker++];
            APPL_TRC("metadata_len: 0x%02X\n", rx_state_src_info.metadata_len[index]);

            rx_state_src_info.metadata = &rx_state_src_info_ptr[marker];

            marker += rx_state_src_info.metadata_len[index];
            APPL_TRC("Metadata:\n");
            appl_dump_bytes
            (
                rx_state_src_info.metadata,
                rx_state_src_info.metadata_len[index]
            );
        }

        retval = GA_SUCCESS;
    }

    return retval;
}

GA_RESULT appl_ga_bass_bc_ba_send_pa_sync_info(void)
{
    GA_RESULT retval;
    UINT16 svc_data;
    UINT16 acl_conn_handle;
    UINT16 sync_handle;
    int choice;

    /* Initialize */
    retval = GA_FAILURE;
    acl_conn_handle = 0U;
    svc_data = 0U;
    sync_handle = 0U;

    /*
     * The HCI_LE_Periodic_Advertising_Sync_Transfer command is used to
     * instruct the Controller to send synchronization information about the periodic
     * advertising train identified by the Sync_Handle parameter to a connected
     * device.
     */
    /* TODO: This needs to be updated based on AdvA */

    /*
     * Bit 0: AdvA in PAST matches AdvA in ADV_EXT_IND
     * 0b0 = Yes, 0b1 = No/Dont know
     * Bit 1: AdvA in PAST matches Source_Address
     * 0b0 = Yes, 0b1 = No/Dont know
     */
    svc_data = 0x03;

    /* TODO: Use the Source_ID received from Server on BR Rx State */
    /* Source_ID */
    svc_data |= 0x00;

    CONSOLE_OUT("Enter the ACL handle of the connection with SD\n");
    CONSOLE_IN("%d", &choice);
    acl_conn_handle = (UINT16)choice;

    CONSOLE_OUT("Enter the Sync handle received during \n");
    CONSOLE_IN("%d", &choice);
    sync_handle = (UINT16)choice;

    retval = BT_hci_le_periodic_advertising_sync_transfer
             (
                 acl_conn_handle,
                 svc_data,
                 sync_handle /* TODO: What if there are multiple */
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return retval;
}

GA_RESULT appl_ga_bass_bc_sd_req_sync_info_past(void)
{
    GA_RESULT  retval;
    UINT8      mode;
    UINT16     skip;
    UINT16     sync_timeout;
    UINT8      cte_type;
    UINT16     acl_conn_handle;
    int choice;

    /* Initialize*/
    retval = GA_FAILURE;
    acl_conn_handle = 0U;

    /*
     * An HCI_LE_Periodic_Advertising_Sync_Transfer_Received event is
     * sent to the Host. HCI_LE_Periodic_Advertising_Report events will be
     * disabled.
     */
    mode = 0x02U;

    /*
     * The number of periodic advertising packets that can be skipped after a
     * successful receive.
     */
    skip = 0x00U;

    /*
     * Synchronization timeout for the periodic advertising train.
     * Range: 0x000A to 0x4000
     * Time = N*10 ms
     * Time Range: 100 ms to 163.84 s
     */
    /* Maximum */
    sync_timeout = 0xC80U;

    /* Constant Tone Extension */
    cte_type = 0x00U;

    CONSOLE_OUT("Enter the ACL handle of the connection with BA\n");
    CONSOLE_IN("%d", &choice);
    acl_conn_handle = (UINT16)choice;
    APPL_TRC("Connection Handle: 0x%04X\n", acl_conn_handle);

    retval = BT_hci_le_set_periodic_advertising_sync_transfer_parameters
             (
                 acl_conn_handle,
                 mode,
                 skip,
                 sync_timeout,
                 cte_type
             );

    return retval;
}

void appl_ga_bass_bc_sd_parse_and_display_add_src_data
     (
         /* IN */    GA_BASS_BAS_CP_ADD_SRC * add_src,
         /* IN */    UINT8                  * bas_cp,
         /* INOUT */ UINT32                 * bis_sync,
         /* INOUT */ UINT8                  * metadata_len,
         /* INOUT */ UINT8                  * metadata
     )
{
    UINT8  prev_metadata_len;
    UINT8  marker;
    UCHAR  i;
    UINT32 value_4;

    marker = 0U;
    prev_metadata_len = 0U;
    value_4 = 0U;

    add_src->adv_addr_type = bas_cp[marker];
    marker++;
    APPL_TRC
    (
        "Len: 0x%02X,  Advertiser_Address_Type: ",
        (UCHAR)sizeof(UINT8)
    );
    appl_ga_bass_bc_sd_parse_and_display_addr_type(add_src->adv_addr_type);

    BT_COPY_BD_ADDR
    (
        add_src->adv_addr,
        &bas_cp[marker]
    );
    marker += GA_BD_ADDR_SIZE;
    APPL_TRC
    (
        "Len: 0x%02X,  Advertiser_Address: %02X %02X %02X %02X %02X %02X\n",
        GA_BD_ADDR_SIZE,
        add_src->adv_addr[0U], add_src->adv_addr[1U], add_src->adv_addr[2U],
        add_src->adv_addr[3U], add_src->adv_addr[4U], add_src->adv_addr[5U]
    );

    add_src->adv_SID = bas_cp[marker];
    marker++;
    APPL_TRC
    (
        "Len: 0x%02X,  Advertising_SID: 0x%02X\n",
        (UCHAR)sizeof(UINT8),
        add_src->adv_SID
    );

    GA_UNPACK_LE_3_BYTE
    (
        add_src->broadcast_ID,
        &bas_cp[marker]
    );
    marker += BASS_BC_ID_LEN;

    GA_UNPACK_LE_3_BYTE
    (
        &value_4,
        &add_src->broadcast_ID[0U]
    );
    APPL_TRC
    (
        "Len: 0x%02X,  Broadcast_ID: 0x%06X\n",
        BASS_BC_ID_LEN,
        value_4
    );

    add_src->pa_sync = bas_cp[marker];
    marker ++;
    appl_ga_bass_bc_sd_parse_and_display_PA_Sync(add_src->pa_sync);

    GA_UNPACK_LE_2_BYTE
    (
        &add_src->pa_interval,
        &bas_cp[marker]
    );
    marker += 2U;
    APPL_TRC
    (
        "Len: 0x%02X,  PA_Interval: 0x%04X\n",
        (UCHAR)sizeof(UINT16),
        add_src->pa_interval
    );

    add_src->num_subgroups = bas_cp[marker];
    marker++;
    APPL_TRC
    (
        "Len: 0x%02X,  Num_Subgroups: 0x%02X\n",
        (UCHAR)sizeof(UINT8),
        add_src->num_subgroups
    );

    for (i = 0U; i < add_src->num_subgroups; i++)
    {
        APPL_TRC("Subgroup Data[%d]:\n", i);
        /* Copy data to the Local array */
        GA_UNPACK_LE_4_BYTE
        (
            &bis_sync[i],
            &bas_cp[marker]
        );
        /* Increment marker by 4B */
        marker += 4U;
        APPL_TRC
        (
            "\tLen: 0x%02X,  BIS_Sync: 0x%08X\n",
            (UCHAR)sizeof(UINT32),
            bis_sync[i]
        );
        /* Copy data to the Local array */
        metadata_len[i] = bas_cp[marker];
        /* Increment marker by 1B */
        marker++;
        APPL_TRC
        (
            "\tLen: 0x%02X,  Metadata_Length: 0x%02X\n",
            (UCHAR)sizeof(UINT8),
            metadata_len[i]
        );
        /* Copy metadata to the Local array */
        BT_UNPACK_LE_N_BYTE
        (
            &metadata[prev_metadata_len],
            &bas_cp[marker],
            metadata_len[i]
        );
        /* Increment marker by metadata_len[i] for metadata_len */
        marker += metadata_len[i];
        APPL_TRC
        (
            "\tLen: 0x%02X,  Metadata:\n",
            metadata_len[i]
        );
        /* TODO: Parse Metadata API */
        appl_ga_bass_utils_bap_parse_and_display_metadata_ltv
        (
            &metadata[prev_metadata_len],
            metadata_len[i],
            NULL,
            NULL
        );
        prev_metadata_len += metadata_len[i];
    }
    /*
     * Make the pointers point to the base address of their
     * respective arrays.
     */
    add_src->bis_sync = &bis_sync[0U];
    add_src->metadata_len = &metadata_len[0U];
    add_src->metadata = &metadata[0U];

    return;
}

void appl_ga_bass_bc_sd_parse_and_display_modify_src_data
     (
         /* IN */    UINT8                     * bas_cp,
         /* INOUT */ GA_BASS_BAS_CP_MODIFY_SRC * modify_src,
         /* INOUT */ UINT32                    * bis_sync,
         /* INOUT */ UINT8                     * metadata_len,
         /* INOUT */ UINT8                     * metadata
     )
{
    UINT8  prev_metadata_len;
    UINT8  marker;
    UCHAR  i;

    marker = 0U;
    prev_metadata_len = 0U;

    modify_src->src_ID = bas_cp[marker];
    marker++;
    APPL_TRC
    (
        "Len: 0x%02X,  Source_ID: 0x%02X\n",
        (UCHAR)sizeof(UINT8), modify_src->src_ID
    );

    modify_src->pa_sync = bas_cp[marker];
    marker++;
    appl_ga_bass_bc_sd_parse_and_display_PA_Sync(modify_src->pa_sync);

    GA_UNPACK_LE_2_BYTE
    (
        &modify_src->pa_interval,
        &bas_cp[marker]
    );
    marker += 2U;
    APPL_TRC
    (
        "Len: 0x%02X,  PA_Interval: 0x%04X\n",
        (UCHAR)sizeof(UINT16),
        modify_src->pa_interval
    );

    modify_src->num_subgroups = bas_cp[marker];
    marker++;
    APPL_TRC
    (
        "Len: 0x%02X,  Num_Subgroups: 0x%02X\n",
        (UCHAR)sizeof(UINT8),
        modify_src->num_subgroups
    );

    for (i = 0U; i < modify_src->num_subgroups; i++)
    {
        APPL_TRC("Subgroup Data[%d]:\n", i);
        /* Copy data to the Local array */
        GA_UNPACK_LE_4_BYTE
        (
            &bis_sync[i],
            &bas_cp[marker]
        );
        /* Increment marker by 4B */
        marker += 4U;
        APPL_TRC
        (
            "\tLen: 0x%02X,  BIS_Sync: 0x%08X\n",
            (UCHAR)sizeof(UINT32),
            bis_sync[i]
        );
        /* Copy data to the Local array */
        metadata_len[i] = bas_cp[marker];
        /* Increment marker by 1B */
        marker++;
        APPL_TRC
        (
            "\tLen: 0x%02X,  Metadata_Length: 0x%02X\n",
            (UCHAR)sizeof(UINT8),
            metadata_len[i]
        );
        /* Copy metadata to the Local array */
        BT_UNPACK_LE_N_BYTE
        (
            &metadata[prev_metadata_len],
            &bas_cp[marker],
            metadata_len[i]
        );
        /* Increment marker by metadata_len[i] for metadata_len */
        marker += metadata_len[i];
        APPL_TRC
        (
            "\tLen: 0x%02X,  Metadata:\n",
            metadata_len[i]
        );
        /* TODO: Parse Metadata API */
        appl_ga_bass_utils_bap_parse_and_display_metadata_ltv
        (
            &metadata[prev_metadata_len],
            metadata_len[i],
            NULL,
            NULL
        );
        prev_metadata_len += metadata_len[i];
    }
    /*
     * Make the pointers point to the base address of their
     * respective arrays.
     */
    modify_src->bis_sync = &bis_sync[0U];
    modify_src->metadata_len = &metadata_len[0U];
    modify_src->metadata = &metadata[0U];

    return;
}

void appl_ga_bass_bc_sd_parse_and_display_addr_type(/* IN */ UINT8 addr_type)
{
    if (BASS_ADDR_TYPE_PUBLIC == addr_type)
    {
        APPL_TRC
        (
            "Public Device Address or Public Identity Address (0x%02X)\n",
            addr_type
        );
    }
    else if (BASS_ADDR_TYPE_RANDOM == addr_type)
    {
        APPL_TRC
        (
            "Random Device Address or Random (static) Identity Address (0x%02X)\n",
            addr_type
        );
    }
    else
    {
        APPL_ERR
        (
            "Unknown Address type (0x%02X) !\n",
            addr_type
        );
    }

    return;
}

void appl_ga_bass_bc_sd_parse_and_display_PA_Sync_State
     (
        /* IN */ UINT8 pa_sync_state
     )
{
    APPL_TRC("Len: 0x%02X,  PA_Sync_State: ", (UCHAR)sizeof(pa_sync_state));
    switch (pa_sync_state)
    {
    case BASS_PA_SYNC_STATE_NOT_SYNCHRONIZED:
        APPL_TRC("Not synchronized to PA (0x%02X)\n", pa_sync_state);
        break;
    case BASS_PA_SYNC_STATE_SYNC_INFO_REQUEST:
        APPL_TRC("SyncInfo Request (0x%02X)\n", pa_sync_state);
        break;
    case BASS_PA_SYNC_STATE_SYNCHRONIZED_TO_PA:
        APPL_TRC("Synchronized to PA (0x%02X)\n", pa_sync_state);
        break;
    case BASS_PA_SYNC_STATE_FAILED_TO_SYNCHRONIZE_TO_PA:
        APPL_TRC("Failed to synchronize to PA (0x%02X)\n", pa_sync_state);
        break;
    case BASS_PA_SYNC_STATE_NOPAST:
        APPL_TRC("No PAST (0x%02X)\n", pa_sync_state);
        break;
    default:
        APPL_ERR("Unknown PA_Sync_State value (0x%02X) !\n", pa_sync_state);
        break;
    }

    return;
}

void appl_ga_bass_bc_sd_parse_and_display_BIG_encryption
     (
        /* IN */ UINT8 big_encryption
     )
{
    APPL_TRC("Len: 0x%02X,  BIG_Encryption: ", (UCHAR)sizeof(big_encryption));
    switch (big_encryption)
    {
    case BASS_BIG_ENCRYPTION_NOT_ENCRYPTED:
        APPL_TRC("Not encrypted (0x%02X)\n", big_encryption);
        break;
    case BASS_BIG_ENCRYPTION_BC_CODE_REQUIRED:
        APPL_TRC("Broadcast_Code required (0x%02X)\n", big_encryption);
        break;
    case BASS_BIG_ENCRYPTION_DECRYPTING:
        APPL_TRC("Decrypting (0x%02X)\n", big_encryption);
        break;
    case BASS_BIG_ENCRYPTION_BAD_CODE:
        APPL_TRC
        (
            "Bad_Code (incorrect encryption key (0x%02X)\n",
            big_encryption
        );
        break;
    default:
        APPL_ERR("Unknown BIG_Encryption value (0x%02X) !\n", big_encryption);
        break;
    }

    return;
}

void appl_ga_bass_bc_sd_parse_and_display_PA_Sync(/* IN */ UINT8 pa_sync)
{
    APPL_TRC("Len: 0x%02X,  PA_Sync: ", (UCHAR)sizeof(pa_sync));
    switch (pa_sync)
    {
    case BASS_PA_SYNC_DO_NOT_SYNC_TO_PA:
        APPL_TRC("Do not synchronize to PA (0x%02X)\n", pa_sync);
        break;
    case BASS_PA_SYNC_SYNC_TO_PA_PAST_AVL:
        APPL_TRC("Synchronize to PA - PAST available (0x%02X)\n", pa_sync);
        break;
    case BASS_PA_SYNC_SYNC_TO_PA_PAST_NOT_AVL:
        APPL_TRC("Synchronize to PA - PAST not available (0x%02X)\n", pa_sync);
        break;
    default:
        APPL_ERR("Unknown PA_Sync value (0x%02X) !\n", pa_sync);
        break;
    }

    return;
}

void appl_ga_bass_utils_bap_parse_and_display_metadata_ltv
     (
         /* IN */    UCHAR  * ltvarray,
         /* IN */    UINT8    ltvarray_len,
         /* INOUT */ UINT16 * pref_audio_ctx,
         /* INOUT */ UINT16 * streaming_audio_ctx
     )
{
    UINT8 marker;
    UINT8 len;
    UINT8 tag;
    UINT16 value2_b;
    UINT32 value4_b;
    UCHAR i;

    marker = 0U;
    value2_b = 0U;
    value4_b = 0U;
    i = 0U;

    if (NULL == ltvarray)
    {
        APPL_TRC("Parameters NULL !\n");
        return;
    }

    if (0U == ltvarray_len)
    {
        APPL_TRC("Metadata LTV Length = 0 !\n");
        return;
    }

    while (marker < ltvarray_len)
    {
        /* Extract the Length and the Tag */
        len = ltvarray[marker];
        APPL_TRC
        (
            "\t\t- Len: 0x%02X,  Length: 0x%02X\n",
            (UCHAR)sizeof(len), len
        );
        marker++;

        tag = ltvarray[marker];
        APPL_TRC
        (
            "\t\t- Len: 0x%02X,  Type: 0x%02X\n",
            (UCHAR)sizeof(tag), tag
        );
        marker++;

        APPL_TRC("\t\t- Len: 0x%02X,  Value: ", (len - (UCHAR)sizeof(tag)));

        switch (tag)
        {
            case GA_LTV_METADATA_PREF_AC_TYPE:
                if (GA_LTV_METADATA_PREF_AC_LEN == len)
                {
                    GA_UNPACK_LE_2_BYTE(&value2_b, &ltvarray[marker]);
                    marker += 2U;
                    APPL_TRC("Preferred Audio Contexts: ");
                    APPL_TRC("0x%04X", (value2_b));
                    if (NULL != pref_audio_ctx)
                    {
                        *pref_audio_ctx = value2_b;
                    }
                }
                else
                {
                    APPL_ERR
                    (
                        "Preferred Audio Contexts Length Wrong: 0x%02X !\n",
                        len
                    );
                }
                break;

            case GA_LTV_METADATA_STREAMING_AC_TYPE:
                if (GA_LTV_METADATA_STREAMING_AC_LEN == len)
                {
                    GA_UNPACK_LE_2_BYTE(&value2_b, &ltvarray[marker]);
                    marker += 2U;
                    APPL_TRC("Streaming Audio Contexts: ");
                    APPL_TRC("0x%04X", (value2_b));
                    if (NULL != streaming_audio_ctx)
                    {
                        *streaming_audio_ctx = value2_b;
                    }
                }
                else
                {
                    APPL_ERR
                    (
                        "Streaming Audio Contexts Length Wrong: 0x%02X !\n",
                        len
                    );
                }
                break;

            case GA_LTV_METADATA_PGM_INFO_TYPE:
                APPL_TRC("Program Info: ");
                for (i = 0U; i < (len - 1U); i++)
                {
                    APPL_TRC("%c", ltvarray[marker + i]);
                }
                APPL_TRC("\n");
                marker += (len - 1U);
                break;

            case GA_LTV_METADATA_LANGUAGE_TYPE:
                if (GA_LTV_METADATA_LANGUAGE_LEN == len)
                {
                    GA_UNPACK_LE_3_BYTE(&value4_b, &ltvarray[marker]);
                    APPL_TRC("Language: ");
                    for (i = 0U; i < (len - 1U); i++)
                    {
                        APPL_TRC("%c", ltvarray[marker + i]);
                    }
                    APPL_TRC("\n");
                    marker += 3U;
                }
                else
                {
                    APPL_ERR("Language Length Wrong: 0x%02X !\n", len);
                }
                break;

            case GA_LTV_METADATA_CCID_LIST_TYPE:
                APPL_TRC("CCID List: ");
                for (i = 0U; i < (len - 1U); i++)
                {
                    APPL_TRC("0x%X ", ltvarray[marker + i]);
                }
                APPL_TRC("\n");
                marker += (len - 1U);
                break;

            case GA_LTV_METADATA_PARENTAL_RATING_TYPE:
                if (GA_LTV_METADATA_PARENTAL_RATING_LEN == len)
                {
                    APPL_TRC("Parental Rating: 0x%06X\n", ltvarray[marker]);
                    marker += 1U;
                }
                else
                {
                    APPL_ERR("Parental Rating Length Wrong: 0x%02X !\n", len);
                }
                break;

            case GA_LTV_METADATA_PROGRAM_INFO_URL_TYPE:
                APPL_TRC("Program Info URI: ");
                for (i = 0U; i < (len - 1U); i++)
                {
                    APPL_TRC("%c", ltvarray[marker + i]);
                }
                APPL_TRC("\n");
                marker += (len - 1U);
                break;

            case GA_LTV_METADATA_EM_TYPE:
                APPL_TRC("\n\tExtended Metadata:\n");
                GA_UNPACK_LE_2_BYTE(&value2_b, &ltvarray[marker]);
                marker += 2U;
                APPL_TRC("\n\tExtended Metadata Type: 0x%04X\n", value2_b);
                len -= 2U;
                appl_dump_bytes(&ltvarray[marker], (len - 1U));
                marker += (len - 1U);
                break;

            case GA_LTV_METADATA_VS_TYPE:
                APPL_TRC("\n\tVendor Specific:\n");
                GA_UNPACK_LE_2_BYTE(&value2_b, &ltvarray[marker]);
                marker += 2U;
                APPL_TRC("\n\tCompany_ID: 0x%04X\n", value2_b);
                len -= 2U;
                appl_dump_bytes(&ltvarray[marker], (len - 1U));
                marker += (len - 1U);
                break;

            default:
                APPL_ERR("\t\tUnknown Metadata Type 0x%02X !\n", tag);
                marker += (len - 1U);
                break;
        }
        APPL_TRC("\n");
    }

    return;
}

#endif /* GA_BAP */
