
/**
 *  \file GA_bearer_api.h
 *
 *  \brief This file defines the GA bearer Interface - includes
 *  Data Structures and Methods.
 */

/*
 *  Copyright (C) 2020. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_GA_BEARER_API_
#define _H_GA_BEARER_API_

/* --------------------------------------------- Header File Inclusion */
#include "GA_common.h"

/**
 * \addtogroup bt_ga
 * \{
 */

/* --------------------------------------------- Global Definitions */
/**
 * \defgroup ga_bearer_module Bearer
 * \{
 * \brief This section describes the interfaces & APIs offered by the EtherMind
 * GA Bearer module.
 */

/**
 * \defgroup ga_brr_defines Defines
 * \{
 * \brief Describes defines for the module.
 */

/**
 * \defgroup ga_brr_macros Utility Macros
 * \{
 * \brief This section describes the various Utility and functional Macros in
 * EtherMind GA Bearer Layer.
 */

/**
 * \name Miscellaneous Macros
 * \{
 */

/** Unreferenced variable macro to avoid compilation warnings */
#define GA_IGNORE_UNUSED_PARAM(v) (void)(v)

/** \} */
/** \} */

/**
 * \defgroup ga_brr_error_code Error Codes
 * \{
 * \brief This section lists the Error Codes that are provided as part of
 * return of functionalities of Bearer.
 */

/**
 * \name Bearer - GA Result Error Codes
 * \{
 * \brief This section lists the error codes for GA Result.
 */

/** Represents Operation is Success */
#define GA_SUCCESS                                  0x0000U

/** Represents Operation is Failure */
#define GA_FAILURE                                  0xFFFFU

/** Represents Event is consumed */
#define GA_EVT_CONSUMED                             0x8000U

/** Represents Operation is not complete, Events to Follow */
#define GA_CONTINUE                                 0x00C0U

/** \} */

/* TODO: Move to GA_error.h? */
/**
 * \name Bearer - Implementation Error Codes
 * \{
 * \brief This section lists Implementation Error Codes for Bearer.
 */

/** Bearer Invalid State */
#define GA_BRR_INVALID_STATE                        0x1011U

/** Bearer Invalid Params */
#define GA_BRR_INVALID_PARAMS                       0x1012U

/** \} */

/**
 * \name Bearer - Common GATT Profile and Service Error Code Descriptions
 * \{
 * \brief Describes Common Error Codes for GATT Profiles and Services. \n
 * Reference: Bluetooth Core Specification Supplement, Version 9 or later.
 */

/** Out of Range */
#define GA_BRR_ERR_OOR                       0xFFU

/** Procedure Already in Progress */
#define GA_BRR_ERR_PROC_ALREADY_IN_PROGRESS  0xFEU

/** Client Characteristic Configuration Descriptor Improperly Configured */
#define GA_BRR_ERR_CCD_IMPROPERLY_CONFIGURED 0xFDU

/** Write Request Rejected */
#define GA_BRR_ERR_WRITE_REQ_REJECTED        0xFCU

/** \} */

/** \} */

/**
 * \defgroup ga_bearer_constants Constants
 * \{
 * \brief This section lists Bearer Constants.
 */

/**
 * \name General Macros
 * \{
 * \brief Describes general macros for the module.
 */

/** Invalid Bearer Profile ID */
#define GA_BRR_PROFILE_ID_INVALID                   0xFFU

/** Invalid Bearer Service ID */
#define GA_BRR_SERVICE_ID_INVALID                   0xFFU

/** Invalid Bearer Service Type */
#define GA_BRR_SERVICE_TYPE_INVALID                 0xFFU

/** Invalid Bearer UUID */
#define GA_BRR_UUID_INVALID                         0x0000U

/** Dont care Service and Characteristic instance */
#define GA_BRR_INST_DONTCARE                        0xFFU

/** HCI Connectionless Event Code - Adv/Scan/BIG related */
#define GA_BRR_CONNECTIONLESS_EVENT_CODE            0xC0U

/** \} */

/**
 * \name Service Discover Types
 * \{
 * \brief Describes Service Discover Types for the module, which is used in
 * Client Role.
 */

/** Primary Service Discovery Type */
#define GA_BRR_PS_DISCOVERY                         0x00U
/** Included Service Discovery Type */
#define GA_BRR_IS_DISCOVERY                         0x01U
/** Secondary Service Discovery Type */
#define GA_BRR_SS_DISCOVERY                         0x02U

/** \} */

/**
 * \name Service Types
 * \{
 * \brief Describes Service Types for the module, which is used in Server Role.
 */

/** Primary Service Type */
#define GA_BRR_PS_TYPE                              0x00U
/** Secondary Service Type */
#define GA_BRR_SS_TYPE                              0x01U

/** \} */

/**
 * \name Service Handle Range
 * \{
 * \brief Describes Service Handle Range for the module.
 */

/** Invalid Service Handle Value */
#define GA_BRR_INVALID_SERV_HANDLE_VAL              0x0000U
/** Service Handle Start Range */
#define GA_BRR_SERV_HANDLE_START_RANGE              0x0001U
/** Service Handle End Range */
#define GA_BRR_SERV_HANDLE_END_RANGE                0xFFFFU

/** \} */

/**
 * \name BLE RPA Operations
 * \{
 * \brief Describes events associated with BLE RPA
 * generation and verification operations.
 */

/** Resolvable Private Address Operation: Create */
#define GA_BRR_RPA_CREATE                    0x00U
/** Resolvable Private Address Operation: Verify */
#define GA_BRR_RPA_VERIFY                    0x01U

/** \} */

/** \} */

/**
 * \defgroup ga_brr_events Events
 * \{
 * \brief Describes Events for the module.
 */

/**
 * \defgroup ga_brr_client_evt_defs Client
 * \{
 * \brief This section describes the Generic Audio Bearer
 * Events for Client.
 */

/*
 * TODO: Verify the description
 */
/**
 * \brief This event is notified when transport setup is complete from the
 * bearer to a profile from peer device. \n
 * Callback is triggered with the following values as parameters in the
 * \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL
 * \param [in] context Pointer to peer device handle \ref
 * \param [in] event_type \ref GA_BRR_SETUP_TRANSPORT_CNF
 * \param [in] event_status \ref GA_SUCCESS : Setup Complete \n
 *                          \ref GA_FAILURE : Others \n
 * \param [in] event_data If status is \ref GA_SUCCESS or \ref GA_FAILURE, \n
 *                           - event_data: NULL \n
 *                           .
 * \param [in] event_datalen If status is \ref GA_SUCCESS or
 *                           \ref GA_FAILURE, \n
 *                              - event_datalen: 0 \n
 *                              .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BRR_SETUP_TRANSPORT_CNF                  0x00U

/**
 * \brief This event is notified on discovery of primary/secondary/included
 * services with peer device with the following values as parameters in the
 * \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL
 * \param [in] context Pointer to peer device handle \ref
 * \param [in] event_type \ref GA_BRR_DISCOVER_SERVICE_CNF
 * \param [in] event_status \ref GA_CONTINUE : Service Handle range of
 *                          discovered service \n
 *                          \ref GA_SUCCESS : Service Discovery Complete \n
 *                          \ref GA_FAILURE : Others \n
 * \param [in] event_data If status is \ref GA_CONTINUE \n
 *                        - event_data: Pointer to object of type
 *                                      \ref GA_BRR_SVC_INFO \n
 *                        .
 * \param [in] event_datalen If status is \ref GA_CONTINUE \n
 *                              - event_datalen: \ref sizeof ( \ref GA_BRR_SVC_INFO) \n
 *                              .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BRR_DISCOVER_SERVICE_CNF                 0x01U

/**
 * \brief This event is notified on Characteristics discovery. \n
 * Callback is triggered with the following values as parameters in the
 * \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL
 * \param [in] context Pointer to peer device handle \ref
 * \param [in] event_type \ref GA_BRR_GET_SERVICE_COMPOSITION_CNF
 * \param [in] event_status \ref GA_CONTINUE : Perform Service Composition \n
 *                          \ref GA_SUCCESS : Service Composition Complete \n
 *                          \ref GA_FAILURE : Others \n
 * \param [in] event_data If status is \ref GA_CONTINUE \n
 *                           - event_data: Pointer to object of type
 *                                         \ref GA_BRR_SERVICE_COMPOSITION \n
 *                           .
 * \param [in] event_datalen If status is \ref GA_CONTINUE \n
 *                              - event_datalen: \ref sizeof ( \ref GA_BRR_SERVICE_COMPOSITION) \n
 *                              .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BRR_GET_SERVICE_COMPOSITION_CNF          0x02U

/**
 * \brief This event is notified on Characteristics Descriptor discovery. \n
 * Callback is triggered with the following values as parameters in the
 * \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL
 * \param [in] context Pointer to peer device handle \ref
 * \param [in] event_type \ref GA_BRR_GET_CHARACTERISTIC_COMPOSITION_CNF
 * \param [in] event_status \ref GA_CONTINUE : Perform Characteristic
 *                          Composition \n
 *                          \ref GA_SUCCESS : Characteristic Composition
 *                          Complete \n
 *                          \ref GA_FAILURE : Others \n
 * \param [in] event_data If status is \ref GA_CONTINUE \n
 *                           - event_data: Pointer to object of type
 *                                         \ref GA_BRR_CHARACTERISTIC_COMPOSITION \n
 *                           .
 * \param [in] event_datalen If status is \ref GA_CONTINUE \n
 *                              - event_datalen: \ref sizeof ( \ref GA_BRR_CHARACTERISTIC_COMPOSITION) \n
 *                              .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BRR_GET_CHARACTERISTIC_COMPOSITION_CNF   0x03U

/**
 * \brief This event is notified when a write response is received for a
 * characteristic from peer device with the following values as
 * parameters in the \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL
 * \param [in] context Pointer to peer device handle \ref
 * \param [in] event_type \ref GA_BRR_WRITE_CHARACTERISTIC_CNF
 * \param [in] event_status \ref GA_SUCCESS : Write Response received \n
 * \param [in] event_data NULL \n
 * \param [in] event_datalen 0
 *
 * \return\ref GA_SUCCESS (always)
 */
#define GA_BRR_WRITE_CHARACTERISTIC_CNF             0x04U

/*
 * TODO: Verify the parameter event_data
 */
/**
 * \brief This event is notified when a read response is received for a
 * characteristic from peer device with the following values as
 * parameters in the \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL
 * \param [in] context Pointer to peer device handle \ref
 * \param [in] event_type \ref GA_BRR_READ_CHARACTERISTIC_CNF
 * \param [in] event_status \ref GA_SUCCESS : Read Response received \n
 * \param [in] event_data Pointer to void
 * \param [in] event_datalen \ref sizeof ( \ref UINT16 )
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BRR_READ_CHARACTERISTIC_CNF              0x05U

/**
 * \brief This event indicates the Configuration of Notification/Indication of
 * Characteristics. Callback is triggered with the following values
 * as parameters in the \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL
 * \param [in] context Pointer to peer device handle \ref
 * \param [in] event_type \ref GA_BRR_CONFIG_CHARACTERISTIC_CNF
 * \param [in] event_status \ref GA_SUCCESS : Configure for Notification
 *                          Complete \n
 *                          \ref GA_FAILURE : Others \n
 * \param [in] event_data NULL \n
 * \param [in] event_datalen 0
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BRR_CONFIG_CHARACTERISTIC_CNF            0x06U

/*
 * TODO: Verify the parameter event_data
 */
/**
 * \brief This event is notified when a notification/indication is received for
 * a characteristic from peer device with the following values as parameters in
 * the \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL
 * \param [in] context Pointer to peer device handle \ref GA_BRR_CHR_HANDLE
 * \param [in] event_type \ref GA_BRR_NOTIFICATION_IND
 * \param [in] event_status \ref GA_SUCCESS : Notification received
 * \param [in] event_data Pointer to void
 * \param [in] event_datalen \ref sizeof ( \ref UINT16 )
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BRR_NOTIFICATION_IND                     0x07U

/** \} */

/**
 * \defgroup ga_brr_server_evt_defs Server
 * \{
 * \brief This section describes the Generic Audio Bearer Events for Server.
 */

/*
 * TODO: Verify the description
 */
/**
 * \brief This event is notified when transport setup from bearer to profile
 * request is received from peer device. \n
 * Callback is triggered with the following values as parameters in the
 * \ref GA_BRR_SERVICE_CB callback.
 *
 * \param [in] device NULL
 * \param [in] context Pointer to peer device handle \ref
 * \param [in] event_type \ref GA_BRR_SETUP_TRANSPORT_IND
 * \param [in] event_status \ref GA_SUCCESS : Setup request received \n
 *                          \ref GA_FAILURE : Others \n
 * \param [in] event_data If status is \ref GA_SUCCESS or \ref GA_FAILURE, \n
 *                           - event_data: NULL \n
 *                           .
 * \param [in] event_datalen If status is \ref GA_SUCCESS or
 *                           \ref GA_FAILURE, \n
 *                              - event_datalen: 0 \n
 *                              .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BRR_SETUP_TRANSPORT_IND                  0x10U

/**
 * \brief This event is notified when a write request is received for a
 * characteristic from peer device with the following values as parameters in
 * the \ref GA_BRR_SERVICE_CB callback.
 *
 * \param [in] device Pointer to peer device handle \ref
 * \param [in] context Pointer to \ref GA_BRR_CHR_CONTEXT
 * \param [in] event_type \ref GA_BRR_WRITE_CHARACTERISTIC_IND
 * \param [in] event_status \ref GA_SUCCESS : Write Request received \n
 * \param [in] event_data Pointer to void
 * \param [in] event_datalen \ref sizeof ( \ref UINT16 ).
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note \ref GA_brr_write_characteristic_rsp() has to be called to
 *       send the write response.
 */
#define GA_BRR_WRITE_CHARACTERISTIC_IND             0x11U

/*
 * TODO: Verify the parameter event_data
 */
/**
 * \brief This event is notified when a read request is received for a
 * characteristic from peer device with the following values as parameters in
 * the \ref GA_BRR_SERVICE_CB callback.
 *
 * \param [in] device Pointer to peer device handle \ref
 * \param [in] context Pointer to \ref GA_BRR_CHR_CONTEXT
 * \param [in] event_type \ref GA_BRR_READ_CHARACTERISTIC_IND
 * \param [in] event_status \ref GA_SUCCESS : Read Request received \n
 * \param [in] event_data Pointer to void
 * \param [in] event_datalen \ref sizeof ( \ref UINT16 ).
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note \ref GA_brr_read_characteristic_rsp() has to be called to
 *       send the write response.
 */
#define GA_BRR_READ_CHARACTERISTIC_IND              0x12U

/*
 * TODO: Verify the parameter event_data and event_datalen
 */
/**
 * \brief This event indicates the Configuration of Notification/Indication of
 * Characteristics. \n
 * Callback is triggered with the following values as parameters in the
 * \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device Pointer to peer device handle \ref
 * \param [in] context Pointer to \ref GA_BRR_CHR_CONTEXT
 * \param [in] event_type \ref GA_BRR_CONFIG_CHARACTERISTIC_IND
 * \param [in] event_status \ref GA_SUCCESS  \n
 * \param [in] event_data
 * \param [in] event_datalen
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BRR_CONFIG_CHARACTERISTIC_IND            0x13U

/*
 * TODO: Verify the parameter event_data
 */
/**
 * \brief This event is notified when a read blob request is received for a
 * characteristic from peer device with the following values as parameters in
 * the \ref GA_BRR_SERVICE_CB callback.
 *
 * \param [in] device Pointer to peer device handle \ref
 * \param [in] context Pointer to \ref GA_BRR_CHR_CONTEXT
 * \param [in] event_type \ref GA_BRR_READ_BLOB_CHARACTERISTIC_IND
 * \param [in] event_status \ref GA_SUCCESS : Read Blob Request received \n
 * \param [in] event_data Pointer to void
 * \param [in] event_datalen \ref sizeof ( \ref UINT16 ).
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note \ref GA_brr_read_characteristic_rsp() has to be called to
 *       send the write response.
 */
