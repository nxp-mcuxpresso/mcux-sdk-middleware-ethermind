
/**
 *  \file appl_avrcp_ct.c
 *
 *  Source file for AVRCP Controller Source Command Line Test Application
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

/* ----------------------------------------- Header File Inclusion */
#include "appl_avrcp_ct.h"
#include "appl_avrcp_tg_virtual_media_player.h"
#include "appl_avrcp.h"
#ifdef AVRCP_BRIDGING
#include "appl_avrcp_tg.h"
#endif /* AVRCP_BRIDGING */
#ifdef AVRCP_CT
/* ----------------------------------------- External Global Variables */

//#define ENABLE_MODULE_LOG
/*disable logs*/
#ifndef ENABLE_MODULE_LOG
#ifdef printf
#undef printf
#define printf(...)
#endif
#endif /*ENABLE_MODULE_LOG*/

#ifdef CONSOLE_OUT
#undef CONSOLE_OUT
#define CONSOLE_OUT(...) (void)PRINTF(__VA_ARGS__)
#endif

#define         HAVE_OBJECT_DUMP
//#define			STREAM_PRINT

#ifdef AVRCP_BRIDGING
/* Currently the assumption is that there will be only one AVRCP target that will be connected
 * and get_ele_attr_command_called API applies to that */
UCHAR get_ele_attr_command_called = BT_FALSE;
AVRCP_ELEMENT_ATTR avrcp_ele_attr;
#define AVRCP_ELE_ATTR_TITLE 		0x01U
#define AVRCP_ELE_ATTR_ARTIST 		0x02U
#define AVRCP_ELE_ATTR_ALBUM		0x03U
#define AVRCP_ELE_ATTR_TRACK_NUM 	0x04U
#define AVRCP_ELE_ATTR_TOTAL_TRACKS 0x05U
#define AVRCP_ELE_ATTR_GENRE		0x06U
#define AVRCP_ELE_ATTR_PLAYTIME		0x07U
#endif

/* ----------------------------------------- Exported Global Variables */

/* ----------------------------------------- Static Global Variables */

/* Additional protocol desc list updation */
static UCHAR   ct_additional_protocol_descriptor_list[] =
                                        {
                                            0x35U, 0x12U, 0x35U, 0x10U, 0x35U, 0x06U,
                                            0x19U, 0x01U, 0x00U, 0x09U, 0x00U, 0x1BU,
                                            0x35U, 0x06U, 0x19U, 0x00U, 0x17U, 0x09U,
                                            0x01U, 0x03U
                                        };
/* for scope in rsp */
AVRCP_AL_GET_FOLDER_ITEMS_PARAM       get_folder_items_param;
UCHAR                                 get_total_num_items_scope;

APPL_AVRCP_MEDIA_PLAYER_LIST_INFO     ct_mp_list_info [APPL_AVRCP_MAX_NUM_PLAYERS];
UINT16                                ct_num_players;
UINT16                                ct_player_list_uid_counter;

APPL_AVRCP_VIRTUAL_FOLDER_LIST_INFO   ct_vf_info[APPL_AVRCP_MAX_FOLDER_ITEMS];
UINT16                                ct_folder_item_count;
UCHAR                                 ct_cur_folder_depth;
UINT16                                ct_folder_uid_counter;

APPL_AVRCP_MEDIA_LIST_INFO            ct_media_list_info [APPL_AVRCP_MAX_MEDIA_LIST_COUNT];
UINT16                                ct_media_list_count;
UINT16                                ct_media_list_uid_counter;

#ifdef AVRCP_COVER_ART_INITIATOR

static SDP_HANDLE               avrcp_sdp_handle;
static AVRCP_CA_HANDLE          appl_avrcp_ct_ca_handles[AVRCP_CAI_NUM_ENTITIES];

static  UINT16                  cover_art_xchg_size;

static UCHAR                    image_descriptor_data[512U];

static AVRCP_CA_IMAGE_DESCRIPTOR  img_desc;

static UCHAR wait_count;

static UCHAR                    avrcp_ct_file_object[AVRCP_CT_MAX_FILE_OBJ_NAME_LEN];

#ifdef HAVE_OBJECT_DUMP

static BT_fops_file_handle      ca_img_prop_fp;
static UCHAR                    cover_art_file_name[32U];
static UINT16                   img_prop_recv_count;
static BT_fops_file_handle      ca_img_thmbnail_fp;
static UINT16                   img_thmbnail_recv_count;

static BT_fops_file_handle      ca_image_fp;
static UINT16                   img_recv_count;

#endif /* HAVE_OBJECT_DUMP */

#endif /* AVRCP_COVER_ART_INITIATOR */


/* ----------------------------------------- Functions */
void main_avrcp_ct_operations (void)
{
    int choice, menu_choice;
    UCHAR index;

    index = 0x00U;

    BT_LOOP_FOREVER()
    {
        printf("%s", avrcp_ct_main_menu); fflush(stdin);
        scanf("%d", &choice);
        menu_choice = choice;

        switch(choice)
        {
        case 0:
            break; /* return; */

        case 1:
            /* Refresh */
            break;

        case 2:
            /* Choose Handle index */
            appl_avrcp_choose_handle(&index);
            break;

        case 3:
            appl_avrcp_ct_send_unit_info_cmd (index);
            break;

        case 4:
            appl_avrcp_ct_send_passthrough_cmd (index, 1U);
            break;

        case 5:
            appl_avrcp_ct_send_passthrough_cmd (index, 3U);
            break;

        case 10:
            appl_avrcp_ct_send_get_capability_cmd (index);
            break;

        case 11:
            appl_avrcp_ct_send_player_appl_setting_cmd (index);
            break;

        case 12:
            appl_avrcp_ct_send_get_element_attibutes_cmd (index);
            break;

        case 13:
            appl_avrcp_ct_send_notification_cmd (index);
            break;

        case 14:
            appl_avrcp_ct_send_continuation_cmd (index);
            break;

        case 15:
            appl_avrcp_ct_send_set_absolute_volume_cmd (index);
            break;

        case 16:
            appl_avrcp_ct_send_set_addressed_player_cmd (index);
            break;

        case 20:
            appl_avrcp_ct_send_browsing_cmd (index);
            break;

        case 21:
            appl_avrcp_ct_send_item_operations (index);
            break;

        case 30:
#ifdef AVRCP_COVER_ART_INITIATOR
            appl_avrcp_cai_operation ();
#else
            printf ("Please enable AVRCP_COVER_ART_INITIATOR compilation flag\n");
#endif /* AVRCP_COVER_ART */
            break;

        default:
            printf("Invalid Choice. Try Again\n");
            break;
        }

        if (0 == menu_choice)
        {
            /* return */
            break;
        }
    }

    return;
}

void appl_avrcp_ct_init (void)
{
    API_RESULT retval;
    UCHAR   i;

    retval = API_SUCCESS;
    i = 0U;

#ifdef AVRCP_COVER_ART_INITIATOR
    printf ("Initializing AVRCP Cover Art Initiator...\n");
    retval = BT_avrcp_cai_init();
    if(API_SUCCESS != retval)
    {
    	printf ("Failed : Retval - 0x%04X\n", retval);
    }
    else
    {
    	printf ("Success : Retval - 0x%04X\n", retval);
    }

    for (i = 0U; i < AVRCP_CAI_NUM_ENTITIES; i++)
    {
        appl_avrcp_ct_ca_handles[i] = AVRCP_CA_ENTITY_INVALID;
    }
#endif /* AVRCP_COVER_ART_INITIATOR */

    return;
}

void appl_avrcp_ct_shutdown (void)
{
    API_RESULT retval;

    retval = API_SUCCESS;

#ifdef AVRCP_COVER_ART_INITIATOR
    printf ("Shutting down AVRCP Cover Art Initiator...\n");
    retval = BT_avrcp_cai_shutdown();
    if(API_SUCCESS != retval)
    {
       printf ("Failed : Retval - 0x%04X\n", retval);
    }
    else
    {
    	printf ("Success : Retval - 0x%04X\n", retval);
    }
#endif /* AVRCP_COVER_ART_INITIATOR */

    return;
}


void appl_avrcp_ct_start (UCHAR index)
{
    API_RESULT    retval;
    UINT32        avrcp_record_handle;
    UINT8        *phandle;

    phandle = NULL;
    retval  = API_SUCCESS;

    BT_IGNORE_UNUSED_PARAM(index);

#ifdef AVRCP_1_4

    /* Update the additional protocol desc list */
    (BT_IGNORE_RETURN_VALUE) BT_dbase_get_record_handle
    (
        DB_RECORD_AVRCP_CONTROLLER,
        0U,
        &avrcp_record_handle
    );

    (BT_IGNORE_RETURN_VALUE) BT_dbase_change_attr_value
    (
        avrcp_record_handle,
        ADDITIONAL_PROT_DESC_LIST_ID,
        ct_additional_protocol_descriptor_list,
        20U
    );

#endif /* AVRCP_1_4 */

#ifdef AVRCP_COVER_ART_INITIATOR

    phandle = &appl_avrcp_ct_ca_handles[index];

    printf ("Starting AVRCP Cover Art Initiator Instance...\n");

    retval = BT_avrcp_cai_start
             (
                 phandle,
                 appl_avrcp_cai_callback
             );

    /* this might not return success value for 2nd instance,
     * currently max value of avrcp CAI value is set to 1 in BT_limits.h
     * will need library build after updating these values,which may affect CLI app as well.
     */
    if (API_SUCCESS != retval)
    {
        *phandle = AVRCP_CA_ENTITY_INVALID;
        printf ("Retval - 0x%04X\n", retval);
    }

#endif /* AVRCP_COVER_ART_INITIATOR */

    return;
}


void appl_avrcp_ct_stop (UCHAR index)
{
    API_RESULT    retval;
    UINT8        *phandle;

    /* Init */
    phandle = NULL;
    retval  = API_SUCCESS;
    BT_IGNORE_UNUSED_PARAM(index);

#ifdef AVRCP_COVER_ART_INITIATOR

    phandle = &appl_avrcp_ct_ca_handles[index];

    if (AVRCP_CA_ENTITY_INVALID == *phandle)
    {
        printf ("Invalid Cover Art Handle to Stop. \n");
        retval = API_FAILURE; /* return; */
    }

    if (API_SUCCESS == retval)
    {
        printf ("Stopping AVRCP Cover Art Initiator Instance...\n");

        retval = BT_avrcp_cai_stop
                 (
                     phandle
                 );

        if (API_SUCCESS == retval)
        {
            *phandle = AVRCP_CA_ENTITY_INVALID;
        }
        printf ("Retval - 0x%04X\n", retval);
    }
#endif /* AVRCP_COVER_ART_INITIATOR */

    return;
}

void appl_avrcp_ct_send_unit_info_cmd (UCHAR index)
{
    API_RESULT retval;
    int read_val;

    retval = API_SUCCESS;

    printf ("Enter Unit Type of command\n");
    printf ("\t0->unit\n");
    printf ("\t1->subunit\n");
    scanf ("%d", &read_val);

    if (0x00U == read_val)
    {
        retval = BT_avrcp_al_send_unit_info
                 (
                     &appl_avrcp_handle[index]
                 );
        if (API_SUCCESS != retval)
        {
            printf("Failed BT_avrcp_al_send_unit_info: Error Code = 0x%04X\n", retval);
        }
    }
    else
    {
        retval = BT_avrcp_al_send_subunit_info
                 (
                     &appl_avrcp_handle[index]
                 );
        if (API_SUCCESS != retval)
        {
            printf("Failed BT_avrcp_al_send_subunit_info: Error Code = 0x%04X\n", retval);
        }
    }

    return;
}

void appl_avrcp_ct_send_passthrough_cmd_variables (UCHAR index, UCHAR button_press_count, UCHAR op_id)
{
    API_RESULT retval;
    UINT16   vu_op_id;
    UCHAR    i;

    retval = API_SUCCESS;
    vu_op_id = 0x7EU;

    for ( i = 0U; i < button_press_count; i++)
    {
        /* Sending passthrough Press */
        retval = BT_avrcp_al_send_passthrough_cmd_rsp
                 (
                     &appl_avrcp_handle[index],
                     0x00U,
                     AVRCP_COMMAND_TYPE_CONTROL,
                     op_id,
                     0x00U,
                     vu_op_id
                 );
        if (API_SUCCESS != retval)
        {
            printf("Failed BT_avrcp_al_send_passthrough_cmd_rsp Press: Error Code = 0x%04X\n", retval);
        }

        if (button_press_count > 1U)
        {
            /* Delay between each Button Press */
            BT_sleep (1U);
        }
    }

    /* Sending passthrough Release */
    retval = BT_avrcp_al_send_passthrough_cmd_rsp
             (
                 &appl_avrcp_handle[index],
                 0x00U,
                 AVRCP_COMMAND_TYPE_CONTROL,
                 op_id,
                 0x01U,
                 vu_op_id
             );
    if (API_SUCCESS != retval)
    {
        printf("Failed BT_avrcp_al_send_passthrough_cmd_rsp Release: Error Code = 0x%04X\n", retval);
    }

    return;
}

void appl_avrcp_ct_send_passthrough_cmd (UCHAR index, UCHAR button_press_count)
{
    API_RESULT retval;
    int read_val;
    UCHAR    op_id;
    UINT16   vu_op_id;
    UCHAR    i;

    retval = API_SUCCESS;
    vu_op_id = 0U;
    op_id = 0U;

    printf ("Enter passthrough operation id(in Hex): ");
    printf ("\n     0x7E -> Vendor Unique op_id.\n");
    scanf ("%x", &read_val);

    op_id = (UCHAR )read_val;

    if (AVRCP_OPERATION_ID_VENDOR_UNIQUE == op_id)
    {
        printf ("Enter Vendor Unique Opertion ID(in Hex): ");

        scanf ("%x", &read_val);

        vu_op_id = (UINT16 )read_val;
    }

    for ( i = 0U; i < button_press_count; i++)
    {
        /* Sending passthrough Press */
        retval = BT_avrcp_al_send_passthrough_cmd_rsp
                 (
                     &appl_avrcp_handle[index],
                     0x00U,
                     AVRCP_COMMAND_TYPE_CONTROL,
                     op_id,
                     0x00U,
                     vu_op_id
                 );
        if (API_SUCCESS != retval)
        {
            printf("Failed BT_avrcp_al_send_passthrough_cmd_rsp Press: Error Code = 0x%04X\n", retval);
        }

        if (button_press_count > 1U)
        {
            /* Delay between each Button Press */
            BT_sleep (1U);
        }
    }

    /* Sending passthrough Release */
    retval = BT_avrcp_al_send_passthrough_cmd_rsp
             (
                 &appl_avrcp_handle[index],
                 0x00U,
                 AVRCP_COMMAND_TYPE_CONTROL,
                 op_id,
                 0x01U,
                 vu_op_id
             );
    if (API_SUCCESS != retval)
    {
        printf("Failed BT_avrcp_al_send_passthrough_cmd_rsp Release: Error Code = 0x%04X\n", retval);
    }

    return;
}

void appl_avrcp_ct_send_get_capability_cmd(UCHAR index)
{
    API_RESULT retval;
    int read_val;

    retval = API_SUCCESS;

    printf ("Enter Capability ID\n");
    printf ("\t0->Company ID\n");
    printf ("\t1->Events Supported\n");
    scanf ("%d", &read_val);

    if (0U == read_val)
    {
        retval = BT_avrcp_al_get_companyid_supported
                 (
                     &appl_avrcp_handle[index]
                 );
    }
    else
    {
        retval = BT_avrcp_al_get_event_supported
                 (
                     &appl_avrcp_handle[index]
                 );
    }

    BT_IGNORE_UNUSED_PARAM(retval);
    return;
}

