/**
 *  \file appl_ga_utils_audio_snk.c
 *
 *  Provides the GA Audio Data Path - Includes Audio Sink Interactions.
 *  1. ISO Module.
 *  2. Audio PL Module.
 *  3. LC3 Module.
 */

/*
 *  Copyright (C) 2020. Mindtree Ltd.
 *  All rights reserved.
 */

/* --------------------------------------------- Header File Inclusion */
#if defined (LC3_DSP) && (LC3_DSP == 1)

#include "appl_ga_utils_audio_snk.h"
#ifdef AUDIO_SNK_PL_SUPPORT
#include "audio_pl.h"
#endif /* AUDIO_SNK_PL_SUPPORT */

#if defined(LE_AUDIO_SINK_SYNC_ENABLE) && (LE_AUDIO_SINK_SYNC_ENABLE > 0)
#include "le_audio_pl_sync.h"
#include "leaudio_pl.h"
#endif /*#defined(LE_AUDIO_SINK_SYNC_ENABLE) && (LE_AUDIO_SINK_SYNC_ENABLE > 0)*/

#include "BT_fops.h"

#ifdef GA_BAP

/* --------------------------------------------- Global Definitions */

#ifdef AUDIO_SNK_ISO_SUPPORT
AUDIO_ISO_INFO audio_iso_snk[AUDIO_SNK_ISO_MAX_ENTRIES];
#ifdef SNK_DISPLAY_MISSED_SEQ_NUM
/* Enable/Disable displaying of missed streaming data's sequence number */
UINT8 config_snk_seq_num;
#endif /* SNK_DISPLAY_MISSED_SEQ_NUM */
#endif /* AUDIO_SNK_ISO_SUPPORT */

#ifdef AUDIO_SNK_PL_SUPPORT

AUDIO_PL_INFO audio_pl_snk;
#endif /* AUDIO_SNK_PL_SUPPORT */

#ifdef AUDIO_SNK_LC3_SUPPORT

#define AUDIO_SNK_LC3_INPUT_FRAME_SIZE_MAX LC3_INPUT_FRAME_SIZE_MAX
#define LC3_SILENCE_BUFFER_COUNT 0U

AUDIO_LC3_SNK_INFO audio_lc3_snk;
#endif /* AUDIO_SNK_LC3_SUPPORT */

#ifdef SNK_DUMP_AUDIO_PREDECODED
FILE* snk_dump_audio_predecoded_fd;
#endif /* SRC_DUMP_AUDIO_PREDECODED */

#ifdef SNK_DUMP_AUDIO_DECODED
FILE* snk_dump_audio_decoded_fd;
#endif /* SNK_DUMP_AUDIO_DECODED */

#if !defined(LE_AUDIO_SINK_SYNC_ENABLE) || (LE_AUDIO_SINK_SYNC_ENABLE == 0)
static INT16  dec16_silence[AUDIO_SNK_LC3_CHANNELS_MAX * AUDIO_SNK_LC3_INPUT_FRAME_SIZE_MAX];
#endif

/* --------------------------------------------- Static Global Variables */

/* --------------------------------------------- External Global Variables */

/* --------------------------------------------- Exported Global Variables */

/* --------------------------------------------- Functions */
#ifdef AUDIO_SNK_PL_SUPPORT
/* This function is empty, No action required */
static void audio_pl_snk_callback
            (
                /* IN */ const UCHAR * p_data,
                /* IN */ UINT16        p_datalen
            );
#endif /* AUDIO_SNK_PL_SUPPORT */

#ifdef AUDIO_SNK_LC3_SUPPORT
static void audio_snk_lc3_interleave_samples
            (
                INT32** in, INT16* out, UINT32 len, UINT32 num_channels
            );
static void audio_snk_lc3_deinterleave_samples
            (
                UINT8* in,
                UINT8** out,
                UINT32 len,
                UINT32 num_channels
            );

GA_RESULT audio_snk_lc3_decode_n_play(UCHAR * data, UINT16 datalen, HCI_ISO_HEADER *iso_hdr);

void audio_snk_write_pl(UCHAR * data, UINT16 datalen);
#endif /* AUDIO_SNK_LC3_SUPPORT */

#ifdef APPL_SNK_TIMESTAMP_DUMP
DECL_STATIC UINT32 snkframecount, snkframecount2;
DECL_STATIC BT_fops_file_handle snkfd;

void appl_snk_dump_isohandle(UINT16 handle)
{
    BT_fops_file_print(snkfd, "ISO Handle: %d\n", handle);
}

void appl_snk_dump_framecount2(void)
{
    snkframecount2++;
    BT_fops_file_print(snkfd, "Frame: %d\n", snkframecount2);
}

void appl_snk_dump_framecount(void)
{
    snkframecount++;
    BT_fops_file_print(snkfd, "Frame: %d\n", snkframecount);
}

void appl_snk_dump_timestamp(UINT8 index, UINT16 datalen)
{
    BT_LOCAL_TIME lt;

    EM_get_local_time(&lt);
    BT_fops_file_print(snkfd, "%d: [%d]: [%d:%d:%d:%d]\n",
        index, datalen, lt.thour, lt.tmin, lt.tsec, lt.tmsec);
}
#endif /* APPL_SNK_TIMESTAMP_DUMP */

void appl_ga_utils_audio_snk_init(void)
{
    UINT8  index;

    APPL_DBG
    (
        "[APPL][GA][AUDIO_SNK][ISO]: >> appl_ga_utils_audio_snk_init\n"
    );

#ifdef APPL_SNK_TIMESTAMP_DUMP
    snkframecount = 0U;
    BT_fops_file_open("SnkProfile.log", "w", &snkfd);
#endif /* APPL_SNK_TIMESTAMP_DUMP */

#ifdef AUDIO_SNK_ISO_SUPPORT
    /* Initialize all fields to 0U */
    for (index = 0U; index < AUDIO_SNK_ISO_MAX_ENTRIES; index++)
    {
        GA_mem_set
        (
            &audio_iso_snk[index],
            0U,
            (sizeof(AUDIO_ISO_INFO))
        );
        audio_iso_snk[index].state = AUDIO_ISO_IDLE;
        audio_iso_snk[index].conn_handle =
            AUDIO_CIS_CONN_HANDLE_INVALID;
        /* 0x3A = ":" [ASCII HEX Value] */
        audio_iso_snk[index].stream_symbol = (UCHAR)(0x3AU + index);
        audio_iso_snk[index].seq_num = 0U;
    }

    (GA_IGNORE_RETURN_VALUE)appl_ga_utils_audio_snk_register_iso_data_handler();
#endif /* AUDIO_SNK_ISO_SUPPORT */

#ifdef AUDIO_SNK_LC3_SUPPORT
    /* Initialize all fields to 0U and state to Idle */
    GA_mem_set
    (
        &audio_lc3_snk,
        0U,
        (sizeof(AUDIO_LC3_SNK_INFO))
    );
    audio_lc3_snk.state = AUDIO_LC3_IDLE;
#endif /* AUDIO_SNK_LC3_SUPPORT */

#ifdef AUDIO_SNK_PL_SUPPORT
    /* Initialize Audio PL */
    audio_init_pl(AUDIO_EP_SINK);

    audio_pl_snk.state = AUDIO_PL_IDLE;
#endif /* AUDIO_SNK_PL_SUPPORT */

    APPL_DBG
    (
        "[APPL][GA][AUDIO_SNK][ISO]: << appl_ga_utils_audio_snk_init\n"
    );
    return;
}