#define GA_BRR_READ_BLOB_CHARACTERISTIC_IND         0x14U

/** \} */

/* TODO: Verify Group name and description */
/**
 * \defgroup ga_brr_crypto_evt_defs Crypto
 * \{
 * \brief This section describes events associated with Bearer BLE RPA and
 * Cryptographic Operations.
 */

/**
 * \name Bearer Server Events - BLE RPA Operational and Cryptographic
 * \{
 * \brief Describes events associated with BLE RPA and Cryptographic
 * operations for Server.
 */

/**
 * \brief This event is notified when an RPA creation operation is completed
 * in the bearer with the following values as parameters in
 * the \ref GA_BRR_CB callback.
 *
 * \param [in] device NULL
 * \param [in] event_type \ref GA_BRR_RPA_CREATE_COMPLETE
 * \param [in] event_status \ref GA_SUCCESS or any Error Code
 * \param [in] event_data Pointer to RPA created if success
 * \param [in] event_datalen Size of Bluetooth Address.
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BRR_RPA_CREATE_COMPLETE                  0x20U

/** \} */

/**
 * \name Bearer Client Events -  BLE RPA and Cryptographic Operational
 * \{
 * \brief Describes events associated with BLE RPA and Cryptographic
 * operations for Client.
 */

/**
 * \brief This event is notified when an RPA verification operation is completed
 * in the bearer with the following values as parameters in
 * the \ref GA_BRR_CB callback.
 *
 * \param [in] device NULL
 * \param [in] event_type \ref GA_BRR_RPA_VERIFY_COMPLETE
 * \param [in] event_status \ref GA_SUCCESS or any Error Code for Verify fail
 * \param [in] event_data Pointer to RPA given for verification
 * \param [in] event_datalen Size of Bluetooth Address.
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BRR_RPA_VERIFY_COMPLETE                  0x21U

/** \} */

/* TODO: Check client/server events */
/**
 * \brief This event is notified when an AES-CMAC operation is completed
 * in the bearer with the following values as parameters in
 * the \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL
 * \param [in] context User context pointer specified in the crypto API
 * \param [in] event_type \ref GA_BRR_CRYPTO_AESCMAC_CREATE_COMPLETE
 * \param [in] event_status \ref GA_SUCCESS or any Error Code for Verify fail
 * \param [in] event_data Pointer to MAC value generated
 * \param [in] event_datalen Size of MAC.
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BRR_CRYPTO_AESCMAC_CREATE_COMPLETE     0x25U

/**
 * \brief This event is notified when an AES-CMAC operation is completed
 * in the bearer with the following values as parameters in
 * the \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL
 * \param [in] context User context pointer specified in the crypto API
 * \param [in] event_type \ref GA_BRR_CRYPTO_AESCMAC_VERIFY_COMPLETE
 * \param [in] event_status \ref GA_SUCCESS or any Error Code for Verify fail
 * \param [in] event_data Pointer to MAC value verified
 * \param [in] event_datalen Size of MAC.
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BRR_CRYPTO_AESCMAC_VERIFY_COMPLETE     0x26U

/** \} */

/* HCI Connectionless Event Identifiers */

/**
 * \defgroup ga_brr_bc_src_evt_defs Broadcast Source
 * \{
 * \brief This section describes the Generic Audio Bearer HCI Connectionless
 * Event Identifiers for Broadcast Source.
 */

/** \} */

/**
 * \defgroup ga_brr_bc_snk_evt_defs Broadcast Sink
 * \{
 * \brief This section describes the Generic Audio Bearer HCI Connectionless
 * Event Identifiers for Broadcast Sink.
 */

/** \} */

/**
 * \addtogroup ga_brr_bc_src_evt_defs
 * \{
 */

/**
 * \brief This event is notified when Extended/Periodic advertising
 * enable/disable is completed, event is notified with the following values
 * as parameters in the \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL, Ignore
 * \param [in] context User context pointer specified in the calling API
 * \param [in] brr_role Refer \ref ga_bearer_constants
 * \param [in] event_type \ref GA_BRR_CONFIGURE_ADV_CNF
 * \param [in] event_status \ref GA_SUCCESS if all the procedures as defined in
 *                          the API have been successfully completed or
 *                          \ref GA_FAILURE in case any of the procedure
 *                          has failed.
 * \param [in] event_data NULL, Ignore
 * \param [in] event_datalen 0, Ignore
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa GA_brr_configure_adv()
 */
#define GA_BRR_CONFIGURE_ADV_CNF                    (0x00U | GA_BRR_CONNECTIONLESS_EVENT_CODE)

/** \} */

/**
 * \addtogroup ga_brr_bc_snk_evt_defs
 * \{
 */

/**
 * \brief This event is notified when Extended/Periodic scan
 * enable/disable is completed, event is notified with the following values
 * as parameters in the \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL, Ignore
 * \param [in] context User context pointer specified in the calling API
 * \param [in] brr_role Refer \ref ga_bearer_constants
 * \param [in] event_type \ref GA_BRR_CONFIGURE_SCAN_CNF
 * \param [in] event_status \ref GA_SUCCESS if all the procedures as defined in
 *                          the API have been successfully completed or
 *                          \ref GA_FAILURE in case any of the procedure has
 *                          failed. If the process of scan has timed-out,
 *                          this event shall be generated. \n
 *                          On \ref GA_SUCCESS,
 *                          \ref GA_BRR_EXTENDED_ADV_REPORT_IND and
 *                          \ref GA_BRR_PERIODIC_ADV_REPORT_IND for EA and PA
 *                          respectively are expected.
 * \param [in] event_data NULL, Ignore
 * \param [in] event_datalen 0, Ignore
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa GA_brr_configure_scan()
 * \sa GA_BRR_PERIODIC_ADV_REPORT_IND
 * \sa GA_BRR_EXTENDED_ADV_REPORT_IND
 */
#define GA_BRR_CONFIGURE_SCAN_CNF                   (0x01U | GA_BRR_CONNECTIONLESS_EVENT_CODE)

/**
 * \brief This event is notified when Sync to Periodic scan
 * enable/disable is completed, event is notified with the following values
 * as parameters in the \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL, Ignore
 * \param [in] context User context pointer specified in the calling API
 * \param [in] brr_role Refer \ref ga_bearer_constants
 * \param [in] event_type \ref GA_BRR_CONFIGURE_SYNC_CNF
 * \param [in] event_status \ref GA_SUCCESS if all the procedures as defined in
 *                          the API have been successfully completed or
 *                          \ref GA_FAILURE in case any of the procedure
 *                          has failed.
 * \param [in] event_data If event_status is \ref GA_SUCCESS, \n
 *                           - Pointer to data as defined in Core Spec
 *                             7.7.65.14 LE Periodic Advertising Sync
 *                             Established event, skipping the Subevent_Code
 *                             parameter for API call triggered to
 *                             Create PA Sync. \n
 *                           - Ignore for PA Terminate Sync. \n
 *                           .
 *                        If event_status is \ref GA_FAILURE,
 *                        - If request is ongoing Create PA Sync, Ignore
 *                        - If request is ongoing Create PA Sync and Create Sync
 *                          Cancel is called, this event is valid with
 *                          event_status as GA_FAILURE
 * \param [in] event_datalen If event_status is \ref GA_SUCCESS, \n
 *                              - 15 Bytes.
 *                              - Ignore for PA Terminate Sync. \n
 *                              .
 *                           If event_status is \ref GA_FAILURE, Ignore.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa GA_brr_configure_sync()
 */
#define GA_BRR_CONFIGURE_SYNC_CNF                   (0x02U | GA_BRR_CONNECTIONLESS_EVENT_CODE)

 /**
  * \brief This event is notified when Sync cancel to Periodic scan
  * is completed, event is notified with the following values
  * as parameters in the \ref GA_BRR_PROFILE_CB callback.
  *
  * \param [in] device NULL, Ignore
  * \param [in] context User context pointer specified in the calling API
  * \param [in] brr_role Refer \ref ga_bearer_constants
  * \param [in] event_type \ref GA_BRR_CONFIGURE_SYNC_CANCEL_CNF
  * \param [in] event_status \ref GA_SUCCESS if all the procedures as defined in
  *                          the API have been successfully completed or
  *                          \ref GA_FAILURE in case any of the procedure
  *                          has failed.
  * \param [in] event_data If event_status is \ref GA_SUCCESS, \n
  *                           - Ignore \n
  *                           .
  *                        If event_status is \ref GA_FAILURE,
  *                        - Ignore \n
  * \param [in] event_datalen If event_status is \ref GA_SUCCESS, \n
  *                              - Ignore \n
  *                              .
  *                           If event_status is \ref GA_FAILURE, Ignore.
  *
  * \return \ref GA_SUCCESS (always)
  *
  * \sa GA_brr_configure_sync_cancel()
  */
#define GA_BRR_CONFIGURE_SYNC_CANCEL_CNF            (0x0C | GA_BRR_CONNECTIONLESS_EVENT_CODE)

/** \} */

/**
 * \addtogroup ga_brr_bc_src_evt_defs
 * \{
 */

/**
 * \brief This event is notified when Create BIG or Terminate BIG is completed,
 * event is notified with the following values as parameters in the
 * \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL, Ignore
 * \param [in] context User context pointer specified in the calling API
 * \param [in] brr_role Refer \ref ga_bearer_constants
 * \param [in] event_type \ref GA_BRR_CONFIGURE_BROADCAST_CNF
 * \param [in] event_status \ref GA_SUCCESS if all the procedures as defined in
 *                           the API have been successfully completed or
 *                           \ref GA_FAILURE in case any of the procedure
 *                           has failed.
 * \param [in] event_data If event_status is \ref GA_SUCCESS, \n
 *                           - Pointer to data as defined in Core Spec
 *                             7.7.65.27 LE Create BIG Complete event,
 *                             skipping the Subevent_Code parameter for API
 *                             call triggered to Create BIG. \n
 *                           - Ignore for Terminate BIG. \n
 *                           .
 *                        If event_status is \ref GA_FAILURE, Ignore.
 * \param [in] event_datalen If event_status is \ref GA_SUCCESS, \n
 *                              - 17 Bytes for API call triggered to Create BIG
 *                                plus Connection_Handle(2B) for 'n' number of
 *                                BISes. \n
 *                              - Ignore for Terminate BIG. \n
 *                              .
 *                           If event_status is \ref GA_FAILURE, Ignore.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa GA_brr_configure_broadcast()
 */
#define GA_BRR_CONFIGURE_BROADCAST_CNF              (0x03U | GA_BRR_CONNECTIONLESS_EVENT_CODE)

/** \} */

/**
 * \addtogroup ga_brr_bc_snk_evt_defs
 * \{
 */

/**
 * \brief This event is notified when BIG Create Sync or BIG Terminate Sync
 * is completed, event is notified with the following values as parameters in the
 * \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL, Ignore
 * \param [in] context User context pointer specified in the calling API
 * \param [in] brr_role Refer \ref ga_bearer_constants
 * \param [in] event_type \ref GA_BRR_CONFIGURE_BROADCAST_CNF
 * \param [in] event_status \ref GA_SUCCESS if all the procedures as defined in
 *                           the API have been successfully completed or
 *                           \ref GA_FAILURE in case any of the procedure
 *                           has failed.
 * \param [in] event_data If event_status is \ref GA_SUCCESS, \n
 *                           - For BIG Create Sync, \n
 *                             Pointer to data as defined in Core Spec
 *                             7.7.65.29 LE BIG Sync Established event,
 *                             skipping the Subevent_Code parameter for API
 *                             call triggered to BIG Create Sync. \n
 *                           - For BIG Terminate Sync \n
 *                             BIG_Handle \n
 *                        If event_status is \ref GA_FAILURE \n
 *                           - For BIG Create Sync, \n
 *                             Ignore
 *                           - For BIG Terminate Sync, \n
 *                             BIG_Handle \n
 *                           .
 * \param [in] event_datalen If event_status is \ref GA_SUCCESS, \n
 *                           - For BIG Create Sync, \n
 *                              - 14 Bytes plus Connection_Handle(2B) for 'n'
 *                                 number of BISes. \n
 *                              - Ignore for BIG Terminate Sync. \n
 *                              - 1B for BIG Terminate Sync, BIG_Handle \n
 *                              .
 *                           If event_status is \ref GA_FAILURE \n
 *                              - For BIG Create Sync, \n
 *                                Ignore
 *                              - For BIG Terminate Sync, \n
 *                                1B, BIG_Handle \n
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa GA_brr_configure_broadcast_sync()
 */
#define GA_BRR_CONFIGURE_BROADCAST_SYNC_CNF         (0x04U | GA_BRR_CONNECTIONLESS_EVENT_CODE)

/** \} */

/**
 * \addtogroup ga_brr_bc_src_evt_defs
 * \{
 */

/**
 * \brief This event is notified when Extended/Periodic advertising
 * enable/disable reconfigure is completed, event is notified with the
 * following values as parameters in the \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL, Ignore
 * \param [in] context User context pointer specified in the calling API
 * \param [in] brr_role Refer \ref ga_bearer_constants
 * \param [in] event_type \ref GA_BRR_RECONFIGURE_ADV_CNF
 * \param [in] event_status \ref GA_SUCCESS if all the procedures as defined in
 *                          the API have been successfully completed or
 *                          \ref GA_FAILURE in case any of the procedure
 *                          has failed.
 * \param [in] event_data NULL, Ignore
 * \param [in] event_datalen 0, Ignore
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa GA_brr_configure_adv()
 */
#define GA_BRR_RECONFIGURE_ADV_CNF                  (0x05U | GA_BRR_CONNECTIONLESS_EVENT_CODE)

/** \} */

/**
 * \addtogroup ga_brr_bc_snk_evt_defs
 * \{
 */

/**
 * \brief This event is notified when EA Scan is triggered successfully
 * post \ref GA_SUCCESS is returned with \ref GA_BRR_CONFIGURE_SCAN_CNF.
 * This event is notified with the following values as parameters in the
 * \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL, Ignore
 * \param [in] context NULL, Ignore
 * \param [in] brr_role Refer \ref ga_bearer_constants
 * \param [in] event_type \ref GA_BRR_EXTENDED_ADV_REPORT_IND
 * \param [in] event_status \ref GA_SUCCESS in all cases
 * \param [in] event_data If event_status is \ref GA_SUCCESS,
 *                           - Pointer to data as defined in Core Spec
 *                             7.7.65.13 LE Extended Advertising Report event,
 *                             skipping the Subevent_Code parameter.
 *                             This event if constitues more than 1 report(n reports),
 *                             this will generate 'n' number of \ref
 *                             GA_BRR_EXTENDED_ADV_REPORT_IND events for the
 *                             same device. \n
 *                           .
 *
 * \param [in] event_datalen If event_status is \ref GA_SUCCESS,
 *                              - 24B per report plus Data_length number of bytes.
 *                              .
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note Also, this event shall be generated if Scan is initiated directly with
 *       the stack.
 *
 * \sa GA_brr_configure_scan()
 */
#define GA_BRR_EXTENDED_ADV_REPORT_IND              (0x06U | GA_BRR_CONNECTIONLESS_EVENT_CODE)

