
/**
 *  \file l2cap_coc.h
 *
 *  \brief Application Header File for L2CAP
 *  Credit Based Flow Control(CBFC) connection oriented channel handling.
 *
 *  This Header File contains declaration of APIs, Macros and
 *  Constant Definitions.
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_L2CAP_COC_
#define _H_L2CAP_COC_

/* --------------------------------------------- Header File Inclusion */
#include "GA_common.h"
#include "GA_bearer_api.h"
#include "BT_features.h"

#define L2CAP_SUPPORT_CBFC_MODE
#define L2CAP_SUPPORT_ECBFC_MODE

/* --------------------------------------------- Global Definitions */

#ifdef L2CAP_SUPPORT_ECBFC_MODE

/*
 *  Maximum number of enhanced credit based Flow Control PSM that L2CAP needs
 *  to support.
 *
 *  Minimum Value: 1
 *  Maximum Value: as required.
 */
#define OTP_L2CAP_MAX_ECBFC_PSM      2U

#define OTP_L2CAP_ECBFC_MAX_NUM_CIDS 5U
#define OTP_L2CAP_COC_MAX_NUM_CIDS   5U
#else
#define OTP_L2CAP_COC_MAX_NUM_CIDS 1
#endif

/* --------------------------------------------- Structures/Data Types */
#if ((defined L2CAP_SUPPORT_CBFC_MODE) || (defined L2CAP_SUPPORT_ECBFC_MODE))



/**
 *  The structure representing the Connection Parameter for
 *  L2CAP Credit Based Flow Control Mode.
 */
typedef struct _OTP_L2CAP_CBFC_CONNECT_PARAM
{
    /**
     * MTU - Maximum SDU Size
     *
     * The MTU field specifies the maximum SDU size (in octets) that the L2CAP
     * layer entity sending the LE Credit Based Connection Request can receive
     * on this channel. L2CAP implementations shall support a minimum MTU size
     * of 23 octets.
     */
    UINT16   mtu;

    /**
     * MPS - Maximum PDU Size
     *
     * The MPS field specifies the maximum payload size (in octets) that the
     * L2CAP layer entity sending the LE Credit Based Connection Request is
     * capable of receiving on this channel. L2CAP implementations shall support
     * a minimum MPS of 23 octets and may support an MPS up to 65533 octets.
     */
    UINT16   mps;

    /**
     * Initial number of Credits
     *
     * The initial credit value indicates the number of LE-frames that the peer
     * device can send to the L2CAP layer entity sending the LE Credit Based
     * Connection Request. The initial credit value shall be in the range of 0 to
     * 65535.
     */
    UINT16   credit;

#ifdef L2CAP_CBFC_CONNECT_WITH_CID_CONTEXT
    /**
     * Local/Remote Channel Identifier
     *
     * - Local CID when l2ca_cbfc_connect_req() returns
     * - Remote CID when l2ca_connect_ind_cb()/l2ca_connect_cnf_cb()
     *   for CBFC PSM is invoked
     */
    UINT16   cid;
#endif /* L2CAP_CBFC_CONNECT_WITH_CID_CONTEXT */

}OTP_L2CAP_CBFC_CONNECT_PARAM;

/**
 *  The structure representing the Connection Parameter for
 *  L2CAP Enhanced Credit Based Flow Control Mode.
 */
typedef struct _OTP_L2CAP_ECBFC_CONNECT_PARAM
{
    /**
     * MTU - Maximum SDU Size
     *
     * The MTU field specifies the maximum SDU size (in octets) that the L2CAP
     * layer entity sending the Enhanced Credit Based Connection Request can receive
     * on this channel. L2CAP implementations shall support a minimum MTU size
     * of 23 octets.
     */
    UINT16   mtu;

    /**
     * MPS - Maximum PDU Size
     *
     * The MPS field specifies the maximum payload size (in octets) that the
     * L2CAP layer entity sending the Enhanced Credit Based Connection Request is
     * capable of receiving on this channel. L2CAP implementations shall support
     * a minimum MPS of 23 octets and may support an MPS up to 65533 octets.
     */
    UINT16   mps;

    /**
     * Initial number of Credits
     *
     * The initial credit value indicates the number of LE-frames that the peer
     * device can send to the L2CAP layer entity sending the Enhanced Credit Based
     * Connection Request. The initial credit value shall be in the range of 0 to
     * 65535.
     */
    UINT16   credit;

    /**
     * Source or Destination CID
     * - based on if used with connection request or response
     *
     * The Source CID is an array of 5 two octet values and represents the channel
     * endpoints on the device sending the request.
     *
     * The Destination CID is an array of 5 two octet values and represents
     * the channel endpoints on the device sending the response.
     */
    UINT16   cid[OTP_L2CAP_ECBFC_MAX_NUM_CIDS];

    /** Number of L2CAP Channels to be connected or requested for connection */
    UINT8    num_cids;

}OTP_L2CAP_ECBFC_CONNECT_PARAM;