void appl_ga_utils_audio_snk_deinit(void)
{
    APPL_DBG
    (
        "[APPL][AUDIO_SNK][ISO]: >> appl_ga_utils_audio_snk_deinit\n"
    );

#ifdef APPL_SNK_TIMESTAMP_DUMP
    BT_fops_file_close(snkfd);
#endif /* APPL_SNK_TIMESTAMP_DUMP */

#ifdef AUDIO_SNK_PL_SUPPORT
    /* Shutdown Audio PL */
    audio_shutdown_pl();
#endif /* AUDIO_SNK_PL_SUPPORT */

    APPL_DBG
    (
        "[APPL][AUDIO_SNK][ISO]: << appl_ga_utils_audio_snk_deinit\n"
    );
    return;
}

#ifdef AUDIO_SNK_ISO_SUPPORT
GA_RESULT appl_ga_utils_audio_snk_set_entry
          (
              UINT16                     conn_handle,
              GA_LC3_CODEC_SPECIFIC_CONF cs_conf
          )
{
    GA_RESULT  retval;
    UINT8      index;

    /* Initialize */
    retval = GA_FAILURE;
    index = 0U;

    APPL_DBG
    (
        "[APPL][GA][AUDIO_SNK][ISO]: >> appl_ga_utils_audio_snk_set_entry\n"
    );

    /* Validate if there is an entry with this conn_handle already,
     * If yes, Update the other fields.
     * If no, Create a new entry.
     */
    if ((GA_SUCCESS == appl_ga_utils_audio_snk_get_entry(conn_handle, &index)) ||
        (GA_SUCCESS == appl_ga_utils_audio_snk_get_free_entry(&index)))
    {
        audio_iso_snk[index].conn_handle = conn_handle;
        audio_iso_snk[index].cs_conf = cs_conf;
        retval = GA_SUCCESS;
    }
    else
    {
        APPL_DBG("[APPL][AUDIO_SNK][ISO]: ISO Entry not Found !\n");
    }

    APPL_DBG
    (
        "[APPL][GA][AUDIO_SNK][ISO]: << appl_ga_utils_audio_snk_set_entry\n"
    );

    return retval;
}

GA_RESULT appl_ga_utils_audio_snk_remove_entry(UINT16 conn_handle)
{
    GA_RESULT  retval;
    UINT8      index;

    /* Initialize */
    retval = GA_FAILURE;
    index = 0U;

    APPL_DBG
    (
        "[APPL][GA][AUDIO_SNK][ISO]: >> appl_ga_utils_audio_snk_remove_entry\n"
    );

    if (GA_SUCCESS == appl_ga_utils_audio_snk_get_entry(conn_handle, &index))
    {
        GA_mem_set
        (
            &audio_iso_snk[index].cs_conf,
            0U,
            sizeof(GA_LC3_CODEC_SPECIFIC_CONF)
        );
        GA_mem_set
        (
            &audio_iso_snk[index].aca_info,
            0U,
            sizeof(APPL_GA_UTILS_AUDIO_ACA_INFO)
        );
        audio_iso_snk[index].streaming_state = GA_FALSE;
        audio_iso_snk[index].state = AUDIO_ISO_IDLE;
        audio_iso_snk[index].conn_handle =
            AUDIO_CIS_CONN_HANDLE_INVALID;
        audio_iso_snk[index].seq_num = 0U;
        retval = GA_SUCCESS;
    }
    else
    {
        APPL_DBG("[APPL][AUDIO_SNK][ISO]: ISO Entry not Found !\n");
    }

    APPL_DBG
    (
        "[APPL][GA][AUDIO_SNK][ISO]: << appl_ga_utils_audio_snk_remove_entry\n"
    );

    return retval;
}

GA_RESULT appl_ga_utils_audio_snk_get_free_entry(UINT8 * index)
{
    GA_RESULT  retval;
    UINT8      i;

    /* Initialize */
    retval = GA_FAILURE;

    APPL_DBG
    (
        "[APPL][GA][AUDIO_SNK][ISO]: >> appl_ga_utils_audio_snk_get_free_entry\n"
    );

    for (i = 0U; i < AUDIO_SNK_ISO_MAX_ENTRIES; i++)
    {
        if ((AUDIO_ISO_IDLE == audio_iso_snk[i].state) &&
            (AUDIO_CIS_CONN_HANDLE_INVALID == audio_iso_snk[i].conn_handle))
        {
            *index = i;
            retval = GA_SUCCESS;
            break;
        }
    }

    APPL_DBG
    (
        "[APPL][GA][AUDIO_SNK][ISO]: << appl_ga_utils_audio_snk_get_free_entry\n"
    );
    return retval;
}

GA_RESULT appl_ga_utils_audio_snk_get_entry
          (
              UINT16   conn_handle,
              UINT8  * index
          )
{
    GA_RESULT  retval;
    UINT8      i;

    /* Initialize */
    retval = GA_FAILURE;
    i = 0U;

    APPL_DBG("[APPL][GA][AUDIO_SNK][ISO]: >> appl_ga_utils_audio_snk_get_entry\n");

    for (i = 0U; i < AUDIO_SNK_ISO_MAX_ENTRIES; i++)
    {
        if (conn_handle == audio_iso_snk[i].conn_handle)
        {
            *index = i;
            retval = GA_SUCCESS;
            break;
        }
    }

    APPL_DBG("[APPL][GA][AUDIO_SNK][ISO]: << appl_ga_utils_audio_snk_get_entry\n");
    return retval;
}