/**
 * \brief This event is notified when PA Scan is triggered successfully
 * post \ref GA_SUCCESS is returned with \ref GA_BRR_CONFIGURE_SCAN_CNF.
 * This event is notified with the following values as parameters in the
 * \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL, Ignore
 * \param [in] context NULL, Ignore
 * \param [in] brr_role Refer \ref ga_bearer_constants
 * \param [in] event_type \ref GA_BRR_PERIODIC_ADV_REPORT_IND
 * \param [in] event_status \ref GA_SUCCESS in all cases
 * \param [in] event_data If event_status is \ref GA_SUCCESS,
 *                           - Pointer to data as defined in Core Spec
 *                             7.7.65.15 LE Periodic Advertising Report event
 *                             skipping the Subevent_Code parameter.
 *                           .
 *
 * \param [in] event_datalen If event_status is \ref GA_SUCCESS,
 *                              - 7 Bytes plus Data_length number of bytes.
 *                              .
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note Also, this event shall be generated if Scan is initiated directly with
 *       the stack.
 *
 * \sa GA_brr_configure_scan()
 */
#define GA_BRR_PERIODIC_ADV_REPORT_IND              (0x07U | GA_BRR_CONNECTIONLESS_EVENT_CODE)

/**
 * \brief This event is notified when PA Scan is triggered successfully
 * post \ref GA_SUCCESS is returned with
 * \ref GA_BRR_CONFIGURE_BROADCAST_SYNC_CNF.
 * This event is notified with the following values as parameters in the
 * \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL, Ignore
 * \param [in] context NULL, Ignore
 * \param [in] brr_role Refer \ref ga_bearer_constants
 * \param [in] event_type \ref GA_BRR_BIGINFO_ADV_REPORT_IND
 * \param [in] event_status \ref GA_SUCCESS in all cases
 * \param [in] event_data If event_status is \ref GA_SUCCESS,
 *                           - Pointer to data as defined in Core Spec
 *                             7.7.65.34 LE BIGInfo Advertising Report event
 *                             skipping the Subevent_Code parameter.
 *                           .
 *
 * \param [in] event_datalen If event_status is \ref GA_SUCCESS,
 *                              - 19 Bytes plus Data_length number of bytes.
 *                              .
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note Also, this event shall be generated if Scan is initiated directly with
 *       the stack.
 *
 * \sa GA_brr_configure_broadcast_sync()
 */
#define GA_BRR_BIGINFO_ADV_REPORT_IND               (0x08U | GA_BRR_CONNECTIONLESS_EVENT_CODE)

/**
 * \brief This event is notified when the Controller has not received a
 * Periodic Advertising packet from the train identified by Sync_Handle within
 * the timeout period.
 * This event is notified with the following values as parameters in the
 * \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL, Ignore
 * \param [in] context NULL, Ignore
 * \param [in] brr_role Refer \ref ga_bearer_constants
 * \param [in] event_type \ref GA_BRR_PERIODIC_ADV_SYNC_LOST_IND
 * \param [in] event_status \ref GA_SUCCESS PA Sync Lost has occurred.
 * \param [in] event_data If event_status is \ref GA_SUCCESS, \n
 *                           - Pointer to data as defined in Core Spec
 *                             7.7.65.16 LE Periodic Advertising Sync Lost event
 *                             skipping the Subevent_Code parameter.
 *                           .
 * \param [in] event_datalen If event_status is \ref GA_SUCCESS, \n
 *                              - 2 Bytes indicating the Sync_Handle.
 *                                Sync_Handle given as part of
 *                                \ref GA_brr_configure_sync()
 *                              .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BRR_PERIODIC_ADV_SYNC_LOST_IND           (0x09U | GA_BRR_CONNECTIONLESS_EVENT_CODE)

/**
 * \brief This event is notified when the Controller has not
 * received any PDUs on a BIG within the timeout period BIG_Sync_Timeout or
 * the BIG has been terminated by the remote device.
 * This event is notified with the following values as parameters in the
 * \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL, Ignore
 * \param [in] context NULL, Ignore
 * \param [in] brr_role Refer \ref ga_bearer_constants
 * \param [in] event_type \ref GA_BRR_BROADCAST_SYNC_LOST_IND
 * \param [in] event_status \ref GA_SUCCESS BIG Sync Timeout/BIG Terminate has
 *                          occurred.
 * \param [in] event_data If event_status is \ref GA_SUCCESS, \n
 *                           - Pointer to data as defined in Core Spec
 *                             7.7.65.30 LE BIG Sync Lost event,
 *                             skipping the Subevent_Code parameter.
 *                           .
 * \param [in] event_datalen If event_status is \ref GA_SUCCESS, \n
 *                              - 2 Bytes indicating the Big_Handle and Reason.
 *                                Big_Handle given as part of
 *                                \ref GA_brr_configure_broadcast_sync()
 *                              .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BRR_BROADCAST_SYNC_LOST_IND              (0x0AU | GA_BRR_CONNECTIONLESS_EVENT_CODE)

/** \} */

/**
 * \addtogroup ga_brr_bc_src_evt_defs
 * \{
 */

/**
 * \brief This event is notified when terminate BIG occurs, transmission
 * of all the BISes in the BIG are terminated.
 * This event is notified with the following values as parameters in the
 * \ref GA_BRR_PROFILE_CB callback.
 *
 * \param [in] device NULL, Ignore
 * \param [in] context NULL, Ignore
 * \param [in] brr_role Refer \ref ga_bearer_constants
 * \param [in] event_type \ref GA_BRR_BIG_TERMINATE_IND
 * \param [in] event_status \ref GA_SUCCESS BIG Terminate has occurred.
 * \param [in] event_data If event_status is \ref GA_SUCCESS, \n
 *                           - Pointer to data as defined in Core Spec
 *                             7.7.65.27 LE Create BIG Complete event,
 *                             skipping the Subevent_Code parameter for API
 *                             call triggered to Create BIG. \n
 *                           .
 * \param [in] event_datalen If event_status is \ref GA_SUCCESS, \n
 *                              - 17 Bytes plus Connection_Handle(2B) for 'n'
 *                                number of BISes. \n
 *                              .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BRR_BIG_TERMINATE_IND                    (0x0BU | GA_BRR_CONNECTIONLESS_EVENT_CODE)

/** \} */

/**
 * \defgroup ga_brr_common_evt_defs Common
 * \{
 * \brief This section describes the Generic Audio Bearer Common Events.
 */

/*
 * TODO: Verify the description
 */
/**
 * \brief This event is notified when ATT Connection is requested. It sets the
 * peer device information.
 * Callback is triggered with the following values as parameters in the
 * \ref GA_BRR_CB callback.
 *
 * \param [in] device Pointer to \ref
 * \param [in] event_type \ref GA_BRR_TRANSPORT_UP_IND
 * \param [in] event_status \ref GA_SUCCESS : ATT Connection Request
 *                          received \n
 * \param [in] event_data NULL \n
 * \param [in] event_datalen 0
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BRR_TRANSPORT_UP_IND                     0x81U

/*
 * TODO: Verify the description
 */
/**
 * \brief This event is notified when ATT Disconnection is requested. It
 * initialize bearer device.
 * Callback is triggered with the following values as parameters in the
 * \ref GA_BRR_CB callback.
 *
 * \param [in] device Pointer to \ref
 * \param [in] event_type \ref GA_BRR_TRANSPORT_DOWN_IND
 * \param [in] event_status \ref GA_SUCCESS : ATT Disconnection Request
 *                          received \n
 * \param [in] event_data NULL \n
 * \param [in] event_datalen 0
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BRR_TRANSPORT_DOWN_IND                   0x82U

/**
 * \brief This is an event to indicate random event. This event shall never be
 * generated. It is used to reset Event ID for the context.
 *
 * \param [in] device NULL
 * \param [in] context NULL
 * \param [in] event_type \ref GA_BRR_EVENT_INVALID
 * \param [in] event_status NULL \n
 * \param [in] event_data NULL \n
 * \param [in] event_datalen 0 \n
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BRR_EVENT_INVALID                        0xFFU

/** \} */

/** \} */

/**
 * \addtogroup ga_bearer_constants
 * \{
 */

/**
 * \name General Macros
 * \{
 */

/** Mask to set notification with response (Indication) */
#define GA_BRR_NTF_RESPONSE_MASK                    0x80U

/** \} */

/**
 * \name Bearer Internal Role
 * \{
 * \brief Describes Bearer Internal Roles, used to identify modes of
 * interaction with upper layer.
 */

/** Bearer Internal Role - Generic */
#define GA_BRR_GENERIC_ROLE                         0x00U

/** Bearer Internal Role - Profile */
#define GA_BRR_PROFILE_ROLE                         0x01U

/** Bearer Internal Role - Service */
#define GA_BRR_SERVICE_ROLE                         0x02U

/** Bearer Internal Role - Invalid */
#define GA_BRR_INVALID_ROLE                         0xFFU

/** \} */

/**
 * \name General Macros
 * \{
 */

/** Offset Value Length : Read Blob Request */
#define GA_BRR_ATT_READ_BLOB_VALUE_OFFSET_LEN       0x02U

/** \} */

/*
 * TODO: Need events for Transport Disconnection too?
 * Currently looks like the Idea was to have
 * - GA_BRR_SETUP_TRANSPORT_CNF for Profile roles
 * - GA_BRR_SETUP_TRANSPORT_IND for Server roles
 * Need to check if these events are to be unified and
 * provided to GA profile and service callbacks or
 * provided only to GA Core Callback.
 */

/**
 * \name Characteristic Properties
 * \{
 * \brief Characteristic Properties - Combination of these properties (combined
 * using bitwise OR) describe properties of the Characteristic.
 */

/**
 * Characteristic support Broadcast of its value to the peer.
 * Setting this property automatically includes Characteristic Server
 * Configuration Descriptor to the Characteristic
 */
#define GA_BRR_CHAR_BROADCAST_PROPERTY                0x00000001U

/** Characteristic support Reading its value by peer */
#define GA_BRR_CHAR_READ_PROPERTY                     0x00000002U

/** Characteristic support Writing its value by peer Without Response  */
#define GA_BRR_CHAR_WRITE_WITHOUT_RSP_PROPERTY        0x00000004U

/** Characteristic supports Writing its value by peer */
#define GA_BRR_CHAR_WRITE_PROPERTY                    0x00000008U

/**
 * Characteristic supports Notifying its value to the peer.
 * Setting this property automatically includes Characteristic Server
 * Configuration Descriptor to the Characteristic
 */
#define GA_BRR_CHAR_NOTIFY_PROPERTY                   0x00000010U

/** Characteristic supports Indicating its value to the peer */
#define GA_BRR_CHAR_INDICATE_PROPERTY                 0x00000020U

/** Characteristic supports Signed Write on its value */
#define GA_BRR_CHAR_SIGNED_WRITE_PROPERTY             0x00000040U

/** Characteristic supports write on its User Description Descriptor */
#define GA_BRR_CHAR_WRIEABLE_AUX_PROPERTY             0x00000200U

/** No Auxillary Property */
#define GA_BRR_NO_AUXILLARY_PROPERTY                  0x00U

/** Characteristic Value is Fixed Length */
#define GA_BRR_FIXED_LENGTH_PROPERTY                  0x01U

/** Authorization Property */
#define GA_BRR_AUTHORIZATION_PROPERTY                 0x02U

/** Peer Specific Value property */
#define GA_BRR_PEER_SPECIFIC_VAL_PROPERTY             0x40U

/** Constant Attribute Value Property */
#define GA_BRR_CONST_ATTR_VAL_PROPERTY                0x80U

/** \} */

/**
 * \name Write Type
 * \{
 * Write Type - Request/Command.
 */

/** Write Type: Request */
#define GA_BRR_WRITE_TYPE_REQ                         0x00U
/** Write Type: Command/Write Without Response */
#define GA_BRR_WRITE_TYPE_CMD                         0x01U

/** \} */

/**
 * \name Attribute Value Length
 * \{
 */

/** Max Attribute Value length at bearer */
#define GA_BRR_MAX_ATTRVAL_LEN                         512U

/** \} */

/**
 * \name Advertising Types
 * \{
 * \brief Advertising types used for broadcast
 */

/** Advertising Types - Extended Advertising */
#define GA_BRR_ADV_TYPE_EA                            (0x01U << 0U)
/** Advertising Types - Periodic Advertising */
#define GA_BRR_ADV_TYPE_PA                            (0x01U << 1U)

/** \} */

/**
 * \name Cryptographic blocks
 * \{
 * \brief Cryptographic blocks supported
 */

/** Crypto - None */
#define GA_BRR_CRYPTO_NONE                            0x00U

/** Crypto - AES-CMAC */
#define GA_BRR_CRYPTO_AESCMAC                         0x01U

/** \} */

#define GA_HCI_INQUIRY_RESULT_EVENT                             0x02U
#define GA_HCI_EXTENDED_INQUIRY_RESULT_EVENT                    0x2FU

#define GA_HCI_LE_SCAN_TIMEOUT_SUBEVENT                         0x11U

#define GA_HCI_LE_META_EVENT                                    0x3EU
#define GA_HCI_LE_READ_REMOTE_USED_FEATURES_COMPLETE_SUBEVENT   0x04U
#define GA_HCI_LE_ADVERTISING_REPORT_SUBEVENT                   0x02U
#define GA_HCI_LE_DIRECTED_ADVERTISING_REPORT_SUBEVENT          0x0BU
#define GA_HCI_LE_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_SUBEVENT \
                                                                0x18U
#ifdef GA_SUPPORT_5_4
#define GA_HCI_LE_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_V2_SUBEVENT \
                                                                0x26U
#endif /* GA_SUPPORT_5_4 */
#define GA_HCI_LE_EXTENDED_ADVERTISING_REPORT_SUBEVENT          0x0DU
#define GA_HCI_LE_ENHANCED_CONNECTION_COMPLETE_SUBEVENT         0x0AU
#ifdef GA_SUPPORT_5_4
#define GA_HCI_LE_ENHANCED_CONNECTION_COMPLETE_V2_SUBEVENT      0x29U
#endif /* GA_SUPPORT_5_4 */
#define GA_HCI_LE_CIS_ESTABLISHED_SUBEVENT                      0x19U
#define GA_HCI_LE_CIS_REQUEST_SUBEVENT                          0x1AU
#define GA_HCI_LE_ADVERTISING_SET_TERMINATED_SUBEVENT           0x12U
#define GA_HCI_LE_CONNECTION_COMPLETE_SUBEVENT                  0x01U
#define GA_HCI_LE_CONNECTION_UPDATE_COMPLETE_SUBEVENT           0x03U
#define GA_HCI_LE_REMOTE_CONN_PARAM_REQ_SUBEVENT                0x06U
#define GA_HCI_DISCONNECTION_COMPLETE_EVENT                     0x05U
#define GA_HCI_COMMAND_COMPLETE_EVENT                           0x0EU
#define GA_HCI_COMMAND_STATUS_EVENT                             0x0FU
#define GA_HCI_ENCRYPTION_CHANGE_EVENT                          0x08U
#define GA_HCI_LE_LONG_TERM_KEY_REQUESTED_SUBEVENT              0x05U

#define GA_HCI_READ_BD_ADDR_OPCODE                              0x1009U
#define GA_HCI_LE_CREATE_CONNECTION_CANCEL_OPCODE               0x200EU
#define GA_HCI_LE_SET_HOST_FEATURE_OPCODE                       0x2074U
#define GA_HCI_LE_SETUP_ISO_DATA_PATH_OPCODE                    0x206EU
#define GA_HCI_LE_REMOVE_ISO_DATA_PATH_OPCODE                   0x206FU
#define GA_HCI_LE_SET_PERIODIC_ADVERTISING_SYNC_TRANSFER_PARAMETERS_OPCODE \
                                                                0x205CU

#define GA_HCI_LE_SET_CIG_PARAMETERS_OPCODE                     0x2062U
#define GA_HCI_LE_SET_CIG_PARAMETERS_TEST_OPCODE                0x2063U
#define GA_HCI_LE_CREATE_CIS_OPCODE                             0x2064U
#define GA_HCI_LE_REMOVE_CIG_OPCODE                             0x2065U
#define GA_HCI_LE_ACCEPT_CIS_REQUEST_OPCODE                     0x2066U
#define GA_HCI_LE_REJECT_CIS_REQUEST_OPCODE                     0x2067U

