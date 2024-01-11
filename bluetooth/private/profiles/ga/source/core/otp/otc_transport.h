
/**
 *  \file otc_transport.h
 *
 *  \brief This file defines the Object Transfer Client Transport Module.
 *         This file provides definitions that interact with the L2CAP COC
 *         layer for OTC and translates the callbacks to events to the
 *         registered application.
 */

/*
 *  Copyright (C) 2020. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_OTC_TRANSPORT_
#define _H_OTC_TRANSPORT_

/* --------------------------------------------- Header File Inclusion */
#include "otc_internal.h"

#ifdef OTP_CLIENT
/* --------------------------------------------- Global Definitions */

/* --------------------------------------------- Data types /Structures */

/* --------------------------------------------- Macros */
#define OTS_TRANS_IDLE           0x01
#define OTS_TRANS_TX_IN_PROGRESS 0x02
#define OTS_TRANS_RX_IN_PROGRESS 0x03
#define OTS_TRANS_ABORT          0x04

#define OTP_DATA_CHANNEL_DISCONNECTED 0x00
/* --------------------------------------------- APIs */

/**
 *  \brief To Init the OTC module with L2CAP COC layer.
 *
 *  \par Description:
 *       This function initializes OTC transport layer by registering with COC
 *       channel with the PSM. However, the channel identified will be allocated
 *       post connection with a peer OTS. All COC related callbacks are handled
 *       in the callbacks registered and these are translated as events to
 *       higher application layer.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
GA_RESULT otc_data_channel_init(void);

/**
 *  \brief To De-Init the OTC module with GATT Layer.
 *
 *  \par Description:
 *       This function removes the callback with the L2CAP COC layer. This call
 *       must be triggered only when there are no applications registered with
 *       OTC module.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
GA_RESULT otc_data_channel_deinit(void);

/**
 *  \brief To trigger a L2CAP COC channel for this OTC session.
 *
 *  \par Description:
 *       This function triggers a L2CAP COC connection and once the connection
 *       is successful, the context maintained for this registered index will be
 *       updated with the channel identifier. If the OTC transport already
 *       exists for this session on this device, returns accordingly. Handling
 *       of connection response etc.,. are handled internally. On successful
 *       channel connection, OTC_TRANS_UP_EVT is notified.
 *
 *  \param [in] otc_sess_id
 *         This provides the device address, handle
 *
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
GA_RESULT otc_data_channel_connect(OTP_CE_SESSION_ID otc_sess_id);

/**
 *  \brief To trigger a L2CAP COC channel disconnect for this OTC session.
 *
 *  \par Description:
 *       This function triggers a L2CAP COC disconnection. On successful
 *       disconnect, OTS_TRANS_DOWN_EVT is notified.
 *
 *  \param [in] otc_reg_inst
 *         This provides the device address, handle
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
GA_RESULT otc_data_channel_disconnect(OTP_CE_SESSION_ID otc_sess_id);

#endif /* OTP_CLIENT */

#endif /* _H_OTC_TRANSPORT_ */