GA_RESULT appl_ga_utils_audio_snk_update_entry
          (
              UINT16 conn_handle,
              UINT8  state,
              UINT8  status,
              UINT8  streaming_state
          )
{
    GA_RESULT  retval;
    UINT8      index;
    UINT8      i;

    /* Initialize */
    retval = GA_SUCCESS;
    index = 0U;
    i = 0U;

    APPL_DBG
    (
        "[APPL][GA][AUDIO_SNK][ISO]: >> appl_ga_utils_audio_snk_update_entry\n"
    );

    if (GA_SUCCESS == appl_ga_utils_audio_snk_get_entry(conn_handle, &index))
    {
        if ((GA_TRUE == streaming_state) || (GA_FALSE == streaming_state))
        {
            for (i = 0U; i < AUDIO_SNK_ISO_MAX_ENTRIES; i++)
            {
                /* Reset all ISO's streaming state to GA_FALSE */
                audio_iso_snk[i].streaming_state = GA_FALSE;
            }
            audio_iso_snk[index].streaming_state = streaming_state;
        }

        if (0x00 == status)
        {
            /* ISO Setup is complete */
            if ((AUDIO_ISO_DATA_SETUP == state)
                &&
                (AUDIO_ISO_UPDATE_IN_PROGRESS == audio_iso_snk[index].state))
            {
                APPL_DBG("[APPL][AUDIO_SNK][ISO]: ISO Data Path Setup Status: Complete\n");
                audio_iso_snk[index].state = AUDIO_ISO_SETUP_COMPLETE;
            }
            else if ((AUDIO_ISO_DATA_REMOVE == state)
                     &&
                     (AUDIO_ISO_UPDATE_IN_PROGRESS == audio_iso_snk[index].state))
            {
                APPL_DBG("[APPL][AUDIO_SNK][ISO]: ISO Data Path Removal Status: Complete\n");
                audio_iso_snk[index].state = AUDIO_ISO_IDLE;
                audio_iso_snk[index].seq_num = 0U;
            }
            else
            {
                /* Unknown State */
            }
        }
        else if (AUDIO_IGNORE_VALUE != status)
        {
            /* ISO Setup Failed */
            if ((AUDIO_ISO_DATA_SETUP == state)
                &&
                (AUDIO_ISO_UPDATE_IN_PROGRESS == audio_iso_snk[index].state))
            {
                APPL_DBG("[APPL][AUDIO_SNK][ISO]: ISO Data Path Setup Status: Failed !\n");
                audio_iso_snk[index].state = AUDIO_ISO_IDLE;
                audio_iso_snk[index].seq_num = 0U;
            }
            else if ((AUDIO_ISO_DATA_REMOVE == state)
                     &&
                     (AUDIO_ISO_UPDATE_IN_PROGRESS == audio_iso_snk[index].state))
            {
                /*
                 * If the Host issues this command with a
                 * Connection_Handle that does not exist or is not for
                 * a CIS, CIS configuration, or BIS, the Controller
                 * shall return the error code Unknown Connection
                 * Identifier (0x02).
                 */
                /*
                 * TODO: Laird: On removing ISO data path after CIS is
                 * disconnected, Command Disallowed (0x0C) is received
                 * instead of Unknown Connection Identifier (0x02).
                 * Check.
                 */
                if ((0x02U == status) || (0x0CU == status))
                {
                    APPL_DBG("[APPL][AUDIO_SNK][ISO]: ISO Data Path Removal Status: Complete\n");
                    audio_iso_snk[index].state = AUDIO_ISO_IDLE;
                }
                else
                {
                    APPL_DBG("[APPL][AUDIO_SNK][ISO]: ISO Data Path Removal Status: Failed !\n");
                    audio_iso_snk[index].state = AUDIO_ISO_SETUP_COMPLETE;
                }
            }
            else
            {
                /* Unknown State */
            }
        }
        else
        {
            /* No action required */
        }
    }
    else
    {
        APPL_DBG("[APPL][AUDIO_SNK][ISO]: ISO Entry not Found !\n");
        retval = GA_FAILURE;
    }

    APPL_DBG
    (
        "[APPL][GA][AUDIO_SNK][ISO]: << appl_ga_utils_audio_snk_update_entry\n"
    );
    return retval;
}

GA_RESULT appl_ga_utils_audio_snk_le_setup_iso_data_path
          (
              /* IN */  UINT16   conn_handle,
              /* OUT */ UCHAR  * stream_symbol
          )
{
    GA_RESULT  retval;
    UINT8      index;
    UINT8      codec_id[5U] = { 0U };

    /* Initialize */
    retval = GA_FAILURE;
    index = 0U;

    APPL_DBG
    (
        "[APPL][GA][AUDIO_SNK][ISO]: >> appl_ga_utils_audio_snk_le_setup_iso_data_path\n"
    );

    if (GA_SUCCESS != appl_ga_utils_audio_snk_get_entry(conn_handle, &index))
    {
        APPL_DBG("[APPL][AUDIO_SNK][ISO]: ISO Entry not Found !\n");
        return retval;
    }

    if (AUDIO_ISO_UPDATE_IN_PROGRESS == audio_iso_snk[index].state)
    {
        /* Do not allow again since already in progress */
        APPL_DBG("[APPL][AUDIO_SNK][ISO]: ISO Data Path Setup Status: Already In-progress !\n");
    }
    else if (AUDIO_ISO_IDLE == audio_iso_snk[index].state)
    {
        /* The ISO Data Path is not setup yet, Set it up */

        /*
         * NOTE: The if the codec in use resides in the Bluetooth Host of the
         * device using the LE Setup ISO Data Path command, the Unicast Client
         * and/or Unicast Server shall:
         * Write the LE Setup ISO Data Path command Codec_Configuration_Length
         * parameter with the value 0x00.
         * Write octet 0 (Coding_Format) of the LE Setup ISO Data Path command
         * Codec_ID parameter with the value 0x03 (Transparent)
         */
        codec_id[0U] = AUDIO_CODING_FORMAT_TRANSPARENT;

        if (GA_SUCCESS == BT_hci_le_setup_iso_data_path
                          (
                              audio_iso_snk[index].conn_handle,
                              AUDIO_ISO_OUTPUT_C_TO_H,
                              AUDIO_DATA_PATH_ID_HCI,
                              &codec_id[0U],
                              AUDIO_ISO_CONTROLLER_DELAY,
                              0U,
                              NULL
                          ))
        {
            APPL_DBG("[APPL][AUDIO_SNK][ISO]: ISO Data Path Setup Status: In-progress\n");
            retval = GA_CONTINUE;
            audio_iso_snk[index].state = AUDIO_ISO_UPDATE_IN_PROGRESS;
            if (NULL != stream_symbol)
            {
                /* Update stream symbol */
                *stream_symbol = audio_iso_snk[index].stream_symbol;
            }
        }
    }
    else if (AUDIO_ISO_SETUP_COMPLETE == audio_iso_snk[index].state)
    {
        /* ISO Data Path is already ready */
        APPL_DBG("[APPL][AUDIO_SNK][ISO]: ISO Data Path Setup Status: Already Complete\n");
        if (NULL != stream_symbol)
        {
            /* Update stream symbol */
            *stream_symbol = audio_iso_snk[index].stream_symbol;
        }
        retval = GA_SUCCESS;
    }

    APPL_DBG
    (
        "[APPL][GA][AUDIO_SNK][ISO]: << appl_ga_utils_audio_snk_le_setup_iso_data_path\n"
    );
    return retval;
}