#define GA_HCI_LE_SET_ADVERTISING_PARAMETERS_OPCODE             0x2006U
#define GA_HCI_LE_SET_ADVERTISING_DATA_OPCODE                   0x2008U
#define GA_HCI_LE_SET_ADVERTISING_ENABLE_OPCODE                 0x200AU

#define HCI_LE_REMOTE_CONNECTION_PARAMETER_REQUEST_REPLY_OPCODE 0x2020U
#define HCI_LE_REMOTE_CONNECTION_PARAMETER_REQUEST_NEGATIVE_REPLY_OPCODE \
                                                                0x2021U

#define GA_HCI_LE_SET_EXTENDED_ADV_PARAMS_OPCODE                0x2036U
#define GA_HCI_LE_SET_EXTENDED_ADVERTISING_PARAMETERS_OPCODE    0x2036U
#define GA_HCI_LE_SET_EXTENDED_ADVERTISING_DATA_OPCODE          0x2037U
#define GA_HCI_LE_SET_EXTENDED_ADVERTISE_ENABLE_OPCODE          0x2039U

#define GA_HCI_LE_SET_SCAN_PARAMETERS_OPCODE                    0x200BU
#define GA_HCI_LE_SET_SCAN_ENABLE_OPCODE                        0x200CU

#define GA_HCI_LE_SET_EXTENDED_SCAN_PARAMETERS_OPCODE           0x2041U
#define GA_HCI_LE_SET_EXTENDED_SCAN_ENABLE_OPCODE               0x2042U

#define GA_HC_CONNECTION_TREMINATED_DUE_TO_MIC_FAILURE          0x003DU

#define GA_AD_FLAGS_LE_LIMITED_DISC_MODE          0x01U
#define GA_AD_FLAGS_LE_GENERAL_DISC_MODE          0x02U
#define GA_AD_FLAGS_BR_EDR_NOT_SUPPORTED          0x04U
#define GA_AD_FLAGS_LE_BR_EDR_CONTROLLER          0x08U
#define GA_AD_FLAGS_LE_BR_EDR_HOST                0x10U

/** \} */

/* --------------------------------------------- Data types /Structures */

/**
 * \defgroup ga_brr_structures Structures
 * \{
 * \brief This section lists the various data structures and typedefs for use
 * by the module.
 */

/** GA Result type */
typedef UINT16 GA_RESULT;

/** GA Bearer Device Indentifier */
typedef GA_ENDPOINT GA_BRR_DEVICE;

/** GA Bearer Profile Handle */
typedef UINT8 GA_BRR_PRF_HANDLE;

/** GA Bearer Characteristic Handle */
typedef UINT16 GA_BRR_CHR_HANDLE;

/** GA Bearer Characteristic Descriptor Handle */
typedef UINT16 GA_BRR_CHR_DESC_HANDLE;

/** GA Bearer Service Instance */
typedef UINT8 GA_BRR_SVC_INST;

/** GA Bearer Characteristic Instance */
typedef UINT8 GA_BRR_CHR_INST;

/** GA Bearer UUID type */
/* TODO: <- Make provision for 128bit? */
typedef UINT16 GA_BRR_UUID;

/** GA Bearer Write Type */
typedef UINT8 GA_BRR_WRITE_TYPE;

/** GA Bearer Device Information */
typedef struct _GA_BRR_DEVICE_INFO
{
    /** Bonding state */
    UINT8 bonded;

} GA_BRR_DEVICE_INFO;

/** GA Bearer Characteristic Context localy */
typedef struct _GA_BRR_CHR_CONTEXT
{
    /** Attribute Value - ReadByType */
    UCHAR value[GA_BRR_MAX_ATTRVAL_LEN];

    /** Attribute Value Length - ReadByType */
    UINT16 length;

    /** Status - ReadByType */
    UINT16 status;

    /** UUID of Characteristic */
    GA_BRR_UUID uuid;

    /** Characteristic Instance */
    GA_BRR_CHR_INST inst;

    /** is response required */
    UINT8 to_rsp;

    /** Is Blob Request */
    UCHAR is_blob;

} GA_BRR_CHR_CONTEXT;

/** GA Bearer Characteristic Value */
typedef struct _GA_BRR_CHR_VAL
{
    /** Value array of octets */
    UCHAR * val;

    /** Value length */
    UINT16 len;

} GA_BRR_CHR_VAL;

/** GA Bearer Service Range */
typedef struct _GA_BRR_ATTR_RANGE
{
    /** Start of Service */
    UINT16 start;

    /** End of Service */
    UINT16 end;

} GA_BRR_ATTR_RANGE;

/** GA Bearer Service Range */
typedef GA_BRR_ATTR_RANGE GA_BRR_SVC_RANGE;

/** GA Bearer Characteristic Range */
typedef GA_BRR_ATTR_RANGE GA_BRR_CHAR_RANGE;

/**
 * Service UUID information - Will be a list of this as event_data in
 * \ref GA_BRR_DISCOVER_SERVICE_CNF
 */
typedef struct _GA_BRR_SVC_INFO
{
    /** UUID of the Service */
    GA_BRR_UUID uuid;

    /** Service Range */
    GA_BRR_ATTR_RANGE range;

} GA_BRR_SVC_INFO;

/** Write Request Format */
typedef struct _GA_BRR_WRITE_REQ
{
    /** Write request Value */
    GA_BRR_CHR_VAL     req_data;

    /** Write Type representation */
    GA_BRR_WRITE_TYPE  write_type;

}GA_BRR_WRITE_REQ;

/** Broadcast Parameters - To setup the BIG */
typedef struct _GA_BRR_BCAST_PARAM
{
    /** Broadcast code */
    UCHAR broadcast_code[16];

    /** SDU Interval */
    UINT32 sdu_interval;

    /** Maximum SDU */
    UINT16 max_sdu;

    /** Maximum latency */
    UINT16 max_latency;

    /** Retransmission count */
    UCHAR rtn;

    /** Phy to use */
    UCHAR phy;

    /** packing format */
    UCHAR packing;

    /** Framing format */
    UCHAR framing;

    /** Encryption state */
    UCHAR encryption;

    /** Number of BIS */
    UCHAR bis_count;

} GA_BRR_BCAST_PARAM;

/** Broadcast Sync Parameters - To sync with the available BIG reported */
typedef struct _GA_BRR_BCAST_SYNC_PARAM
{
    /** Broadcast code */
    UCHAR broadcast_code[16];

    /** Pointer to the BIS stream */
    UCHAR * bis;

    /** Sync Timeout */
    UINT16 sync_timeout;

    /** Encryption state */
    UCHAR encryption;

    /** Maximum SubEvents */
    UCHAR mse;

    /** Number of BIS */
    UCHAR bis_count;

} GA_BRR_BCAST_SYNC_PARAM;

/** Characteristic UUID information */
typedef struct _GA_BRR_CHR_INFO
{
    /** UUID of the characteristic */
    GA_BRR_UUID uuid;

    /** Characteristic Handle */
    UINT16 handle;

    /** Characteristic Property */
    UINT8 property;

} GA_BRR_CHR_INFO;

/** Characteristic Descriptor UUID information */
typedef struct _GA_BRR_CHRDESC_INFO
{
    /** UUID of the characteristic descriptor */
    GA_BRR_UUID uuid;

    /** Characteristic Descriptor Handle */
    UINT16 handle;

} GA_BRR_CHRDESC_INFO;

/**
 * Service Composition Data - Will be the event_data in
 * \ref GA_BRR_GET_SERVICE_COMPOSITION_CNF
 */
typedef struct _GA_BRR_SERVICE_COMPOSITION
{
    /** Service Information */
    GA_BRR_SVC_INFO * service;

    /** List of Characteristic Information */
    GA_BRR_CHR_INFO * characteristic;

    /** Number of Characteristics */
    UINT8 characteristic_count;

} GA_BRR_SERVICE_COMPOSITION;

/**
 * Characteristic Composition Data - Will be the event_data in
 * \ref GA_BRR_GET_CHARACTERISTIC_COMPOSITION_CNF
 */
typedef struct _GA_BRR_CHARACTERISTIC_COMPOSITION
{
    /** List of Characteristic Descriptor Information */
    GA_BRR_CHRDESC_INFO * desc;

    /** Number of Characteristic Descriptors */
    UINT8 desc_count;

} GA_BRR_CHARACTERISTIC_COMPOSITION;

/**
 * Data - Will be the event_data in
 * \ref
 */
typedef struct _GA_BRR_EVENT_PARAMS
{
    /** Event data pointer */
    void        * event_data;

    /** Event data length */
    UINT16        event_datalen;

    /** Event Status */
    UINT16        event_status;

    /** Event type */
    UINT8         event_type;

} GA_BRR_EVENT_PARAMS;

/** AES-CMAC Info */
typedef struct _GA_BRR_AESCMAC_INFO
{
    /** Plain Text to be authenticated */
    UCHAR * text;

    /** 16 octet Key for Authentication */
    UCHAR * key;

    /** Plain Text length */
    UINT16 textlen;

    /** MAC length required */
    UINT8 maclen;

    /**
     * Generate/Verify
     * 0x00U - Generate
     * 0x01U - Verify
     */
    UINT8 verify;

} GA_BRR_AESCMAC_INFO;

/** \} */

/** \} */

/**
 * \defgroup ga_brr_cb Application Callback
 * \{
 * \brief This Section Describes the module Callback interface offered
 * to the application.
 */

/**
 * \brief GA Bearer Callback to core
 *
 * \param [in] device        Peer Device Info
 * \param [in] event_type    Event Type
 * \param [in] event_status  Event Status
 * \param [in] event_data    Event Data
 * \param [in] event_datalen Event Data Length
 */
typedef GA_RESULT (* GA_BRR_CB)
                  (
                      /* IN */ GA_BRR_DEVICE * device,
                      /* IN */ void          * context,
                      /* IN */ UINT8           event_type,
                      /* IN */ UINT16          event_status,
                      /* IN */ void          * event_data,
                      /* IN */ UINT16          event_datalen
                  );

/**
 * \brief GA Profile Callback to core
 *
 * \param [in] device        Peer Device Info
 * \param [in] context       Reference context
 * \param [in] event_type    Event Type
 * \param [in] event_status  Event Status
 * \param [in] event_data    Event Data
 * \param [in] event_datalen Event Data Length
 */
typedef GA_BRR_CB GA_BRR_PROFILE_CB;

/**
 * \brief GA Service Callback to core
 *
 * \param [in] device        Peer Device Info
 * \param [in] context       Reference context
 * \param [in] event_type    Event Type
 * \param [in] event_status  Event Status
 * \param [in] event_data    Event Data
 * \param [in] event_datalen Event Data Length
 */
typedef GA_BRR_CB GA_BRR_SERVICE_CB;

/**
 * \brief GA Crypto Callback to core
 *
 * \param [in] event_type    Event Type
 * \param [in] event_status  Event Status
 * \param [in] event_data    Event Data
 * \param [in] event_datalen Event Data Length
 * \param [in] context       User context given
 */
typedef void (*GA_BRR_CRYPTO_CB)
             (
                 /* IN */ UINT8         event_type,
                 /* IN */ UINT16        event_status,
                 /* IN */ void        * event_data,
                 /* IN */ UINT16        event_datalen,
                 /* IN */ void        * context
             );

/** \} */

/**
 * \addtogroup ga_brr_defines
 * \{
 */

/**
 * \addtogroup ga_brr_structures
 * \{
 */

/**
 * \defgroup ga_brr_interface Bearer Interface
 * \{
 * \brief This section lists the bearer interface for use
 * by the module.
 */

/** Interface structure for all bearer procedures */
typedef struct _GA_BRR_INTERFACE
{
    /**
     *  \brief To Init the GA Bearer Layer.
     *
     *  \par Description:
     *       This function enables to inilialize the GA Bearer Layer.
     *
     *  \param [in] cb
     *         Common callback of GA core
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* init) (/* IN */ GA_BRR_CB cb);

    /**
     *  \brief To Shutdown the GA Bearer Layer.
     *
     *  \par Description:
     *       This function enables to shutdown the GA Bearer Layer.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* shutdown) (void);

    /*
     * Register a profile callback from GA and assign a profile ID for further
     * referencing.
     */
    /**
     *  \brief Register a profile client.
     *
     *  \par Description:
     *       This function enables to Register a profile client module
     *       with the GA Bearer.
     *
     *  \param [in] id
     *         Module ID.
     *
     *  \param [in] cb
     *         Profile Callback.
     *
     *  \param [out] pid
     *         Profile context ID.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* register_profile) \
              (
                  /* IN  */ UINT32 id,
                  /* IN  */ GA_BRR_PROFILE_CB cb,
                  /* OUT */ GA_BRR_PRF_HANDLE * pid
              );

    /**
     *  \brief To Unregister a GA Profile with GA Bearer.
     *
     *  \par Description:
     *       This function enables to unregister a profile with GA Bearer.
     *
     *  \param [in] pid
     *         Profile context ID.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* unregister_profile) (/* IN */ GA_BRR_PRF_HANDLE pid);