void appl_avrcp_ct_send_player_appl_setting_cmd(UCHAR index)
{
    int choice, read_val;

    API_RESULT retval;

    AVRCP_AL_VD_CMD_INFO pdu_info;
    UCHAR   *param;
    UINT16   paramlen, offset;

    printf ("Select option below: \n");
    printf ("   1. ListPlayerApplicationSettingAttributes.\n");
    printf ("   2. ListPlayerApplicationSettingValues.\n");
    printf ("   3. GetCurrentPlayerApplicationSettingValue.\n");
    printf ("   4. SetPlayerApplicationSettingValue.\n");
    printf ("   5. GetPlayerApplicationSettingAttributeText.\n");
    printf ("   6. GetPlayerApplicatoinSettingValueText.\n");
    printf ("   7. InformDisplayableCharacterSet.\n");
    printf ("   8. InformBatterSatusofCT.\n");

    scanf ("%d", &choice);

    /* Init */
    offset = 0U;
    param = NULL;
    paramlen = 0U;
    retval = API_SUCCESS;

    pdu_info.tl = 0x00U;
    pdu_info.packet_type = AVRCP_METADATA_PACKET_TYPE_SINGLE;

    if (0x04U == choice)
    {
        pdu_info.cmd_type    = AVRCP_COMMAND_TYPE_CONTROL;
    }
    else
    {
        pdu_info.cmd_type    = AVRCP_COMMAND_TYPE_STATUS;
    }

    switch(choice)
    {
    case 1: /* ListPlayerApplicationSettingAttributes */

        pdu_info.pdu_id = AVRCP_METADATA_PDU_ID_LIST_PLAYER_APP_SETTING_ATTR;

        param = NULL;
        paramlen = 0U;

        pdu_info.vd_cmd_data = param;
        pdu_info.vd_cmd_datalen = paramlen;

        break;

    case 2: /* ListPlayerApplicationSettingValues */
        {
            UCHAR attr_id;

            pdu_info.pdu_id = AVRCP_METADATA_PDU_ID_LIST_PLAYER_APP_SETTING_VAL;

            printf ("Enter Player Appl. Attr. ID(in Hex): ");
            scanf ("%x", &read_val);

            attr_id = (UCHAR) read_val;
            paramlen = 1U;

            pdu_info.vd_cmd_data = &attr_id;
            pdu_info.vd_cmd_datalen = paramlen;
        }

        break;

    case 3: /* GetCurrentPlayerApplicationSettingValue */
    case 5: /* GetPlayerApplicationSettingAttributeText */
        {
            UCHAR   num_attr_ids, i;

            if (3U == choice)
            {
                pdu_info.pdu_id = AVRCP_METADATA_PDU_ID_GET_CUR_PLAYER_APP_SETTING_VAL;
            }
            else
            {
                pdu_info.pdu_id = AVRCP_METADATA_PDU_ID_GET_PLAYER_APP_SETTING_ATTR_TXT;
            }

            printf ("Enter No. of Player Appl. Attr. ID\n");
            scanf ("%d", &read_val);

            num_attr_ids = (UCHAR )read_val;

            paramlen = 1U + (UINT16)num_attr_ids;

            param = BT_alloc_mem(paramlen);
            if (NULL == param)
            {
                printf ("Failed to allocate memory\n");
                retval = API_FAILURE; /* return; */
            }
            else
            {
                /* Fill parameter data */
                param[offset++] = num_attr_ids;

                for (i = 0U; i < num_attr_ids; i++)
                {
                    printf("Enter Player Appl. Attr. ID %d(in Hex): ", (i + 1U));
                    scanf("%d", &read_val);

                    param[offset++] = (UCHAR)read_val;;
                }

                pdu_info.vd_cmd_data = param;
                pdu_info.vd_cmd_datalen = paramlen;
            }
        }

        break;

    case 4: /* SetPlayerApplicationSettingValue */
        {
            UCHAR   num_attr_ids, i;

            pdu_info.pdu_id = AVRCP_METADATA_PDU_ID_SET_PLAYER_APP_SETTING_VAL;

            printf ("Enter No. of Player Appl. Attr. ID: ");
            scanf ("%d", &read_val);

            num_attr_ids = (UCHAR )read_val;

            /* 1 + (1+1) num_attr_ids */
            paramlen = 1U + 2U * (UINT16)num_attr_ids;

            param = BT_alloc_mem(paramlen);
            if (NULL == param)
            {
                printf ("Failed to allocate memory\n");
                retval = API_FAILURE; /* return; */
            }
            else
            {
                /* No. of Attr. ID's */
                param[offset++] = num_attr_ids;

                for (i = 0U; i < num_attr_ids; i++)
                {
                    printf("Enter Player Appl. Attr. ID %d(in Hex): ", (i + 1U));
                    scanf("%x", &read_val);

                    /* Attr. ID */
                    param[offset++] = (UCHAR)read_val;

                    printf("Enter Player Appl. Attr. ID %d value(in Hex): ", (i + 1U));
                    scanf("%x", &read_val);

                    /* Attr. ID value */
                    param[offset++] = (UCHAR)read_val;
                }

                pdu_info.vd_cmd_data = param;
                pdu_info.vd_cmd_datalen = paramlen;
            }
        }

        break;

    case 6: /* GetPlayerApplicatoinSettingValueText */
        {
            UCHAR   attr_id, num_attr_id_val, i;

            pdu_info.pdu_id = AVRCP_METADATA_PDU_ID_GET_PLAYER_APP_SETTING_VAL_TXT;

            printf ("Enter Player Appl. Attr. ID \n");
            scanf ("%d", &read_val);

            attr_id = (UCHAR )read_val;


            printf ("Enter No. of Player Appl. Attr. ID values \n");
            scanf ("%d", &read_val);

            num_attr_id_val = (UCHAR )read_val;

            /* 1 + (1+1) num_attr_ids */
            paramlen = 1U + 1U +  (UINT16)num_attr_id_val;

            param = BT_alloc_mem(paramlen);
            if (NULL == param)
            {
                printf ("Failed to allocate memory\n");
                retval = API_FAILURE; /* return; */
            }
            else
            {
                /* Attr. ID */
                param[offset++] = attr_id;

                /* No. of Attr. ID val */
                param[offset++] = num_attr_id_val;

                for (i = 0U; i < num_attr_id_val; i++)
                {
                    printf("Enter Player Appl. Attr. ID value %d(in Hex): ", (i + 1U));
                    scanf("%x", &read_val);

                    /* Attr. ID value */
                    param[offset++] = (UCHAR)read_val;
                }

                pdu_info.vd_cmd_data = param;
                pdu_info.vd_cmd_datalen = paramlen;
            }
        }

        break;

    case 7: /* InformDisplayableCharacterSet */
        {
            UCHAR   num_char_set, i;
            UINT16  char_set_id;

            pdu_info.pdu_id = AVRCP_METADATA_PDU_ID_INFORM_DISPLAYABLE_CHAR_SET;

            printf ("Enter No. of Display Char Set: ");
            scanf ("%d", &read_val);

            num_char_set = (UCHAR )read_val;

            paramlen = 1U + 1U + 2U * (UINT16)num_char_set;

            param = BT_alloc_mem(paramlen);
            if (NULL == param)
            {
                printf ("Failed to allocate memory\n");
                retval = API_FAILURE; /* return; */
            }
            else
            {
                /* No. of Attr. ID val */
                param[offset++] = num_char_set;

                for (i = 0U; i < num_char_set; i++)
                {
                    printf("Enter Char Set ID %d(in Hex): ", (i + 1U));
                    scanf("%x", &read_val);

                    char_set_id = (UINT16)read_val;

                    avrcp_pack_2_byte_metadata_param
                    (
                        &param[offset],
                        &char_set_id
                    );

                    offset += 2U;
                }

                pdu_info.vd_cmd_data = param;
                pdu_info.vd_cmd_datalen = paramlen;
            }
        }

        break;

    case 8: /* InformBatterSatusofCT */
        {
            /* UCHAR   battery_status; */

            pdu_info.pdu_id = AVRCP_METADATA_PDU_ID_INFORM_BATTERY_STATUS;

            printf ("Enter Batter Status: ");
            printf ("   0 -> Normal. \n");
            printf ("   1 -> Warning. \n");
            printf ("   2 -> Critical. \n");
            printf ("   3 -> External. \n");
            printf ("   4 -> Full Charge. \n");
            scanf ("%d", &read_val);

            battery_status = (UCHAR )read_val;
            paramlen = 1U;

            pdu_info.vd_cmd_data = &battery_status;
            pdu_info.vd_cmd_datalen = paramlen;

        }

        break;

    default:
        printf ("Invalid Option.\n");
        retval = API_FAILURE; /* return; */
    }

    if (API_SUCCESS == retval)
    {
        retval = BT_avrcp_al_send_metadata_pdu
                 (
                     &appl_avrcp_handle[index],
                     &pdu_info,
                     0x00U
                 );

        /* Free the memory */
        if (NULL != param)
        {
            BT_free_mem(param);

            param = NULL;
        }
    }

    BT_IGNORE_UNUSED_PARAM(retval);
    return;
}

void appl_avrcp_ct_send_get_element_attibutes_cmd (UCHAR index)
{
    API_RESULT retval;

    int read_val;
    UINT32 uid[2U], attr_id[APPL_AVRCP_MAX_ATTR_COUNT];
    UCHAR num_attrs, i;
    UCHAR *param;
    UCHAR  paramlen, offset;
    AVRCP_AL_VD_CMD_INFO pdu_info;

    /* Init */
    offset      = 0U;
    paramlen    = 0U;
    param      =  NULL;
    uid[0U]      = 0x00U; //0 -> Current Track
    uid[1U]      = 0x00U; //0 -> Current Track


    num_attrs = 0; //0 for all attributes

    /* Limits check, to avoid buffer overflow */
    if (APPL_AVRCP_MAX_ATTR_COUNT < num_attrs)
    {
        printf("Number of Attributes: %d > APPL_AVRCP_MAX_ATTR_COUNT: %d. Limiting to %d\n",
        num_attrs, APPL_AVRCP_MAX_ATTR_COUNT, APPL_AVRCP_MAX_ATTR_COUNT);

        num_attrs = APPL_AVRCP_MAX_ATTR_COUNT;
    }

    for (i = 0U; i < num_attrs; i++)
    {
        printf ("Enter attr id %d (in Hex):  ", (i+1U));
        scanf ("%x", &read_val);

        attr_id[i] = (UINT32)read_val;
    }

    /* UID length */
    paramlen = 8U;

    if (0U == num_attrs)
    {
        paramlen += 1U;
    }
    else
    {
        paramlen += (1U + 4U * num_attrs);
    }

    /* Allocate memory for param  */
    param = BT_alloc_mem(paramlen);
    if (NULL == param)
    {
        printf ("Failed to allocate memory\n");
        retval = API_FAILURE; /* return; */
    }
    else
    {
        /* ====  Fill param ======= */

        /* UID */
        avrcp_pack_4_byte_metadata_param
        (
            &param[offset],
            &uid[1U]
        );

        offset += 4U;

        avrcp_pack_4_byte_metadata_param
        (
            &param[offset],
            &uid[0U]
        );

        offset += 4U;

        /* No. of Attributes */
        param[offset++] = num_attrs;

        /* Pack Attribute ID's */
        for (i = 0U; i < num_attrs; i++)
        {
            avrcp_pack_4_byte_metadata_param
            (
                &param[offset],
                &attr_id[i]
            );

            offset += 4U;
        }

        /* Update PDU params */
        pdu_info.tl                 = 0x00U;
        pdu_info.packet_type        = AVRCP_METADATA_PACKET_TYPE_SINGLE;
        pdu_info.cmd_type           = AVRCP_COMMAND_TYPE_STATUS;
        pdu_info.pdu_id             = AVRCP_METADATA_PDU_ID_GET_ELEMENT_ATTRIBUTE;
        pdu_info.vd_cmd_data        = param;
        pdu_info.vd_cmd_datalen     = paramlen;

        /* Send PDU Command over Control Channel */
        retval = BT_avrcp_al_send_metadata_pdu
                 (
                     &appl_avrcp_handle[index],
                     &pdu_info,
                     0x00U
                 );
#ifdef AVRCP_BRIDGING
        set_ele_attr_command_called(BT_TRUE);
#endif //AVRCP_BRIDGING

        /* Free the memory */
        if (NULL != param)
        {
            BT_free_mem(param);

            param = NULL;
        }
    }

    BT_IGNORE_UNUSED_PARAM(retval);
    return;
}

void appl_avrcp_ct_send_notification_cmd (UCHAR index)
{
    int choice;
    API_RESULT retval;
    UCHAR event_id;
    UINT32 playback_interval;

    printf (" 1. GetPlayStatus.\n");
    printf (" 2. RegisterNotification.\n");

    scanf ("%d", &choice);

    switch(choice)
    {
    case 1:
        retval = BT_avrcp_al_get_play_status
                 (
                     &appl_avrcp_handle[index]
                 );
        break;

    case 2:
        printf ("Select Event ID(in Hex): \n");
        printf ("    1. EVENT_PLAYBACK_STATUS_CHANGED\n");
        printf ("    2. EVENT_TRACK_CHANGED\n");
        printf ("    3. EVENT_TRACK_REACHED_END\n");
        printf ("    4. EVENT_TRACK_REACHED_START\n");
        printf ("    5. EVENT_PLAYBACK_POS_CHANGED\n");
        printf ("    6. EVENT_BATT_STATUS_CHANGED\n");
        printf ("    7. EVENT_SYSTEM_STATUS_CHANGED\n");
        printf ("    8. EVENT_PLAYER_APPLICATION_SETTING_CHANGED\n");
        printf ("    9. EVENT_NOW_PLAYING_CONTENT_CHANGED\n");
        printf ("    a. EVENT_AVAILABLE_PLAYERS_CHANGED\n");
        printf ("    b. EVENT_ADDRESSED_PLAYER_CHANGED\n");
        printf ("    c. EVENT_UIDS_CHANGED\n");
        printf ("    d. EVENT_VOLUME_CHANGED\n");
        scanf ("%x", &choice);

        event_id = (UCHAR ) choice;
        playback_interval = 0x00U;

        if (AVRCP_EVENT_PLAYBACK_POS_CHANGED == event_id)
        {
            printf ("Enter playback interval(in Hex): ");
            scanf ("%x", &choice);

            playback_interval = (UINT32 )choice;
        }
        retval = BT_avrcp_al_register_notification
                 (
                     &appl_avrcp_handle[index],
                     event_id,
                     playback_interval
                 );

        break;

    default:
        printf ("Invalid Option.\n");
        break;
    }

    BT_IGNORE_UNUSED_PARAM(retval);
    return;
}

void appl_avrcp_ct_send_continuation_cmd(UCHAR index)
{
    API_RESULT retval;

    int choice, read_val;
    UCHAR  pdu_id;

    retval = API_SUCCESS;

    printf ("Select option\n");
    printf ("1. RequestContinuingResponse.\n");
    printf ("2. AbortContinuingResponse.\n");

    scanf ("%d", &choice);

    printf ("Enter PDU ID(in Hex): ");
    scanf ("%x", &read_val);
    pdu_id = (UCHAR ) read_val;

    switch(choice)
    {
    case 1:

        retval = BT_avrcp_al_send_request_continuing_rsp
                 (
                     &appl_avrcp_handle[index],
                     pdu_id
                 );
        break;

    case 2:

        retval = BT_avrcp_al_send_abort_continuing_rsp
                 (
                     &appl_avrcp_handle[index],
                     pdu_id
                 );
        break;

    default:
        printf ("Invalid Option.\n");
        break;
    }

    BT_IGNORE_UNUSED_PARAM(retval);
    return;
}

void appl_avrcp_ct_send_set_absolute_volume_cmd(UCHAR index)
{
    API_RESULT retval;

    int read_val;
    UCHAR  abs_vol;

    retval = API_SUCCESS;

    printf ("Enter Absolute Volume(in Hex): \n");
    scanf ("%x", &read_val);

    abs_vol = (UCHAR )read_val;

    retval = BT_avrcp_al_set_absolute_volume
             (
                 &appl_avrcp_handle[index],
                 abs_vol
             );

    BT_IGNORE_UNUSED_PARAM(retval);
    return;
}

void appl_avrcp_ct_send_set_addressed_player_cmd (UCHAR index)
{
    API_RESULT retval;
    int read_val;

    retval = API_SUCCESS;

    printf ("Enter Addressed Player ID(in Hex): ");
    scanf ("%x", &read_val);

    retval  =  BT_avrcp_al_send_set_addressed_player_cmd
               (
                   &appl_avrcp_handle[index],
                   (UINT16) read_val
                );
    if(API_SUCCESS != retval)
    {
        printf("Failed BT_avrcp_al_send_set_addressed_player_cmd: Error Code = 0x%04X\n", retval);
    }

    return;
}

