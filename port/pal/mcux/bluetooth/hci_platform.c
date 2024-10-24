
/**
 *  \file hci_platform.c
 *
 *  This File contains the routines to Transmit and Receive Data from
 *  the FWK_PLATFORM_BLE Transport Layer (Windows Version).
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

/* ----------------------------------------- Header File Inclusion */
#include "BT_hci_api.h"
#include "hci_transport.h"

#ifdef BT_ANALYZER
#include "BT_analyzer.h"
#endif /* BT_ANALYZER */

/* IMX RW610 SDK Includes */
#include "fsl_common.h"
#include "fsl_debug_console.h"

/* Connectivity Framework Includes */
#include "fwk_platform_ble.h"

#ifdef BT_PLATFORM

#define HCI_PLATFORM_TRC(...) PRINTF(__VA_ARGS__)
#define HCI_PLATFORM_INF(...)
#define HCI_PLATFORM_ERR(...) PRINTF(__VA_ARGS__)

/* ----------------------------------------- Function Declarations */

DECL_STATIC void hci_platform_rx_callback(uint8_t packetType, uint8_t *data, uint16_t len);

/* ----------------------------------------- External Global Variables */

/* ----------------------------------------- Static Global Variables */

DECL_STATIC UCHAR hci_platform_wr_buf[HCI_PLATFORM_WR_BUF_SIZE];
DECL_STATIC UCHAR hci_platform_rd_buf[HCI_PLATFORM_MAX_PACKET_SIZE];

/* ----------------------------------------- Functions */

/** HCI-PLATFORM Initialization */
void hci_platform_init (void)
{
    static int init = 0;

    if (init == 0)
    {
        init = 1;

        PLATFORM_SetHciRxCallback(hci_platform_rx_callback);
    }
}

DECL_STATIC void hci_platform_rx_callback(uint8_t packetType, uint8_t *data, uint16_t len)
{
    static UINT16 total_len = 0U;

    hci_platform_rd_buf[0U] = packetType;
    BT_mem_copy (hci_platform_rd_buf + 1U, data, len);
    total_len = len + 1U;

#ifdef HT_ENQUEUE_WITH_RETURN
    uint16_t nbytes = 0U;
    (void)hci_transport_enqueue(hci_platform_rd_buf, total_len, &nbytes);
    assert(nbytes == total_len);
#else /* HT_ENQUEUE_WITH_RETURN */
    hci_transport_enqueue(hci_platform_rd_buf, total_len);
#endif /* HT_ENQUEUE_WITH_RETURN */
}

/** HCI-PLATFORM Bluetooth-ON Initialization */
void hci_platform_bt_init(void)
{
    PLATFORM_StartHci();
}

/** HCI-PLATFORM Bluetooth-OFF Shutdown */
void hci_platform_bt_shutdown (void)
{
    /* nothing to do */
}

/** HCI-PLATFORM Send Data */
API_RESULT hci_platform_send_data
           (UCHAR type, UCHAR * buf, UINT16 length, UCHAR flag)
{
    static INT32 total_len = 0U;
    static INT32 cur_len = 0U;
    static UCHAR acl_data_pkt = BT_FALSE;

    if (0 != flag)
    {
        if (HCI_ACL_DATA_PACKET == type)
        {
            acl_data_pkt = BT_TRUE;
            total_len = ((buf[3U] << 8U) | buf[2U]) + 5U;
        }
        else
        {
            total_len = length + 1U;
        }

        if (HCI_PLATFORM_WR_BUF_SIZE < total_len)
        {
            HCI_PLATFORM_ERR(
            "[HCI-PLATFORM] HCI Packet Size %d exceeds Configuration %d bytes\n",
            total_len, HCI_PLATFORM_WR_BUF_SIZE);

            return API_FAILURE;
        }
    }

    if (0U != acl_data_pkt)
    {
        if (0U == cur_len)
        {
            hci_platform_wr_buf[0U] = type;
            cur_len = 1U;
        }

        BT_mem_copy (hci_platform_wr_buf + cur_len, buf, length);
        cur_len += length;

        if (cur_len != total_len)
        {
            return API_SUCCESS;
        }
    }
    else
    {
        hci_platform_wr_buf[0U] = type;
        BT_mem_copy (hci_platform_wr_buf + 1U, buf, length);
        total_len = length + 1U;
    }

    /* Send HCI message to PLATFORM transport abstraction layer */
    PLATFORM_SendHciMessage(hci_platform_wr_buf, total_len);

    /* Transmitted packet logging in btanalyzer format */
    BT_analyzer_write_packet(hci_platform_wr_buf[0U], 0U, &hci_platform_wr_buf[1], (total_len - 1U));

    /* Re-initialize */
    cur_len = 0U;
    total_len = 0U;
    if (BT_FALSE != acl_data_pkt)
    {
        acl_data_pkt = BT_FALSE;
    }

    return API_SUCCESS;
}

API_RESULT hci_transport_write_data (UCHAR type, UCHAR * buf, UINT16 length, UCHAR flag)
{
	   return hci_platform_send_data(type, buf, length, flag);
}

#endif /* BT_PLATFORM */