#ifdef BRR_GATT_SERVER
    /**
     *  \brief Add a GATT Service.
     *
     *  \par Description:
     *       This function enables to add a GATT Service with the GA Bearer.
     *
     *  \param [in] service_uuid
     *         Assigned UUID of this GATT Service.
     *
     *  \param [in] service_type
     *         Type associated with the service.
     *
     *  \param [in] cb
     *         Callback associated with Service ID.
     *
     *  \param [out] sid
     *         Service context ID.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (*add_service) \
              (
                  /* IN  */ GA_BRR_UUID service_uuid,
                  /* IN  */ UINT8 service_type,
                  /* IN  */ GA_BRR_SERVICE_CB cb,
                  /* OUT */ GA_BRR_SVC_INST * sid
              );

    /**
     *  \brief Add a Included GATT Service.
     *
     *  \par Description:
     *       This function enables to add a Included GATT Service with the
     *       GA Bearer.
     *
     *  \param [in] sid
     *         Service context ID.
     *
     *  \param [in] service_uuid
     *         Assigned UUID of this GATT Service.
     *
     *  \param [in] service_state
     *         Initial state of the Included service. \n
     *         Enabled ( \ref GA_TRUE) or Disabled ( \ref GA_FALSE).
     *
     *  \param [out] isid
     *         Included Service context ID.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* include_service) \
              (
                  /* IN */ GA_BRR_SVC_INST sid,
                  /* IN */ GA_BRR_UUID service_uuid,
                  /* IN */ UINT8 service_state,
                  /* IN */ GA_BRR_SVC_INST * isid
              );

    /**
     *  \brief Remove a GATT Service.
     *
     *  \par Description:
     *       This function enables to remove a GATT Service with the GA Bearer.
     *
     *  \param [in] sid
     *         Service context ID.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* remove_service) (/* IN  */ GA_BRR_SVC_INST sid);

    /**
     *  \brief Add a GATT Characteristic to a Service.
     *
     *  \par Description:
     *       This function enables to add a GATT Characteristic to a given
     *       Service with the GA Bearer.
     *
     *  \param [in] sid
     *         Service context ID.
     *
     *  \param [in] char_uuid
     *         Assigned UUID of this GATT Characteristic.
     *
     *  \param [in] char_property
     *         Properties associated with this GATT Characteristic.
     *
     *  \param [in] value
     *         Any value associated with this GATT Characteristic.
     *
     *  \param [out] cid
     *         Characteristic context ID.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* add_characteristic) \
              (
                  /* IN  */ GA_BRR_SVC_INST sid,
                  /* IN  */ GA_BRR_UUID     char_uuid,
                  /* IN  */ UINT16          char_property,
                  /* IN  */ GA_BRR_CHR_VAL  * value,
                  /* OUT */ GA_BRR_CHR_INST * cid
              );

    /**
     *  \brief Enable/Disable a GATT Service.
     *
     *  \par Description:
     *       This function enables/disables GATT Service.
     *
     *  \param [in] sid
     *         Service ID.
     *
     *  \param [in] iid
     *         Including Service ID, if sid is of an included service. \n
     *         \ref GA_BRR_SERVICE_ID_INVALID if not applicable.
     *
     *  \param [in] state
     *         Enable ( \ref GA_TRUE) or Disable ( \ref GA_FALSE).
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* manage_service) \
              (
                  /* IN  */ UINT8 sid,
                  /* IN  */ UINT8 iid,
                  /* IN  */ UINT8 state
              );

    /**
     *  \brief Enable/Disable a GATT Characteristic.
     *
     *  \par Description:
     *       This function enables/disables GATT Characteristic.
     *
     *  \param [in] sid
     *         Service ID.
     *
     *  \param [in] cid
     *         Characteristic ID.
     *
     *  \param [in] state
     *         Enable ( \ref GA_TRUE) or Disable ( \ref GA_FALSE).
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* manage_characteristic) \
              (
                  /* IN  */ UINT8 sid,
                  /* IN  */ UINT8 cid,
                  /* IN  */ UINT8 state
              );

    /*
     * Provision to update the characteric value
     */
    /**
     *  \brief Update a GATT Characteristic to a Service.
     *
     *  \par Description:
     *       This function enables to Update a GATT Characteristic to a given
     *       Service with the GA Bearer.
     *
     *  \param [in] sid
     *         Service context ID.
     *
     *  \param [in] char_uuid
     *         Assigned UUID of this GATT Characteristic.
     *
     *  \param [in] cid
     *         Characteristic context ID.
     *
     *  \param [in] value
     *         Any value associated with this GATT Characteristic.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* update_characteristic_value) \
              (
                  /* IN */ GA_BRR_SVC_INST sid,
                  /* IN */ GA_BRR_UUID char_uuid,
                  /* IN */ GA_BRR_CHR_INST cid,
                  /* IN */ GA_BRR_CHR_VAL * value
              );

    /**
     *  \brief Send response for a Characterisitc Write.
     *
     *  \par Description:
     *       This function enables to respond to a Characteritis Write
     *       from a peer device.
     *
     *  \param [in] device
     *         Peer Device Connection Identifier.
     *
     *  \param [in] ctx
     *         Assigned UUID of this GATT Characteristic.
     *
     *  \param [in] status
     *         Characteristic context ID.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* write_characteristic_rsp) \
              (
                  /* IN */ GA_BRR_DEVICE      * device,
                  /* IN */ GA_BRR_CHR_CONTEXT * ctx,
                  /* IN */ UINT16             status
              );

    /**
     *  \brief Send response for a Characterisitc Read.
     *
     *  \par Description:
     *       This function enables to respond to a Characteritis Read
     *       from a peer device.
     *
     *  \param [in] device
     *         Peer Device Connection Identifier.
     *
     *  \param [in] ctx
     *         Assigned UUID of this GATT Characteristic.
     *
     *  \param [in] status
     *         Characteristic context ID.
     *
     *  \param [in] value
     *         Any value associated with this GATT Characteristic.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* read_characteristic_rsp) \
              (
                  /* IN */ GA_BRR_DEVICE      * device,
                  /* IN */ GA_BRR_CHR_CONTEXT * ctx,
                  /* IN */ UINT16             status,
                  /* IN */ GA_BRR_CHR_VAL     * value
              );

    /*
     * Notify/Indicate value of the specified characteristic UUID for
     * the peer device
     */
    /**
     *  \brief Notify/Indicate a Characterisitic Value to peer device.
     *
     *  \par Description:
     *       This function enables to send a charactertisic Notifications/Indications to
     *       peer device.
     *
     *  \param [in] device
     *         Peer Device Connection Identifier.
     *
     *  \param [in] sid
     *         Service context ID.
     *
     *  \param [in] char_uuid
     *         Assigned UUID of this GATT Characteristic.
     *
     *  \param [in] cid
     *         Characteristic context ID where needed, else can be
     *         \ref GA_BRR_INST_DONTCARE.
     *
     *  \param [in] value
     *         Any value associated with this GATT Characteristic.
     *
     *  \param [in] nwr
     *         If Notification, Set nwr to \ref GA_TRUE. \n
     *         Else for Indication, Set nwr to \ref GA_FALSE.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* notify_characteristic) \
              (
                  /* IN */ GA_BRR_DEVICE   * device,
                  /* IN */ GA_BRR_SVC_INST sid,
                  /* IN */ GA_BRR_UUID     char_uuid,
                  /* IN */ GA_BRR_CHR_INST cid,
                  /* IN */ GA_BRR_CHR_VAL  * value,
                  /* IN */ UINT8           nwr
              );
#endif /* BRR_GATT_SERVER */

#ifdef BRR_GATT_CLIENT
    /*
     * Enhance the bearer transport if required by the profile or application - eATT
     * Should the needed MTU(or other associated things incase of eATT) also be
     * part of this interface? Else, we might need some other interface for that.
     */
    /**
     *  \brief Update or Setup a new Transport.
     *
     *  \par Description:
     *       TODO: Need to revist for both Profile and Server roles.
     *
     *  \param [in] pid
     *         Profile context ID.
     *
     *  \param [in] type
     *         Type of Transport.
     *
     *  \param [in] enable
     *         State of Transport.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* setup_transport) \
              (
                  /* IN */ GA_BRR_PRF_HANDLE pid,
                  /* IN */ UINT8 type,
                  /* IN */ UINT8 enable
              );

    /*
     * Discover the service information from a profile instance for a service from
     * the peer device.
     */
    /**
     *  \brief Discover a peer GATT Service.
     *
     *  \par Description:
     *       This function enables to discover a Peer GATT Service.
     *
     *  \param [in] pid
     *         Profile context ID.
     *
     *  \param [in] device
     *         Peer Device Connection Identifier.
     *
     *  \param [in] svc_info
     *         Contains the assigned UUID of this GATT Primary Service to be looked
     *         for in remote. Or, contains the Service Handle Range where Included
     *         services are to be looked for in remote.
     *
     *  \param [in] disc_type
     *         Type of Service discovery to be performed in the remote.
     *         \ref GA_BRR_PS_DISCOVERY or \ref GA_BRR_SS_DISCOVERY or
     *         \ref GA_BRR_IS_DISCOVERY.
     *
     *  \param [in] context
     *         Any(Optional) Upper Layer provided context for Book-keeping.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* discover_service) \
              (
                  /* IN */ GA_BRR_PRF_HANDLE pid,
                  /* IN */ GA_BRR_DEVICE     * device,
                  /* IN */ GA_BRR_SVC_INFO   * svc_info,
                  /* IN */ UCHAR             disc_type,
                  /* IN */ void              * context
              );

    /*
     * Load the service information (characteristics and descriptors
     * of the specified service) and have it in the datastructure for
     * lookup during read/write.
     * - Should this have an associated service id?
     */
    /**
     *  \brief Discover composition of a given peer Service.
     *
     *  \par Description:
     *       This function enables to discover constituents of a given
     *       peer service.
     *
     *  \param [in] pid
     *         Profile context ID.
     *
     *  \param [in] device
     *         Peer Device Connection Identifier.
     *
     *  \param [in] service
     *         Service Related Information.
     *
     *  \param [in] context
     *         Any(Optional) Upper Layer provided context for Book-keeping.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* get_service_composition) \
              (
                  /* IN */ GA_BRR_PRF_HANDLE pid,
                  /* IN */ GA_BRR_DEVICE     * device,
                  /* IN */ GA_BRR_SVC_INFO   * service,
                  /* IN */ void              * context
              );

    /*
     * Load the characteristic information (descriptors
     * of the specified characteristic) and have it in the datastructure for
     * lookup during read/write.
     * - Should this have an associated characteristic id?
     */
    /**
     *  \brief Discover composition of a given peer Characteristic.
     *
     *  \par Description:
     *       This function enables to discover descriptors of a given
     *       peer characteristic.
     *
     *  \param [in] pid
     *         Profile context ID.
     *
     *  \param [in] device
     *         Peer Device Connection Identifier.
     *
     *  \param [in] characteristic
     *         Characterisitc Related Information.
     *
     *  \param [in] context
     *         Any(Optional) Upper Layer provided context for Book-keeping.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* get_characteristic_composition) \
              (
                  /* IN */ GA_BRR_PRF_HANDLE pid,
                  /* IN */ GA_BRR_DEVICE     * device,
                  /* IN */ GA_BRR_CHAR_RANGE * characteristic,
                  /* IN */ void              * context
              );

    /* Write value to the specified characteristic UUID for the peer device */
    /*
     * NOTE:
     * - Should this Interface also handle Prepare Write/ Reliable Write etc?
     * - Also, Will this interface need a Char Instance associated with it
     *   esp in case of multiple instance of same char?
     */
    /**
     *  \brief Write the Characterisitc Value.
     *
     *  \par Description:
     *       This function enables to Write value of a Peer GATT Characteristic.
     *
     *  \param [in] pid
     *         Profile context ID.
     *
     *  \param [in] device
     *         Peer Device Connection Identifier.
     *
     *  \param [in] characteristic
     *         Characteristic Handle to be Read.
     *
     *  \param [in] value
     *         Value to be written to the Characteristic.
     *
     *  \param [in] wwr
     *         Flag to inform if Write Without Response or otherwise.
     *
     *  \param [in] context
     *         Any(Optional) Upper Layer provided context for Book-keeping.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* write_characteristic) \
              (
                  /* IN */ GA_BRR_PRF_HANDLE pid,
                  /* IN */ GA_BRR_DEVICE     * device,
                  /* IN */ GA_BRR_CHR_HANDLE characteristic,
                  /* IN */ GA_BRR_CHR_VAL    * value,
                  /* IN */ UINT8             wwr,
                  /* IN */ void              * context
              );

    /* Read value of the specified characteristic UUID for the peer device */
    /*
     * NOTE:
     * - Should this Interface take care of handling Read Long/Blob?
     *   Else, it might need an Offset too.
     * - Also, Will this interface need a Char Instance associated with it
     *   esp in case of multiple instance of same char?
     */
    /**
     *  \brief Read the Characterisitc Value.
     *
     *  \par Description:
     *       This function enables to read value of a Peer GATT Characteristic.
     *
     *  \param [in] pid
     *         Profile context ID.
     *
     *  \param [in] device
     *         Peer Device Connection Identifier.
     *
     *  \param [in] characteristic
     *         Characteristic Handle to be Read.
     *
     *  \param [in] context
     *         Any(Optional) Upper Layer provided context for Book-keeping.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* read_characteristic) \
              (
                  /* IN */ GA_BRR_PRF_HANDLE  pid,
                  /* IN */ GA_BRR_DEVICE      *device,
                  /* IN */ GA_BRR_CHR_HANDLE  characteristic,
                  /* IN */ void               *context
              );

    /*
     * Configure notification/Indication enable/disable specified
     * characteristic UUID for the peer device.
     * NOTE:
     * - Either the state can be 0, 1, 2 or it can be TRUE/FALSE.
     *   If its the latter, then internally it should detect if its IND/NTF
     *   based on each character.
     * - Also, Will this interface need a Char Instance associated with it
     *   esp in case of multiple instance of same char?
     */

    /**
     *  \brief Configure Notification/Indication for a Characterisitic Value.
     *
     *  \par Description
     *  This routine configures Notification/Indication enable/disable for
     *  specified characteristic descriptor for the peer device.
     *
     *  \param [in] pid
     *         Profile context ID.
     *
     *  \param [in] device
     *         Peer Device Connection Identifier.
     *
     *  \param [in] characteristic
     *         Descriptor/CCCD Handle of the Char.
     *
     *  \param [in] state
     *         Enable/Disable the Notification/Indication. \n
     *         Or the value with \ref GA_BRR_NTF_RESPONSE_MASK to configure for
     *         Indications.
     *
     *  \param [in] context
     *         Any(Optional) Upper Layer provided context for Book-keeping.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* config_notification) \
              (
                  /* IN */ GA_BRR_PRF_HANDLE    pid,
                  /* IN */ GA_BRR_DEVICE        *device,
                  /* IN */ GA_BRR_CHR_HANDLE    characteristic,
                  /* IN */ UINT8                state,
                  /* IN */ void                 *context
              );
#endif /* BRR_GATT_CLIENT */

#ifdef BRR_GAP_BROADCASTER
    /**
     *  \brief Configure Extended/Periodic Advertising.
     *
     *  \par Description
     *  This routine Configures the BLE Advertisment.
     *
     *  \param [in] pid
     *         Profile context ID.
     *
     *  \param [in] type
     *         Extended Advertising, Use \ref GA_BRR_ADV_TYPE_EA. \n
     *         Periodic Advertising, Use \ref GA_BRR_ADV_TYPE_PA.
     *
     *  \param [in] handle
     *         Advertising Handle.
     *
     *  \param [in] enable
     *         Enable advertising, Use \ref GA_TRUE. \n
     *         Disable advertising, Use \ref GA_FALSE.
     *
     *  \param [in] data
     *         Advertising Data for Extended/Periodic Advertising.
     *
     *  \param [in] datalen
     *         Advertising Datalen for Extended/Periodic Advertising.
     *
     *  \param [in] context
     *         Any(Optional) Upper Layer provided context for Book-keeping.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* config_adv) \
              (
                  /* IN */ GA_BRR_PRF_HANDLE pid,
                  /* IN */ UINT8             type,
                  /* IN */ UINT8             handle,
                  /* IN */ UINT8             enable,
                  /* IN */ UCHAR             *data,
                  /* IN */ UINT8             datalen,
                  /* IN */ void              *context
              );

    /**
     *  \brief Configure BIG
     *
     *  \par Description
     *  This routine Configures the BLE BIG for broadcast.
     *
     *  \param [in] pid
     *         Profile context ID.
     *
     *  \param [in] handle
     *         Valid handle.
     *
     *  \param [in] adv_handle
     *         Valid Adv Handle. \n
     *         NULL for Terminate BIG.
     *
     *  \param [in] param
     *         Valid params for Create BIG. \n
     *         NULL for Terminate BIG.
     *
     *  \param [in] context
     *         Any(Optional) Upper Layer provided context for Book-keeping.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* config_broadcast) \
              (
                  /* IN */ GA_BRR_PRF_HANDLE  pid,
                  /* IN */ UINT8              handle,
                  /* IN */ UINT8              adv_handle,
                  /* IN */ GA_BRR_BCAST_PARAM *param,
                  /* IN */ void               *context
              );
#endif /* BRR_GAP_BROADCASTER */

