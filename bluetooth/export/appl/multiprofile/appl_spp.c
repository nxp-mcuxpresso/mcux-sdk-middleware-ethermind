
/**
 *  \file appl_spp.c
 *
 *  Source file for SPP Command Line Application.
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

/* ----------------------------------------- Header File Inclusion */
#include "appl_spp.h"
#include "vcom_pl.h"

#ifdef APPL_LOG
#undef APPL_LOG
#define APPL_LOG(...)
#endif

#ifdef SPP
/* ----------------------------------------- Exported Global Variables */
/* SPP Handle */
SPP_HANDLE  g_spp_handle;

/* ----------------------------------------- Static Global Variables */
/* Local SPP Server Channel */
DECL_STATIC UINT8 local_server_channel;

/* SPP SDP record handle */
DECL_STATIC UINT32 spp_record_handle;

/* VCOM specific variables */
DECL_STATIC VCOM_HANDLE appl_vcom_handle;
DECL_STATIC CHAR spp_port[16];
DECL_STATIC UINT32 spp_baud;
DECL_STATIC UCHAR spp_flow;

/* ----------------------------------------- Static Function Declarations */
void spp_read_cb(UCHAR * data, UINT16 datalen);

/* ------------------------------------------ Functions */
void spp_read_configuration(void)
{
    UCHAR config_str[18];
    UINT32 value;

    BT_mem_set(config_str, 0x00, sizeof(config_str));
    if (API_SUCCESS != BT_config_read
                       (
                           "EtherMind.conf",
                           "SPP_PORT",
                           (CHAR *)config_str
                       ))
    {
        APPL_LOG("Failed to read SPP_PORT from the Config\n");
    }
    else
    {
        sscanf((const char *)config_str, "%s", spp_port);
        APPL_LOG("SPP Port\t\t\t: %s\n", spp_port);
    }

    BT_mem_set(config_str, 0x00, sizeof(config_str));
    if (API_SUCCESS != BT_config_read
                       (
                           "EtherMind.conf",
                           "SPP_BAUD",
                           (CHAR *)config_str
                       ))
    {
        APPL_LOG("Failed to read SPP_BAUD from the Config\n");
    }
    else
    {
        sscanf((const char *)config_str, "%ld", &value);
        spp_baud = (UINT32)value;
        APPL_LOG("SPP Baudrate\t\t\t: %lu\n", spp_baud);
    }

    BT_mem_set(config_str, 0x00, sizeof(config_str));
    if (API_SUCCESS != BT_config_read
                       (
                           "EtherMind.conf",
                           "SPP_FLOW",
                           (CHAR *)config_str
                       ))
    {
        APPL_LOG("Failed to read SPP_FLOW from the Config\n");
    }
    else
    {
        sscanf((const char *)config_str, "%ld", &value);
        spp_flow = (UCHAR)value;
        APPL_LOG("SPP Flow\t\t\t: %d\n", spp_flow);
    }
}

void spp_appl_init (void)
{
    API_RESULT retval;

    retval = BT_spp_init(spp_application_callback);
    if (API_SUCCESS == retval)
    {
        APPL_LOG("SPP Init Successful!\n");

        spp_read_configuration();

        /* Initialize the VCOM */
        vcom_init_pl();
    }
    else
    {
        APPL_LOG("SPP Init failed. retval = 0x%04X\n", retval);
    }
}

void spp_appl_start (void)
{
    API_RESULT retval;

    APPL_LOG("Starting SPP ...\n");

    BT_dbase_get_record_handle
    (
        DB_RECORD_SPP,
        0,
        &spp_record_handle
    );

    BT_dbase_get_server_channel
    (
        spp_record_handle,
        PROTOCOL_DESC_LIST,
        &local_server_channel
    );

    APPL_LOG("SPP Local Server Channel = %d\n",local_server_channel);

    retval = BT_spp_start( local_server_channel, &g_spp_handle );
    if (API_SUCCESS != retval)
    {
        APPL_LOG("SPP Start failed. retval = 0x%04X\n", retval);
    }

    APPL_LOG("Activating SPP SDP Record...\n");

    /* Get record handle */
    retval = BT_dbase_get_record_handle
             (
                 DB_RECORD_SPP,
                 0,
                 &spp_record_handle
             );

    if (API_SUCCESS != retval)
    {
        APPL_LOG("Failed to get SPP record handle : 0x%04X\n",
        retval);

    }
    else
    {
        APPL_LOG("SPP SDP Rec Handle = 0x%08lX\n",
        spp_record_handle);

        /* Activate record */
        BT_dbase_activate_record(spp_record_handle);
    }
}


void spp_appl_stop (void)
{
    API_RESULT retval;

    retval = BT_spp_stop(g_spp_handle);

    if (API_SUCCESS == retval)
    {
        APPL_LOG("SPP Stop Successful\n");
    }
    else if (SPP_ERR_STOP_PENDING == retval)
    {
        APPL_LOG("SPP Stop Pending\n");
    }
    else if (API_SUCCESS != retval)
    {
        APPL_LOG("SPP Stop failed. retval = 0x%04X\n", retval);
    }
}