void appl_avrcp_ct_send_browsing_cmd (UCHAR index)
{
    API_RESULT retval;

    int choice, read_val;
    UINT16  brow_player_id, i;

    printf ("Select Option\n");
    printf ("   1. SetBrowsedPlayer.\n");
    printf ("   2. GetFolderItems.\n");
    printf ("   3. ChangePath.\n");
    printf ("   4. GetItemAttributes.\n");
    printf ("   5. GetTotalNumberOfItems.\n");
    printf ("   6. Search.\n");

    scanf ("%d", &choice);

    retval = API_SUCCESS;

    switch(choice)
    {
    case 1: /* Set Browsed Player */
        printf ("Enter Browsed Player ID(in Hex)\n");
        scanf ("%x", &read_val);

        brow_player_id = (UINT16 )read_val;

        retval =  BT_avrcp_al_set_browsed_player
                  (
                      &appl_avrcp_handle[index],
                      brow_player_id
                  );
        if(API_SUCCESS != retval)
        {
            printf("BT_avrcp_al_set_browsed_player Failed: Error Code = 0x%04X\n", retval);
        }

        break;

    case 2: /* Get Folder Items */
        {
            printf ("Enter the folder scope to send\n");
            printf ("    0 -> Media Player\n");
            printf ("    1 -> Filesys\n");
            printf ("    2 -> Search\n");
            printf ("    3 -> Now Playing\n");
            scanf ("%d", &read_val);

            get_folder_items_param.scope = (UCHAR )read_val;

            printf ("Enter Start Item Index(0-10): \n");
            scanf ("%d", &read_val);

            get_folder_items_param.start_item = read_val;

            printf ("Enter End Item Index(0-10): \n");
            scanf ("%d", &read_val);

            get_folder_items_param.end_item = read_val;

            printf ("Enter Total No. of Attr.(in Hex)\n");
            printf ("\t0x00: For All Attributes\n");
            printf ("\t0x01: For One Attribute\n");
            printf ("\t0xFF: For Zero Attributes\n");

            scanf ("%x", &read_val);

            get_folder_items_param.attr_count = (UCHAR )read_val;

            if ((0x00U != get_folder_items_param.attr_count) &&
                (0xFFU != get_folder_items_param.attr_count))
            {
                for (i = 0U; i < get_folder_items_param.attr_count; i++)
                {
                    printf ("Enter Attr. id %d (in Hex): \n", (i+1U));
                    scanf ("%x", &read_val);
                    get_folder_items_param.attr_list[i] = read_val;
                }
            }

            retval = BT_avrcp_al_get_folder_items
                     (
                         &appl_avrcp_handle[index],
                         &get_folder_items_param
                     );
        }

        break;

    case 3: /* Change Path */
        {
            UINT16    uid_counter;
            UCHAR     path_dir;
            UCHAR   * folder_uid;
            UINT32    uid_msb, uid_lsb;

            printf ("Enter UID counter(in Hex): ");
            scanf ("%x", &read_val);

            uid_counter = (UINT16 )read_val;

            printf ("Enter Path Direction(0->up, 1->down): ");
            scanf ("%x", &read_val);

            path_dir = (UCHAR )read_val;

            /* Allocate memory for parameter */
            folder_uid = BT_alloc_mem (8U);
            if (NULL == folder_uid)
            {
                printf (" Memory Allocation failed\n");
                retval = API_FAILURE; /* return; */
            }
            else
            {
                printf ("Enter msb of folder uid(in Hex): ");
                scanf ("%x", &read_val);

                uid_msb = (UINT32)read_val;

                avrcp_pack_4_byte_metadata_param
                (
                    &folder_uid[0U],
                    &uid_msb
                );

                printf ("Enter lsb of folder uid(in Hex): ");
                scanf ("%x", &read_val);
                uid_lsb = (UINT32)read_val;

                avrcp_pack_4_byte_metadata_param
                (
                    &folder_uid[4U],
                    &uid_lsb
                );

                /* Send command */
                retval = BT_avrcp_al_change_path
                         (
                             &appl_avrcp_handle[index],
                             uid_counter,
                             path_dir,
                             folder_uid
                         );

                /* Free Memory */
                BT_free_mem(folder_uid);
            }
        }

        break;

    case 4: /* Get Item Attributes */
        {
            AVRCP_AL_GET_ITEM_ATTRIBUTE_PARAMS  get_item_attr_param;

            printf ("Enter Scope: \n");

            printf ("    1 -> Filesys\n");
            printf ("    2 -> Search\n");
            printf ("    3 -> Now Playing\n");
            scanf ("%d", &read_val);

            get_item_attr_param.scope = (UCHAR )read_val;

            printf ("Enter msb of item uid(in Hex): ");
            scanf ("%x", &read_val);

            get_item_attr_param.uid_msb = (UINT32) read_val;

            printf ("Enter lsb of item uid(in Hex): ");
            scanf ("%x", &read_val);

            get_item_attr_param.uid_lsb = (UINT32) read_val;

            printf ("Enter UID counter(in Hex): ");
            scanf ("%x", &read_val);

            get_item_attr_param.uid_counter = (UINT16 )read_val;

            printf ("Enter Total No. of Attr.(in Hex)(0 for All): ");
            scanf ("%x", &read_val);

            get_item_attr_param.attr_count = (UCHAR )read_val;

            for (i = 0U; i < get_item_attr_param.attr_count; i++)
            {
                printf ("Enter Attr. id %d (in Hex): ", (i+1U));
                scanf ("%x", &read_val);

                get_item_attr_param.attr_list[i] = (UINT32 )read_val;
            }

            retval = BT_avrcp_al_get_items_attribute
                     (
                         &appl_avrcp_handle[index],
                         &get_item_attr_param
                     );
        }
        break;

    case 5: /* Get Total number of Items */
        {
#ifdef AVRCP_GET_NUM_OF_ITEMS
            printf ("Enter Scope:\n");
            printf ("    0 -> Media Player\n");
            printf ("    1 -> Filesys\n");
            printf ("    2 -> Search\n");
            printf ("    3 -> Now Playing\n");
            scanf ("%d", &read_val);

            get_total_num_items_scope = (UCHAR )read_val;

            retval = BT_avrcp_al_get_total_number_of_items
                     (
                         &appl_avrcp_handle[index],
                         get_total_num_items_scope
                     );

#else
            printf ("Enable AVRCP_GET_NUM_OF_ITEMS Feature Flag. \n");

#endif /* AVRCP_GET_NUM_OF_ITEMS */

        }

        break;

    case 6: /* Search */
        {
            UINT16    char_set;
            UCHAR     search_str[64U];
            UINT16    search_str_len;

            printf ("Enter Char Set (in Hex):\n ");
            printf ("    0x6A -> UTF-8 \n");
            scanf ("%x", &read_val);

            char_set = (UINT16 )read_val;

            printf ("Enter Search String: ");
            scanf ("%s", search_str);

            search_str_len = (UINT16)BT_str_len(search_str);

            retval = BT_avrcp_al_search
                     (
                         &appl_avrcp_handle[index],
                         char_set,
                         search_str,
                         search_str_len
                     );
        }

        break;

    default:

        printf ("Invalid Option\n");
        break;
    }

    return;
}

void appl_avrcp_ct_send_item_operations(UCHAR   index)
{
    API_RESULT retval;

    int      choice, read_val;
    UCHAR    scope;
    UINT32   uid_msb, uid_lsb;
    UINT16   uid_counter;
    UCHAR   *param;
    UCHAR   paramlen, offset;
    AVRCP_AL_VD_CMD_INFO pdu_info;

    printf ("1. PlayItem.\n");
    printf ("2. AddToNowPlaying.\n");

    scanf ("%d", &choice);

    retval = API_SUCCESS;
    param = NULL;
    paramlen = 0U;

    switch(choice)
    {
    case 1: /* Fall Through */
    case 2:

        printf ("Enter Scope:\n ");
        printf ("    0 -> Media Player\n");
        printf ("    1 -> Filesys\n");
        printf ("    2 -> Search\n");
        printf ("    3 -> Now Playing\n");
        scanf ("%d", &read_val);

        scope = (UCHAR )read_val;

        printf ("Enter msb of item uid(in Hex): ");
        scanf ("%x", &read_val);

        uid_msb = (UINT32) read_val;

        printf ("Enter lsb of item uid(in Hex): ");
        scanf ("%x", &read_val);

        uid_lsb = (UINT32) read_val;

        printf ("Enter UID counter(in Hex): ");
        scanf ("%x", &read_val);

        uid_counter = (UINT16 )read_val;
        paramlen = 1U + 8U + 4U;

        /* Allocate memory for param  */
        param = BT_alloc_mem(paramlen);
        if (NULL == param)
        {
            printf ("Failed to allocate memory\n");
            retval = API_FAILURE; /* return; */
        }
        else
        {
            offset = 0U;

            param[offset++] = scope;

            /* Pack UID */
            avrcp_pack_4_byte_metadata_param
            (
                &param[offset],
                &uid_msb
            );

            offset += 4U;

            avrcp_pack_4_byte_metadata_param
            (
                &param[offset],
                &uid_lsb
            );

            offset += 4U;

            /* Pack UID counter */
            avrcp_pack_2_byte_metadata_param
            (
                &param[offset],
                &uid_counter
            );

            offset += 2U;

            /* Update PDU params */
            pdu_info.tl                 = 0x00U;
            pdu_info.packet_type        = AVRCP_METADATA_PACKET_TYPE_SINGLE;
            pdu_info.cmd_type           = AVRCP_COMMAND_TYPE_CONTROL;

            pdu_info.vd_cmd_data        = param;
            pdu_info.vd_cmd_datalen     = offset;

            if (1U == choice)
            {
                pdu_info.pdu_id         = AVRCP_PDU_ID_PLAY_ITEMS;
            }
            else
            {
                pdu_info.pdu_id         = AVRCP_PDU_ID_ADD_TO_NOW_PLAYING;
            }

            /* Send PDU Command over Control Channel */
            retval = BT_avrcp_al_send_metadata_pdu
                     (
                        &appl_avrcp_handle[index],
                        &pdu_info,
                        0x00U
                     );
        }

        break;

    default:
        printf ("Invalid Option.\n");
        break;
    }

    /* Free the memory */
    if (NULL != param)
    {
        BT_free_mem(param);
        param = NULL;
    }

    BT_IGNORE_UNUSED_PARAM(retval);
    return;
}


void appl_avrcp_ct_send_set_browsed_player(UCHAR index)
{
    API_RESULT retval;
    int read_val;

    retval = API_SUCCESS;

    printf ("Enter Browsed Player ID(in Hex): ");
    scanf ("%x", &read_val);

    retval = BT_avrcp_al_set_browsed_player
             (
                 &appl_avrcp_handle[index],
                 (UINT16 ) read_val
             );
    if(API_SUCCESS != retval)
    {
        printf("Failed BT_avrcp_al_set_browsed_player: Error Code = 0x%04X\n", retval);
    }

    return;
}

void appl_avrcp_ct_handle_message_cnf
     (
         UCHAR *    event_data,
         UINT16     event_datalen
     )
{
    UCHAR       op_id;
    UCHAR       op_id_state;
    UINT16      vu_op_id;

    AVRCP_AL_CT_RSP_INFO   *avrcp_rsp_info;

    BT_IGNORE_UNUSED_PARAM(event_datalen);

    printf("\n");
    printf("AVRCP Control Response:\n");

    avrcp_rsp_info = (AVRCP_AL_CT_RSP_INFO *)event_data;

    appl_avrcp_print_opcode (avrcp_rsp_info->cmd_opcode);

    /* Print operation id for passthrough command */
    if (AVRCP_OPCODE_PASS_THROUGH == avrcp_rsp_info->cmd_opcode)
    {
        AVRCP_GET_MSG_OPERATION_INFO((UCHAR *)avrcp_rsp_info->rsp_info, op_id, op_id_state);

        appl_avrcp_print_operation_id(op_id);
        printf("    State = ");
        if (0x00U == op_id_state)
        {
            printf ("Pressed\n");
        }
        else
        {
            printf ("Released\n");
        }

        if (AVRCP_OPERATION_ID_VENDOR_UNIQUE == op_id)
        {
            /* Extract Vendor Unique operation id */
            avrcp_extract_2_byte_metadata_param
            (
                &((UCHAR *)avrcp_rsp_info->rsp_info)[9U],
                &vu_op_id
            );

            printf ("    Vendor Unique Op Id: 0x%04x\n", vu_op_id);
        }
    }
    appl_avrcp_print_response_type (avrcp_rsp_info->rsp_type);

    return;
}

void appl_avrcp_ct_handle_vendor_dependent_cmd_rsp
     (
         UCHAR       inst,
         void      * event_data,
         UINT16      event_datalen
     )
{
    AVRCP_AL_VD_CMD_INFO * vd_cmd_info;

   /* BT_IGNORE_UNUSED_PARAM(inst); */
    BT_IGNORE_UNUSED_PARAM(event_datalen);

    vd_cmd_info     = (AVRCP_AL_VD_CMD_INFO *)event_data;
    /* Command Type */
    printf ("    Response Type - ");
    switch(vd_cmd_info->cmd_type)
    {
    case AVRCP_RESPONSE_TYPE_ACCEPTED:
        printf ("ACCEPTED\n");
        break;

    case AVRCP_RESPONSE_TYPE_INTERIM:
        printf ("INTERIM\n");
        break;

    case AVRCP_RESPONSE_TYPE_STABLE:
        printf ("STABLE\n");
        break;

    case AVRCP_RESPONSE_TYPE_REJECTED:
        printf ("REJECTED\n");
        break;

    case AVRCP_RESPONSE_TYPE_NOT_IMPLEMENTED:
        printf ("NOT IMPLEMENTED\n");
        break;

    case AVRCP_RESPONSE_TYPE_CHANGED:
        printf ("CHANGED\n");
        break;

    default:
        printf ("UNKNOWN\n");
        break;
    }

    printf ("\n    PDU-ID -> ");

    switch(vd_cmd_info->pdu_id)
    {
    case AVRCP_METADATA_PDU_ID_GET_CAPABILITY:
        printf ("Get Capability <0x%x>.\n", vd_cmd_info->pdu_id);
        break;

    case AVRCP_METADATA_PDU_ID_LIST_PLAYER_APP_SETTING_ATTR:
        printf ("List Player Appl. Setting Attributes<0x%x>.\n", vd_cmd_info->pdu_id);
        break;

    case AVRCP_METADATA_PDU_ID_LIST_PLAYER_APP_SETTING_VAL:
        printf ("List Player Appl. Setting Values<0x%x>.\n", vd_cmd_info->pdu_id);
        break;

    case AVRCP_METADATA_PDU_ID_GET_CUR_PLAYER_APP_SETTING_VAL:
        printf ("Get Current Player Appl. Setting Value<0x%x>.\n", vd_cmd_info->pdu_id);
        break;

    case AVRCP_METADATA_PDU_ID_SET_PLAYER_APP_SETTING_VAL:
        printf ("Set Player Appl. Setting Value<0x%x>.\n", vd_cmd_info->pdu_id);
        break;

    case AVRCP_METADATA_PDU_ID_GET_PLAYER_APP_SETTING_ATTR_TXT:
        printf ("Get Player Appl. Setting Attr. Text<0x%x>.\n", vd_cmd_info->pdu_id);
        break;

    case AVRCP_METADATA_PDU_ID_GET_PLAYER_APP_SETTING_VAL_TXT:
        printf ("Get Player Appl. Setting Value Text<0x%x>.\n", vd_cmd_info->pdu_id);
        break;

    case AVRCP_METADATA_PDU_ID_INFORM_DISPLAYABLE_CHAR_SET:
        printf ("Inform Displayable Char Set<0x%x>.\n", vd_cmd_info->pdu_id);
        break;

    case AVRCP_METADATA_PDU_ID_INFORM_BATTERY_STATUS:
        printf ("Inform Battery Status<0x%x>.\n", vd_cmd_info->pdu_id);
        break;

    case AVRCP_METADATA_PDU_ID_GET_ELEMENT_ATTRIBUTE:
        CONSOLE_OUT ("Get Element Attributes<0x%x>.\n", vd_cmd_info->pdu_id);
        break;

    case AVRCP_METADATA_PDU_ID_GET_PLAY_STATUS:
        printf ("Get Play Status<0x%x>.\n", vd_cmd_info->pdu_id);
        break;

    case AVRCP_METADATA_PDU_ID_REGISTER_NOTIFICATION:
        printf ("Register Notification<0x%x>.\n", vd_cmd_info->pdu_id);

        break;

    case AVRCP_METADATA_PDU_ID_REQUEST_CONTINUING_RESPONSE:
        printf ("Request Continue Response <0x%x>.\n", vd_cmd_info->pdu_id);
        break;

    case AVRCP_METADATA_PDU_ID_ABORT_CONTINUING_RESPONSE:
        printf ("Abort Continue Response <0x%x>.\n", vd_cmd_info->pdu_id);
        break;

    case AVRCP_PDU_ID_SET_ABSOLUTE_VOLUME:
        printf ("Set Absolute Volume<0x%x>.\n", vd_cmd_info->pdu_id);

        break;

    case AVRCP_PDU_ID_SET_ADDRESSED_PLAYER:
        printf ("Set Addressed Player<0x%x>.\n", vd_cmd_info->pdu_id);
        break;

    case AVRCP_PDU_ID_PLAY_ITEMS:
        printf ("Play Item<0x%x>.\n", vd_cmd_info->pdu_id);
        break;

    case AVRCP_PDU_ID_ADD_TO_NOW_PLAYING:
        printf ("Add To Now Playing<0x%x>.\n", vd_cmd_info->pdu_id);
        break;

    default:
        printf ("Unknown PDU-ID<0x%x>\n", vd_cmd_info->pdu_id);

        break;
    }

    appl_avrcp_ct_display_vd_cmd_rsp_info
    (
        vd_cmd_info
    );

    return;
}