#ifdef BRR_GAP_OBSERVER
    /**
     *  \brief Configure Extended Scanning.
     *
     *  \par Description
     *  This routine Configures the BLE Scanning.
     *
     *  \param [in] pid
     *         Profile context ID.
     *
     *  \param [in] enable
     *         Enable Scan, Use \ref GA_TRUE. \n
     *         Disable Scan, Use \ref GA_FALSE.
     *
     *  \param [in] context
     *         Any(Optional) Upper Layer provided context for Book-keeping.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* config_scan) \
              (
                  /* IN */ GA_BRR_PRF_HANDLE pid,
                  /* IN */ UINT8             enable,
                  /* IN */ void              *context
              );

    /**
     *  \brief Configure scan syncing with Periodic Adv
     *
     *  \par Description
     *  This routine Configures the BLE scan syncing with PA.
     *
     *  \param [in] pid
     *         Profile context ID.
     *
     *  \param [in] handle
     *         Valid UINT8 handle for Periodic Adv Create Sync. \n
     *         Valid UINT16 handle for Periodic Adv Terminate Sync.
     *
     *  \param [in] device
     *         Valid Device for Periodic Adv Create Sync. \n
     *         NULL for Periodic Adv Terminate Sync.
     *
     *  \param [in] context
     *         Any(Optional) Upper Layer provided context for Book-keeping.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* config_sync) \
              (
                  /* IN */ GA_BRR_PRF_HANDLE pid,
                  /* IN */ UINT16            handle,
                  /* IN */ GA_BRR_DEVICE     *device,
                  /* IN */ void              *context
              );

    /**
     *  \brief Cancel syncing with Periodic Adv.
     *
     *  \par Description
     *  This routine cancels syncing with ongoing Sync request for PA.
     *
     *  \param [in] pid
     *         Profile context ID.
     *
     *  \param [in] context
     *         Any(Optional) Upper Layer provided context for Book-keeping.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* config_sync_cancel) \
              (
                  /* IN */ GA_BRR_PRF_HANDLE pid,
                  /* IN */ void              *context
              );

    /**
     *  \brief Configure BIG sync
     *
     *  \par Description
     *  This routine Configures the BLE BIG sync for broadcast.
     *
     *  \param [in] pid
     *         Profile context ID.
     *
     *  \param [in] handle
     *         Valid handle.
     *
     *  \param [in] sync_handle
     *         Valid Sync Handle. \n
     *         NULL for Terminate BIG.
     *
     *  \param [in] param
     *         Valid params for BIG Create Sync. \n
     *         NULL for BIG Terminate Sync.
     *
     *  \param [in] context
     *         Any(Optional) Upper Layer provided context for Book-keeping.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* config_broadcast_sync) \
              (
                  /* IN */ GA_BRR_PRF_HANDLE        pid,
                  /* IN */ UINT8                    handle,
                  /* IN */ UINT16                   sync_handle,
                  /* IN */ GA_BRR_BCAST_SYNC_PARAM  *param,
                  /* IN */ void                     *context
              );
#endif /* BRR_GAP_OBSERVER */

    /**
     *  \brief Dispatches the given event to respective profile callback
     *
     *  \par Description
     *  This routine dispatches the said event with parameters to the
     *  respective profile callback.
     *
     *  \param [in] pid
     *         Profile context ID.
     *
     *  \param [in] device
     *         Device associated with the event.
     *
     *  \param [in] event_params
     *         Params associated with the event that identifies type,
     *         status, data and datalen.
     *
     *  \param [in] context
     *         Any(Optional) Upper Layer provided context for Book-keeping.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT (* dispatch_event) \
              (
                  /* IN */ GA_BRR_PRF_HANDLE        pid,
                  /* IN */ GA_BRR_DEVICE           *device,
                  /* IN */ GA_BRR_EVENT_PARAMS     *event_params,
                  /* IN */ void                    *context
              );

    /**
     *  \brief Create/Verify Resolvable Private Address
     *
     *  \par Description
     *  This routine triggers the Resolvable Private Address
     *  operation at the bearer stack.
     *
     *  \param [in] pid
     *         Profile context ID.
     *
     *  \param [in] addr
     *         Valid Address for Verify Resolvable Private Address. \n
     *         NULL for Create Resolvable Private Address.
     *
     *  \param [in] irk
     *         Valid Identity Resolving Key.
     *
     *  \param [in] context
     *         Any(Optional) Upper Layer provided context for Book-keeping.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT(*rpa_operate) \
             (
                 /* IN */ GA_BRR_PRF_HANDLE     pid,
                 /* IN */ UCHAR               * addr,
                 /* IN */ UCHAR               * irk,
                 /* IN */ void                * context
             );

    /**
     *  \brief Triggers the Cryptographic operation
     *
     *  \par Description
     *  This routine triggers the Cryptographic operation for the
     *  specified operation on the given information.
     *
     *  \param [in] op
     *         Refer \ref GA_BRR_CRYPTO_AESCMAC
     *
     *  \param [in] info
     *         Valid info, Refer \ref GA_BRR_AESCMAC_INFO
     *
     *  \param [in] cb
     *         Callback for event after completion.
     *
     *  \param [in] context
     *         Any(Optional) Upper Layer provided context for Book-keeping.
     *
     *  \return \ref GA_SUCCESS or one of the error codes as defined in
     *          \ref GA_error.h.
     */
    GA_RESULT(*crypto) \
             (
                 /* IN */ UCHAR             op,
                 /* IN */ void            * info,
                 /* IN */ GA_BRR_CRYPTO_CB  cb,
                 /* IN */ void            * context
             );

} GA_BRR_INTERFACE;

/** \} */

/** \} */

/* --------------------------------------------- Macros */
/**
 * \addtogroup ga_brr_macros
 * \{
 */

/**
 * \name BD Address Related
 * \{
 * \brief This section describes the BD address related macros defined for Bearer.
 */

/** Check for connectionless event code */
#define GA_BRR_ISEVENT_CONNECTIONLESS(ev) \
    (GA_BRR_CONNECTIONLESS_EVENT_CODE == (GA_BRR_CONNECTIONLESS_EVENT_CODE & (ev)))

/** Compare Bearer Device address type */
#define GA_COMPARE_BRR_DEV_ADDR_TYPE(type_a,type_b)\
        (((type_a) == (type_b))? GA_TRUE: GA_FALSE)

/** Compare Bearer Device address */
#define GA_COMPARE_BRR_DEV_ADDR(dev_a,dev_b)\
        ((0 == GA_mem_cmp((dev_a), (dev_b), GA_BD_ADDR_SIZE))? GA_TRUE: GA_FALSE)

/**
 * Compare Bearer Device.
 * It compares device address and address type
 */
#define GA_COMPARE_BRR_DEVICE(dev_a,dev_b)\
        ((GA_COMPARE_BRR_DEV_ADDR_TYPE((dev_a)->bd_type,(dev_b)->bd_type)) &&\
         (GA_COMPARE_BRR_DEV_ADDR((dev_a)->bd_addr,(dev_b)->bd_addr)))

/** Initialize Bearer Device */
#define GA_INIT_BRR_DEVICE(dev) \
        GA_mem_set ((dev)->bd_addr, 0, GA_BD_ADDR_SIZE); \
        (dev)->bd_type = 0x00

/** Check Bearer Device address for Non-Zero */
#define GA_BRR_DEV_ADDR_IS_NON_ZERO(addr)\
        ((0x00 == (*((addr) + 0) | *((addr) + 1) | *((addr) + 2) | *((addr) + 3) | *((addr) + 4) | *((addr) + 5)))?\
        GA_FALSE:GA_TRUE)

/** Bearer Device address */
#define GA_BRR_DEV_ADDR(dev) (dev)->bd_addr

/** Bearer Device address type */
#define GA_BRR_DEV_ADDR_TYPE(dev) (dev)->bd_type

/** Copy Bearer Device address */
#define GA_COPY_BRR_DEV_ADDR(dest, src) \
        GA_mem_copy ((dest), (src), GA_BD_ADDR_SIZE);

/** Copy Bearer Device type */
#define GA_COPY_BRR_DEV_TYPE(dest,src)\
        (dest) = (src);

/**
 * Copy Bearer Device.
 * It copies Bearer device type and address.
 */
#define GA_COPY_BRR_DEVICE(dest,src)\
        GA_COPY_BRR_DEV_TYPE((dest)->bd_type,(src)->bd_type)\
        GA_COPY_BRR_DEV_ADDR((dest)->bd_addr,(src)->bd_addr)

/** Bearer Device format specifier */
#define GA_BRR_DEVICE_FRMT_SPECIFIER\
        "ADDR: %02X:%02X:%02X:%02X:%02X:%02X, TYPE: %02X"

/** Prints device address and type */
#define GA_BRR_DEVICE_PRINT_STR(ref)\
        (ref)->bd_addr[0],(ref)->bd_addr[1],(ref)->bd_addr[2],\
        (ref)->bd_addr[3],(ref)->bd_addr[4],(ref)->bd_addr[5],\
        (ref)->bd_type

/** \} */
/** \} */

/** \} */

/* --------------------------------------------- APIs */

/**
 * \defgroup ga_brr_api_defs API Definitions
 * \{
 * \brief This section describes the EtherMind Generic Audio Bearer APIs.
 */

/**
 * \defgroup ga_brr_server_api_defs Server
 * \{
 * \brief This section describes the Generic Audio Bearer APIs for Server.
 */

/**
 * \name Bearer Server APIs - Init
 * \{
 * \brief This section describes the Generic Audio Bearer Init APIs for Server.
 */

/**
 *  \brief To Register a BLE bearer to the GA Layer.
 *
 *  \par Description:
 *       This function enables to register the BLE bearer to GA Bearer Layer.
 *
 *  \param [in] iface
 *         The interface structure with assigned functions to different interfaces
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_register(GA_BRR_INTERFACE * iface);

/** \} */

/** \} */

/**
 * \defgroup ga_brr_common_api_defs Common
 * \{
 * \brief This section describes the Generic Audio Bearer APIs for both Client
 * and Server.
 */

/**
 * \name Bearer Common APIs - Init
 * \{
 * \brief This section describes the Generic Audio Bearer Common Init APIs.
 */

/**
 *  \brief To Init the GA Bearer Layer.
 *
 *  \par Description:
 *       This function enables to inilialize the GA Bearer Layer.
 *
 *  \param [in] cb
 *         Common callback of GA core
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_init(GA_BRR_CB cb);

/** \} */

/**
 * \name Bearer Common APIs - De-Init
 * \{
 * \brief This section describes the Generic Audio Bearer Common De-Init APIs.
 */

/**
 *  \brief To Shutdown the GA Bearer Layer.
 *
 *  \par Description:
 *       This function enables to shutdown the GA Bearer Layer.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_shutdown(void);

/** \} */

/** \} */

/**
 * \addtogroup ga_brr_server_api_defs
 * \{
 */

/**
 * \name Bearer Server APIs - Setup
 * \{
 * \brief This section describes the Generic Audio Bearer Setup APIs for Server.
 */

/**
 *  \brief Add a GATT Service.
 *
 *  \par Description:
 *       This function enables to add a GATT Service with the GA Bearer.
 *
 *  \param [in] service_uuid
 *         Assigned UUID of this GATT Service.
 *
 *  \param [in] service_type
 *         Type associated with the service.
 *
 *  \param [in] cb
 *         Callback associated with Service ID.
 *
 *  \param [out] sid
 *         Service context ID.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_add_service
          (
              /* IN  */ GA_BRR_UUID       service_uuid,
              /* IN  */ UINT8             service_type,
              /* IN  */ GA_BRR_SERVICE_CB cb,
              /* OUT */ GA_BRR_SVC_INST   * sid
          );

/** \} */

/**
 * \name Bearer Server APIs - Release
 * \{
 * \brief This section describes the Generic Audio Bearer Release APIs for
 * Server.
 */

/**
 *  \brief Remove a GATT Service.
 *
 *  \par Description:
 *       This function enables to remove a GATT Service with the GA Bearer.
 *
 *  \param [in] sid
 *         Service context ID.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_remove_service
          (
              /* IN */ GA_BRR_SVC_INST sid
          );

/** \} */

/**
 * \name Bearer Server APIs - Setup
 * \{
 * \brief This section describes the Generic Audio Bearer Setup APIs for Server.
 */

/**
 *  \brief Add a Included GATT Service.
 *
 *  \par Description:
 *       This function enables to add a Included GATT Service with the
 *       GA Bearer.
 *
 *  \param [in] sid
 *         Service context ID.
 *
 *  \param [in] service_uuid
 *         Assigned UUID of this GATT Service.
 *
 *  \param [in] service_state
 *         Initial state of the Included service. \n
 *         Enabled ( \ref GA_TRUE) or Disabled ( \ref GA_FALSE).
 *
 *  \param [in] isid
 *         Included Service context ID.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_include_service
          (
              /* IN  */ GA_BRR_SVC_INST sid,
              /* IN  */ GA_BRR_UUID     service_uuid,
              /* IN  */ UINT8           service_state,
              /* IN */ GA_BRR_SVC_INST * isid
          );

/**
 *  \brief Add a GATT Characteristic to a Service.
 *
 *  \par Description:
 *       This function enables to add a GATT Characteristic to a given
 *       Service with the GA Bearer.
 *
 *  \param [in] sid
 *         Service context ID.
 *
 *  \param [in] char_uuid
 *         Assigned UUID of this GATT Characteristic.
 *
 *  \param [in] char_property
 *         Properties associated with this GATT Characteristic.
 *
 *  \param [in] value
 *         Any value associated with this GATT Characteristic.
 *
 *  \param [out] cid
 *         Characteristic context ID.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_add_characteristic
          (
              /* IN  */ GA_BRR_SVC_INST sid,
              /* IN  */ GA_BRR_UUID     char_uuid,
              /* IN  */ UINT16          char_property,
              /* IN  */ GA_BRR_CHR_VAL  * value,
              /* OUT */ GA_BRR_CHR_INST * cid
          );

/**
 *  \brief Enable/Disable a GATT Service.
 *
 *  \par Description:
 *       This function enables/disables GATT Service.
 *
 *  \param [in] sid
 *         Service ID.
 *
 *  \param [in] iid
 *         Including Service ID, if sid is of an included service. \n
 *         \ref GA_BRR_SERVICE_ID_INVALID if not applicable.
 *
 *  \param [in] state
 *         Enable ( \ref GA_TRUE) or Disable ( \ref GA_FALSE).
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_manage_service
          (
              /* IN  */ UINT8 sid,
              /* IN  */ UINT8 iid,
              /* IN  */ UINT8 state
          );

/**
 *  \brief Enable a GATT Service.
 *
 *  \par Description:
 *       This function enables GATT Service.
 *
 *  \param [in] sid
 *         Service ID.
 *
 *  \param [in] iid
 *         Including Service ID, if sid is of an included service. \n
 *         \ref GA_BRR_SERVICE_ID_INVALID if not applicable.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
#define GA_brr_enable_service(sid, iid)\
        GA_brr_manage_service\
        (\
            (sid),\
            (iid),\
            GA_TRUE\
        )

/**
 *  \brief Disable a GATT Service.
 *
 *  \par Description:
 *       This function disables GATT Service.
 *
 *  \param [in] sid
 *         Service ID.
 *
 *  \param [in] iid
 *         Including Service ID, if sid is of an included service. \n
 *         \ref GA_BRR_SERVICE_ID_INVALID if not applicable.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
#define GA_brr_disable_service(sid, iid)\
        GA_brr_manage_service\
        (\
            (sid),\
            (iid),\
            GA_FALSE\
        )

/**
 *  \brief Enable/Disable a GATT Characteristic.
 *
 *  \par Description:
 *       This function enables/disables GATT Characteristic.
 *
 *  \param [in] sid
 *         Service ID.
 *
 *  \param [in] cid
 *         Characteristic ID.
 *
 *  \param [in] state
 *         Enable ( \ref GA_TRUE) or Disable ( \ref GA_FALSE).
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_manage_characteristic
          (
              /* IN  */ UINT8 sid,
              /* IN  */ UINT8 cid,
              /* IN  */ UINT8 state
          );

/**
 *  \brief Enable a GATT Characteristic.
 *
 *  \par Description:
 *       This function enables GATT Characteristic.
 *
 *  \param [in] sid
 *         Service ID.
 *
 *  \param [in] cid
 *         Characteristic ID.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
#define GA_brr_enable_characteristic(sid, cid)\
        GA_brr_manage_characteristic\
        (\
            (sid),\
            (cid),\
            GA_TRUE\
        )

/**
 *  \brief Disable a GATT Characteristic.
 *
 *  \par Description:
 *       This function disables GATT Characteristic.
 *
 *  \param [in] sid
 *         Service ID.
 *
 *  \param [in] cid
 *         Characteristic ID.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
#define GA_brr_disable_characteristic(sid, cid)\
        GA_brr_manage_characteristic\
        (\
            (sid),\
            (cid),\
            GA_FALSE\
        )

/** \} */