GA_RESULT appl_ga_utils_audio_snk_le_remove_iso_data_path
          (
              /* IN */ UINT16 conn_handle
          )
{
    GA_RESULT  retval;
    UINT8      index;

    /* Initialize */
    retval = GA_FAILURE;
    index = 0U;

    APPL_DBG
    (
        "[APPL][GA][AUDIO_SNK][ISO]: >> appl_ga_utils_audio_snk_le_remove_iso_data_path\n"
    );

    if (GA_SUCCESS != appl_ga_utils_audio_snk_get_entry(conn_handle, &index))
    {
        APPL_DBG("[APPL][AUDIO_SNK][ISO]: ISO Entry not Found !\n");
        return retval;
    }

    if (AUDIO_ISO_UPDATE_IN_PROGRESS == audio_iso_snk[index].state)
    {
        /* Do not allow now since already in progress */
        APPL_DBG("[APPL][AUDIO_SNK][ISO]: ISO Data Path Removal Status: Already In-progress !\n");
    }
    else if (AUDIO_ISO_IDLE == audio_iso_snk[index].state)
    {
        /* The ISO Data Path is already removed */
        APPL_DBG("[APPL][AUDIO_SNK][ISO]: ISO Data Path Removal Status: Already Removed !\n");
        retval = GA_SUCCESS;
    }
    else if (AUDIO_ISO_SETUP_COMPLETE == audio_iso_snk[index].state)
    {
        /* The ISO Data Path is setup, Remove it */
        if (GA_SUCCESS == BT_hci_le_remove_iso_data_path
                          (
                              conn_handle,
                              AUDIO_ISO_OUTPUT_DATA_PATH
                          ))
        {
            APPL_DBG("[APPL][AUDIO_SNK][ISO]: ISO Data Path Removal Status: In-progress\n");
            retval = GA_CONTINUE;
            audio_iso_snk[index].state = AUDIO_ISO_UPDATE_IN_PROGRESS;
        }
        else
        {
            APPL_DBG("[APPL][AUDIO_SNK][ISO]: ISO Data Path Removal Status: Failed !\n");
        }
    }

    APPL_DBG
    (
        "[APPL][GA][AUDIO_SNK][ISO]: << appl_ga_utils_audio_snk_le_remove_iso_data_path\n"
    );
    return retval;
}

GA_RESULT appl_ga_utils_audio_snk_register_iso_data_handler(void)
{
    GA_RESULT  retval;

    /* Initialize */
    retval = GA_FAILURE;

    APPL_DBG
    (
        "[APPL][AUDIO_SNK][ISO]: "
        ">> appl_ga_utils_audio_snk_register_iso_data_handler\n"
    );

    retval = BT_hci_register_iso_data_handler
             (
                 &appl_ga_utils_audio_snk_hci_iso_data_ind_cb
             );

    if (GA_SUCCESS != retval)
    {
        APPL_DBG
        (
            "[APPL][GA][AUDIO_SNK][ISO]: "
            "Register ISO Data Handler Failed 0x%04X !\n",
            retval
        );
    }
    else
    {
        APPL_DBG
        (
            "[APPL][AUDIO_SNK][ISO]: "
            "Register ISO Data Handler Success 0x%04X !\n",
            retval
        );
    }

    APPL_DBG
    (
        "[APPL][AUDIO_SNK][ISO]: "
        "<< appl_ga_utils_audio_snk_register_iso_data_handler\n"
    );

    return retval;
}

GA_RESULT appl_ga_utils_audio_snk_hci_iso_data_ind_cb
          (
              UCHAR  * header,
              UCHAR  * data,
              UINT16  datalen
          )
{
    GA_RESULT retval;
    HCI_ISO_HEADER iso_header;
    UINT8 i;

#ifdef SNK_DISPLAY_MISSED_SEQ_NUM
    UINT16 index;
#endif /* SNK_DISPLAY_MISSED_SEQ_NUM */

#ifndef AUDIO_SNK_PL_SUPPORT
    GA_IGNORE_UNUSED_PARAM(data);
    GA_IGNORE_UNUSED_PARAM(datalen);
#endif /* AUDIO_SNK_PL_SUPPORT */

    retval = GA_FAILURE;

    /* APPL_TRC("ISO: LC3 Encoded Data : %d\n", datalen); */
    /* APPL_TRC("."); */

#ifdef AUDIO_SNK_LC3_SUPPORT
#if !defined(LE_AUDIO_SINK_SYNC_ENABLE) || (LE_AUDIO_SINK_SYNC_ENABLE == 0)
    if ((datalen > 0) && (NULL != data))
#endif /*!defined(LE_AUDIO_SINK_SYNC_ENABLE) || (LE_AUDIO_SINK_SYNC_ENABLE == 0)*/
    {
        /*
         * Fetch the handle and check the ISO state.
         * If streaming state is GA_TRUE call decode_n_play
         */
        HCI_EXTRACT_ISO_HEADER(header, &iso_header);

#ifdef APPL_SNK_TIMESTAMP_DUMP
        if (0 == ((iso_header.conn_handle) & 1U))
        {
            appl_snk_dump_framecount();
        }
        else
        {
            appl_snk_dump_framecount2();
        }
        appl_snk_dump_timestamp(1, datalen);
        appl_snk_dump_isohandle(iso_header.conn_handle);
#endif /* APPL_SNK_TIMESTAMP_DUMP */

        for (i = 0U; i < AUDIO_SNK_ISO_MAX_ENTRIES; i++)
        {
            if (audio_iso_snk[i].conn_handle == iso_header.conn_handle)
            {
#ifdef SNK_DISPLAY_MISSED_SEQ_NUM
                if (GA_TRUE == config_snk_seq_num)
                {
                    /* For the first packet, Do not compare, Initialize the
                     * Local Seq Num to obtained one.
                     */
                    if ((audio_iso_snk[i].seq_num != 0U) &&
                        ((audio_iso_snk[i].seq_num + 1U) != iso_header.seqnum))
                    {
                        /* If received Seq Num is not the one that we are
                         * waiting for display all the missed seq num
                         */
                        APPL_TRC("%c! ", audio_iso_snk[i].stream_symbol);
                        for (index = (audio_iso_snk[i].seq_num + 1U); index < iso_header.seqnum; index++)
                        {
                            APPL_TRC("%d ", index);
                        }
                        APPL_TRC("\n");
                    }
                    /* Assign it back to current running Seq Num */
                    audio_iso_snk[i].seq_num = iso_header.seqnum;
                }
#endif /* SNK_DISPLAY_MISSED_SEQ_NUM */

                if (GA_TRUE == audio_iso_snk[i].streaming_state)
                {
                    /* Decode and send the rx packet */
                    retval = audio_snk_lc3_decode_n_play(data, datalen, &iso_header);
                    break;
                }
                else
                {
                 //   APPL_TRC("%c ", audio_iso_snk[i].stream_symbol);
                    break;
                }
            }
        }
    }
#endif /* AUDIO_SNK_LC3_SUPPORT */
    return retval;
}