/**
 *  The structure representing the Reconfiguration Parameter for
 *  L2CAP Enhanced Credit Based Flow Control Mode.
 */
typedef struct _OTP_L2CAP_ECBFC_RECONFIG_PARAM
{
    /**
     * MTU - Maximum SDU Size
     *
     * The MTU field specifies the maximum SDU size (in octets) that the L2CAP
     * layer entity sending the Enhanced Credit Based Connection Request can receive
     * on this channel. L2CAP implementations shall support a minimum MTU size
     * of 23 octets.
     */
    UINT16   mtu;

    /**
     * MPS - Maximum PDU Size
     *
     * The MPS field specifies the maximum payload size (in octets) that the
     * L2CAP layer entity sending the Enhanced Credit Based Connection Request is
     * capable of receiving on this channel. L2CAP implementations shall support
     * a minimum MPS of 23 octets and may support an MPS up to 65533 octets.
     */
    UINT16   mps;

    /* TODO: Below comment to be updated */
    /**
     * Source or Destination CID
     * - based on if used with connection request or response
     *
     * The Source CID is an array of 5 two octet values and represents the channel
     * endpoints on the device sending the request.
     *
     * The Destination CID is an array of 5 two octet values and represents
     * the channel endpoints on the device sending the response.
     */
    UINT16   cid[OTP_L2CAP_ECBFC_MAX_NUM_CIDS];

    /** Number of L2CAP Channels to be reconfigured */
    UINT8    num_cids;

}OTP_L2CAP_ECBFC_RECONFIG_PARAM;