/**
 * \name Bearer Server APIs - Read/Write
 * \{
 * \brief This section describes the Generic Audio Bearer Read/Write APIs
 * for Server.
 */

/*
 * Provision to update the characteric value
 */
/**
 *  \brief Update a GATT Characteristic to a Service.
 *
 *  \par Description:
 *       This function enables to Update a GATT Characteristic to a given
 *       Service with the GA Bearer.
 *
 *  \param [in] sid
 *         Service context ID.
 *
 *  \param [in] char_uuid
 *         Assigned UUID of this GATT Characteristic.
 *
 *  \param [in] cid
 *         Characteristic context ID.
 *
 *  \param [in] value
 *         Any value associated with this GATT Characteristic.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_update_characteristic_value
          (
              /* IN */ GA_BRR_SVC_INST sid,
              /* IN */ GA_BRR_UUID     char_uuid,
              /* IN */ GA_BRR_CHR_INST cid,
              /* IN */ GA_BRR_CHR_VAL  * value
          );

/**
 *  \brief Send response for a Characterisitc Write.
 *
 *  \par Description:
 *       This function enables to respond to a Characteritis Write
 *       from a peer device.
 *
 *  \param [in] device
 *         Peer Device Connection Identifier.
 *
 *  \param [in] ctx
 *         Assigned UUID of this GATT Characteristic.
 *
 *  \param [in] status
 *         Characteristic context ID.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_write_characteristic_rsp
          (
              /* IN */ GA_BRR_DEVICE      * device,
              /* IN */ GA_BRR_CHR_CONTEXT * ctx,
              /* IN */ UINT16             status
          );

/**
 *  \brief Send response for a Characterisitc Read.
 *
 *  \par Description:
 *       This function enables to respond to a Characteritis Read
 *       from a peer device.
 *
 *  \param [in] device
 *         Peer Device Connection Identifier.
 *
 *  \param [in] ctx
 *         Assigned UUID of this GATT Characteristic.
 *
 *  \param [in] status
 *         Characteristic context ID.
 *
 *  \param [in] value
 *         Any value associated with this GATT Characteristic.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_read_characteristic_rsp
          (
              /* IN */ GA_BRR_DEVICE      * device,
              /* IN */ GA_BRR_CHR_CONTEXT * ctx,
              /* IN */ UINT16             status,
              /* IN */ GA_BRR_CHR_VAL     * value
          );

/** \} */

/**
 * \name Bearer Server APIs - Notify
 * \{
 * \brief This section describes the Generic Audio Bearer Notify APIs
 * for Server.
 */

/* Notify/Indicate value of the specified characteristic UUID for the peer device */
/**
 *  \brief Notify/Indicate a Characterisitic Value to peer device.
 *
 *  \par Description:
 *       This function enables to send a charactertisic Notifications/Indications to
 *       peer device.
 *
 *  \param [in] device
 *         Peer Device Connection Identifier.
 *
 *  \param [in] sid
 *         Service context ID.
 *
 *  \param [in] char_uuid
 *         Assigned UUID of this GATT Characteristic.
 *
 *  \param [in] cid
 *         Characteristic context ID where needed, else can be
 *         \ref GA_BRR_INST_DONTCARE.
 *
 *  \param [in] value
 *         Any value associated with this GATT Characteristic.
 *
 *  \param [in] nwr
 *         If Notification, Set nwr to \ref GA_TRUE. \n
 *         Else for Indication, Set nwr to \ref GA_FALSE.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_notify_characteristic
          (
              /* IN */ GA_BRR_DEVICE   * device,
              /* IN */ GA_BRR_SVC_INST sid,
              /* IN */ GA_BRR_UUID     char_uuid,
              /* IN */ GA_BRR_CHR_INST cid,
              /* IN */ GA_BRR_CHR_VAL  * value,
              /* IN */ UINT8           nwr
          );

/** \} */

/** \} */

/**
 * \defgroup ga_brr_client_api_defs Client
 * \{
 * \brief This section describes the Generic Audio Bearer APIs for Client.
 */

/**
 * \name Bearer Client APIs - Init
 * \{
 * \brief This section describes the Generic Audio Bearer Init APIs for Client.
 */

/*
 * Register a profile callback from GA and assign a profile ID for further
 * referencing.
 * Assign a profile ID or Profile ID gets assigned internally and comes
 * as Out?
 */
/**
 *  \brief Register a profile client.
 *
 *  \par Description:
 *       This function enables to Register a profile client module
 *       with the GA Bearer.
 *
 *  \param [in] id
 *         Module ID.
 *
 *  \param [in] cb
 *         Profile Callback.
 *
 *  \param [out] pid
 *         Profile context ID.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_register_profile
          (
              /* IN  */ UINT32 id,
              /* IN  */ GA_BRR_PROFILE_CB  cb,
              /* OUT */ GA_BRR_PRF_HANDLE * pid
          );

/** \} */

/**
 * \name Bearer Client APIs - De-Init
 * \{
 * \brief This section describes the Generic Audio Bearer De-Init APIs for
 * Client.
 */

/**
 *  \brief To Unregister a GA Profile with GA Bearer.
 *
 *  \par Description:
 *       This function enables to unregister a profile with GA Bearer.
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \return \ref GA_SUCCESS or an error code indicating reason for failure.
 */
GA_RESULT GA_brr_unregister_profile
          (
              /* IN */ GA_BRR_PRF_HANDLE pid
          );

/** \} */

/**
 * \name Bearer Client APIs - Setup
 * \{
 * \brief This section describes the Generic Audio Bearer Setup APIs
 * for Client.
 */

/*
 * Enhance the bearer transport if required by the profile or application - eATT
 * Should the needed MTU(or other associated things incase of eATT) also be
 * part of this interface? Else, we might need some other interface for that.
 */
/**
 *  \brief Update or Setup a new Transport.
 *
 *  \par Description:
 *       TODO: Need to revist for both Profile and Server roles.
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \param [in] type
 *         Type of Transport.
 *
 *  \param [in] enable
 *         State of Transport.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_setup_transport
          (
              /* IN */ GA_BRR_PRF_HANDLE pid,
              /* IN */ UINT8             type,
              /* IN */ UINT8             enable
          );

/*
 * Discover the service information from a profile instance for a service from
 * the peer device.
 */
/**
 *  \brief Discover a peer GATT Service.
 *
 *  \par Description:
 *       This function enables to discover a Peer GATT Service.
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \param [in] device
 *         Peer Device Connection Identifier.
 *
 *  \param [in] svc_info
 *         Contains the assigned UUID of this GATT Primary Service to be looked
 *         for in remote. Or, contains the Service Handle Range where Included
 *         services are to be looked for in remote.
 *
 *  \param [in] disc_type
 *         Type of Service discovery to be performed in the remote.
 *         \ref GA_BRR_PS_DISCOVERY or \ref GA_BRR_SS_DISCOVERY or
 *         \ref GA_BRR_IS_DISCOVERY.
 *
 *  \param [in] context
 *         Any(Optional) Upper Layer provided context for Book-keeping.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_discover_service
          (
              /* IN */ GA_BRR_PRF_HANDLE pid,
              /* IN */ GA_BRR_DEVICE     * device,
              /* IN */ GA_BRR_SVC_INFO   * svc_info,
              /* IN */ UCHAR             disc_type,
              /* IN */ void              * context
          );

/*
 * Discover the primary service information from a profile instance for a
 * service from the peer device.
 */
/**
 *  \brief Discover a peer GATT Primary Service.
 *
 *  \par Description:
 *       This function enables to discover a Peer GATT Service with a given
 *       UUID present as a Primary Service in the Peer GATT DB.
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \param [in] device
 *         Peer Device Connection Identifier.
 *
 *  \param [in] svc_info
 *         Contains the assigned UUID of this GATT Primary Service to be looked
 *         for in remote.
 *
 *  \param [in] context
 *         Any(Optional) Upper Layer provided context for Book-keeping.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
#define GA_brr_discover_ps(pid, device, svc_info, context)\
        GA_brr_discover_service\
        (\
            (pid),\
            (device),\
            (svc_info),\
            GA_BRR_PS_DISCOVERY,\
            (context)\
        )

/*
 * Discover the included service information from a profile instance for a
 * service range from the peer device.
 */
/**
 *  \brief Discover a peer GATT Included Service.
 *
 *  \par Description:
 *       This function enables to discover a Peer GATT Services in a given
 *       Service range present as Included Service in the Peer GATT DB.
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \param [in] device
 *         Peer Device Connection Identifier.
 *
 *  \param [in] svc_info
 *         Contains the Service Handle Range where Included services are to
 *         be looked for in remote.
 *
 *  \param [in] context
 *         Any(Optional) Upper Layer provided context for Book-keeping.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
#define GA_brr_discover_is(pid, device, svc_info, context)\
        GA_brr_discover_service\
        (\
            (pid),\
            (device),\
            (svc_info),\
            GA_BRR_IS_DISCOVERY,\
            (context)\
        )

/*
 * Discover the secondary service information from a profile instance for a
 * service from the peer device.
 */
/**
 *  \brief Discover a peer GATT Secondary Service.
 *
 *  \par Description:
 *       This function enables to discover a Peer GATT Service with a given
 *       UUID present as a Secondary Service in the Peer GATT DB.
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \param [in] device
 *         Peer Device Connection Identifier.
 *
 *  \param [in] svc_info
 *         Contains the assigned UUID of this GATT Secondary Service to be looked
 *         for in remote.
 *
 *  \param [in] context
 *         Any(Optional) Upper Layer provided context for Book-keeping.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
#define GA_brr_discover_ss(pid, device, svc_info, context)\
        GA_brr_discover_service\
        (\
            (pid),\
            (device),\
            (svc_info),\
            GA_BRR_SS_DISCOVERY,\
            (context)\
        )

/*
 * Load the service information (characteristics and descriptors
 * of the specified service) and have it in the datastructure for
 * lookup during read/write.
 * - Should this have an associated service id?
 */
/**
 *  \brief Discover composition of a given peer Service.
 *
 *  \par Description:
 *       This function enables to discover constituents of a given
 *       peer service.
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \param [in] device
 *         Peer Device Connection Identifier.
 *
 *  \param [in] service
 *         Service Related Information.
 *
 *  \param [in] context
 *         Any(Optional) Upper Layer provided context for Book-keeping.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_get_service_composition
          (
              /* IN */ GA_BRR_PRF_HANDLE   pid,
              /* IN */ GA_BRR_DEVICE     * device,
              /* IN */ GA_BRR_SVC_INFO   * service,
              /* IN */ void              * context
          );

/*
 * Load the characteristic information (descriptors
 * of the specified characteristic) and have it in the datastructure for
 * lookup during read/write.
 * - Should this have an associated characterisitc id?
 */
/**
 *  \brief Discover composition of a given peer Characteristic.
 *
 *  \par Description:
 *       This function enables to discover constituents of a given
 *       peer characteristic.
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \param [in] device
 *         Peer Device Connection Identifier.
 *
 *  \param [in] characteristic
 *         Characteristic Related Information.
 *
 *  \param [in] context
 *         Any(Optional) Upper Layer provided context for Book-keeping.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_get_characteristic_composition
          (
              /* IN */ GA_BRR_PRF_HANDLE   pid,
              /* IN */ GA_BRR_DEVICE     * device,
              /* IN */ GA_BRR_CHAR_RANGE * characteristic,
              /* IN */ void              * context
          );

/** \} */

/**
 * \name Bearer Client APIs - Write
 * \{
 * \brief This section describes the Generic Audio Bearer Write APIs for Client.
 */

/* Write value to the specified characteristic UUID for the peer device */
/*
 * NOTE:
 * - Should this Interface also handle Prepare Write/ Reliable Write etc?
 * - Also, Will this interface need a Char Instance associated with it
 *   esp in case of multiple instance of same char?
 */
/**
 *  \brief Write the Characterisitc Value.
 *
 *  \par Description:
 *       This function enables to Write value of a Peer GATT Characteristic.
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \param [in] device
 *         Peer Device Connection Identifier.
 *
 *  \param [in] characteristic
 *         Characteristic Handle to be Read.
 *
 *  \param [in] value
 *         Value to be written to the Characteristic.
 *
 *  \param [in] wwr
 *         Flag to inform if Write Without Response or otherwise.
 *
 *  \param [in] context
 *         Any(Optional) Upper Layer provided context for Book-keeping.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_write_characteristic
          (
              /* IN */ GA_BRR_PRF_HANDLE pid,
              /* IN */ GA_BRR_DEVICE     * device,
              /* IN */ GA_BRR_CHR_HANDLE characteristic,
              /* IN */ GA_BRR_CHR_VAL    * value,
              /* IN */ UINT8             wwr,
              /* IN */ void              * context
          );

/** \} */

/**
 * \name Bearer Client APIs - Read
 * \{
 * \brief This section describes the Generic Audio Bearer Read APIs for Client.
 */

/* Read value of the specified characteristic UUID for the peer device */
/*
 * NOTE:
 * - Should this Interface take care of handling Read Long/Blob?
 *   Else, it might need an Offset too.
 * - Also, Will this interface need a Char Instance associated with it
 *   esp in case of multiple instance of same char?
 */
/**
 *  \brief Read the Characterisitc Value.
 *
 *  \par Description:
 *       This function enables to read value of a Peer GATT Characteristic.
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \param [in] device
 *         Peer Device Connection Identifier.
 *
 *  \param [in] characteristic
 *         Characteristic Handle to be Read.
 *
 *  \param [in] context
 *         Any(Optional) Upper Layer provided context for Book-keeping.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_read_characteristic
          (
              /* IN */ GA_BRR_PRF_HANDLE pid,
              /* IN */ GA_BRR_DEVICE     * device,
              /* IN */ GA_BRR_CHR_HANDLE characteristic,
              /* IN */ void              * context
          );

/** \} */

/**
 * \name Bearer Client APIs - Setup
 * \{
 * \brief This section describes the Generic Audio Bearer Setup APIs for
 * Client.
 */

/*
 * Configure notification/Indication enable/disable specified characteristic UUID for
 * the peer device.
 * NOTE:
 * - Either the state can be 0, 1, 2 or it can be TRUE/FALSE.
 *   If its the latter, then internally it should detect if its IND/NTF
 *   based on each character.
 * - Also, Will this interface need a Char Instance associated with it
 *   esp in case of multiple instance of same char?
 */

/**
 *  \brief Configure Notification for a Characterisitic Descriptor Handle.
 *
 *  \par Description:
 *       This routine configures Notification for the Characteristic Descriptor
 *       Handle on the Peer device.
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \param [in] device
 *         Peer Device Connection Identifier.
 *
 *  \param [in] desc
 *         Characteristic Descriptor Handle.
 *
 *  \param [in] state
 *         \ref GA_TRUE : Enable Notification. \n
 *         \ref GA_FALSE : Disable Notification.
 *
 *  \param [in] context
 *         Any(Optional) Upper Layer provided context for Book-keeping.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_config_notification
          (
              /* IN */ GA_BRR_PRF_HANDLE pid,
              /* IN */ GA_BRR_DEVICE     * device,
              /* IN */ GA_BRR_CHR_DESC_HANDLE desc,
              /* IN */ UINT8             state,
              /* IN */ void              * context
          );