void appl_avrcp_ct_display_vd_cmd_rsp_info
     (
         AVRCP_AL_VD_CMD_INFO  *rsp_info
     )
{
    API_RESULT retval;
    UCHAR   * rsp_param_info;
    UCHAR     pkt_type;
    UINT16    offset, param_len;

    /* Init */
    retval = API_SUCCESS;
    rsp_param_info = NULL;
    offset = 0U;

    /* param check */
    if (NULL == rsp_info)
    {
        printf ("NULL rsp_info\n");
        retval = API_FAILURE; /* return; */
    }
    else
    {
        pkt_type = 0U;
        rsp_param_info = rsp_info->vd_cmd_data;

        /* offset till control cmd hdr */
        offset = 6U + 1U;

        /* skip PDU ID + packet type +  parameter length */
        offset += (1U + 1U + 2U);

        pkt_type = rsp_param_info[8U] & 0x03U;
        printf("    Pkt_Type : ");

        /* Displaying only Single Packet params */
        switch (pkt_type)
        {
        case AVRCP_METADATA_PACKET_TYPE_START:
            printf("Start\n");
            printf("====== Params are Not Displaying ======= \n");
            printf("Take Action to Send Continue/Abort Command\n");
            retval = API_FAILURE; /* return; */
            break;

        case AVRCP_METADATA_PACKET_TYPE_CONTINUE:
            printf("Continue\n");
            printf("====== Params are Not Displaying ======= \n");
            printf("Take Action to Send Continue/Abort Command\n");
            retval = API_FAILURE; /* return; */
            break;

        case AVRCP_METADATA_PACKET_TYPE_END:
            printf("End\n");
            printf("====== Params are Not Displaying ======= \n");

            /**
             * Since the previously received fragments are not saves, parameters will not be correct.
             * So returning from here.
             */
            retval = API_FAILURE; /* return; */
            break;

        default: /* AVRCP_METADATA_PACKET_TYPE_SINGLE */
            printf("Single\n");
            break;
        }
    }

    if (API_SUCCESS == retval)
    {
        /* Extract param length */
        avrcp_extract_2_byte_metadata_param
        (
            &rsp_param_info[9U],
            &param_len
        );

        CONSOLE_OUT ("    Param Length: 0x%04x\n", param_len);

        switch(rsp_info->pdu_id)
        {
        case AVRCP_METADATA_PDU_ID_GET_CAPABILITY:
            {
                UCHAR   cap_id;
                UCHAR   no_ids, i;
                UINT32  company_id;

                cap_id = rsp_param_info[offset];

                offset += 1U;

                if (AVRCP_CAP_ID_COMPANY_ID == cap_id)
                {
                    no_ids = rsp_param_info[offset++];

                    printf ("    No. of Company ID's Supported: %d\n", no_ids);

                    for (i = 0U; i < no_ids; i++)
                    {
                        /* Extract Company ID's */
                        avrcp_extract_3_byte_metadata_param
                        (
                            &rsp_param_info[offset],
                            &company_id
                        );

                        printf ("     - 0x%06x\n", company_id);

                        offset += 3U;
                    }
                }
                else if (AVRCP_CAP_ID_EVENTS_SUPPORTED == cap_id)
                {
                    no_ids = rsp_param_info[offset++];

                    printf ("    No. of Events Supported: %d\n", no_ids);

                    for (i = 0U; i < no_ids; i++)
                    {
                        printf ("     - 0x%02x\n", rsp_param_info[offset++]);
                    }
                }
                else
                {
                    printf ("    Unknown Capability ID Received.\n");
                }
            }

            break;

        case AVRCP_METADATA_PDU_ID_LIST_PLAYER_APP_SETTING_ATTR:
            {
                UCHAR num_attr, i, attr_id;

                /* variable needed for printing command response info */
                BT_IGNORE_UNUSED_PARAM(attr_id);

                num_attr = rsp_param_info[offset++];

                printf ("    No. of Player Appl. Attributes = 0x%0x\n", num_attr);

                for (i = 0U; i < num_attr; i++)
                {
                    attr_id = rsp_param_info[offset++];

                    printf ("     - 0x%0x\n", attr_id);
                }
            }

            break;

        case AVRCP_METADATA_PDU_ID_LIST_PLAYER_APP_SETTING_VAL:
            {
                UCHAR   i, num_attr_val, attr_val ;

                /* variable needed for printing command response info */
                BT_IGNORE_UNUSED_PARAM(attr_val);

                num_attr_val = rsp_param_info[offset++];

                printf ("    No. of Player Appl. Attr. Values = 0x%0x\n", num_attr_val);

                for (i = 0U; i < num_attr_val; i++)
                {
                    attr_val = rsp_param_info[offset++];

                    printf ("     - 0x%0x\n", attr_val);
                }
            }

            break;

        case AVRCP_METADATA_PDU_ID_GET_CUR_PLAYER_APP_SETTING_VAL:
            {
                UCHAR i, num_attr, attr_id, attr_val;

                /* variables needed for printing command response info */
                BT_IGNORE_UNUSED_PARAM(attr_val);
                BT_IGNORE_UNUSED_PARAM(attr_id);

                num_attr = rsp_param_info[offset++];

                printf ("    No. of Player Appl. Attributes = 0x%0x\n", num_attr);

                for (i = 0U; i < num_attr; i++)
                {
                    attr_id = rsp_param_info[offset++];
                    attr_val = rsp_param_info[offset++];

                    printf ("     - ID: 0x%0x\n", attr_id);
                    printf ("     - Value: 0x%0x\n", attr_val);
                }
            }
            break;

        case AVRCP_METADATA_PDU_ID_SET_PLAYER_APP_SETTING_VAL:
            /* No params expected in the response */
            break;

        case AVRCP_METADATA_PDU_ID_GET_PLAYER_APP_SETTING_ATTR_TXT: /* Fall Through */
        case AVRCP_METADATA_PDU_ID_GET_PLAYER_APP_SETTING_VAL_TXT:
            {
                UCHAR    num_attr, attr_id, i;
                UCHAR    attr_val_txt_len, attr_val_txt[64U];
                UINT16   char_set;

                /* variable needed for printing command response info */
                BT_IGNORE_UNUSED_PARAM(attr_id);

                num_attr = rsp_param_info[offset++];

                for (i = 0U; i < num_attr; i++)
                {
                    /* Attribute ID */
                    attr_id = rsp_param_info[offset++];

                    /* Char set */
                    avrcp_extract_2_byte_metadata_param
                    (
                        &rsp_param_info[offset],
                        &char_set
                    );

                    offset += 2U;

                    /* Attribute value text length */
                    attr_val_txt_len = rsp_param_info[offset++];

                    /* Attribute Value Text */
                    BT_mem_copy
                    (
                        attr_val_txt,
                        &rsp_param_info[offset],
                        attr_val_txt_len
                    );

                    attr_val_txt[attr_val_txt_len] = (UCHAR)'\0';

                    offset += attr_val_txt_len;

                    if (AVRCP_METADATA_PDU_ID_GET_PLAYER_APP_SETTING_ATTR_TXT == rsp_info->pdu_id)
                    {
                        printf ("     - Attr. ID: 0x%0x\n", attr_id);
                    }
                    else
                    {
                        printf ("     - Attr. Val ID: 0x%0x\n", attr_id);
                    }

                    printf ("     - Value Txt: %s\n", attr_val_txt);
                }
            }
            break;

        case AVRCP_METADATA_PDU_ID_INFORM_DISPLAYABLE_CHAR_SET:
            /* No params expected in the response */
            break;

        case AVRCP_METADATA_PDU_ID_INFORM_BATTERY_STATUS:
            /* No params expected in the response */
            break;
        case AVRCP_METADATA_PDU_ID_GET_ELEMENT_ATTRIBUTE:
            {
                UCHAR   num_attr, i, attr_val[255U];
                UINT32  attr_id;
                UINT16  char_set, attr_len;

                num_attr = 0U;
                attr_id  = 0U;
                char_set = 0U;
                attr_len = 0U;

                if (AVRCP_RESPONSE_TYPE_REJECTED == rsp_info->cmd_type)
                {
                	CONSOLE_OUT ("    Reason: 0x%02x\n", rsp_param_info[offset]);
                    break;
                }

                /* No. of attributes */
                num_attr = rsp_param_info[offset++];

                CONSOLE_OUT ("    No. of Attributes: %d\n", num_attr);
#ifdef AVRCP_BRIDGING
                memset(&avrcp_ele_attr, 0x0, sizeof(avrcp_ele_attr));
#endif //AVRCP_BRIDGING

                for (i = 0U; i < num_attr; i++)
                {
                    /* Attribute ID */
                    avrcp_extract_4_byte_metadata_param
                    (
                        &rsp_param_info[offset],
                        &attr_id
                    );

                    offset += 4U;

                    /* Char set */
                    avrcp_extract_2_byte_metadata_param
                    (
                        &rsp_param_info[offset],
                        &char_set
                    );

                    offset += 2U;

                    /* Attribule value length */
                    avrcp_extract_2_byte_metadata_param
                    (
                        &rsp_param_info[offset],
                        &attr_len
                    );

                    offset += 2U;

                    /* Attribute value */
                    BT_mem_copy
                    (
                        attr_val,
                        &rsp_param_info[offset],
                        attr_len
                    );

                    attr_val[attr_len] = (UCHAR)'\0';
                    offset += attr_len;

                    CONSOLE_OUT ("       - ID: 0x%04x\n", attr_id);
                    CONSOLE_OUT ("       - Value: %s\n", attr_val);
#ifdef AVRCP_BRIDGING
                    UINT16 len = 0;
                    switch(attr_id)
                    {
                    case AVRCP_ELE_ATTR_TITLE:
                    	len = ((attr_len > (AVRCP_ATTR_STR_LEN - 1)) ? (AVRCP_ATTR_STR_LEN - 1) : attr_len);
                    	BT_mem_copy(avrcp_ele_attr.title, attr_val, len);
                    	avrcp_ele_attr.title[len] = '\0';
                    	break;
                    case AVRCP_ELE_ATTR_ARTIST:
                    	len = ((attr_len > (AVRCP_ATTR_STR_LEN - 1)) ? (AVRCP_ATTR_STR_LEN - 1) : attr_len);
                    	BT_mem_copy(avrcp_ele_attr.artist, attr_val, len);
                    	avrcp_ele_attr.artist[len] = '\0';
                    	break;
                    case AVRCP_ELE_ATTR_ALBUM:
                    	len = ((attr_len > (AVRCP_ATTR_STR_LEN - 1)) ? (AVRCP_ATTR_STR_LEN - 1) : attr_len);
                    	BT_mem_copy(avrcp_ele_attr.album, attr_val, len);
                    	avrcp_ele_attr.album[len] = '\0';
                    	break;
                    case AVRCP_ELE_ATTR_TRACK_NUM:
                    	if(attr_len < AVRCP_ATTR_NUM_LEN)
                    	{
                    		BT_mem_copy(avrcp_ele_attr.track_num, attr_val, attr_len);
                    		avrcp_ele_attr.track_num[attr_len] = '\0';
                    	}
                    	break;
					case AVRCP_ELE_ATTR_TOTAL_TRACKS:
						if(attr_len < AVRCP_ATTR_NUM_LEN)
						{
							BT_mem_copy(avrcp_ele_attr.total_tracks, attr_val, attr_len);
							avrcp_ele_attr.total_tracks[attr_len] = '\0';
						}
						break;
					case AVRCP_ELE_ATTR_GENRE:
						len = ((attr_len > (AVRCP_ATTR_STR_LEN - 1)) ? (AVRCP_ATTR_STR_LEN - 1) : attr_len);
						BT_mem_copy(avrcp_ele_attr.genre, attr_val, len);
						avrcp_ele_attr.genre[len] = '\0';
						break;
					case AVRCP_ELE_ATTR_PLAYTIME:
						len = ((attr_len > (AVRCP_ATTR_STR_LEN - 1)) ? (AVRCP_ATTR_STR_LEN - 1) : attr_len);
						BT_mem_copy(avrcp_ele_attr.play_time, attr_val, len);
						avrcp_ele_attr.play_time[len] = '\0';
						break;
                    }

#endif //AVRCP_BRIDGING
                }
#ifdef AVRCP_BRIDGING
                AVRCP_ELEMENT_ATTR* attr;
				attr = get_current_song_attributes();
				CONSOLE_OUT("*********************************************************\n");
				CONSOLE_OUT("TITLE        :	%s\n",avrcp_ele_attr.title);
				CONSOLE_OUT("ARTIST       :	%s\n",avrcp_ele_attr.artist);
				CONSOLE_OUT("ALBUM        :	%s\n",avrcp_ele_attr.album);
				CONSOLE_OUT("TRACK NUM    :	%s\n",avrcp_ele_attr.track_num);
				CONSOLE_OUT("TOTAL TRACKS :	%s\n",avrcp_ele_attr.total_tracks);
				CONSOLE_OUT("GENRE        :	%s\n",avrcp_ele_attr.genre);
				CONSOLE_OUT("PLAYING TIME :	%s\n",avrcp_ele_attr.play_time);
				CONSOLE_OUT("*********************************************************\n");

				/* variable needed for printing command response info */
				BT_IGNORE_UNUSED_PARAM(attr);
#endif //AVRCP_BRIDGING
            }
            break;
        case AVRCP_METADATA_PDU_ID_GET_PLAY_STATUS:
            {
                UINT32 song_total_len;
                UINT32 song_cur_pos;
                UCHAR  song_play_status;

                /* Extract song length */
                avrcp_extract_4_byte_metadata_param
                (
                    &rsp_param_info[offset],
                    &song_total_len
                );

                offset += 4U;

                /* Extract song current playing position */
                avrcp_extract_4_byte_metadata_param
                (
                    &rsp_param_info[offset],
                    &song_cur_pos
                );

                offset += 4U;

                /* Play status */
                song_play_status = rsp_param_info[offset];

                printf ("\n    Current Media Play Status:\n");
                printf ("       - Song Total Length(in msec): %d\n", song_total_len);
                printf ("       - Song Current postion: %d\n", song_cur_pos);
                printf ("       - Song Play Status: ");

                switch(song_play_status)
                {
                case 0x00U:
                    printf ("0x00(STOPPED)");
                    break;

                case 0x01U:
                    printf ("0x01(PLAYING)");
                    break;

                case 0x02U:
                    printf ("0x02(PAUSED)");
                    break;

                case 0x03U:
                    printf ("0x03(FWD_SEEK)");
                    break;

                case 0x04U:
                    printf ("0x04(REV_SEEK)");
                    break;

                case 0xFFU:
                    printf ("0xFF(ERROR)");
                    break;

                default:
                    printf ("??");
                    break;
                }

                printf ("\n");
            }
            break;

        case AVRCP_METADATA_PDU_ID_REGISTER_NOTIFICATION:
            {
                UCHAR   event_id;
                UCHAR   *notify_param;
                UINT16  notify_param_len;

                notify_param_len = param_len;
                event_id = rsp_param_info[offset++];

                notify_param = &rsp_param_info[offset];
                notify_param_len--;

                appl_avrcp_ct_display_notify_rsp
                (
                    event_id,
                    notify_param,
                    notify_param_len
                );
            }
            break;

        case AVRCP_METADATA_PDU_ID_REQUEST_CONTINUING_RESPONSE: /* Fallthrough */
        case AVRCP_METADATA_PDU_ID_ABORT_CONTINUING_RESPONSE:
            printf ("    Error: 0x%02x\n", rsp_param_info[offset]);
            break;

        case AVRCP_PDU_ID_SET_ABSOLUTE_VOLUME:
            {
                UCHAR volume;

                /* variable needed for printing command response info */
                BT_IGNORE_UNUSED_PARAM(volume);

                /* Consider only 7 bits */
                volume = rsp_param_info[offset] & 0x7FU;
                printf ("    Volume: 0x%02x\n", volume);
            }
            break;

        case AVRCP_PDU_ID_SET_ADDRESSED_PLAYER:
        case AVRCP_PDU_ID_PLAY_ITEMS:         /* Fall Through */
        case AVRCP_PDU_ID_ADD_TO_NOW_PLAYING: /* Fall Through */
            {
                UCHAR status;

                status = rsp_param_info[offset];
                if (AVRCP_METADATA_ERROR_OPERATION_SUCCESSFUL == status)
                {
                    printf ("    Status: Operation Completed Without error\n");
                }
            }
            break;
        default:
            printf ("Invalid PDU ID: %d\n", rsp_info->pdu_id);
            break;
        }
    }

    return;
}

void appl_avrcp_ct_display_notify_rsp
     (
         UCHAR      event_id,
         UCHAR     *notify_param,
         UINT16     notify_param_len
     )
{
    UCHAR   play_status;
    UCHAR   volume;

    /* variable needed for printing command response info */
    BT_IGNORE_UNUSED_PARAM(volume);

    switch (event_id)
    {
    case AVRCP_EVENT_PLAYBACK_STATUS_CHANGED:
        printf ("\n    Event-ID -> AVRCP_EVENT_PLAYBACK_STATUS_CHANGED<0x%x>.\n", event_id);

        if ((NULL != notify_param) &&
            (1U == notify_param_len))
        {
            play_status = notify_param[0U];

            printf ("     - Player Status: ");
            switch(play_status)
            {
            case 0x00U:
                printf ("0x00(STOPPED)");
                break;

            case 0x01U:
                printf ("0x01(PLAYING)");
                break;

            case 0x02U:
                printf ("0x02(PAUSED)");
                break;

            case 0x03U:
                printf ("0x03(FWD_SEEK)");
                break;

            case 0x04U:
                printf ("0x04(REV_SEEK)");
                break;

            case 0xFFU:
                printf ("0xFF(ERROR)");
                break;

            default:
                printf ("??");
                break;
            }
        }

        break;

    case AVRCP_EVENT_TRACK_CHANGED:
        printf ("\n    Event-ID -> AVRCP_EVENT_TRACK_CHANGED<0x%x>.\n", event_id);
        break;

    case AVRCP_EVENT_TRACK_REACHED_END:
        printf ("\n    Event-ID -> AVRCP_EVENT_TRACK_REACHED_END<0x%x>.\n", event_id);
        break;

    case AVRCP_EVENT_TRACK_REACHED_START:
        printf ("\n    Event-ID -> AVRCP_EVENT_TRACK_REACHED_START<0x%x>.\n", event_id);
        break;

    case AVRCP_EVENT_PLAYBACK_POS_CHANGED:
        printf ("\n    Event-ID -> AVRCP_EVENT_PLAYBACK_POS_CHANGED<0x%x>.\n", event_id);
        break;

    case AVRCP_EVENT_BATT_STATUS_CHANGED:
        printf ("\n    Event-ID -> AVRCP_EVENT_BATT_STATUS_CHANGED<0x%x>.\n", event_id);
        break;

    case AVRCP_EVENT_SYSTEM_STATUS_CHANGED:
        printf ("\n    Event-ID -> AVRCP_EVENT_SYSTEM_STATUS_CHANGED<0x%x>.\n", event_id);
        break;

    case AVRCP_EVENT_PLAYER_APP_SETTING_CHANGED:
        printf ("\n    Event-ID -> AVRCP_EVENT_PLAYER_APP_SETTING_CHANGED<0x%x>.\n", event_id);
        break;

#ifdef AVRCP_1_4
    case AVRCP_EVENT_NOW_PLAYING_CONTENT_CHANGED:
        printf ("\n    Event-ID -> AVRCP_EVENT_NOW_PLAYING_CONTENT_CHANGED<0x%x>.\n", event_id);
        break;

    case AVRCP_EVENT_AVAILABLE_PLAYER_CHANGED:
        printf ("\n    Event-ID -> AVRCP_EVENT_AVAILABLE_PLAYER_CHANGED<0x%x>.\n", event_id);
        break;

    case AVRCP_EVENT_ADDRESSED_PLAYER_CHANGED:
        printf ("\n    Event-ID -> AVRCP_EVENT_ADDRESSED_PLAYER_CHANGED<0x%x>.\n", event_id);
        break;

    case AVRCP_EVENT_UIDS_CHANGED:
        printf ("\n    Event-ID -> AVRCP_EVENT_UIDS_CHANGED<0x%x>.\n", event_id);
        break;

    case AVRCP_EVENT_VOLUME_CHANGED:

        printf ("\n    Event-ID -> AVRCP_EVENT_VOLUME_CHANGED<0x%x>.\n", event_id);
        if ((NULL != notify_param) &&
            (1U == notify_param_len))
        {
            volume = notify_param[0U] & 0x7FU;
            printf("    Volume: 0x%02x\n", volume);
        }
        break;

#endif /* AVRCP_1_4 */
    default:
        printf ("\n    Event-ID -> ??? \n");
        break;
    }

    return;
}