typedef struct psm_struct_coc
{
    /**
     * Callback to inform application of the incoming L2CAP CBFC/ECBFC
     * Connection Request.
     *
     * l2cap_coc_conn_ind_cb provides following parameters to the
     * application:
     *     1. Pointer to Device Queue Handle: the peer device sending the
     *        request.
     *     2. CID: Channel Identifier.
     *     3. PSM: LE Protocol/Service Multiplexer.
     *     4. CBFC/ECBFC connect Request Parameters (MTU, MPS and
     *        Initial Credits)
     *        Type OTP_L2CAP_ECBFC_CONNECT_PARAM in case of
     *        L2CAP_COC_ECBFC_MODE mode.
     *        Type OTP_L2CAP_CBFC_CONNECT_PARAM in case of L2CAP_COC_CBFC_MODE
     *        mode.
     *     5. L2CAP COC Mode: L2CAP COC Mode on which connection indication
     *                        is received.
     */
    GA_RESULT(* l2cap_coc_conn_ind_cb)(UCHAR *, UINT16 *,
        UINT16, void *, UCHAR);

    /**
     * Callback to inform application of the L2CAP CBFC/ECBFC Connection
     * Response/Confirmation.
     *
     * l2cap_coc_conn_cnf_cb provides following parameters to the
     * application:
     *     1. Pointer to Device Queue Handle: the peer device sending the
     *        request.
     *     2. CID: Channel Identifier.
     *     3. PSM: LE Protocol/Service Multiplexer.
     *     4. Result: A result value of 0x0000 indicates success while a
     *                non-zero value indicates the connection request was
     *                refused.
     *     5. CBFC/ECBFC connect Request Parameters (MTU, MPS and
     *        Initial Credits)
     *        Type OTP_L2CAP_ECBFC_CONNECT_PARAM in case of
     *        L2CAP_COC_ECBFC_MODE mode.
     *        Type OTP_L2CAP_CBFC_CONNECT_PARAM in case of L2CAP_COC_CBFC_MODE
     *        mode.
     *     6. L2CAP COC Mode: L2CAP COC Mode on which connection indication
     *                        is received.
     */
    GA_RESULT(* l2cap_coc_conn_cnf_cb)(UCHAR *, UINT16 *,
        UINT16, UINT16, void *, UCHAR);

#ifdef L2CAP_SUPPORT_ECBFC_MODE
    /**
     * Callback to inform application of the incoming L2CAP ECBFC
     * Reconfiguration Request.
     *
     * This needs to be NULL in case of registered L2CAP Mode is CBFC.
     *
     * l2cap_coc_reconfig_ind_cb provides following parameters to the
     * application:
     *     1. Pointer to Device Queue Handle: the peer device sending the
     *        request.
     *     2. CID: List of Channel Identifiers.
     *     3. ECBFC Reconfiguration Request Parameters (MTU, MPS
     *        and Num of CIDs in Reconfig Request)
     */
    GA_RESULT(* l2cap_coc_reconfig_ind_cb)(UCHAR *, UINT16 *,
        OTP_L2CAP_ECBFC_RECONFIG_PARAM *);

    /**
     * Callback to inform application of the L2CAP ECBFC Reconfig
     * Response/Confirmation.
     *
     * This needs to be NULL in case of registered L2CAP Mode is CBFC.
     *
     * l2cap_coc_reconfig_cnf_cb provides following parameters to the
     * application:
     *     1. Pointer to Device Queue Handle: the peer device sending the
     *        response.
     */
    GA_RESULT(* l2cap_coc_reconfig_cnf_cb)(UCHAR *);
#endif /* L2CAP_SUPPORT_ECBFC_MODE */

    /**
     * Callback to inform application of the L2CAP CBFC/ECBFC Disconnection
     * Request received from the Peer device. This callback is for the
     * responder of the L2CAP Disconnection request.
     *
     * l2cap_coc_disconnect_ind_cb provides following parameters to the
     * application:
     *     1. CID: Channel Identifier of a previously connected channel.
     *     2. L2CAP COC Mode: L2CAP COC Mode on which disconnection indication
     *                        is received.
     *
     * Note: On receiving this callback, previously connected channel for which
     * disconnection is initiated by the peer device will be considered closed.
     */
    GA_RESULT(* l2cap_coc_disconnect_ind_cb)(UINT16, UCHAR);

    /**
     * Callback to inform application of the L2CAP CBFC/ECBFC Disconnection
     * confirmation/Response received from the Peer device. This callback is
     * for the initiator of the L2CAP Disconnection request.
     *
     * l2cap_coc_disconnect_cnf_cb provides following parameters to the
     * application:
     *     1. CID: Channel Identifier of a previously connected channel
     *             for which disconnection was initiated by local device.
     *     2. Result: A result value of 0x0000 indicates success while a
     *                non-zero value indicates the disconnection request
     *                has failed (timed out).
     *     3. L2CAP COC Mode: L2CAP COC Mode on which disconnection
     *                        confirmation is received.
     * Note: Irrespective of the 'Result' is success/failure, once the local
     * device has initiated L2CAP Disconnection, the channel will be
     * considered closed.
     */
    GA_RESULT(* l2cap_coc_disconnect_cnf_cb)(UINT16, UINT16, UCHAR);


    /**
     * Callback to inform application of data received over L2CAP CBFC/ECBFC
     * channel.
     *
     * l2cap_coc_data_read_cb provides following parameters to the
     * application:
     *     1. CID: Channel Identifier of a previously connected channel.
     *     2. Result: A result value of 0x0000 indicates success, while a
     *                non-zero value indicates an error condition
     *                (e.g. peer device violating credit flow, or MTU
     *                 size limit)
     *     3. Buffer Pointer: Data/payload received from the peer device.
     *     4. Buffer Length: Receieved data/payload length.
     */
    GA_RESULT(* l2cap_coc_data_read_cb)(UINT16, UINT16, UCHAR *, UINT16);

    /**
     * Callback to inform application of receive credits reached low water
     * mark or below.
     * After receiving L2CAP data/payload from peer device for a specification
     * Channel, the available credits are calculated. If the credit count
     * reaches or goes below the low water mark, this callback is called to
     * inform application of the condition, so that if application wants can
     * send more credits to the peer device.
     *
     * l2cap_coc_rx_credit_ind provides following parameters :
     *     1. CID: Channel Identifier of a previously connected channel.
     *     2. Receive Credits: The current received credits count.
     */
    GA_RESULT(* l2cap_coc_rx_credit_ind) (UINT16, UINT16);

    /**
     * Callback to inform application of having received transmit credits.
     * This callback is called on receiving LE Flow Control Credit from peer
     * device.
     *
     * l2cap_coc_tx_credit_ind provides following parameters to the
     * application:
     *     1. CID: Channel Identifier of a previously connected channel.
     *     2. Result: A result value of 0x0000 indicates success, while a
     *                non-zero value indicates an error condition
     *                (e.g. credit overflow, if total number of credits
     *                crosses specification defined maximum limit of 0xFFFF)
     *     3. Transmit Credits: The cumulative transmit credit count.
     *                          This is the number of LE-frames that can be
     *                          sent to the peer device sending the LE Flow
     *                          Control Credit packet.
     */
    GA_RESULT(* l2cap_coc_tx_credit_ind) (UINT16, UINT16, UINT16);

    /** The LE Protocol/Service Multiplexer */
    UINT16 psm;

#if ((defined L2CAP_CBFC_SUPPORT_UL_CREDIT_LWM) || (defined L2CAP_ECBFC_SUPPORT_UL_CREDIT_LWM))
    /** Upper Layer defined Receive Credit Low Water Mark */
    UINT16 credit_lwm;
#endif /* L2CAP_CBFC_SUPPORT_UL_CREDIT_LWM */

    /**
     * Callback to inform application of data transmission completion over
     * L2CAP CBFC/ECBFC channel.
     *
     * l2cap_coc_data_write_cb provides following parameters to the
     * application:
     *     1. CID: Channel Identifier of a previously connected channel.
     *     2. Result: A result value of 0x0000 indicates success, while a
     *                non-zero value indicates an error condition
     *                (e.g. peer device violating credit flow, or MTU size
     *                 limit)
     *     3. Buffer Pointer: Currently NULL. For future usage.
     *     4. Buffer Length: Currently 0. For future usage.
     */
    GA_RESULT(* l2cap_coc_data_write_cb)(UINT16, UINT16, UCHAR *, UINT16);

    /** L2CAP COC mode */
    UCHAR l2cap_coc_mode;

    /** L2CAP Local CID: 1 in case of CBFC mode and 1 or >1 in ECBFC mode */
    UINT16 lcid[OTP_L2CAP_COC_MAX_NUM_CIDS];

    /** L2CAP Number of Local CID */
    UINT8 num_cids;

}OTP_L2CAP_PSM_COC;
#endif /* L2CAP_SUPPORT_CBFC_MODE || L2CAP_SUPPORT_ECBFC_MODE */