/**
 *  \brief Configure Indication for a Characterisitic Descriptor Handle.
 *
 *  \par Description:
 *       This routine configures Indication for the Characteristic Descriptor
 *       Handle on the Peer device.
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \param [in] device
 *         Peer Device Connection Identifier.
 *
 *  \param [in] desc
 *         Characteristic Descriptor Handle.
 *
 *  \param [in] state
 *         \ref GA_TRUE : Enable Indication. \n
 *         \ref GA_FALSE : Disable Indication.
 *
 *  \param [in] context
 *         Any(Optional) Upper Layer provided context for Book-keeping.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_config_indication
          (
              /* IN */ GA_BRR_PRF_HANDLE pid,
              /* IN */ GA_BRR_DEVICE     * device,
              /* IN */ GA_BRR_CHR_DESC_HANDLE desc,
              /* IN */ UINT8             state,
              /* IN */ void              * context
          );

/** \} */
/** \} */

/**
 * \addtogroup ga_brr_common_api_defs
 * \{
 */

/**
 * \name Bearer Common APIs - Setup
 * \{
 * \brief This section describes the Generic Audio Bearer Common Setup APIs.
 */

/**
 *  \brief Dispatches the given event to respective profile callback
 *
 *  \par Description:
 *       This routine dispatches the said event with parameters to the
 *       respective profile callback.
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \param [in] device
 *         Device associated with the event.
 *
 *  \param [in] event_params
 *         Params associated with the event that identifies type,
 *         status, data and datalen.
 *
 *  \param [in] context
 *         Any(Optional) Upper Layer provided context for Book-keeping.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_dispatch_event
          (
              /* IN */ GA_BRR_PRF_HANDLE     pid,
              /* IN */ GA_BRR_DEVICE       * device,
              /* IN */ GA_BRR_EVENT_PARAMS * event_params,
              /* IN */ void                * context
          );

/** \} */
/** \} */

/**
 * \defgroup ga_brr_bc_src_api_defs Broadcast Source
 * \{
 * \brief This section describes the Generic Audio Bearer APIs
 * for Broadcast Source.
 */

/**
 *  \brief Configure Extended/Periodic Advertising.
 *
 *  \par Description:
 *       This routine enables/disables Extended/Periodic Advertising.
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \param [in] type
 *         Use \ref GA_BRR_ADV_TYPE_EA for Extended Advertising. \n
 *         Use \ref GA_BRR_ADV_TYPE_PA for Periodic Advertising.
 *
 *  \param [in] handle
 *         Advertising Handle.
 *
 *  \param [in] enable
 *         \ref GA_TRUE : Enable Advertising. \n
 *         \ref GA_FALSE : Disable Advertising.
 *
 *  \param [in] data
 *         Can be NULL or valid parameters for Set Extended/Periodic
 *         Advertising data.
 *
 *  \param [in] datalen
 *         Can be 0 or Valid length for Set Extended/Periodic
 *         Advertising data.
 *
 *  Disable EA, \n
 *  type as \ref GA_BRR_ADV_TYPE_EA, enable as \ref GA_FALSE, data as NULL. \n
 *  Disable PA, \n
 *  type as \ref GA_BRR_ADV_TYPE_PA, enable as \ref GA_FALSE, data as NULL. \n
 *  Expected Event: Refer \ref GA_BRR_CONFIGURE_ADV_CNF
 *
 *  Enable EA, \n
 *  type as \ref GA_BRR_ADV_TYPE_EA, enable as \ref GA_TRUE, data as Valid. \n
 *     - Set Extended Advertising Params with params configured during
 *       calling of \ref ga_brr_set_default_broadcast_settings() or
 *       \ref ga_brr_config_eadv_params_pl() \n
 *     - Set Extended Advertising Data with data as Valid. \n
 *     - Set Extended Advertising Enable. \n
 *     .
 *  Expected Event: Refer \ref GA_BRR_CONFIGURE_ADV_CNF
 *
 *  Enable PA, \n
 *  type as \ref GA_BRR_ADV_TYPE_PA, enable as \ref GA_TRUE, data as Valid. \n
 *     - Set Periodic Advertising Parameters with params configured during
 *       calling of \ref ga_brr_set_default_broadcast_settings() or
 *       \ref ga_brr_config_padv_params_pl() \n
 *     - Set Periodic Advertising Data with data as Valid. \n
 *     - Set Random Address, if address was set to Random via
 *       \ref ga_brr_set_default_broadcast_settings() or
 *       \ref ga_brr_config_padv_params_pl() \n
 *     - Set Periodic Advertising Enable. \n
 *     .
 *  Expected Event: Refer \ref GA_BRR_CONFIGURE_ADV_CNF
 *
 *  Reconfigure EA, \n
 *  type as \ref GA_BRR_ADV_TYPE_EA, enable as \ref GA_FALSE, data as Valid. \n
 *     - Set Extended Advertising Data with data as Valid. \n
 *     .
 *  Expected Event: Refer \ref GA_BRR_RECONFIGURE_ADV_CNF
 *
 *  Reconfigure PA, \n
 *  type as \ref GA_BRR_ADV_TYPE_PA, enable as \ref GA_FALSE, data as Valid. \n
 *     - Set Periodic Advertising Data with data as Valid. \n
 *     .
 *  Expected Event: Refer \ref GA_BRR_RECONFIGURE_ADV_CNF
 *
 *  \param [in] context
 *         Any(Optional) Upper Layer provided context for Book-keeping.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_configure_adv
          (
              GA_BRR_PRF_HANDLE pid,
              UINT8   type,
              UINT8   handle,
              UINT8   enable,
              UCHAR * data,
              UINT8   datalen,
              void  * context
          );

/**
 *  \brief Configure BIG
 *
 *  \par Description:
 *       This routine Configures the BLE BIG for broadcast.
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \param [in] handle
 *         Valid handle.
 *
 *  \param [in] adv_handle
 *         Valid Adv Handle. \n
 *         NULL for Terminate BIG.
 *
 *  \param [in] param
 *         Valid params for Create BIG. \n
 *         NULL for Terminate BIG.
 *
 *  \param [in] context
 *         Any(Optional) Upper Layer provided context for Book-keeping.
 *
 *  Create BIG, \n
 *  handle: Valid, adv_handle: Valid, param: Valid \n
 *     - Create BIG \n
 *     .
 *  Expected Event: Refer \ref GA_BRR_CONFIGURE_BROADCAST_CNF
 *
 *  Terminate BIG, \n
 *  handle: Valid, adv_handle: NULL, param: NULL \n
 *     - Terminate BIG \n
 *     .
 *  Expected Event: Refer \ref GA_BRR_CONFIGURE_BROADCAST_CNF
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_configure_broadcast
          (
              GA_BRR_PRF_HANDLE pid,
              UCHAR   handle,
              UCHAR   adv_handle,
              GA_BRR_BCAST_PARAM * param,
              void  * context
          );

/** \} */

/**
 * \defgroup ga_brr_bc_snk_api_defs Broadcast Sink
 * \{
 * \brief This section describes the Generic Audio Bearer APIs
 * for Broadcast Sink.
 */

/**
 *  \brief Configure Extended Scanning.
 *
 *  \par Description:
 *       This routine enables/disables Extended Scanning.
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \param [in] enable
 *         \ref GA_TRUE : Enable Extended Scanning. \n
 *         \ref GA_FALSE : Disable Extended Scanning.
 *
 *  \param [in] context
 *         Any(Optional) Upper Layer provided context for Book-keeping.
 *
 *  Enable EA Scanning, \n
 *  enable as \ref GA_TRUE, \n
 *     - Set extended scan parameters with params configured during
 *       calling of \ref ga_brr_set_default_broadcast_settings() or
 *       \ref ga_brr_config_escan_params_pl() \n
 *     .
 *  Expected Event: Refer \ref GA_BRR_CONFIGURE_SCAN_CNF \n
 *                  If \ref GA_SUCCESS, \n
 *                  Refer \ref GA_BRR_EXTENDED_ADV_REPORT_IND
 *
 *  Disable PA Scanning, \n
 *  enable as \ref GA_FALSE, \n
 *     - Set extended scan enable \n
 *     .
 *  Expected Event: Refer \ref GA_BRR_CONFIGURE_SCAN_CNF \n
 *                  If \ref GA_SUCCESS, \n
 *                  Refer \ref GA_BRR_PERIODIC_ADV_REPORT_IND
 *
 * On Scan Timeout, \n
 * Expected Event: \ref GA_BRR_CONFIGURE_SCAN_CNF
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_configure_scan
          (
              GA_BRR_PRF_HANDLE   pid,
              UCHAR               enable,
              void              * context
          );

/**
 *  \brief Configure scan syncing with Periodic Adv
 *
 *  \par Description:
 *       This routine Configures the BLE scan syncing with PA
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \param [in] handle
 *         Valid UINT8 Advertising SID for Periodic Adv Create Sync received as
 *         part of \ref GA_BRR_EXTENDED_ADV_REPORT_IND. \n
 *         Valid UINT16 handle for Periodic Adv Terminate Sync received as part
 *         of \ref GA_BRR_PERIODIC_ADV_REPORT_IND.
 *
 *  \param [in] device
 *         Valid Device for Periodic Adv Create Sync. \n
 *         NULL for Periodic Adv Terminate Sync.
 *
 *  \param [in] context
 *         Any(Optional) Upper Layer provided context for Book-keeping.
 *
 *  PA Create Sync,  \n
 *  handle: UINT8, device: Valid \n
 *     - Periodic Adv Create Sync, with params configured during
 *       calling of \ref ga_brr_set_default_broadcast_settings() or
 *       \ref ga_brr_config_psync_params_pl() \n
 *     .
 *  Expected Event: Refer \ref GA_BRR_CONFIGURE_SYNC_CNF
 *
 *  PA Terminate Sync, \n
 *  handle: UINT16, device: NULL \n
 *     - Periodic Adv Terminate Sync \n
 *     .
 *  Expected Event: Refer \ref GA_BRR_CONFIGURE_SYNC_CNF
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_configure_sync
          (
              GA_BRR_PRF_HANDLE pid,
              UINT16            handle,
              GA_BRR_DEVICE   * device,
              void            * context
          );


/**
 *  \brief Cancel the ongoing PA Create Sync
 *
 *  \par Description:
 *       This routine cancels the ongoing PA Sync
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \param [in] context
 *         Any(Optional) Upper Layer provided context for Book-keeping.
 *     .
 *  Expected Event: Refer \ref GA_BRR_CONFIGURE_SYNC_CNF
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_configure_sync_cancel
          (
              GA_BRR_PRF_HANDLE pid,
              void * context
          );

/**
 *  \brief Configure BIG sync
 *
 *  \par Description:
 *       This routine Configures the BLE BIG Sync for broadcast.
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \param [in] handle
 *         Valid handle.
 *
 *  \param [in] sync_handle
 *         Valid Sync Handle. \n
 *         NULL for Terminate BIG.
 *
 *  \param [in] param
 *         Valid params for BIG Create Sync. \n
 *         NULL for BIG Terminate Sync.
 *
 *  \param [in] context
 *         Any(Optional) Upper Layer provided context for Book-keeping.
 *
 *  BIG Create Sync, \n
 *  handle: Valid, sync_handle: Valid, param: Valid \n
 *     - BIG Create Sync \n
 *     .
 *  Expected Event: Refer \ref GA_BRR_CONFIGURE_BROADCAST_SYNC_CNF
 *
 *  BIG Terminate Sync, \n
 *  handle: Valid, adv_handle: NULL, param: NULL \n
 *     - BIG Terminate Sync \n
 *     .
 *  Expected Event: Refer \ref GA_BRR_CONFIGURE_BROADCAST_SYNC_CNF
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_configure_broadcast_sync
          (
              GA_BRR_PRF_HANDLE pid,
              UCHAR   handle,
              UINT16  sync_handle,
              GA_BRR_BCAST_SYNC_PARAM * param,
              void  * context
          );

/** \} */

/* TODO: Verify Group name and description */
/**
 * \defgroup ga_brr_crypto_api_defs Crypto
 * \{
 * \brief This section describes the Generic Audio Bearer APIs
 * for Cryptographic and BLE RPA Operations.
 */

/**
 *  \brief Create/Verify Resolvable Private Address
 *
 *  \par Description:
 *       This routine triggers the Resolvable Private Address
 *       operation at the bearer stack.
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \param [in] addr
 *         Valid Address for Verify Resolvable Private Address. \n
 *         NULL for Create Resolvable Private Address.
 *
 *  \param [in] irk
 *         Valid Identity Resolving Key.
 *
 *  \param [in] context
 *         Any(Optional) Upper Layer provided context for Book-keeping.
 *
 *  Create RPA, \n
 *  addr: Valid, irk: Valid \n
 *     - Create RPA \n
 *     .
 *  Expected Event: Refer \ref GA_BRR_RPA_CREATE_COMPLETE
 *
 *  Verify RPA, \n
 *  addr: NULL, irk: Valid \n
 *     - Verify RPA \n
 *     .
 *  Expected Event: Refer \ref GA_BRR_RPA_VERIFY_COMPLETE
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_rpa_operate
          (
              /* IN */ GA_BRR_PRF_HANDLE     pid,
              /* IN */ UCHAR               * addr,
              /* IN */ UCHAR               * irk,
              /* IN */ void                * context
          );

/**
 * \name Bearer Server APIs - BLE RPA and Cryptographic Operation
 * \{
 */

/**
 *  \brief Create Resolvable Private Address
 *
 *  \par Description:
 *       This routine triggers the Resolvable Private Address
 *       operation at the bearer stack.
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \param [in] irk
 *         Valid Identity Resolving Key.
 *
 *  \param [in] context
 *         Any(Optional) Upper Layer provided context for Book-keeping.
 *
 *  Create RPA, \n
 *  addr: Valid, irk: Valid \n
 *     - Create RPA \n
 *     .
 *  Expected Event: Refer \ref GA_BRR_RPA_CREATE_COMPLETE
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */

#define GA_brr_rpa_create(pid, irk, context)\
        GA_brr_rpa_operate\
        (\
            (pid),\
            NULL,\
            (irk),\
            (context)\
        )
/** \} */

/**
 * \name Bearer Client APIs - BLE RPA and Cryptographic Operation
 * \{
 */

/**
 *  \brief Verify Resolvable Private Address
 *
 *  \par Description:
 *       This routine triggers the Resolvable Private Address
 *       operation at the bearer stack.
 *
 *  \param [in] pid
 *         Profile context ID.
 *
 *  \param [in] addr
 *         Valid Address for Verify Resolvable Private Address.
 *
 *  \param [in] irk
 *         Valid Identity Resolving Key.
 *
 *  \param [in] context
 *         Any(Optional) Upper Layer provided context for Book-keeping.
 *
 *  Verify RPA, \n
 *  addr: NULL, irk: Valid \n
 *     - Verify RPA \n
 *     .
 *  Expected Event: Refer \ref GA_BRR_RPA_VERIFY_COMPLETE
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */

#define GA_brr_rpa_verify(pid, addr, irk, context)\
        GA_brr_rpa_operate\
        (\
            (pid),\
            (addr),\
            (irk),\
            (context)\
        )
/** \} */

/**
 *  \brief Triggers the Cryptographic operation
 *
 *  \par Description:
 *       This routine triggers the Cryptographic operation for the
 *       specified operation on the given information.
 *
 *  \param [in] op
 *         Refer \ref GA_BRR_CRYPTO_AESCMAC
 *
 *  \param [in] info
 *         Valid info, Refer \ref GA_BRR_AESCMAC_INFO
 *
 *  \param [in] cb
 *         Callback for event after completion.
 *
 *  \param [in] context
 *         Any(Optional) Upper Layer provided context for Book-keeping.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_brr_crypto
          (
              /* IN */ UCHAR             op,
              /* IN */ void            * info,
              /* IN */ GA_BRR_CRYPTO_CB  cb,
              /* IN */ void            * context
          );

/** \} */
/** \} */

/** \} */
/** \} */

#endif /* _H_GA_BEARER_API_ */