void appl_avrcp_ct_handle_brow_cmd_rsp
     (
         UCHAR       inst,
         void      * event_data,
         UINT16      event_datalen
     )
{
    AVRCP_AL_BROW_RSP_INFO * brow_rsp_info;
    UCHAR                  * rsp_info;
    UINT16                   param_len;

    BT_IGNORE_UNUSED_PARAM(inst);
    BT_IGNORE_UNUSED_PARAM(event_datalen);

    /* Init */
    brow_rsp_info     = (AVRCP_AL_BROW_RSP_INFO *)event_data;
    rsp_info        = (UCHAR *)brow_rsp_info->param_info;

    /* Extract param length */
    avrcp_extract_2_byte_metadata_param
    (
        &rsp_info[2U],
        &param_len
    );

    printf ("    param len : 0x%04x\n", param_len);

    /* For error response, just display the error and return */
    if (AVRCP_METADATA_ERROR_OPERATION_SUCCESSFUL != rsp_info[4U])
    {
        appl_avrcp_ct_print_error (rsp_info[4U]);
    }
    else
    {
        switch (brow_rsp_info->pdu_id)
        {
        case AVRCP_PDU_ID_SET_BROWSED_PLAYER:
            appl_avrcp_ct_handle_set_brow_player_rsp
            (
                brow_rsp_info
            );
            break;

        case AVRCP_PDU_ID_GET_FOLDER_ITEMS:
            appl_avrcp_ct_handle_get_folder_items_rsp
            (
                brow_rsp_info
            );
            break;

        case AVRCP_PDU_ID_CHANGE_PATH:
            {
                UINT32 num_items;

                printf ("    PDU ID - Change Path (0x%x).\n", brow_rsp_info->pdu_id);
                printf ("    Status : ");
                if (AVRCP_METADATA_ERROR_OPERATION_SUCCESSFUL == rsp_info[4U])
                {
                    printf ("Operation Completed Without error\n");
                }

                /* Extract no. of items */
                avrcp_extract_4_byte_metadata_param
                (
                    &rsp_info[5U],
                    &num_items
                );

                printf ("     - No. of Items: %d\n", num_items);
            }
            break;

        case AVRCP_PDU_ID_GET_ITEM_ATTRIBUTES:
            appl_avrcp_ct_handle_get_item_attributes_rsp
            (
                brow_rsp_info
            );
            break;

        case AVRCP_PDU_ID_SEARCH:
            {
                UINT16 uid_counter;
                UINT32 num_items;

                printf ("\n");
                printf ("    PDU ID - Search (0x%x).\n", brow_rsp_info->pdu_id);

                printf ("    Status : ");
                if (AVRCP_METADATA_ERROR_OPERATION_SUCCESSFUL == rsp_info[4U])
                {
                    printf ("Operation Completed Without error\n");
                }

                /* Extract UID counter */
                avrcp_extract_2_byte_metadata_param
                (
                    &rsp_info[5U],
                    &uid_counter
                );

                /* Extract no. of items */
                avrcp_extract_4_byte_metadata_param
                (
                    &rsp_info[7U],
                    &num_items
                );

                printf ("      - UID Counter : 0x%04x\n", uid_counter);
                printf ("      - No. of Items Found: %d\n", num_items);
            }

            break;

#ifdef AVRCP_GET_NUM_OF_ITEMS
        case AVRCP_PDU_ID_GET_TOTAL_NUM_ITEMS:
            {
                UINT16 uid_counter;
                UINT32 num_items;

                printf ("\n");
                printf ("    PDU ID - Get Total Number of Items (0x%x).\n", brow_rsp_info->pdu_id);

                printf ("    Status : ");
                if (AVRCP_METADATA_ERROR_OPERATION_SUCCESSFUL == rsp_info[4U])
                {
                    printf ("Operation Completed Without error\n");
                }

                /* Extract UID counter */
                avrcp_extract_2_byte_metadata_param
                (
                    &rsp_info[5U],
                    &uid_counter
                );

                /* Extract no. of items */
                avrcp_extract_4_byte_metadata_param
                (
                    &rsp_info[7U],
                    &num_items
                );

                printf ("    Scope: ");
                switch(get_total_num_items_scope)
                {
                case AVRCP_SCOPE_MEDIA_PLAYER_LIST:
                    printf ("Media Player List\n");
                    break;

                case AVRCP_SCOPE_VIRTUAL_FILESYSTEM:
                    printf ("Virtual Filesystem\n");
                    break;

                case AVRCP_SCOPE_SEARCH:
                    printf ("Search\n");
                    break;

                case AVRCP_SCOPE_NOW_PLAYING:
                    printf ("Now Playing\n");
                    break;

                default:
                    printf("Invalid Scope: %d\n", get_total_num_items_scope);
                    break;
                }
                printf ("    - UID Counter : 0x%04x\n", uid_counter);
                printf ("    - No. of Items: %d\n", num_items);
            }
            break;
#endif /* AVRCP_GET_NUM_OF_ITEMS */

        default:
            printf("Invalid PDU ID: %d\n", brow_rsp_info->pdu_id);
            break;
        }
    }

    return;
}

void appl_avrcp_ct_handle_get_folder_items_rsp
     (
            AVRCP_AL_BROW_RSP_INFO  *brow_rsp_info
     )
{
    if (NULL == brow_rsp_info)
    {
        printf ("NULL brow_rsp_info\n");
        /* return; */
    }
    else
    {
        printf("    PDU ID - Get Folder Items(0x%x).\n", brow_rsp_info->pdu_id);

        printf("    Status : ");
        if (AVRCP_METADATA_ERROR_OPERATION_SUCCESSFUL == ((UCHAR *)brow_rsp_info->param_info)[4U])
        {
            printf("Operation Completed Without error\n");
        }

        printf("    Scope : ");
        /* Process the response based on scope sent in req */
        switch (get_folder_items_param.scope)
        {
        case AVRCP_SCOPE_MEDIA_PLAYER_LIST:
            printf("Media Player List\n");
            appl_avrcp_ct_handle_get_media_player_list_rsp
            (
                (UCHAR *)brow_rsp_info->param_info,
                brow_rsp_info->param_info_len
            );
            break;

        case AVRCP_SCOPE_VIRTUAL_FILESYSTEM:
        case AVRCP_SCOPE_SEARCH: /* Fall through */
            printf("%s\n", (AVRCP_SCOPE_SEARCH == get_folder_items_param.scope) ?
                "Search" : "Virtual FileSystem");
            appl_avrcp_ct_handle_get_virtual_filesytem_rsp
            (
                (UCHAR *)brow_rsp_info->param_info,
                brow_rsp_info->param_info_len
            );
            break;

        case AVRCP_SCOPE_NOW_PLAYING:
            printf("Now Playing\n");
            appl_avrcp_ct_handle_get_media_element_list_rsp
            (
                (UCHAR *)brow_rsp_info->param_info,
                brow_rsp_info->param_info_len
            );
            break;

        default:
            printf("Invalid Scope: %d\n", get_folder_items_param.scope);
            break;
        }
    }

    return;
}

void appl_avrcp_ct_handle_get_media_player_list_rsp
     (
         UCHAR    *mp_list_info,
         UINT16    mp_list_param_len
     )
{
    UINT16 offset, i;

    BT_IGNORE_UNUSED_PARAM(mp_list_param_len);

    /* param check */
    if (NULL == mp_list_info)
    {
        printf ("NULL mp_list_info\n");
        /* return; */
    }
    else
    {
        /* Reset Media Player List */
        BT_mem_set
        (
            ct_mp_list_info,
            0x00U,
            sizeof (APPL_AVRCP_MEDIA_PLAYER_LIST_INFO) * APPL_AVRCP_MAX_NUM_PLAYERS
        );

        /* offset till UID counter */
        offset = 5U;

        /* Extract UID counter */
        avrcp_extract_2_byte_metadata_param
        (
            &mp_list_info[offset],
            &ct_player_list_uid_counter
        );
        offset += 2U;

        printf ("    UID counter : 0x%04x\n", ct_player_list_uid_counter);

        /* Extract no. of players */
        avrcp_extract_2_byte_metadata_param
        (
            &mp_list_info[offset],
            &ct_num_players
        );
        offset += 2U;

        printf ("    No. of Players : 0x%04x\n", ct_num_players);

        for (i = 0U; i < ct_num_players; i++)
        {
            /* Item type */
            ct_mp_list_info[i].item_type = mp_list_info[offset++];

            /* Item length */
            avrcp_extract_2_byte_metadata_param
            (
                &mp_list_info[offset],
                &ct_mp_list_info[i].item_len
            );
            offset += 2U;

            /* player id */
            avrcp_extract_2_byte_metadata_param
            (
                &mp_list_info[offset],
                &ct_mp_list_info[i].player_id
            );
            offset += 2U;

            /* Major payer type */
            ct_mp_list_info[i].major_player_type = mp_list_info[offset++];

            /* Player sub type */
            avrcp_extract_4_byte_metadata_param
            (
                &mp_list_info[offset],
                &ct_mp_list_info[i].player_sub_type
            );
            offset += 4U;

            /* Play status */
            ct_mp_list_info[i].play_status = mp_list_info[offset++];

            /* player feature bit mask */
            avrcp_extract_4_byte_metadata_param
            (
                &mp_list_info[offset],
                &ct_mp_list_info[i].features_bit_mask[3U]
            );
            offset += 4U;

            avrcp_extract_4_byte_metadata_param
            (
                &mp_list_info[offset],
                &ct_mp_list_info[i].features_bit_mask[2U]
            );
            offset += 4U;

            avrcp_extract_4_byte_metadata_param
            (
                &mp_list_info[offset],
                &ct_mp_list_info[i].features_bit_mask[1U]
            );
            offset += 4U;

            avrcp_extract_4_byte_metadata_param
            (
                &mp_list_info[offset],
                &ct_mp_list_info[i].features_bit_mask[0U]
            );
            offset += 4U;

             /* char set */
            avrcp_extract_2_byte_metadata_param
            (
                &mp_list_info[offset],
                &ct_mp_list_info[i].char_set
            );
            offset += 2U;

            /* name len */
            avrcp_extract_2_byte_metadata_param
            (
                &mp_list_info[offset],
                &ct_mp_list_info[i].name_len
            );
            offset += 2U;

            /* name */
            BT_mem_copy
            (
                ct_mp_list_info[i].name,
                &mp_list_info[offset],
                ct_mp_list_info[i].name_len
            );

            offset += ct_mp_list_info[i].name_len;
        }

        /* Display Media players */
        appl_avrcp_ct_display_media_player_list ();
    }

    return;
}

void appl_avrcp_ct_display_media_player_list(void)
{
    UCHAR i, j;
    APPL_AVRCP_MEDIA_PLAYER_LIST_INFO * m;

    m = ct_mp_list_info;

    printf ("---------------------------\n");
    printf ("#### Media Player List ####\n");
    printf ("---------------------------\n");

    for(i = 0U; i < ct_num_players; ++i)
    {
        /* Player Id */
        printf("Player ID: 0x%x\n", m[i].player_id);

        /* Player Displayable name */
        printf("Player Name: ");
        for (j = 0U; j < m[i].name_len; j++)
        {
            printf ("%c", m[i].name[j]);
        }
        printf ("\n");

        /* Major Player Type: Audio, Video, etc. */
        printf("Major Player Type: ");
        switch(m[i].major_player_type)
        {
            case AVRCP_MP_MAJOR_PLAYER_TYPE_AUDIO:
                printf("Audio");
                break;
            case AVRCP_MP_MAJOR_PLAYER_TYPE_VIDEO:
                printf("Video");
                break;
            case AVRCP_MP_MAJOR_PLAYER_TYPE_BROADCASTING_AUDIO:
                printf("Broadcasting Audio");
                break;
            case AVRCP_MP_MAJOR_PLAYER_TYPE_BROADCASTING_VIDEO:
                printf("Broadcasting Video");
                break;
            default:
                printf("Reserved");
                break;
        }
        printf ("\n");

        printf("Player Sub Type: ");
        switch(m[i].player_sub_type)
        {
            case AVRCP_MP_PLAYER_SUBTYPE_AUDIO_BOOK:
                printf("Audio Book");
                break;
            case AVRCP_MP_PLAYER_SUBTYPE_PODCAST:
                printf("Podcast");
                break;
            default :
                printf("Reserved");
                break;
        }
        printf ("\n");

        printf("Play Status: ");
        switch(m[i].play_status)
        {
            case AVRCP_MP_PLAY_STATUS_STOPPED:
                printf("Stopped");
                break;
            case AVRCP_MP_PLAY_STATUS_PLAYING:
                printf("Playing");
                break;
            case AVRCP_MP_PLAY_STATUS_PAUSED:
                printf("Paused");
                break;
            case AVRCP_MP_PLAY_STATUS_FWD_SEEK:
                printf("Fwd Seek");
                break;
            case AVRCP_MP_PLAY_STATUS_REV_SEEK:
                printf("Rev Seek");
                break;
            case AVRCP_MP_PLAY_STATUS_ERROR:
                printf("Error");
                break;
            default:
                printf("Reserved");
                break;
        }
        printf ("\n");

        printf ("Feature Bit Mask: 0x%x%x%x%x\n", m[i].features_bit_mask[3U],
                m[i].features_bit_mask[2U], m[i].features_bit_mask[1U],
                m[i].features_bit_mask[0U]);
    }

    printf ("--- End of Player List ----\n\n");

    return;
}

API_RESULT appl_avrcp_ct_reset_virtual_folder_items (void)
{
    UCHAR    i;

    for (i = 0U; i < APPL_AVRCP_MAX_FOLDER_ITEMS; i++)
    {
        ct_vf_info[i].item_type = 0x00U;

        ct_vf_info[i].item_length = 0x00U;

        ct_vf_info[i].item_uid_msb = 0x00U;

        ct_vf_info[i].item_uid_msb = 0x00U;

        BT_mem_set
        (
            &ct_vf_info[i].folder_item_info,
            0x00U,
            sizeof(APPL_AVRCP_FOLDER_ITEM_TYPE_INFO)
        );

        ct_vf_info[i].media_item_info.media_type = 0x00U;
        ct_vf_info[i].media_item_info.char_set = 0x00U;
        ct_vf_info[i].media_item_info.name_len = 0x00U;

        BT_mem_set
        (
            ct_vf_info[i].media_item_info.name,
            0x00U,
            sizeof(ct_vf_info[i].media_item_info.name)
        );
        ct_vf_info[i].media_item_info.num_attr = 0x00U;

        BT_mem_set
        (
            ct_vf_info[i].media_item_info.attr_info,
            0x00U,
            (sizeof(APPL_AVRCP_MEDIA_ITEM_ATTR_INFO) * APPL_AVRCP_MAX_ATTR_COUNT)
        );
    }

    return API_SUCCESS;
}

void appl_avrcp_ct_handle_get_virtual_filesytem_rsp
     (
         UCHAR    *vf_info,
         UINT16    vf_param_len
     )
{
    UINT16      offset, i;
    UINT16      temp_len;
    UCHAR       item_type;

    BT_IGNORE_UNUSED_PARAM(vf_param_len);

    /* NULL check */
    if (NULL == vf_info)
    {
        printf ("NULL mp_list_info\n");
        /* return; */
    }
    else
    {
        /* Reset Virtual Folder Items */
        (BT_IGNORE_RETURN_VALUE) appl_avrcp_ct_reset_virtual_folder_items ();

        /* offset till UID counter */
        offset = 5U;

        /* Extract UID counter */
        avrcp_extract_2_byte_metadata_param
        (
            &vf_info[offset],
            &ct_folder_uid_counter
        );
        offset += 2U;

        printf ("    UID counter : 0x%04x\n", ct_folder_uid_counter);

        /* Extract  no. of items in rsp */
        avrcp_extract_2_byte_metadata_param
        (
            &vf_info[offset],
            &ct_folder_item_count
        );
        offset += 2U;

        printf ("    Folder Item Count : 0x%04x\n", ct_folder_item_count);

        for (i = 0U; i < ct_folder_item_count; i++)
        {
            /* ==== Extract Virtual Filesystem response params === */

            /* Item Type */
            item_type = vf_info[offset++];

            ct_vf_info[i].item_type = item_type;

            /* Extract Item legth */
            avrcp_extract_2_byte_metadata_param
            (
                &vf_info[offset],
                &ct_vf_info[i].item_length
            );
            offset += 2U;

            /* Extract UID */
            avrcp_extract_4_byte_metadata_param
            (
                &vf_info[offset],
                &ct_vf_info[i].item_uid_msb
            );
            offset += 4U;

            avrcp_extract_4_byte_metadata_param
            (
                &vf_info[offset],
                &ct_vf_info[i].item_uid_lsb
            );
            offset += 4U;

            temp_len = 0U;

            /**
             * Item_type can be either a Folder or Media Element
             */
            if (APPL_AVRCP_ITEM_TYPE_FOLDER == item_type)
            {
                /* Extract Folder Item parameters */
                temp_len = appl_avrcp_ct_unpack_folder_item_info
                           (
                               &vf_info[offset],
                               &ct_vf_info[i].folder_item_info
                           );
            }
            else if (APPL_AVRCP_ITEM_TYPE_MEDIA == item_type)
            {
                /* Extract Media Item parameters */
                temp_len = appl_avrcp_ct_unpack_media_element_item_info
                           (
                               &vf_info[offset],
                               &ct_vf_info[i].media_item_info
                           );
            }
            else
            {
                /* MISRA C-2012 Rule 15.7 */
            }

            offset += temp_len;
        }

        /* Display */
        (BT_IGNORE_RETURN_VALUE) appl_avrcp_ct_display_virtual_filesystem_items ();
    }

    return;
}

API_RESULT appl_avrcp_ct_unpack_folder_item_info
           (
               UCHAR *data,
               APPL_AVRCP_FOLDER_ITEM_TYPE_INFO *info
           )
{
    UINT16 offset;

    offset = 0U;

    /* Folder type */
    info->folder_type = data [offset++];

    /* is playable */
    info->is_playable = data [offset++];

    /* char set */
    avrcp_extract_2_byte_metadata_param
    (
        &data[offset],
        &info->char_set
    );
    offset += 2U;

    /* name len */
    avrcp_extract_2_byte_metadata_param
    (
        &data[offset],
        &info->name_len
    );
    offset += 2U;

    /* name */
    BT_mem_copy(info->name, &data[offset], info->name_len);

    offset += info->name_len;

    return offset;
}