/* --------------------------------------------- Macros */
/**
 *   L2CAP COC Channel Mode
 */

typedef UINT8 L2CAP_COC_MODE;

#define L2CAP_COC_CBFC_MODE                       1U
#define L2CAP_COC_ECBFC_MODE                      2U

#ifdef L2CAP_SUPPORT_CBFC_MODE
#define OTP_L2CAP_MAX_COC_CBFC                    2U
#endif /* L2CAP_SUPPORT_CBFC_MODE */

#ifdef L2CAP_SUPPORT_ECBFC_MODE
#define OTP_L2CAP_MAX_COC_ECBFC                   2U
#endif /* L2CAP_SUPPORT_ECBFC_MODE */

/* --------------------------------------------- Internal Functions */
/**
 *  \cond ignore_this Internal
 */
 /* Capture the internal functions needed here */
 /** \endcond */


/* --------------------------------------------- API Declarations */

/**
 * \defgroup l2cap_coc API Definitions
 * \{
 * This section describes the EtherMind L2CAP COC Handler functions.
 */
#if ((defined L2CAP_SUPPORT_CBFC_MODE) || (defined L2CAP_SUPPORT_ECBFC_MODE))
/**
 *  \brief To register a higher level protocol (PSM) which supports
 *  CBFC/ECBFC mode over L2CAP.
 *
 *  \par Description:
 *  This API registers a new upper layer protocol, or, PSM to L2CAP,
 *  along with the set of callbacks, for the L2CAP CBFC/ECBFC mode.
 *
 *  \param [in] psm
 *         This parameter must be a pointer to the L2CAP_PSM_COC variable
 *         containing the PSM value of the higher-level protocol and
 *         the set of callbacks for this protocol (PSM).
 *
 *  \return GA_RESULT
 *          - GA_SUCCESS: If successful.
 *          - Error Codes: Error code describing cause of failure.
 */
 GA_RESULT l2cap_coc_register_psm
            (
                /* IN */ OTP_L2CAP_PSM_COC * psm
            );