#ifdef SNK_DISPLAY_MISSED_SEQ_NUM
void appl_ga_utils_audio_snk_config_missed_seq_num_display(UINT8 op)
{
    if (1U == op)
    {
        config_snk_seq_num = GA_TRUE;
    }
    else if (2U == op)
    {
        config_snk_seq_num = GA_FALSE;
    }
    else
    {
        APPL_DBG("Invalid Operation\n");
    }
}
#endif /* SNK_DISPLAY_MISSED_SEQ_NUM */
#endif /* AUDIO_SNK_ISO_SUPPORT */

#ifdef AUDIO_SNK_PL_SUPPORT

void audio_snk_write_pl(UCHAR * data, UINT16 datalen)
{
    audio_write_pl
    (
        AUDIO_EP_SINK,
        data,
        datalen
    );

    return;
}

static void audio_pl_snk_callback
            (
                /* IN */ const UCHAR * p_data,
                /* IN */ UINT16        p_datalen
            )
{
    /* No action required */
    GA_IGNORE_UNUSED_PARAM(p_data);
    GA_IGNORE_UNUSED_PARAM(p_datalen);

    return;
}

GA_RESULT appl_ga_utils_audio_snk_setup_playback_pl
          (
              GA_LC3_CODEC_SPECIFIC_CONF cs_conf,
              UCHAR                      bps,
              UINT16                     size
          )
{
    GA_RESULT  retval;
    UINT32     sf_hz;
    UINT8      cc;

    /* Initialize */
    sf_hz = 0U;
    cc = 0U;

    /* Fetch Sampling Freq in Hz */
    sf_hz = appl_ga_utils_bap_fetch_sf(cs_conf.sf);

    /* Fetch Channel Count from Audio Channel Allocation */
    cc = appl_ga_utils_fetch_sacc_from_aca(cs_conf.aca);
    retval = audio_setup_pl
             (
                 AUDIO_EP_SINK,
                 audio_pl_snk_callback,
                 (UINT16 )sf_hz,
                 bps,
                 cc,
                 size
             );

    if (GA_SUCCESS == retval)
    {
        APPL_DBG("[APPL][AUDIO_SNK][PL]: Audio PL Playback Setup Status: Success\n");
        /*
         * Save/Update the Settings that the Audio PL is configured currently.
         */
        audio_pl_snk.sf_hz = (UINT16 )sf_hz;
        audio_pl_snk.bps = bps;
        audio_pl_snk.cc = cc;
        audio_pl_snk.size = size;
        audio_pl_snk.state = AUDIO_PL_SETUP_COMPLETE;
    }
    else
    {
        APPL_DBG("[APPL][AUDIO_SNK][PL]: Audio PL Playback Setup Status: Failed !\n");
    }
    return retval;
}

GA_RESULT appl_ga_utils_audio_snk_start_playback_pl(void)
{
    GA_RESULT retval;

    /* Initialize */
    retval = GA_FAILURE;

    if (AUDIO_PL_SETUP_COMPLETE == audio_pl_snk.state)
    {
        retval = audio_start_pl(AUDIO_EP_SINK);

        if (GA_SUCCESS == retval)
        {
            APPL_DBG("[APPL][AUDIO_SNK][PL]: Audio PL Playback Start Process Status: Success\n");
            audio_pl_snk.state = AUDIO_PL_STREAM_PLAYBACK;
        }
        else
        {
            APPL_DBG("[APPL][AUDIO_SNK][PL]: Audio PL Playback Start Process Status: Failed !\n");
        }
    }
    else
    {
        /* Already Audio Playback in Progress, Do nothing */
        APPL_DBG("[APPL][AUDIO_SNK][PL]: Audio PL Playback Start Process Status: Already playing !\n");
    }
    return retval;
}

UINT8 appl_ga_utils_audio_snk_is_playback_pl_running(void)
{
    UINT8 isRunning;

    /* Initialize */
    isRunning = GA_FALSE;

    if ((AUDIO_PL_SETUP_COMPLETE == audio_pl_snk.state)
        || (AUDIO_PL_IDLE == audio_pl_snk.state))
    {
        APPL_DBG("[APPL][GA][AUDIO_SNK][PL]: Audio PL Playback Status: Already Stopped !\n");
    }
    else
    {
        APPL_DBG("[APPL][GA][AUDIO_SNK][PL]: Audio PL Playback Status: Playing !\n");
        isRunning = GA_TRUE;
    }

    return isRunning;
}

GA_RESULT appl_ga_utils_audio_snk_stop_playback_pl(void)
{
    GA_RESULT retval;

    /* Initialize */
    retval = GA_FAILURE;

    if (AUDIO_PL_STREAM_PLAYBACK == audio_pl_snk.state)
    {
        retval = audio_stop_pl(AUDIO_EP_SINK);

        if (GA_SUCCESS == retval)
        {
            APPL_DBG("[APPL][AUDIO_SNK][PL]: Audio PL Playback Stop Process Status: Success\n");
            audio_pl_snk.state = AUDIO_PL_SETUP_COMPLETE;
        }
        else
        {
            APPL_DBG("[APPL][AUDIO_SNK][PL]: Audio PL Playback Stop Process Status: Failed !\n");
        }
    }
    else
    {
        /* Already Audio Playback is Stopped, Do nothing */
        APPL_DBG("[APPL][AUDIO_SNK][PL]: Audio PL Playback Stop Process Status: Already stopped !\n");
    }

    return retval;
}

#endif /* AUDIO_SNK_PL_SUPPORT */

GA_RESULT appl_ga_utils_audio_snk_audio_lc3_dec_allowed
          (
              GA_LC3_CODEC_SPECIFIC_CONF cs_conf
          )
{
#ifdef AUDIO_SNK_LC3_SUPPORT

    GA_RESULT retval;

    /*
     * Even if the Audio PL module can playback only one stream at a time,
     * We should still be able to receive the audio stream irrespective of
     * the configuration.
     */
    retval = GA_SUCCESS;

    return retval;
#else /* AUDIO_SNK_LC3_SUPPORT */
    return GA_SUCCESS;
#endif /* AUDIO_SNK_LC3_SUPPORT */
}

#ifdef AUDIO_SNK_LC3_SUPPORT