API_RESULT appl_avrcp_ct_display_virtual_filesystem_items (void)
{
    API_RESULT      retval;
    UCHAR           i, j, k;

    retval = API_SUCCESS;

    /* printf folder items */
    for (i = 0U; i < ct_folder_item_count; i++)
    {
        printf ("---Item #%d ---\n", (i+1U));

        printf ("ITEM_TYPE: ");
        if (APPL_AVRCP_ITEM_TYPE_FOLDER == ct_vf_info[i].item_type)
        {
            printf ("Folder\n");

            /* Folder UID */
            printf ("FOLDER UID: ");
            printf ("0x%04x", ct_vf_info[i].item_uid_msb);
            printf ("%04x\n", ct_vf_info[i].item_uid_lsb);

            /* Folder type */
            printf ("TYPE: ");
            switch(ct_vf_info[i].folder_item_info.folder_type)
            {
                case AVRCP_VFS_FOLDER_TYPE_MIXED:
                    printf ("Mixed\n");
                    break;

                case AVRCP_VFS_FOLDER_TYPE_TITLES:
                    printf ("Titles\n");
                    break;

                case AVRCP_VFS_FOLDER_TYPE_ALBUMS:
                    printf ("Albums\n");
                    break;

                case AVRCP_VFS_FOLDER_TYPE_ARTISTS:
                    printf ("Artists\n");
                    break;

                case AVRCP_VFS_FOLDER_TYPE_GENRES:
                    printf ("Genres\n");
                    break;

                case AVRCP_VFS_FOLDER_TYPE_PLAYLISTS:
                    printf ("Playlists\n");
                    break;

                case AVRCP_VFS_FOLDER_TYPE_YEARS:
                    printf ("Years\n");
                    break;

                default:
                    printf ("Reserved\n");
                    break;
            }

            printf ("Is playable: ");
            if (0 != ct_vf_info[i].folder_item_info.is_playable)
            {
                printf ("Yes\n");
            }
            else
            {
                printf ("No\n");
            }

            printf ("Display Name Length:0x%x\n", ct_vf_info[i].folder_item_info.name_len);
            printf ("Display Name:");
            for (j = 0U; j < ct_vf_info[i].folder_item_info.name_len; j++)
            {
                printf ("%c", ct_vf_info[i].folder_item_info.name[j]);
            }
            printf ("\n");
        }
        else
        {
            printf ("Media Element Item\n");

            /* Media Element UID */
            printf ("MEDIA ELEMENT UID: ");
            printf ("0x%04x", ct_vf_info[i].item_uid_msb);
            printf ("%04x\n", ct_vf_info[i].item_uid_lsb);

             /* Media Element type */
            printf ("TYPE: ");
            switch(ct_vf_info[i].media_item_info.media_type)
            {
                case AVRCP_MEDIA_ELEMENT_TYPE_AUDIO:
                    printf ("Audio\n");
                    break;

                case AVRCP_MEDIA_ELEMENT_TYPE_VIDEO:
                    printf ("Video\n");
                    break;

                default:
                    printf ("Reserved\n");
                    break;
            }

            printf ("DISPLAY NAME: ");
            for (k = 0U; k < ct_vf_info[i].media_item_info.name_len; k++)
            {
                printf ("%c", ct_vf_info[i].media_item_info.name[k]);
            }
            printf ("\n");

            printf ("ATTRIBUTE COUNT: %d\n", ct_vf_info[i].media_item_info.num_attr);
            for (j = 0U; j < APPL_AVRCP_MAX_ATTR_COUNT; j++)
            {
                if (0x00U != ct_vf_info[i].media_item_info.attr_info[j].attr_id)
                {
                    printf ("    ID: 0x%x\n", ct_vf_info[i].media_item_info.attr_info[j].attr_id);
                    printf ("    VALUE: ");
                    for (k = 0U; k < ct_vf_info[i].media_item_info.attr_info[j].att_val_len; k++)
                    {
                        printf ("%c", ct_vf_info[i].media_item_info.attr_info[j].att_val[k]);
                    }
                    printf ("\n");
                }
            }
        }
    }

    return retval;
}

/* Unpacking the attributes of media elements */
API_RESULT appl_avrcp_ct_unpack_media_element_item_info
           (
               UCHAR *data,
               APPL_AVRCP_MEDIA_ELEMENT_ITEM_TYPE_INFO *info
           )
{
    UINT16      offset;
    UCHAR       j;
    UINT32      attr_id;
    UCHAR       attr_id_count;

    offset = 0U;

    /* Media type */
    info->media_type = data [offset++];

    /* char set */
    avrcp_extract_2_byte_metadata_param
    (
        &data [offset],
        &info->char_set
    );
    offset += 2U;

    /*  name length */
    avrcp_extract_2_byte_metadata_param
    (
        &data[offset],
        &info->name_len
    );
    offset += 2U;

    /* name */
    BT_mem_copy
    (
        info->name,
        &data[offset],
        info->name_len
    );

    offset += info->name_len;

    /* No. of Attributes */
    attr_id_count = data [offset++];

    info->num_attr = attr_id_count;

    for(j = 0U; j < attr_id_count; j++)
    {
        /* Attr ID */
        avrcp_extract_4_byte_metadata_param
        (
            &data [offset],
            &attr_id
        );
        offset += 4U;

        if ((attr_id >= AVRCP_MEDIA_ATTR_ID_MEDIA_TITLE) &&
#ifdef AVRCP_COVER_ART
            (attr_id <= AVRCP_MEDIA_ATTR_ID_DEFAULT_COVER_ART)
#else
            (attr_id <= AVRCP_MEDIA_ATTR_ID_PLAYING_TIME)
#endif /* AVRCP_COVER_ART */
            )
        {
            info->attr_info[attr_id-1U].attr_id = attr_id;

            /* Char set */
            avrcp_extract_2_byte_metadata_param
            (
                &data[offset],
                &info->attr_info[attr_id-1U].char_set
            );
            offset += 2U;

            /* value length */
            avrcp_extract_2_byte_metadata_param
            (
                &data [offset],
                &info->attr_info[attr_id-1U].att_val_len
            );
            offset += 2U;

            /* value */
            BT_mem_copy
            (
                info->attr_info[attr_id-1U].att_val,
                &data[offset],
                info->attr_info[attr_id-1U].att_val_len
            );

            offset += info->attr_info[attr_id-1U].att_val_len;
        }
    }

    return offset;
}

void appl_avrcp_ct_reset_media_element_list (void)
{
    UCHAR   i;

    ct_media_list_uid_counter = 0x00U;
    ct_media_list_count       = 0x00U;

    for (i = 0U; i < APPL_AVRCP_MAX_MEDIA_LIST_COUNT; i++)
    {
        ct_media_list_info[i].item_type    = 0x00U;
        ct_media_list_info[i].item_length  = 0x00U;
        ct_media_list_info[i].item_uid_msb = 0x00U;
        ct_media_list_info[i].item_uid_lsb = 0x00U;

        BT_mem_set
        (
            &ct_media_list_info[i].media_item_info,
            0x00U,
            (sizeof(APPL_AVRCP_MEDIA_ELEMENT_ITEM_TYPE_INFO))
        );
    }

    return;
}

void appl_avrcp_ct_handle_get_media_element_list_rsp
     (
         UCHAR    *media_list_data,
         UINT16    media_list_data_len
     )
{
    UINT16      offset, i;
    UINT16      temp_len;

    BT_IGNORE_UNUSED_PARAM(media_list_data_len);

    /* NULL check */
    if (NULL == media_list_data)
    {
        printf ("NULL media_list_data\n");
        /* return; */
    }
    else
    {
        /* Reset ct_media_list_info */
        appl_avrcp_ct_reset_media_element_list ();

        /* offset till UID counter */
        offset = 5U;

        /* Extract UID counter */
        avrcp_extract_2_byte_metadata_param
        (
            &media_list_data[offset],
            &ct_media_list_uid_counter
        );
        offset += 2U;

        printf ("    UID counter : 0x%04x\n", ct_media_list_uid_counter);

        /* Extract Media Element Count */
        avrcp_extract_2_byte_metadata_param
        (
            &media_list_data[offset],
            &ct_media_list_count
        );
        offset += 2U;

        printf ("    Media Items Count : 0x%04x\n", ct_media_list_count);

        for (i = 0U; i < ct_media_list_count; i++)
        {
            /* ==== Extract Media Eelement params === */

            /* Item Type */
            ct_media_list_info[i].item_type = media_list_data[offset++];

            /* Item Length */
            avrcp_extract_2_byte_metadata_param
            (
                &media_list_data[offset],
                &ct_media_list_info[i].item_length
            );
            offset += 2U;

            /* UID */
            avrcp_extract_4_byte_metadata_param
            (
                &media_list_data[offset],
                &ct_media_list_info[i].item_uid_msb
            );
            offset += 4U;

            avrcp_extract_4_byte_metadata_param
            (
                &media_list_data[offset],
                &ct_media_list_info[i].item_uid_lsb
            );
            offset += 4U;

            /* Extract Media Element Attributes */
            temp_len = 0U;
            temp_len = appl_avrcp_ct_unpack_media_element_item_info
                       (
                           &media_list_data[offset],
                           &ct_media_list_info[i].media_item_info
                       );

            offset += temp_len;
        }

        /* Display */
        (BT_IGNORE_RETURN_VALUE) appl_avrcp_ct_display_media_element_list ();
    }

    return;
}

API_RESULT appl_avrcp_ct_display_media_element_list (void)
{
    API_RESULT      retval;
    UCHAR           i, j, k;

    retval = API_SUCCESS;

    /* Print Media Element List */
    for (i = 0U; i < ct_media_list_count; i++)
    {
        printf ("---Media Element Item #%d ---\n", (i+1U));

        printf ("ITEM_TYPE: ");
        if (APPL_AVRCP_ITEM_TYPE_MEDIA == ct_media_list_info[i].item_type)
        {
            printf ("Media Element Item\n");

            /* Media Element UID */
            printf ("MEDIA ELEMENT UID: ");
            printf ("0x%08x", ct_media_list_info[i].item_uid_msb);
            printf ("%08x\n", ct_media_list_info[i].item_uid_lsb);

             /* Media Element type */
            printf ("TYPE: ");
            switch(ct_media_list_info[i].media_item_info.media_type)
            {
                case AVRCP_MEDIA_ELEMENT_TYPE_AUDIO:
                    printf ("Audio\n");
                    break;

                case AVRCP_MEDIA_ELEMENT_TYPE_VIDEO:
                    printf ("Video\n");
                    break;

                default:
                    printf ("Reserved\n");
                    break;
            }

            printf ("DISPLAY NAME: \n");
            for (k = 0U; k < ct_media_list_info[i].media_item_info.name_len; k++)
            {
                printf ("%c", ct_media_list_info[i].media_item_info.name[k]);
            }
            printf ("\n");

            printf ("ATTRIBUTE COUNT: %d\n", ct_media_list_info[i].media_item_info.num_attr);
            for (j = 0U; j < APPL_AVRCP_MAX_ATTR_COUNT; j++)
            {
                if (0x00U != ct_media_list_info[i].media_item_info.attr_info[j].attr_id)
                {
                    printf ("    ID: 0x%x\n", ct_media_list_info[i].media_item_info.attr_info[j].attr_id);

                    printf ("    VALUE: ");
                    for (k = 0U; k < ct_media_list_info[i].media_item_info.attr_info[j].att_val_len; k++)
                    {
                        printf ("%c", ct_media_list_info[i].media_item_info.attr_info[j].att_val[k]);
                    }
                    printf ("\n");
                }
            }
        }
        else
        {
            printf ("???\n");
        }
    }

    return retval;
}

void appl_avrcp_ct_handle_set_brow_player_rsp
     (
            AVRCP_AL_BROW_RSP_INFO  *brow_rsp_info
     )
{
    UCHAR  * rsp_info;
    UINT16   offset, char_set, uid_counter;
    UINT32   num_items;

    if (NULL == brow_rsp_info)
    {
        printf ("NULL brow_rsp_info\n");
        /* return; */
    }
    else
    {
        rsp_info        = (UCHAR *)brow_rsp_info->param_info;

        printf ("    PDU ID - Set Browsed Player(0x%x).\n", brow_rsp_info->pdu_id);

        /* offset till status */
        offset = 4U;
        printf ("    Status : ");
        if (AVRCP_METADATA_ERROR_OPERATION_SUCCESSFUL == rsp_info[offset++])
        {
            printf ("Operation Completed Without error\n");
        }

        /* Extract UID counter */
        avrcp_extract_2_byte_metadata_param
        (
            &rsp_info[offset],
            &uid_counter
        );
        offset += 2U;

        /* Extract no. of items in current folder */
        avrcp_extract_4_byte_metadata_param
        (
            &rsp_info[offset],
            &num_items
        );
        offset += 4U;

        /* Extract char set */
        avrcp_extract_2_byte_metadata_param
        (
            &rsp_info[offset],
            &char_set
        );
        offset += 2U;

        printf ("     - UID counter : 0x%04x\n", uid_counter);
        printf ("     - No. of Items: %d\n", num_items);
        printf ("     - Char Set    : 0x%04x\n", char_set);
        printf ("     - Folder Depth: %d\n", rsp_info[offset]);
    }

    return;
}

void appl_avrcp_ct_handle_get_item_attributes_rsp
     (
            AVRCP_AL_BROW_RSP_INFO  *brow_rsp_info
     )
{
    UCHAR   *rsp_info;
    UCHAR    num_attrs;
    UINT32   attr_id;
    UCHAR    i, j;
    UINT16   attr_len, offset;
    UCHAR    attr_val[64U];

    if (NULL == brow_rsp_info)
    {
        printf ("NULL brow_rsp_info\n");
        /* return; */
    }
    else
    {
        rsp_info        = (UCHAR *)brow_rsp_info->param_info;

        printf ("\n");
        printf ("    PDU ID - Get Item Atrributes(0x%x).\n", brow_rsp_info->pdu_id);

        /* offset till status */
        offset = 4U;
        printf ("    Status : ");
        if (AVRCP_METADATA_ERROR_OPERATION_SUCCESSFUL == rsp_info[offset++])
        {
            printf ("Operation Completed Without error\n");
        }

        /* No. of attributes */
        num_attrs = rsp_info[offset++];

        printf ("    No. of Attributes: %d\n", num_attrs);

        for (i = 0U; i < num_attrs; i++)
        {
            /* Attribute ID */
            avrcp_extract_4_byte_metadata_param
            (
                &rsp_info[offset],
                &attr_id
            );
            offset += 4U;

            /* Ignore char set */
            offset += 2U;

            /* Attribute value length */
            avrcp_extract_2_byte_metadata_param
            (
                &rsp_info[offset],
                &attr_len
            );
            offset += 2U;

            /* Attribute Value */
            BT_mem_copy (attr_val, &rsp_info[offset], attr_len);

            offset += attr_len;

            printf ("    - Attr-ID  : %d\n", attr_id);
            printf ("    - Attr-Val : ");
            for (j = 0U; j < attr_len; j++)
            {
                printf ("%c", attr_val[j]);
            }
            printf ("\n");
        }
    }

    return;
}

void appl_avrcp_ct_print_error (UCHAR status_code)
{
    switch(status_code)
    {
        case AVRCP_METADATA_ERROR_INVALID_COMMAND:
            printf("*** Error: Invalid Command\n");
            break;
        case AVRCP_METADATA_ERROR_INVALID_PARAMETER:
            printf("*** Error: Invalid parameter\n");
            break;
        case AVRCP_METADATA_ERROR_PARAMETER_NOT_FOUND:
            printf("*** Error: Parameter not found\n");
            break;
        case AVRCP_METADATA_ERROR_INTERNAL:
            printf("*** Error: Internal Error\n");
            break;
        case AVRCP_METADATA_ERROR_UID_CHANGED:
            printf("*** Error: UID Changed\n");
            break;
#ifdef AVRCP_1_4
        case AVRCP_BOW_ERROR_INVALID_DIRECTION:
            printf("*** Error: Invalid direction\n");
            break;
        case AVRCP_BOW_ERROR_NOT_A_DIRECTORY:
            printf("*** Error: Not a directory\n");
            break;
        case AVRCP_BOW_ERROR_DOES_NOT_EXIST:
            printf("*** Error: Item doesnot exist\n");
            break;
        case AVRCP_BOW_ERROR_INVALID_SCOPE:
            printf("*** Error: Invalid scope\n");
            break;
        case AVRCP_BOW_ERROR_RANGE_OUT_OF_BOUNDS:
            printf("*** Error: Range out of bounds\n");
            break;
        case AVRCP_BOW_ERROR_DIRECTORY_NOT_HANDLED:
            printf("*** Error: Directory not handled\n");
            break;
        case AVRCP_BOW_ERROR_MEDIA_IN_USE:
            printf("*** Error: Media in use\n");
            break;
        case AVRCP_BOW_ERROR_NOW_PLAYING_LIST_FULL:
            printf("*** Error: Now playing list full\n");
            break;
        case AVRCP_BOW_ERROR_SEARCH_NOT_SUPPORTED:
            printf("*** Error: Search not supported\n");
            break;
        case AVRCP_BOW_ERROR_SEARCH_IN_PROGRESS:
            printf("*** Error: Search in progress\n");
            break;
        case AVRCP_BOW_ERROR_INVALID_PLAYER_ID:
            printf("*** Error: Invalid player id\n");
            break;
        case AVRCP_BOW_ERROR_PLAYER_NOT_BROWSABLE:
            printf("*** Error: Player not browsable\n");
            break;
        case AVRCP_BOW_ERROR_PLAYER_NOT_ADDRESSED:
            printf("*** Error: Player not addressed\n");
            break;
        case AVRCP_BOW_ERROR_NO_VALID_SEARCH_RESULTS:
            printf("*** Error: No valid search results\n");
            break;
        case AVRCP_BOW_ERROR_NO_AVAILABLE_PLAYERS:
            printf("*** Error: No Available Players\n");
            break;
        case AVRCP_BOW_ERROR_ADDR_PLAYER_CHANGED:
            printf("*** Error: Address Player Changed\n");
            break;
#endif /* AVRCP_1_4 */
        default:
            printf("This should not happen!\n");
            break;
    }
}