void spp_appl_connect (UCHAR * bd_addr, UCHAR server_channel)
{
    API_RESULT retval;

    retval = BT_spp_connect
             (
                 g_spp_handle,
                 bd_addr,
                 server_channel
             );
    if (API_SUCCESS != retval)
    {
        APPL_LOG("SPP Connect failed. retval = 0x%04X\n",retval);
    }
}


void spp_appl_disconnect (void)
{
    API_RESULT retval;

    retval = BT_spp_disconnect(g_spp_handle);
    if (API_SUCCESS != retval)
    {
        APPL_LOG("SPP Disconnect failed. retval = 0x%04X\n",retval);
    }
}


void spp_appl_send_data (UCHAR * data, UINT16 datalen)
{
    API_RESULT retval;

    retval = BT_spp_send
             (
                 g_spp_handle,
                 data,
                 datalen
             );
    if (API_SUCCESS != retval)
    {
        APPL_LOG("Send string failed retval = 0x%04X\n",retval);
    }
}


/* Callback function registered with SPP profile */
API_RESULT spp_application_callback
           (
               /* IN */  SPP_HANDLE spp_handle,
               /* IN */  SPP_EVENTS spp_event,
               /* IN */  API_RESULT      status,
               /* IN */  void          * data,
               /* IN */  UINT16          data_length
           )
{
#if 0
    UINT8   index;
#endif /* 0 */
    UCHAR * l_data;

    l_data = (UCHAR*)( data );

#if 0
    APPL_LOG("\n"\
           "SPP HANDLE : %u\n"\
           "EVENT      : %d\n"\
           "RESULT     : 0x%04X\n",
            (unsigned int) spp_handle, spp_event, status);

    if (API_SUCCESS != status)
    {
        APPL_LOG("\nSPP Command failure\n");
        return API_FAILURE;
    }
#endif /* 0 */

    switch(spp_event)
    {

    case SPP_CONNECT_CNF:
        APPL_LOG("SPP_CONNECT_CNF -> Connection Successful\n");
        APPL_LOG("Remote device " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER " \n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (l_data));

        if (API_SUCCESS == status)
        {
            /* Set the global handle */
            g_spp_handle = spp_handle;

            /* Connect the VCOM */
            appl_vcom_handle = vcom_connect_pl(spp_port, spp_baud, spp_flow, spp_read_cb);
        }

        break;

    case SPP_CONNECT_IND:
        APPL_LOG("SPP_CONNECT_IND -> Connection Successful\n");
        APPL_LOG("Remote device " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER " \n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (l_data));

        /* Set the global handle */
        g_spp_handle = spp_handle;

        /* Connect the VCOM */
        appl_vcom_handle = vcom_connect_pl(spp_port, spp_baud, spp_flow, spp_read_cb);

        break;

    case SPP_DISCONNECT_CNF:
        APPL_LOG("SPP_DISCONNECT_CNF -> Disconnection Successful\n");
        APPL_LOG("Remote device " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER " \n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (l_data));

        if (API_SUCCESS == status)
        {
            /* Disconnect the VCOM */
            vcom_disconnect_pl(appl_vcom_handle);
        }

        break;

    case SPP_DISCONNECT_IND:
        APPL_LOG("SPP_DISCONNECT_IND -> Disconnection Successful\n");
        APPL_LOG("Remote device " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER " \n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (l_data));

        /* Disconnect the VCOM */
        vcom_disconnect_pl(appl_vcom_handle);

        break;

    case SPP_STOP_CNF:
        APPL_LOG("SPP_STOP_CNF -> Stop Successful\n");
        break;

    case SPP_SEND_CNF:
        /* APPL_LOG("SPP_SEND_CNF -> String sent successfully\n"); */
        break;

    case SPP_RECVD_DATA_IND:
#if 0
        APPL_LOG("SPP_RECVD_DATA_IND -> Data received successfully\n");
        APPL_LOG("\n----------------CHAR DUMP-----------------------\n");
        for(index = 0; index <data_length; index++ )
        {
            APPL_LOG("%c ",l_data[index]);
        }
        APPL_LOG("\n------------------------------------------------\n");
        APPL_LOG("\n----------------HEX DUMP------------------------\n");
        for(index = 0; index <data_length; index++ )
        {
            APPL_LOG("%02X ",l_data[index]);
        }
        APPL_LOG("\n------------------------------------------------\n");
#endif /* 0 */

        /* Write to the VCOM */
        vcom_write_pl(appl_vcom_handle, l_data, data_length);

        break;

    default:
        APPL_LOG("\nUnknown command type\n");
        break;
    } /* switch */

    return API_SUCCESS;
}

void spp_read_cb(UCHAR * data, UINT16 datalen)
{
    API_RESULT retval;

    /* printf("~ "); */

    retval = BT_spp_send
             (
                 g_spp_handle,
                 data,
                 datalen
             );
    if (API_SUCCESS != retval)
    {
        printf("SPP send data failed retval = 0x%04X\n", retval);
    }
}

#endif /* SPP */