GA_RESULT appl_ga_utils_audio_snk_create_lc3_decoder
          (
              GA_LC3_CODEC_SPECIFIC_CONF cs_conf,
              UCHAR                      bps
          )
{
    GA_RESULT  retval;
    INT32      lc3_retval;
    UINT8      index;
    UINT16     fd_in_us;
    UINT32     sf_hz;
    UINT8      cc;
    UINT16     fd_as_per_lc3_format;

    /* Initialize */
    retval = GA_FAILURE;
    fd_in_us = 0U;
    sf_hz = 0U;
    cc = 0U;

    /* Fetch Sampling Freq in Hz */
    sf_hz = appl_ga_utils_bap_fetch_sf(cs_conf.sf);

    /* Get the Frame Duration in us */
    fd_in_us = appl_ga_utils_get_fd_in_us(cs_conf.fd);

    /* Fetch Channel Count from Audio Channel Allocation */
    cc = appl_ga_utils_fetch_sacc_from_aca(cs_conf.aca);

    GET_SUPP_FRAME_DURATION_FOR_LC3(fd_in_us, fd_as_per_lc3_format);
    /*
     * By default, we assume that the LC3 Decoder is called only after
     * validating appl_ga_utils_audio_snk_set_entry(), hence return GA_SUCCESS
     * by default.
     */

    if (AUDIO_LC3_IDLE == audio_lc3_snk.state)
    {
        for (index = 0U; index < cc; index++)
        {
            /*
             * Assign Appl Buffer for enc_buf - Source -> LC3 Encoded Input,
             *                        dec_buf - Resultant -> LC3 Decoded Output
             */

            GA_mem_set
            (
                audio_lc3_snk.ctx.snk_enc_buffer, 0, sizeof(audio_lc3_snk.ctx.snk_enc_buffer)
            );
            GA_mem_set
            (
                audio_lc3_snk.ctx.snk_dec_buffer, 0, sizeof(audio_lc3_snk.ctx.snk_dec_buffer)
            );

            audio_lc3_snk.ctx.snk_enc_buf[index] = &audio_lc3_snk.ctx.snk_enc_buffer[index][0U];
            audio_lc3_snk.ctx.snk_dec_buf[index] = &audio_lc3_snk.ctx.snk_dec_buffer[index][0U];
        }

        /* Init LC3 Decode Module */
        lc3_retval = LC3_decoder_create
                     (
                         &audio_lc3_snk.ctx.dec_ctx,
                         sf_hz,
                         bps,
                         cc,
                         fd_as_per_lc3_format,
                         AUDIO_LC3_DEC_PLC_TYPE_DEFAULT,
                         audio_lc3_snk.ctx.dec_core_buffer,
                         audio_lc3_snk.ctx.dec_work_buffer,
                         audio_lc3_snk.ctx.snk_enc_buf,
                         audio_lc3_snk.ctx.snk_dec_buf
                     );

        if (LC3_DECODER_SUCCESS == lc3_retval)
        {
            APPL_DBG("[APPL][AUDIO_SNK][LC3]: LC3 Decoder Setup Status: Created\n");
            audio_lc3_snk.sf_hz = (UINT16 )sf_hz;
            audio_lc3_snk.bps = bps;
            audio_lc3_snk.cc = cc;
            audio_lc3_snk.fd_in_us = fd_in_us;
            audio_lc3_snk.state = AUDIO_LC3_CREATED;
            retval = GA_SUCCESS;
        }
        else
        {
            APPL_DBG("[APPL][AUDIO_SNK][LC3]: LC3 Decoder Setup Status: Could not create !\n");
            GA_mem_set
            (
                &audio_lc3_snk.ctx.dec_ctx,
                0U,
                sizeof(LC3_DECODER_CNTX)
            );
            audio_lc3_snk.state = AUDIO_LC3_IDLE;
        }
    }

    return retval;
}

UINT8 appl_ga_utils_audio_snk_is_lc3_decoder_running(void)
{
    UINT8 isRunning;

    /* Initialize */
    isRunning = GA_FALSE;

    if (AUDIO_LC3_IDLE == audio_lc3_snk.state)
    {
        APPL_DBG("[APPL][GA][AUDIO_SNK][LC3]: LC3 Decoder Setup Status: Already Deleted !\n");
    }
    else
    {
        APPL_DBG("[APPL][GA][AUDIO_SNK][LC3]: LC3 Decoder Setup Status: In Progress !\n");
        isRunning = GA_TRUE;
    }

    return isRunning;
}

GA_RESULT appl_ga_utils_audio_snk_delete_lc3_decoder(void)
{
    GA_RESULT retval;

    /* Initialize */
    retval = GA_FAILURE;

    if (AUDIO_LC3_IDLE != audio_lc3_snk.state)
    {
        LC3_decoder_delete(&audio_lc3_snk.ctx.dec_ctx);
        GA_mem_set
        (
            &audio_lc3_snk.ctx.dec_ctx,
            0U,
            sizeof(LC3_DECODER_CNTX)
        );
        audio_lc3_snk.sf_hz = 0U;
        audio_lc3_snk.bps = 0U;
        audio_lc3_snk.cc = 0U;
        audio_lc3_snk.fd_in_us = 0U;
        audio_lc3_snk.state = AUDIO_LC3_IDLE;

        retval = GA_SUCCESS;
        APPL_DBG("[APPL][AUDIO_SNK][LC3]: LC3 Decoder Setup Status: Deleted\n");
    }
    else
    {
        APPL_DBG("[APPL][AUDIO_SNK][LC3]: LC3 Decoder Setup Status: Already Deleted !\n");
    }

    return retval;
}

static void audio_snk_lc3_deinterleave_samples(UINT8 *in, UINT8 **out, UINT32 len, UINT32 num_channels)
{
    UINT32 i, j, k;
    k = 0U;

    for (j = 0; j < num_channels; j++)
    {
        for (i = 0; i < len; i++)
        {
            out[j][i] = in[k];
            k++;
        }
    }
}

static void audio_snk_lc3_interleave_samples(INT32 **in, INT16 *out, UINT32 len, UINT32 num_channels)
{
    UINT32 i, j;
    for (j = 0; j < num_channels; j++)
    {
        for (i = 0; i < len; i++)
        {
            out[(i * num_channels) + j] = (INT16)(in[j][i]);
        }
    }
}