#ifdef AVRCP_COVER_ART_INITIATOR
void appl_avrcp_cai_operation(void)
{
    int read_val, menu_read_val;
    UCHAR index;
    UINT16 size;
    API_RESULT retval;

    /* AVRCP_CA_HANDLE ca_handle; */
    AVRCP_CA_CONNECT_STRUCT ca_connect_info;
    AVRCP_CA_HEADER_STRUCT  ca_img_handle_info;
    AVRCP_CA_HEADER_STRUCT  ca_img_descriptor_info;
    AVRCP_CA_REQUEST_STRUCT ca_req_info;
    UCHAR image_handle[16U];
    UINT16 image_handle_len;

    BT_LOOP_FOREVER()
    {
        printf ("%s\n", avrcp_cai_menu);
        printf ("Enter the choice:");
        fflush (stdout);

        scanf ("%d", &read_val);
        menu_read_val = read_val;

        printf ("--%d--\n", read_val);

        /* Switch on the choice */
        switch (read_val)
        {
            case 0:
                break; /*  return; */

            case 1:
                break;

            case 12: /* SDP Query */

                /**
                 * SDP Query Should be done only after the Previously Initiated
                 * ACL Connection Completes Successfully.
                 *
                 * Start SDP Query to Find out if the Peer Device is running PBAP
                 * Service and if so on which Server Channel the Remote PBAP PSE
                 * is Listening to.
                 *
                 * In this Non-Blocking Implemenation, the whole process of
                 * Performing SDP Query is boot-starped by first establishing
                 * an SDP Connection with the Peer.
                 *
                 * At the time of Requesting SDP to Establish a Connection, the
                 * Application also Registers a Callback function with SDP, using
                 * that Callback function SDP Module will keep indicating
                 * Asynchronous SDP events to the Application.
                 *
                 * The Application Callback for SDP is the Third argument of
                 * the SDP_SET_HANDLE() Macro.
                 */

                printf("Querying Remote Device 0x%02X:%02X:%02X:%02X:%02X:%02X\n",
                       appl_avrcp_bd_addr[0U], appl_avrcp_bd_addr[1U],
                       appl_avrcp_bd_addr[2U], appl_avrcp_bd_addr[3U],
                       appl_avrcp_bd_addr[4U], appl_avrcp_bd_addr[5U]);


                SDP_SET_HANDLE
                (
                    avrcp_sdp_handle,
                    appl_avrcp_bd_addr,
                    appl_avrcp_cai_sdp_callback
                );

                retval = BT_sdp_open(&avrcp_sdp_handle);

                if ( retval != API_SUCCESS )
                {
                    printf("SDP Connect FAILED !! Error Code = 0x%04X\n", retval);
                }

                printf("Please Wait for SDP Operation to Complete\n");

            break;

            case 15:

                appl_avrcp_choose_handle(&index);

                /* BD Address */
                ca_connect_info.bd_addr = appl_avrcp_handle[index].bd_addr;

                /* For Cover Art feature, OBEX tranport is over L2CAP */
#ifdef OBEX_OVER_L2CAP

                printf ("Enter Remote PSM(in Hex): ");
                scanf ("%x", &read_val);
                ca_connect_info.l2cap_rpsm = (UINT16)read_val;
                fflush(stdin);

                printf ("Enter Data Exchange Size: ");
                scanf ("%d", &read_val);
                size = (UINT16) read_val;
                ca_connect_info.max_recv_size = size;

#else
                printf ("Please enable OBEX_OVER_L2CAP flag. \n");

#endif /* OBEX_OVER_L2CAP */

                printf ("Connecting AVRCP_CT Cover Art ......\n");

                retval = BT_avrcp_cai_connect
                         (
                             &appl_avrcp_ct_ca_handles[index],
                             &ca_connect_info
                         );

                printf ("Retval - 0x%04X\n", retval);

                break;

            case 16:
                appl_avrcp_choose_handle(&index);

                printf ("Disconnecting AVRCP_CT Cover Art ......\n");
                retval = BT_avrcp_cai_disconnect
                         (
                            &appl_avrcp_ct_ca_handles[index]
                         );
                printf ("Retval - 0x%04X\n", retval);

                break;

            case 20: /* Get Image Properities */

                appl_avrcp_choose_handle(&index);

                BT_mem_set(&ca_req_info, 0, sizeof(AVRCP_CA_REQUEST_STRUCT));

                printf ("Enter Image Handle\n");
                scanf("%s", image_handle);

                image_handle_len = (UINT16)(BT_str_len(image_handle) + 1U);

                printf ("Image Handle: %s\n", image_handle);

                printf("Enter number of wait stages: ");
                scanf("%d", &read_val);
                wait_count = (UCHAR )read_val;

                if (0U < wait_count)
                {
                    ca_req_info.wait = BT_TRUE;
                    wait_count--;
                }
                else
                {
                    ca_req_info.wait = BT_FALSE;
                }

                ca_req_info.img_handle = &ca_img_handle_info;

                ca_img_handle_info.value = image_handle;
                ca_img_handle_info.length = image_handle_len;

                printf ("Sending AVRCP_CT Cover Art Get Image  Properties..\n");
                retval = BT_avrcp_cai_get_image_properties
                         (
                             &appl_avrcp_ct_ca_handles[index],
                             &ca_req_info
                         );
                printf ("Retval - 0x%04X\n", retval);

                break;

            case 21: /* Get Image */

                appl_avrcp_choose_handle(&index);

                BT_mem_set(&ca_req_info, 0, sizeof(AVRCP_CA_REQUEST_STRUCT));

                /* Update headers in the request */
                ca_req_info.img_handle     = &ca_img_handle_info;
                ca_req_info.img_descriptor = &ca_img_descriptor_info;

                printf ("Enter Image Handle\n");
                scanf("%s", image_handle);

                image_handle_len = (UINT16)(BT_str_len(image_handle) + 1U);

                printf("Image Handle: %s\n", image_handle);

                printf("Enter number of wait stages: ");
                scanf("%d", &read_val);
                wait_count = (UCHAR )read_val;

                if (0U < wait_count)
                {
                    ca_req_info.wait = BT_TRUE;
                    wait_count--;
                }
                else
                {
                    ca_req_info.wait = BT_FALSE;
                }

                /* Image Handle */
                ca_img_handle_info.value = image_handle;
                ca_img_handle_info.length = image_handle_len;

                /**
                 * Constructing Image Descriptor Object based on the image
                 * information given by the user
                 */

                {
                    UCHAR *img_format;
                    UINT16 img_width;
                    UINT16 img_height;

                    /* Set to default Cover Art Format */
                    img_desc.format = COVER_ART_FORMAT_JPEG;
                    img_desc.img_width = 0U;
                    img_desc.img_height = 0U;
                    BT_mem_set(image_descriptor_data, 0, sizeof(image_descriptor_data));

                    printf ("Select Cover Art Descriptor Format:\n");
                    printf ("0 -> For Default(with pixel attr. range)\n");
                    printf ("1 -> For Other (take pixel attr. from the user)\n");
                    scanf ("%d", &read_val);

                    if (0U != read_val)
                    {
                        /* Get the Image format from user */
                        printf ("Enter Image Format\n");
                        printf ("\t1 -> JPEG\n");
                        printf ("\t2 -> GIF\n:");
                        scanf ("%d", &read_val);

                        if (COVER_ART_FORMAT_JPEG == read_val)
                        {
                            img_format = (UCHAR *)"JPEG";
                        }
                        else if (COVER_ART_FORMAT_GIF == read_val)
                        {
                            img_format = (UCHAR *)"GIF";
                        }
                        else
                        {
                            printf("Invalid Input...\n");
                            break;
                        }

                        img_desc.format = (UCHAR )read_val;

                        /* Get Image Width */
                        printf ("Enter Image Width:");
                        scanf ("%d", &read_val);
                        img_width = (UINT16 )read_val;
                        img_desc.img_width = (UINT16 )read_val;

                        /* Get Image Length */
                        printf ("Enter Image Height:");
                        scanf ("%d", &read_val);
                        img_height = (UINT16 )read_val;
                        img_desc.img_height = (UINT16 )read_val;

                        /* Form image descriptor object with the given parameters */
                        BT_str_print((CHAR *)image_descriptor_data,
                                      "<image-descriptor version=\"1.0\" > \n"
                                      "<image encoding = \"%s\" "
                                      "pixel = \"%d*%d\" /> \n"
                                      "</image-descriptor>",
                                      img_format, img_width, img_height);
                    }
                    else
                    {
                        EM_str_copy
                        (
                            image_descriptor_data,
                            IMAGE_DESCRIPTOR_DEFAULT
                        );
                    }
                }

                /* Initialze the image descriptor handle */
                ca_img_descriptor_info.value = image_descriptor_data;
                ca_img_descriptor_info.length = (UINT16)BT_str_len(image_descriptor_data);;

                printf ("Sending AVRCP_CT Cover Art Get Image..\n");

                retval = BT_avrcp_cai_get_image
                         (
                            &appl_avrcp_ct_ca_handles[index],
                            &ca_req_info
                         );

                printf ("Retval - 0x%04X\n", retval);

                break;

            case 22: /* Get LinkedThumbnail */

                appl_avrcp_choose_handle(&index);

                BT_mem_set(&ca_req_info, 0, sizeof(AVRCP_CA_REQUEST_STRUCT));

                printf ("Enter Image Handle\n");
                scanf("%s", image_handle);

                image_handle_len = (UINT16)(BT_str_len(image_handle) + 1U);

                printf("Image Handle: %s\n", image_handle);

                printf("Enter number of wait stages: ");
                scanf("%d", &read_val);
                wait_count = (UCHAR )read_val;

                if (0U < wait_count)
                {
                    ca_req_info.wait = BT_TRUE;
                    wait_count--;
                }
                else
                {
                    ca_req_info.wait = BT_FALSE;
                }

                ca_img_handle_info.value = image_handle;
                ca_img_handle_info.length = image_handle_len;

                ca_req_info.img_handle = &ca_img_handle_info;

                printf ("Sending AVRCP_CT Cover Art Get LinkedThumbNail..\n");
                retval = BT_avrcp_cai_get_linked_thumbnail
                         (
                             &appl_avrcp_ct_ca_handles[index],
                             &ca_req_info
                         );
                printf ("Retval - 0x%04X\n", retval);

                break;

            case 30:
                appl_avrcp_choose_handle(&index);

                printf ("Sending AVRCP_CT Cover Art Transport Close..\n");
                retval = BT_avrcp_cai_transport_close
                         (
                             &appl_avrcp_ct_ca_handles[index]
                         );
                printf ("Retval - 0x%04X\n", retval);

                break;

            default:

                printf ("Invalid choice\n");
                fflush (stdout);
                break;
        }

        if (0 == menu_read_val)
        {
            /* return */
            break;
        }
    }
}

/**
 * Callback Function Registered with SDP,
 * Using SDP_SET_HANDLE() and BT_sdp_open ()
 */

void appl_avrcp_cai_sdp_callback
     (
         UCHAR command,
         UCHAR * data,
         UINT16 length,
         UINT16 status
     )
{
    static UCHAR avrcp_attrib_data[250U];
    UINT16 avrcp_len_attrib_data = 250U;

    S_UUID uuid[3U];
    UINT16 num_uuid;
    UINT16 attrib_id[5U], num_attrib_id;

    UCHAR * sdp_query_result;

    API_RESULT retval;

    BT_IGNORE_UNUSED_PARAM(length);

    /*
     * Frame the SDP Search pattern with following UUIDs
     * - AVRCP_TARGET_UUID
     * - OBEX_UUID
     * - L2CAP_UUID
     * and only one Attribute ID "PROTOCOL_DESC_LIST"
     * (For getting the RFCOMM Server Channel on which Peer PBAP Service
     *  is Listening)
     *
     */
    uuid[0U].uuid_type = UUID_16;
    uuid[0U].uuid_union.uuid_16 =  AVRCP_TARGET_UUID;
    num_uuid = 1U;

     num_attrib_id = 0U;

    /* In ascending order */
    attrib_id[num_attrib_id++] = SERVICE_CLASS_ID_LIST;
    attrib_id[num_attrib_id++] = PROTOCOL_DESC_LIST;
    attrib_id[num_attrib_id++] = BLUETOOTH_PROFILE_DESC_LIST;
    attrib_id[num_attrib_id++] = ADDITIONAL_PROT_DESC_LIST_ID;
    attrib_id[num_attrib_id++] = SUPPORTED_FEATURES_ATTR_ID;

    switch(command)
    {
    case SDP_Open:
        if(status != API_SUCCESS)
        {
            printf("SDP OPEN FAILED!\n");
            break;
        }

        printf("SDP OPEN\n\n");

        printf("Initiating SDP Service Attribute Request ....\n");
        retval = BT_sdp_servicesearchattributerequest
                 (
                     &avrcp_sdp_handle,
                     uuid,
                     num_uuid,
                     attrib_id,
                     num_attrib_id,
                     NULL,
                     0U,
                     avrcp_attrib_data,
                     &avrcp_len_attrib_data
                 );

        if(API_SUCCESS != retval)
        {
            printf("SDP SEARCH Failed for AVRCP..Closing SDP\n");
            (BT_IGNORE_RETURN_VALUE) BT_sdp_close(&avrcp_sdp_handle);
        }
        break;

    case SDP_Close:
        printf("SDP CLOSE\n\n");
        break;

    case SDP_ErrorResponse:
        printf("SDP ERROR RESPONSE\n\n");
        break;

    case SDP_ServiceSearchAttributeResponse:
        printf("\n");
        {
            UINT16 avrcp_ca_psm = 0x0000U;
            UINT16 avrcp_peer_supp_feat;
            UINT16 peer_supp_features_len = sizeof(UINT16);

            sdp_query_result = data;

            /* Get Peer Supported Features */
            printf ("Getting Peer Supported Features..\n");
            retval = BT_sdp_get_attr_value
                     (
                         SUPPORTED_FEATURES_ATTR_ID,
                         sdp_query_result,
                         (UCHAR *)&avrcp_peer_supp_feat,
                         &peer_supp_features_len
                     );
            if (API_SUCCESS != retval)
            {
                printf ("Failed - 0x%04X\n", retval);
            }
            else
            {
                printf ("Successs\n");

                printf ("Peer AVRCP Supported Features 0x%04X\n", avrcp_peer_supp_feat);

                /* Check if peer supports Cover Art */
                if (0U != (0x0100U & avrcp_peer_supp_feat))
                {
                    /* Yes, Extract L2CAP psm for Cover Art Connection */
                    retval = BT_sdp_get_additional_psm_with_index
                             (
                                 sdp_query_result,
                                 &avrcp_ca_psm,
                                 0x01U
                             );
                    if (API_SUCCESS == retval)
                    {
                        printf ("AVRCP Cover Art PSM: 0x%04X\n", avrcp_ca_psm);
                    }
                    else
                    {
                        printf ("Failed: BT_sdp_get_additional_psm_with_index(0x01), retval: 0x%04X\n", retval);
                    }
                }
                else
                {
                    printf ("Peer Does NOT support Cover Art\n");
                }
            }
        }

        /* Now Close the SDP Connection */
        (BT_IGNORE_RETURN_VALUE) BT_sdp_close(&avrcp_sdp_handle);
        break;

    default: /* Events not needed to be Handled */
        printf("Unhandled SDP Event (0x%02X)\n", command);
        break;
    }/* switch */

    return;
}