/**
 *  \brief To de-register an Upper Layer LE_PSM from L2CAP.
 *
 *  \par Description:
 *  This API de-registers a upper layer protocol, or, LE_PSM from L2CAP,
 *  for the L2CAP CBFC/ECBFC mode.
 *
 *  \param [in] psm
 *         Already registered LE Protocol/Service Multiplexer for L2CAP
 *         CBFC/ECBFC Mode.
 *
 *  \param [in] l2cap_coc_mode
 *         L2CAP COC mode registered for this PSM.
 *
 *  \return GA_RESULT
 *          - GA_SUCCESS: If successful.
 *          - Error Codes: Error code describing cause of failure.
 *  \note
 *  It must be noted that this routine can succeed for a registered
 *  LE_PSM only if there exists no active L2CAP channels for it.
 */
GA_RESULT l2cap_coc_unregister_psm
           (
               /* IN */ UINT16  psm,
               /* IN */ UCHAR   l2cap_coc_mode
           );


/**
 *  \brief To establish L2CAP channel for CBFC/ECBFC mode.
 *
 *  \par Description:
 *  This L2CAP service interface initiates L2CAP channel establishment
 *  procedure for CBFC/ECBFC mode, to the specified remote Bluetooth device,
 *  for the specified PSM representing an upper layer protocol above L2CAP.
 *
 *  \param [in] handle
 *         Device handle of the peer device.
 *  \param [in] remote_psm
 *         Remote PSM, representing the upper layer protocol above L2CAP.
 *  \param [in] local_psm
 *         Local PSM, representing the upper layer protocol above L2CAP.
 *  \param [in] l2cap_coc_mode
 *         L2CAP COC mode registered for this PSM.
 *  \param [in] param
 *         This parameter must be a pointer to OTP_L2CAP_CBFC_CONNECT_PARAM
 *         in case of L2CAP_COC_CBFC_MODE or OTP_L2CAP_ECBFC_CONNECT_PARAM
 *         in case of L2CAP_COC_ECBFC_MODE
 *         containing the connection parameters for the L2CAP channel.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure
 */
GA_RESULT l2cap_coc_connect_req
           (
               /* IN */ UCHAR *  handle,
               /* IN */ UINT16           remote_psm,
               /* IN */ UINT16           local_psm,
               /* IN */ UCHAR            l2cap_coc_mode,
               /* IN */ void *           param
           );

/**
 *  \brief To respond to an incoming L2CAP connection request for
 *  CBFC/ECBFC mode.
 *
 *  \par Description:
 *  This L2CAP service interface enables an upper layer protocol to respond
 *  to L2CAP connection request for LE CBFC/ECBFC mode
 *  for the specified PSM from the specified remote Bluetooth device.
 *  It is mandatory that the upper layer PSM always responds back by calling
 *  this service interface upon receiving CBFC/ECBFC Connection Request.
 *  The channel is established (opened) only when the PSM concerned responds
 *  back with successful response. Otherwise, the channel establishment request
 *  from the peer will be rejected by L2CAP with appropriate result
 *  and status as received from the upper layer PSM.
 *
 *  \param [in] local_cid
 *         TODO: Edit the text below to take care of list of CIDs
 *
 *         This parameter specifies the local L2CAP channel end-points for
 *         this new set of L2CAP channels. On receipt of L2CAP Connect Request command
 *         from the peer, local L2CAP will temporarily create a channel -
 *         this parameter identifies the new channel.
 *         If the upper layer PSM chooses to reject this connection,
 *         this temporary channel will be closed.
 *  \param [in] local_cid_len
 *         Number of Local CIDs
 *  \param [in] response
 *         This parameter specifies the response of the upper layer for
 *         the new L2CAP channel establishment request from the peer.
 *         It must be set to a value as specified in L2CAP Connect Result Codes.
 *  \param [in] l2cap_coc_mode
 *         L2CAP COC mode registered for this PSM.
 *  \param [in] param
 *         This parameter must be a pointer to OTP_L2CAP_CBFC_CONNECT_PARAM
 *         in case of L2CAP_COC_CBFC_MODE or OTP_L2CAP_ECBFC_CONNECT_PARAM
 *         in case of L2CAP_COC_ECBFC_MODE
 *         containing the connection parameters for the L2CAP channel.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure
 */
