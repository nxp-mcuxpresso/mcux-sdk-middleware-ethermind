
/**
 *  \file ots_transport.h
 *
 *  \brief This file defines the Object Transfer Server Transport Module.
 *         This file provides definitions that interact with the L2CAP COC
 *         layer for OTS and translates the callbacks to events to the
 *         registered application.
 */

/*
 *  Copyright (C) 2020. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_OTS_TRANSPORT_
#define _H_OTS_TRANSPORT_

/* --------------------------------------------- Header File Inclusion */
#include "ots_internal.h"

#ifdef OTP_SERVER
/* --------------------------------------------- Global Definitions */

/* --------------------------------------------- Data types /Structures */

/* --------------------------------------------- Macros */
#define OTS_TRANS_IDLE           0x01
#define OTS_TRANS_TX_IN_PROGRESS 0x02
#define OTS_TRANS_RX_IN_PROGRESS 0x03
#define OTS_TRANS_ABORT          0x04
/* --------------------------------------------- APIs */

/**
 *  \brief To Init the OTS module with L2CAP COC layer.
 *
 *  \par Description:
 *       This function initializes OTS transport layer by registering with COC
 *       channel with the PSM. However, the channel identified will be allocated
 *       post connection with a peer OTS. All COC related callbacks are handled
 *       in the callbacks registered and these are translated as events to
 *       higher application layer.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT ots_data_channel_init(void);

/**
 *  \brief To De-Init the OTS module with GATT Layer.
 *
 *  \par Description:
 *       This function removes the callback with the L2CAP COC layer. This call
 *       must be triggered only when there are no applications registered with
 *       OTS module.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT ots_data_channel_deinit(void);

/**
 *  \brief To trigger a L2CAP COC channel disconnect for this OTS session.
 *
 *  \par Description:
 *       This function triggers a L2CAP COC disconnection. On successful
 *       disconnect, OTS_TRANS_DOWN_EVT is notified.
 *
 *  \param [in] lcid
 *         lcid for disconnect
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT ots_data_channel_disconnect(UINT16 lcid);

/**
 *  \brief To trigger a write on L2CAP COC for this OTS session.
 *
 *  \par Description:
 *       This function triggers a L2CAP COC write.
 *
 *  \param [in] dev addr
 *         Remote device address
 *
 *  \param [in] cid
 *         Channel Identifier provided as part of OTC_DATA_CHANNEL_UP_EVT.
 *
 *  \param [in] buffer
 *         Buffer containing packet to be sent
 *
 *  \param [in] buffer_len
 *         Packet length
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT ots_data_channel_write
           (
               /* IN */ BT_DEVICE_ADDR * dev,
               /* IN */ UINT16           cid,
               /* IN */ UCHAR          * buffer,
               /* IN */ UINT16           buffer_len
           );

#endif /* OTP_SERVER */

#endif /* _H_OTS_TRANSPORT_ */