GA_RESULT audio_snk_lc3_decode_n_play(UCHAR * data, UINT16 datalen, HCI_ISO_HEADER *iso_hdr)
{
    INT32         encoded_byte_len[AUDIO_SNK_LC3_CHANNELS_MAX];
    INT32         flg_bytes[AUDIO_SNK_LC3_CHANNELS_MAX];
    UINT16        index;
    INT32         samples_per_frame_per_channel;
    INT16  		  pcm_buffer[AUDIO_SNK_LC3_CHANNELS_MAX * (AUDIO_SNK_LC3_INPUT_FRAME_SIZE_MAX + 120U)];
#if defined(LE_AUDIO_SINK_SYNC_ENABLE) || (LE_AUDIO_SINK_SYNC_ENABLE > 0)
	INT16 		  resampler_in[AUDIO_LC3_INPUT_FRAME_SIZE_MAX + 120U];
	INT16         resampler_out[AUDIO_LC3_INPUT_FRAME_SIZE_MAX + 120U];
	INT32 		  resampler_samples_out = 0;
    INT16 		  sample_out = 0;
#endif /*defined(LE_AUDIO_SINK_SYNC_ENABLE) || (LE_AUDIO_SINK_SYNC_ENABLE > 0)*/
    /* Initialize */
    index = 0U;
    samples_per_frame_per_channel = 0;

#ifdef SNK_DUMP_AUDIO_PREDECODED
    if (NULL != snk_dump_audio_predecoded_fd)
    {
        fwrite(data, sizeof(UINT8), (datalen), snk_dump_audio_predecoded_fd);
    }
#endif /* SNK_DUMP_AUDIO_PREDECODED */

    if (AUDIO_LC3_IDLE == audio_lc3_snk.state)
    {
        return GA_FAILURE;
    }

    /*
     * De-Interleave Samples Per Channel:
     *  The Length per channel will be (datalen / channel count).
     *  1. data to be fed to deinterleave:
     *     S11, S21, S31, S41, ....
     *     S11 - Sample 1 Channel 1
     *     S21 - Sample 1 Channel 2
     *     S31 - Sample 1 Channel 3
     *     S41 - Sample 1 Channel 4
     *  S11, S21, S31... for snk_enc_buf[0U]
     *  S21, S22, S32... for snk_enc_buf[1U]
     * For Channel 1,
     * out[0][0] = in[0]
     * out[0][1] = in[1]
     * out[0][2] = in[2]
     * out[0][3] = in[3]
     * For Channel 2,
     * out[1][0] = in[n]
     * out[1][1] = in[n + 1]
     * out[1][2] = in[n + 2]
     * out[1][3] = in[n + 3]
     */

#if defined(LE_AUDIO_SINK_SYNC_ENABLE) && (LE_AUDIO_SINK_SYNC_ENABLE > 0)
    /*If this data is correct!*/
    if (iso_hdr->ps_flag == 0U)
#endif
    {
        audio_snk_lc3_deinterleave_samples
        (
            data,
            audio_lc3_snk.ctx.snk_enc_buf,
            (datalen / audio_lc3_snk.cc),
            audio_lc3_snk.cc
        );
    }

    /* Memset all fields */
    for (index = 0U; index < audio_lc3_snk.cc; index++)
    {
        encoded_byte_len[index] = 0;
        flg_bytes[index] = 0; /* G192_GOOD_FRAME = 0 */
    }

    /*
     * Total Data Length given is datalen, Divide it per Channel.
     * CF_1, CF_2, CF_m - Block_1
     * CF_1, CF_2, CF_m - Block_2
     * ..................
     * CF_1, CF_2, CF_m = Block_n
     *
     * If cc: 2, datalen is datalen/cc, datalen/2
     */
    for (index = 0U; index < audio_lc3_snk.cc; index++)
    {
        encoded_byte_len[index] = (datalen / audio_lc3_snk.cc);
#if defined(LE_AUDIO_SINK_SYNC_ENABLE) && (LE_AUDIO_SINK_SYNC_ENABLE > 0)
        flg_bytes[index] = iso_hdr->ps_flag;
#endif
    }

    samples_per_frame_per_channel = LC3_decoder_get_frame_length(&audio_lc3_snk.ctx.dec_ctx);
    INT32 ret = LC3_decoder_process
            (
                &audio_lc3_snk.ctx.dec_ctx,
                flg_bytes,
                encoded_byte_len
            );
    if (LC3_DECODER_SUCCESS == ret)
    {
#ifdef APPL_SNK_TIMESTAMP_DUMP
        appl_snk_dump_timestamp(2, encoded_byte_len);
#endif /* APPL_SNK_TIMESTAMP_DUMP */

        /* APPL_DBG("[APPL][AUDIO_SNK][LC3]: LC3 Decoder Process Start Status: Succes\n"); */
        /* APPL_TRC("ISO: LC3 Decoded Data : %d\n", samples_per_frame_per_channel); */
#if defined(LE_AUDIO_SINK_SYNC_ENABLE) || (LE_AUDIO_SINK_SYNC_ENABLE > 0)

        for (UINT16 ch_index = 0U; ch_index < audio_lc3_snk.cc; ch_index++)
        {
        	/*fetch 16bit samples from 32bit sample array*/
            for (UINT16 sample = 0U; sample < samples_per_frame_per_channel; sample++)
            {
            	resampler_in[sample] = (INT16)(audio_lc3_snk.ctx.snk_dec_buffer[ch_index][sample]);
            }

            /*run re-sampler asrc per channel*/
            sample_out = le_audio_asrc_process
											(
												LE_AUDIO_SDU_FLAG_VALID,
												iso_hdr,
												(INT16*) &resampler_in[0],
												samples_per_frame_per_channel,
												(INT16*) &resampler_out[0],
												ch_index + 1U
											);

        	/*interleave samples to even, odd pattern*/
            for (UINT16 sample = 0U; sample < sample_out; sample++)
            {
            	pcm_buffer[(sample * audio_lc3_snk.cc) + ch_index] = resampler_out[sample];
            }

            if ((ch_index == 1) && (resampler_samples_out != sample_out))
            {
            	PRINTF ("[sdu:%d] %d %d]", iso_hdr->seqnum, resampler_samples_out, sample_out);
            }

            resampler_samples_out += sample_out;
        }

#endif /*defined(LE_AUDIO_SINK_SYNC_ENABLE) || (LE_AUDIO_SINK_SYNC_ENABLE > 0)*/

#if defined(LE_AUDIO_SINK_SYNC_ENABLE) || (LE_AUDIO_SINK_SYNC_ENABLE > 0)
#else
        if (1U < audio_lc3_snk.cc)
        {
            /* This is a Handle that is supporting more than 1 CC */
            /* Interleave the samples */
            audio_snk_lc3_interleave_samples
            (
                audio_lc3_snk.ctx.snk_dec_buf,
                pcm_buffer,
                samples_per_frame_per_channel,
                audio_lc3_snk.cc
            );
        }
        else
        {
            /* It is supporting 1 CC */
            for (index = 0U; index < samples_per_frame_per_channel; index++)
            {
                pcm_buffer[index] = (INT16)(audio_lc3_snk.ctx.snk_dec_buffer[0U][index]);
            }
        }
#endif /*(LE_AUDIO_SINK_SYNC_ENABLE) || (LE_AUDIO_SINK_SYNC_ENABLE > 0)*/

#ifdef SNK_DUMP_AUDIO_DECODED
        if (NULL != snk_dump_audio_decoded_fd)
        {
            fwrite(pcm_buffer, sizeof(INT16), (samples_per_frame_per_channel), snk_dump_audio_decoded_fd);
        }
#endif /* SNK_DUMP_AUDIO_DECODED */

#ifdef AUDIO_SNK_PL_SUPPORT
        if (AUDIO_LC3_CREATED == audio_lc3_snk.state)
        {
#if !defined(LE_AUDIO_SINK_SYNC_ENABLE) || (LE_AUDIO_SINK_SYNC_ENABLE == 0)
            for (index = 0; index < LC3_SILENCE_BUFFER_COUNT; index++)
            {
                /*
                 * audio_snk_write_pl API will take data of type UCHAR pointer and
                 * dec16_silence is an array of INT16. So, datalen will become
                 * (samples_per_frame_per_channel * channel count * 2(for data type conversion))
                 * For 1 channel: samples_per_frame_per_channel * 1 * 2
                 *              = samples_per_frame_per_channel * 2
                 *              = (samples_per_frame_per_channel << 1(audio_lc3_snk.cc))
                 * For 2 channel: samples_per_frame_per_channel * 2 * 2
                 *              = samples_per_frame_per_channel * 4
                 *              = (samples_per_frame_per_channel << 2(audio_lc3_snk.cc))
                 */
                audio_snk_write_pl
                (
                    (UCHAR *)dec16_silence,
                    (UINT16)(samples_per_frame_per_channel << audio_lc3_snk.cc) /* Check this */
                );
            }
#endif
            audio_lc3_snk.state = AUDIO_LC3_IN_PROGRESS;
        }

        /*
         * audio_snk_write_pl API will take data of type UCHAR pointer and
         * pcm_buffer is an array of INT16 and if channel count > 1, then
         * it will have interleaved data. So, datalen will become
         * (samples_per_frame_per_channel * channel count * 2(for data type conversion))
         * For 1 channel: samples_per_frame_per_channel * 1 * 2
         *              = samples_per_frame_per_channel * 2
         *              = (samples_per_frame_per_channel << 1(audio_lc3_snk.cc))
         * For 2 channel: samples_per_frame_per_channel * 2 * 2
         *              = samples_per_frame_per_channel * 4
         *              = (samples_per_frame_per_channel << 2(audio_lc3_snk.cc))
         */

        audio_snk_write_pl
        (
            (UCHAR *)pcm_buffer,
#if defined(LE_AUDIO_SINK_SYNC_ENABLE) && (LE_AUDIO_SINK_SYNC_ENABLE > 0)
			resampler_samples_out * (audio_lc3_snk.bps / 8U)
#else
            (UINT16)(samples_per_frame_per_channel << audio_lc3_snk.cc) /* Check this */
#endif /*defined(LE_AUDIO_SINK_SYNC_ENABLE) && (LE_AUDIO_SINK_SYNC_ENABLE > 0)*/
        );

#ifdef APPL_SNK_TIMESTAMP_DUMP
        appl_snk_dump_timestamp(3, (UINT16)(samples_per_frame_per_channel << audio_lc3_snk.cc));
#endif /* APPL_SNK_TIMESTAMP_DUMP */
#endif /* AUDIO_SNK_PL_SUPPORT */
    }
    else
    {
    	PRINTF ("^");
    }

    return GA_SUCCESS;
}