GA_RESULT l2cap_coc_connect_rsp
           (
               /* IN */ UINT16 *  local_cid,
               /* IN */ UINT16    local_cid_len,
               /* IN */ UINT16    response,
               /* IN */ UCHAR     l2cap_coc_mode,
               /* IN */ void *    param
           );

/**
 *  \brief To reconfigure L2CAP channel for Enhanced Credit Based Flow Control mode.
 *
 *  \par Description:
 *  This L2CAP service interface initiates L2CAP channel reconfiguration
 *  procedure for ECBFC mode, to the specified remote Bluetooth device.
 *
 *  \param [in] handle
 *         Device handle of the peer device.
 *  \param [in] param
 *         This parameter must be a pointer to the GA_L2CAP_ECBFC_RECONFIG_PARAM
 *         variable containing the reconfiguration parameters for the L2CAP channel.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure
 */
GA_RESULT l2cap_coc_reconfig_req
           (
               /* IN */ UCHAR *  handle,
               /* IN */ void          *  param
           );

/**
 *  \brief To respond to an incoming L2CAP reconfiguration request for
 *  Enhanced Credit Based Flow Control mode.
 *
 *  \par Description:
 *  This L2CAP service interface enables an upper layer protocol to respond
 *  to L2CAP reconfiguration request for Enhanced Credit Based Flow Control mode
 *  for the already established L2CAP Channels in ECBFC mode.
 *  It is mandatory that the upper layer PSM always responds back by calling
 *  this service interface upon receiving ECBFC Reconfiguration Request.
 *
 *  \param [in] local_cid
 *         TODO: Edit the text below to take care of list of CIDs
 *
 *         This parameter specifies the local L2CAP channel end-points for
 *         this new set of L2CAP channels. On receipt of L2CAP Connect Request command
 *         from the peer, local L2CAP will temporarily create a channel -
 *         this parameter identifies the new channel.
 *         If the upper layer PSM chooses to reject this connection,
 *         this temporary channel will be closed.
 *  \param [in] local_cid_len
 *         Number of Local CIDs
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure
 */
GA_RESULT l2cap_coc_reconfig_rsp
           (
               UINT16 *  local_cid,
               UINT16    local_cid_len
           );

/**
 *  \brief To send Flow Control Credit packet for CBFC/ECBFC Mode.
 *
 *  \par Description:
 *  This L2CAP service interface enables an upper layer protocol to send
 *  Flow Control Credit packet to remote Bluetooth device, when it is
 *  capable of receiving additional LE-frames.
 *
 *  \param [in] local_cid
 *         This parameter specifies the local channel end-point for the L2CAP
 *         channel. For initiator of L2CAP channel establishment, this must be
 *         set to the value indicated by the L2CA_ConnectCNF callback.
 *         For responder, upper layer protocol obtains this value when L2CAP
 *         invokes L2CA_ConnectIND callback.
 *  \param [in] credit
 *         The credit value field represents number of credits the receiving
 *         device can increment, corresponding to the number of LE-frames
 *         that can be sent to the peer device sending the Flow Control
 *         Credit packet.
 *         The credit value field shall be a number between 1 and 65535.
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure
 */
GA_RESULT l2cap_coc_send_flow_control_credit
           (
               /* IN */ UINT16  local_cid,
               /* IN */ UINT16  credit
           );