API_RESULT appl_avrcp_cai_callback
           (
               AVRCP_CA_HANDLE    * avrcp_ca_handle,
               UINT8                event_type,
               UINT16               event_result,
               AVRCP_CA_HEADERS   * avrcp_ca_headers,
               UINT16               num_headers
           )
{
    AVRCP_CA_HANDLE handle;
    AVRCP_CA_HEADERS *ca_event_headers;
    AVRCP_CA_REQUEST_STRUCT req_info;
    UCHAR send_request;
    UINT16 actual;
    API_RESULT retval;

    BT_IGNORE_UNUSED_PARAM(num_headers);

    /* Init */
    handle           = *avrcp_ca_handle;
    ca_event_headers = avrcp_ca_headers;
    send_request     = 0U;
    retval           = API_SUCCESS;
    BT_mem_set(&req_info, 0, sizeof(AVRCP_CA_REQUEST_STRUCT));

    switch(event_type)
    {
    case AVRCP_CAI_TRANSPORT_CLOSE_CNF: /* Fall Through */
    case AVRCP_CAI_TRANSPORT_CLOSE_IND:
        printf ("Recvd %s  - %04X\n", (event_type == AVRCP_CAI_TRANSPORT_CLOSE_CNF) ?
        "AVRCP_CAI_TRANSPORT_CLOSE_CNF":"AVRCP_CAI_TRANSPORT_CLOSE_IND", event_result);
        printf ("AVRCP-CT Cover Art Handle - 0x%02X\n", handle);

        break;

    case AVRCP_CAI_CONNECT_CNF:
        printf ("Recvd AVRCP_CAI_CONNECT_CNF - %04X\n", event_result);
        printf ("AVRCP-CT Cover Art Handle - 0x%02X\n", handle);

        printf("Peer Address " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (ca_event_headers->ca_connect_info->bd_addr));

        printf ("MAX Exchange Size: %d\n",
            ca_event_headers->ca_connect_info->max_recv_size);

        cover_art_xchg_size = ca_event_headers->ca_connect_info->max_recv_size;

        break;

    case AVRCP_CAI_DISCONNECT_CNF:
        printf ("Recvd AVRCP_CAI_DISCONNECT_CNF - 0x%04X\n", event_result);
        printf ("AVRCP-CT Cover Art Handle - 0x%02X\n", handle);

        break;

    case AVRCP_CAI_GET_IMAGE_PROPERTIES_CNF:
        printf ("Recvd AVRCP_CAI_GET_IMAGE_PROPERTIES_CNF - 0x%04X\n",
            event_result);
        printf ("AVRCP-CT Cover Art Handle - 0x%02X\n", handle);

        if ((AVRCP_CA_SUCCESS_RSP != event_result) &&
            (AVRCP_CA_CONTINUE_RSP != event_result))
        {
            break;
        }

        if (AVRCP_CA_CONTINUE_RSP == event_result)
        {
            send_request = 1U;
        }

        /* Get Body content -Image Properties */
        if ((NULL == ca_event_headers->ca_rsp_info->body->value) ||
            (0U    == ca_event_headers->ca_rsp_info->body->length))
        {
            printf ("No Body Content found\n");
        }
        else
        {
            UINT16 length, i;
            UCHAR * data;

            data = ca_event_headers->ca_rsp_info->body->value;
            length = ca_event_headers->ca_rsp_info->body->length;

            /* Print the stream */
            printf ("\n========== Cover Art Get Image Properites ==========\n");
            for (i = 0U; i < length; i++)
            {
                printf ("%c", data[i]);
            }
            printf ("\n======================================\n");

#ifdef HAVE_OBJECT_DUMP

            /* Open file to dump raw message */
            if (NULL == ca_img_prop_fp)
            {
                img_prop_recv_count++;
                BT_str_print((CHAR *)cover_art_file_name, "ca_ct_image_properties_%d.txt", img_prop_recv_count);

                /* MISRA C-2012 Rule 17.7 | Coverity CHECKED_RETURN */
                (void)BT_vfops_create_object_name
                (
                    (UCHAR *)APPL_AVRCP_CT_BASE_FOLDER,
                    cover_art_file_name,
                    avrcp_ct_file_object
                );

                /* ca_img_prop_fp = fopen ((CHAR *)cover_art_file_name, "wb"); */
                retval = BT_fops_file_open(avrcp_ct_file_object, (UCHAR *)"wb", &ca_img_prop_fp);

                if (NULL != ca_img_prop_fp)
                {
                    printf("%s file open success\n", avrcp_ct_file_object);
                }
            }

            /* Dump the raw message */
            if (NULL != ca_img_prop_fp)
            {
                /* fwrite (data, length, 1, ca_img_prop_fp); */
                (BT_IGNORE_RETURN_VALUE) BT_fops_file_write(data, length, ca_img_prop_fp, &actual);
            }

            if (AVRCP_CA_SUCCESS_RSP == event_result)
            {
                /* MISRA C-2012 Rule 17.7 | Coverity CHECKED_RETURN */
                (void)BT_fops_file_close(ca_img_prop_fp);
                ca_img_prop_fp = NULL;
            }

#endif /* HAVE_OBJECT_DUMP */
        }

        break;

    case AVRCP_CAI_GET_IMAGE_CNF:
        printf ("Recvd AVRCP_CAI_GET_IMAGE_CNF - 0x%04X\n", event_result);
        printf ("AVRCP-CT Cover Art Handle - 0x%02X\n", handle);

        if ((AVRCP_CA_SUCCESS_RSP != event_result) &&
            (AVRCP_CA_CONTINUE_RSP != event_result))
        {
            break;
        }

        if (AVRCP_CA_CONTINUE_RSP == event_result)
        {
            send_request = 1U;
        }

        /* Get Body content -Image ThumbNail */
        if ((NULL == ca_event_headers->ca_rsp_info->body->value) ||
            (0U    == ca_event_headers->ca_rsp_info->body->length))
        {
            printf ("No Body Content found\n");
        }
        else
        {
            UINT16 length;
            UCHAR * data;

            data = ca_event_headers->ca_rsp_info->body->value;
            length = ca_event_headers->ca_rsp_info->body->length;

#ifdef STREAM_PRINT
            /* Print the stream */
            printf ("\n========== Cover Art Get Image ==========\n");
            for (i = 0U; i < length; i++)
            {
                printf ("%c", data[i]);
            }
            printf ("\n======================================\n");
#endif /* 0 */

#ifdef HAVE_OBJECT_DUMP

            /* Open file to dump raw message */
            if (NULL == ca_image_fp)
            {
                UCHAR *format;

                img_recv_count++;

                format =  (UCHAR *)"jpg";
                if (img_desc.format == COVER_ART_FORMAT_GIF)
                {
                    format = (UCHAR *)"gif";
                }

                BT_str_print((CHAR *)cover_art_file_name, "ca_ct_img_%dx%d_%d.%s",
                    img_desc.img_width, img_desc.img_height,
                    img_recv_count, format);

                /* MISRA C-2012 Rule 17.7 | Coverity CHECKED_RETURN */
                (void)BT_vfops_create_object_name
                (
                    (UCHAR *)APPL_AVRCP_CT_BASE_FOLDER,
                    cover_art_file_name,
                    avrcp_ct_file_object
                );

                /* ca_image_fp = fopen ((CHAR *)cover_art_file_name, "wb"); */
                retval = BT_fops_file_open(avrcp_ct_file_object, (UCHAR *)"wb", &ca_image_fp);

                if (NULL != ca_image_fp)
                {
                    printf("%s file open success\n", avrcp_ct_file_object);
                }
            }

            /* Dump the image file message */
            if (NULL != ca_image_fp)
            {
                /* fwrite (data, length, 1, ca_image_fp); */
                (BT_IGNORE_RETURN_VALUE) BT_fops_file_write(data, length, ca_image_fp, &actual);
            }

            if (AVRCP_CA_SUCCESS_RSP == event_result)
            {
                /* MISRA C-2012 Rule 17.7 | Coverity CHECKED_RETURN */
                (void)BT_fops_file_close(ca_image_fp);
                ca_image_fp = NULL;
            }

#endif /* HAVE_OBJECT_DUMP */
        }

        /* Get Image size */
        if ((NULL != ca_event_headers->ca_rsp_info->length->value) &&
            (0U    != ca_event_headers->ca_rsp_info->length->length))
        {
            UINT32 imag_len = 0U;

            imag_len = ca_event_headers->ca_rsp_info->length->value[3U];
            imag_len = (imag_len << 8U)| ca_event_headers->ca_rsp_info->length->value[2U];
            imag_len = (imag_len << 8U)| ca_event_headers->ca_rsp_info->length->value[1U];
            imag_len = (imag_len << 8U)| ca_event_headers->ca_rsp_info->length->value[0U];

            printf("Length of the Image: 0x%08x\n", imag_len);
        }

        break;

    case AVRCP_CAI_GET_LINKED_THUMBNAIL_CNF:
        printf ("Recvd AVRCP_CAI_GET_LINKED_THUMBNAIL_CNF - 0x%04X\n",
                event_result);
        printf ("AVRCP-CT Cover Art Handle - 0x%02X\n", handle);

        if ((AVRCP_CA_SUCCESS_RSP != event_result) &&
            (AVRCP_CA_CONTINUE_RSP != event_result))
        {
            break;
        }

        if (AVRCP_CA_CONTINUE_RSP == event_result)
        {
            send_request = 1U;
        }

        /* Get Body content -Image ThumbNail */
        if ((NULL == ca_event_headers->ca_rsp_info->body->value) ||
            (0U    == ca_event_headers->ca_rsp_info->body->length))
        {
            printf ("No Body Content found\n");
        }
        else
        {
            UINT16 length;
            UCHAR * data;


            data = ca_event_headers->ca_rsp_info->body->value;
            length = ca_event_headers->ca_rsp_info->body->length;

#ifdef STREAM_PRINT
             /* Print the stream */
            printf ("\n========== Cover Art Get LinkedThumbNail ==========\n");
            for (i = 0U; i < length; i++)
            {
                printf ("%c", data[i]);
            }
            printf ("\n======================================\n\n");
#endif /* 0 */

#ifdef HAVE_OBJECT_DUMP

            /* Open file to dump raw message */
            if (NULL == ca_img_thmbnail_fp)
            {
                img_thmbnail_recv_count++;
                BT_str_print((CHAR *)cover_art_file_name, "ca_ct_thumbnail_%d.jpg", img_thmbnail_recv_count);
                /* ca_img_thmbnail_fp = fopen ((CHAR *)cover_art_file_name, "wb"); */

                /* MISRA C-2012 Rule 17.7 | Coverity CHECKED_RETURN */
                (void)BT_vfops_create_object_name
                (
                    (UCHAR *)APPL_AVRCP_CT_BASE_FOLDER,
                    cover_art_file_name,
                    avrcp_ct_file_object
                );

                retval = BT_fops_file_open(avrcp_ct_file_object, (UCHAR *)"wb", &ca_img_thmbnail_fp);

                if (NULL != ca_img_thmbnail_fp)
                {
                    printf("%s file open success\n", avrcp_ct_file_object);
                }
            }

            /* Dump the image file message */
            if (NULL != ca_img_thmbnail_fp)
            {
                /* fwrite (data, length, 1, ca_img_thmbnail_fp); */
                (BT_IGNORE_RETURN_VALUE) BT_fops_file_write(data, length, ca_img_thmbnail_fp, &actual);
            }

            if (AVRCP_CA_SUCCESS_RSP == event_result)
            {
                /* MISRA C-2012 Rule 17.7 | Coverity CHECKED_RETURN */
                (void)BT_fops_file_close(ca_img_thmbnail_fp);
                ca_img_thmbnail_fp = NULL;
            }

#endif /* HAVE_OBJECT_DUMP */

        }

        break;

    case AVRCP_CAI_GET_ABORT_CNF:

        printf ("Recvd AVRCP_CAI_GET_ABORT_CNF - 0x%04X\n",
                event_result);

        printf ("AVRCP Initiator Cover Art Handle - 0x%02X\n", handle);

        break;

    default:
        printf ("Recvd UnKnown Cover Art Event - %02X\n",
        event_type);

        printf ("AVRCP-CT Cover Art Handle - 0x%02X\n", handle);
        break;
    }

    if (0U != send_request)
    {
        /* OBEX over L2CAP is Mandatory for AVRCP Cover Art */
        if (0U < wait_count)
        {
            req_info.wait = BT_TRUE;
            ca_event_headers->ca_req_info = &req_info;

            wait_count--;
        }

        retval =  BT_avrcp_cai_send_req
                  (
                      &handle,
                      event_type,
                      event_result,
                      ca_event_headers
                  );
        if(retval != API_SUCCESS)
        {
             printf ("Cover Art CT Send Request Failed - 0x%04X\n", retval);
        }
    }

    BT_IGNORE_UNUSED_PARAM(cover_art_xchg_size);
    return retval;
}

#endif /* AVRCP_COVER_ART_INITIATOR */

#ifdef AVRCP_BRIDGING
API_RESULT appl_handle_avrcp_bridging_cmd_rsp(uint8_t inst)
{
	    AVRCP_AL_VD_CMD_INFO  * vd_cmd_info;
		AVRCP_AL_VD_CMD_INFO    rsp_pdu_info;
		AVRCP_AL_CT_RSP_INFO   *avrcp_rsp_info;
	    UCHAR*                  rsp_info;
		UCHAR                  *param;
		UCHAR                  volume, event_id, tl;
		API_RESULT             retval = API_SUCCESS;
		UINT16                 param_len, offset, vu_op_id = 0;
		UCHAR                  op_id, op_id_state, tl_type;

		uint8_t sec_avrcp_index = avrcp_find_second_avrcp_instance (inst);
		avrcp_rsp_info = appl_avrcp_get_rsp_info();
	    vd_cmd_info     = appl_avrcp_get_vendor_cmd_info();
	    if (vd_cmd_info != NULL)
	    {
			rsp_info = vd_cmd_info->vd_cmd_data;
			/* Command Type */
			printf ("    Response Type - ");
			switch(vd_cmd_info->cmd_type)
			{
				case AVRCP_RESPONSE_TYPE_ACCEPTED:
					printf ("ACCEPTED\n");
					break;

				case AVRCP_RESPONSE_TYPE_INTERIM:
					printf ("INTERIM\n");
					break;

				case AVRCP_RESPONSE_TYPE_STABLE:
					printf ("STABLE\n");
					break;

				case AVRCP_RESPONSE_TYPE_REJECTED:
					printf ("REJECTED\n");
					break;

				case AVRCP_RESPONSE_TYPE_NOT_IMPLEMENTED:
					printf ("NOT IMPLEMENTED\n");
					break;

				case AVRCP_RESPONSE_TYPE_CHANGED:
					printf ("CHANGED\n");
					break;

				default:
					printf ("UNKNOWN\n");
					break;
			}

			printf ("\n    PDU-ID -> ");
			switch(vd_cmd_info->pdu_id)
			{
				case AVRCP_METADATA_PDU_ID_REGISTER_NOTIFICATION:
					printf ("Register Notification<0x%x>.\n", vd_cmd_info->pdu_id);
					if(sec_avrcp_index != PROFILE_INSTANCE_INVALID)
					{
						if(vd_cmd_info->cmd_type == AVRCP_RESPONSE_TYPE_INTERIM)
						{
							appl_avrcp_tg_send_notify_cmd_interim_rsp
								(
									sec_avrcp_index,
									vd_cmd_info
								);
						}

						else if(vd_cmd_info->cmd_type == AVRCP_RESPONSE_TYPE_CHANGED)
						{
							volume = rsp_info[12] & 0x7FU;
							printf("  notify  Volume: 0x%02x\n", volume);
							system_volume = volume;
							/*appl_avrcp_tg_notify_change_rsp(sec_avrcp_index);*/
							offset    = 0x00U;
							param     = NULL;
							param_len = 0U;
							tl        = 0U;
							retval = API_SUCCESS;
							event_id = 0x0D;

							/* Calculate parameter length */
							param_len = 2U;
							tl        = appl_mp_get_registered_player_event_tl (event_id);

							/* Allocate memory */
							param = BT_alloc_mem(param_len);
							if (NULL == param)
							{
								printf ("Failed to allocate memory\n");
								retval = API_FAILURE; /* return; */
							}
							else
							{

								param[offset++] = event_id;
								param[offset] = system_volume;
							}


							rsp_pdu_info.cmd_type    = AVRCP_RESPONSE_TYPE_CHANGED;

							rsp_pdu_info.vd_cmd_data    = param;
							rsp_pdu_info.vd_cmd_datalen = param_len;

							rsp_pdu_info.tl          = tl;
							rsp_pdu_info.pdu_id      = AVRCP_METADATA_PDU_ID_REGISTER_NOTIFICATION;
							rsp_pdu_info.packet_type = AVRCP_METADATA_PACKET_TYPE_SINGLE;

							if (API_SUCCESS == retval)
							{
								retval = BT_avrcp_al_send_metadata_pdu
										 (
											 &appl_avrcp_handle[sec_avrcp_index],
											 &rsp_pdu_info,
											 0x01U
										 );

								/* Free the memory */
								if (NULL != param)
								{
									BT_free_mem(param);
									param = NULL;
								}
							}
						}
					}
					break;

				case AVRCP_PDU_ID_SET_ABSOLUTE_VOLUME:
					printf ("Set Absolute Volume<0x%x>.\n", vd_cmd_info->pdu_id);
					appl_avrcp_tg_send_set_absolute_volume_cmd_rsp
					  (
						 sec_avrcp_index,
						 vd_cmd_info
					  );
					break;

				default:
					printf ("Unknown PDU-ID<0x%x>\n", vd_cmd_info->pdu_id);
					break;
		   }
		appl_reset_cmd_infos();
	    }
		
        if ( avrcp_rsp_info != NULL)
        {
        	printf("\n handle rsp_info \n");
	        printf("\n");
	        printf("AVRCP Control Response:\n");
	        appl_avrcp_print_opcode (avrcp_rsp_info->cmd_opcode);

	        /* Print operation id for passthrough command */
	        if (AVRCP_OPCODE_PASS_THROUGH == avrcp_rsp_info->cmd_opcode)
	        {
	            AVRCP_GET_MSG_OPERATION_INFO((UCHAR *)avrcp_rsp_info->rsp_info, op_id, op_id_state);

	            appl_avrcp_print_operation_id(op_id);
	            printf("    State = ");
	            if (0x00U == op_id_state)
	            {
	                printf ("Pressed\n");
	            }
	            else
	            {
	                printf ("Released\n");
	            }

	            if (AVRCP_OPERATION_ID_VENDOR_UNIQUE == op_id)
	            {
	                /* Extract Vendor Unique operation id */
	                avrcp_extract_2_byte_metadata_param
	                (
	                    &((UCHAR *)avrcp_rsp_info->rsp_info)[9U],
	                    &vu_op_id
	                );

	                printf ("    Vendor Unique Op Id: 0x%04x\n", vu_op_id);
	            }
	            tl_type = appl_get_avrcp_tl_message_type();
				if (sec_avrcp_index != PROFILE_INSTANCE_INVALID)
				{
					retval = BT_avrcp_al_send_passthrough_cmd_rsp
							(
								&appl_avrcp_handle[sec_avrcp_index],
								tl_type,
								AVRCP_RESPONSE_TYPE_ACCEPTED,
								op_id,
								(op_id_state >> 7U),
								vu_op_id
							);
					printf("\n Sent Passthrough rsp to remote : 0x%04x\n",retval);
				}
	        }

	        appl_avrcp_print_response_type (avrcp_rsp_info->rsp_type);
	        appl_reset_cmd_infos();
        }
		return retval;
}

UCHAR is_ele_attr_command_called()
{
	return get_ele_attr_command_called;
}
void set_ele_attr_command_called(UCHAR value)
{
	get_ele_attr_command_called = value;
}
/*
 * Description: get_current_song_attributes has to be called after
 * AVRCP_METADATA_PDU_ID_GET_ELEMENT_ATTRIBUTE is received
 */
AVRCP_ELEMENT_ATTR* get_current_song_attributes()
{
	return &avrcp_ele_attr;
}
#endif /* AVRCP_BRIDGING */
#endif /* AVRCP_CT */