#endif /* AUDIO_SNK_LC3_SUPPORT */

GA_RESULT appl_ga_utils_audio_snk_config_audio_dump_files
          (
              UINT8 config_audio_dump,
              UINT8 op
          )
{
    GA_RESULT retval;

    retval = GA_FAILURE;

    /* If we need to enable/disable All(1U) or Predecoded(2U) */
    if ((1U == op) || (2U == op))
    {
#ifdef SNK_DUMP_AUDIO_PREDECODED
        /* Enable(Open) the file */
        if (1U == config_audio_dump)
        {
            snk_dump_audio_predecoded_fd = fopen("snk_dump_audio_predecoded", "wb+");
            if (NULL != snk_dump_audio_predecoded_fd)
            {
                APPL_DBG("Sink Audio Pre-Decoded Dump created successfully\n");
                retval = GA_SUCCESS;
            }
            else
            {
                APPL_DBG("Could not create Sink Audio Pre-Decoded Dump\n");
            }
        }
        /* Disable(Close) the file */
        else if (2U == config_audio_dump)
        {
            if(NULL != snk_dump_audio_predecoded_fd)
            {
                fclose(snk_dump_audio_predecoded_fd);
                snk_dump_audio_predecoded_fd = NULL;
                APPL_DBG("Sink Audio Pre-Decoded Dump closed successfully\n");
            }
        }
        else
        {
            APPL_DBG("Invalid Operation\n");
        }
#else /* SNK_DUMP_AUDIO_PREDECODED */
        APPL_ERR("SNK_DUMP_AUDIO_PREDECODED is not enabled !\n");
#endif /* SNK_DUMP_AUDIO_PREDECODED */
    }
    /* If we need to enable/disable All(1U) or Decoded(3U) */
    if ((1U == op) || (3U == op))
    {
#ifdef SNK_DUMP_AUDIO_DECODED
        /* Enable(Open) the file */
        if (1U == config_audio_dump)
        {
            snk_dump_audio_decoded_fd = fopen("snk_dump_audio_decoded", "wb+");
            if (NULL != snk_dump_audio_decoded_fd)
            {
                APPL_DBG("Sink Audio Decoded Dump created successfully\n");
                retval = GA_SUCCESS;
            }
            else
            {
                APPL_DBG("Could not create Sink Audio Decoded Dump\n");
            }
        }
        /* Disable(Close) the file */
        else if (2U == config_audio_dump)
        {
            if(NULL != snk_dump_audio_decoded_fd)
            {
                fclose(snk_dump_audio_decoded_fd);
                snk_dump_audio_decoded_fd = NULL;
                retval = GA_SUCCESS;
                APPL_DBG("Sink Audio Decoded Dump closed successfully\n");
            }
        }
        else
        {
            APPL_DBG("Invalid Operation\n");
        }
#else /* SNK_DUMP_AUDIO_DECODED */
        APPL_ERR("SNK_DUMP_AUDIO_DECODED is not enabled !\n");
#endif /* SNK_DUMP_AUDIO_DECODED */
    }

    return retval;
}

UINT16 appl_ga_utils_audio_snk_get_fd(void)
{
	return (audio_lc3_snk.fd_in_us / 100U);
}

#endif /* GA_BAP */
#endif /*defined (LC3_DSP) && (LC3_DSP == 1)*/