/**
 *  \brief To write on an L2CAP CBFC/ECBFC Channel.
 *
 *  \par Description:
 *  This API is used to send a packet on L2CAP CBFC/ECBFC channel.
 *
 *  \param [in] UCHAR
 *         Device handle of the peer device.
 *  \param [in] cid
 *         This parameter specifies the local channel end-point for the L2CAP
 *         channel. For initiator of L2CAP channel establishment, this must be
 *         set to the value indicated by the L2CA_ConnectCNF callback.
 *         For responder, upper layer protocol obtains this value when L2CAP
 *         invokes L2CA_ConnectIND callback.
 *  \param [in] buffer
 *         Buffer containing packet to be sent
 *  \param [in] buffer_len
 *         Packet length
 *
 *  \return GA_SUCCESS or an error code indicating reason for failure
 *
 *  \note
 *
 *  LE Information frame (LE-Frame) packet format:
 *
 *    16    16    16       n
 *  +-----+-----+-----+---...---+
 *  |  L  |  C  |  S  |    I    |
 *  +-----+-----+-----+---...---+
 *  LSB                       MSB
 *  <-   BLH  ->
 *
 *  BLH: Basic L2CAP Header (4 Octets).
 *  L: Length (2 Octets) and C: Channel ID (2 Octets) of Basic L2CAP Header.
 *  S: L2CAP SDU Length (2 Octets) present in first LE Frame of the SDU.
 *  I: Information Payload ('n' Octets)
 *     For first LE-frame of the SDU, 'n' = L - 2
 *     For subsequent LE-frames, 'n' = L
 *
 *  There are two ways 'buffer' and 'buffer_len' can be passed to this interface,
 *  and that dependts on if 'L2CAP_ALLOC_FOR_CBFC_SDU' feature flag is defined
 *  or not.
 *
 *  If 'L2CAP_ALLOC_FOR_CBFC_SDU' feature flag is defined:
 *  - 'buffer' shall only contain Information Payload.
 *  - 'buffer_len' shall contain the length of the Information Payload.
 *  - L2CAP will allocate memory for complete LE-frame, including associated
 *    header and copy the application provided Information Payload in 'buffer'.
 *    Application can free (if allocated) or reuse the 'buffer' once this API
 *    returns.
 *  - If the 'buffer' is allocated, application can free the memory
 *    on return of this API.
 *
 *  If 'L2CAP_ALLOC_FOR_CBFC_SDU' feature flag is not defined:
 *  - 'buffer' shall have additional 6 Octets of memory for L2CAP header,
 *    and have L2CAP SDU Length field and Information Payload filled.
 *    L2CAP will costruct the remaining Basic L2CAP Header fields,
 *    in the 'buffer' provided by the caller.
 *  - 'buffer_len' shall contain the length 'L2CAP SDU Length' field
 *    in addition to the length of Information Payload (i.e., all the octets
 *    filled by the caller).
 *  - L2CAP will assume the caller has provided an allocate memory for
 *    the complete LE-frame. L2CAP will frame the Basic L2CAP Header in the
 *    provied buffer. L2CAP will free the application 'buffer' once the
 *    transmission of SDU is complete.
 *  - If the 'buffer' is allocated, application shall not free the memory
 *    on return of this API. Application shall free the buffer in the handling
 *    of corresponding Tx complete callback l2ca_data_write_cb().
 *
 *  In general, for memory constaint devices, 'L2CAP_ALLOC_FOR_CBFC_SDU'
 *  should not be defined.
 *  This is to avoid allocation of buffer for L2CAP SDU in the L2CAP implementation
 *  and also to avoid copying the data from application buffer to L2CAP buffer
 *  (as much as possible).
 *  In some cases where the SDU has to be segmented to smaller PDUs, based on the MTU
 *  and MPS value, L2CAP needs to frame the PDUs from the SDU provided by the application.
 */
GA_RESULT l2cap_coc_data_write
           (
               /* IN */ UCHAR *  handle,
               /* IN */ UINT16           cid,
               /* IN */ UCHAR         *  buffer,
               /* IN */ UINT16           buffer_len
           );

/**
 *  \brief To disconnect the L2CAP COC Channel
 *
 *  \par Description:
 *  This API implements the L2CAP_DisconnectREQ service primitive for CBFC and
 *  ECBFC mode, which is used by the L2CAP upper layers to disconnect a L2CAP
 *  connection-oriented data channel.
 *
 *  \param local_cid (IN)
 *         Local Channel Identifier for the L2CAP CBFC/ECBFC channel
 *
 *  \return GA_RESULT:
 *          GA_SUCCESS on success, or, an Error Code (see BT_error.h)
 *          describing the cause of failure.
 */
GA_RESULT l2cap_coc_disconnect_req
           (
               /* IN */  UINT16  local_cid
           );
#endif /* L2CAP_SUPPORT_CBFC_MODE || L2CAP_SUPPORT_ECBFC_MODE */

#endif /* _H_L2CAP_COC_ */


