
/**
 *  \file GA_error.h
 *
 *  \brief This file contains all the error codes defined for GA profiles.
 */

/*
 *  Copyright (C) 2020. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_GA_ERROR_
#define _H_GA_ERROR_

/* --------------------------------------------- Header File Inclusion */

/* --------------------------------------------- Global Definitions */
/**
 * \addtogroup bt_ga_core
 * \{
 */

/**
 * \addtogroup ga_cap_module
 * \{
 */

/**
 * \addtogroup ga_common_module
 * \{
 */

/**
 * \addtogroup ga_common_defines
 * \{
 */

/**
 * \addtogroup ga_common_error_code_def
 * \{
 */

/**
 * \addtogroup ga_common_error_code
 * \{
 */

/**
 * \name Common - OSAL Error Codes
 * \{
 * \brief Set of common OSAL error codes across all profiles.
 */

/** Error Code for MUTEX Initialization Failure */
#define GA_MUTEX_INIT_FAILED                       0x0001
/** Error Code for Conditional Variable Initialization Failure */
#define GA_COND_INIT_FAILED                        0x0002
/** Error Code for MUTEX Lock Failure */
#define GA_MUTEX_LOCK_FAILED                       0x0003
/** Error Code for MUTEX Unlock Failure */
#define GA_MUTEX_UNLOCK_FAILED                     0x0004
/** Error Code for Memory Allocation Failure */
#define GA_MEMORY_ALLOCATION_FAILED                0x0005
/** \} */
/** \} */

/**
 * \addtogroup ga_common_error_group
 * \{
 */

/**
 * \name Profile Error ID
 * \{
 * \brief This section describes GA Profile Module Error ID.
 */

 /** Module Error Code ID - Common Audio Profile */
#define GA_CAP_ERR_ID                                   0x0100U
 /** Module Error Code ID - Basic Audio Profile */
#define GA_BAP_ERR_ID                                   0x0200U
/** Module Error Code ID - Volume Control Profile */
#define GA_VCP_ERR_ID                                   0x0300U
/** Module Error Code ID - Microphone Control Profile */
#define GA_MICP_ERR_ID                                  0x0400U
/** Module Error Code ID - Coordinated Set Identification Profile */
#define GA_CSIP_ERR_ID                                  0x0500U
/** Module Error Code ID - Call Control Profile */
#define GA_CCP_ERR_ID                                   0x0600U
/** Module Error Code ID - Media Control Profile */
#define GA_MCP_ERR_ID                                   0x0700U
/** Module Error Code ID - Object Transfer Profile */
#define GA_OTP_ERR_ID                                   0x0800U
/** Module Error Code ID - Hearing Aid Profile */
#define GA_HAP_ERR_ID                                   0x0900U
/** Module Error Code ID - Telephony & Media Audio Profile */
#define GA_TMAP_ERR_ID                                  0x0A00U
/** Module Error Code ID - Broadcast Audio Scann Service & Profile */
#define GA_BASS_ERR_ID                                  0x0B00U
/** Module Error Code ID - GA BRR PL */
#define GA_BRR_ERR_ID                                   0x0C00U
/** \} */
/** \} */
/** \} */

/** \} */
/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_bearer_module
 * \{
 */

/**
 * \addtogroup ga_brr_defines
 * \{
 */

/**
 * \addtogroup ga_brr_error_code
 * \{
 */

/**
 * \name Bearer - OSAL Error Codes
 * \{
 * \brief This section lists OSAL Error Codes for Bearer.
 */

/** Bearer Error Code ID - MUTEX Initialization Failure */
#define BRR_MUTEX_INIT_FAILED                    \
        (GA_BRR_ERR_ID | GA_MUTEX_INIT_FAILED)
/** Bearer Error Code ID - Conditional Variable Initialization Failure */
#define BRR_COND_INIT_FAILED                     \
        (GA_BRR_ERR_ID | GA_COND_INIT_FAILED)
/** Bearer Error Code ID - MUTEX Lock Failure */
#define BRR_MUTEX_LOCK_FAILED                    \
        (GA_BRR_ERR_ID | GA_MUTEX_LOCK_FAILED)
/** Bearer Error Code ID - MUTEX Unlock Failure */
#define BRR_MUTEX_UNLOCK_FAILED                  \
        (GA_BRR_ERR_ID | GA_MUTEX_UNLOCK_FAILED)
/** Bearer Error Code ID - Memory Allocation Failure */
#define BRR_MEMORY_ALLOCATION_FAILED             \
        (GA_BRR_ERR_ID | GA_MEMORY_ALLOCATION_FAILED)

/** \} */

/**
 * \name BRR - Implementation Error Codes
 * \{
 * \brief This section lists Implementation Error Codes for BRR.
 */

 /** Bearer Error Code ID - Invalid State to perform the operation */
#define GA_BRR_CHAR_CONFIG_DISABLED                     (GA_BRR_ERR_ID | 0x0011U)

/** \} */
/** \} */
/** \} */
/** \} */

/**
 * \addtogroup bt_ga_core
 * \{
 */

/**
 * \addtogroup ga_cap_module
 * \{
 */

/**
 * \addtogroup ga_cas_module
 * \{
 */

/**
 * \addtogroup ga_cas_defines
 * \{
 */

/**
 * \addtogroup ga_cas_error_code
 * \{
 */


/**
 * \name CAS - OSAL Error Codes
 * \{
 * \brief This section lists OSAL Error Codes for CAS.
 */

/** Common Audio Profile Error Code ID - MUTEX Initialization Failure */
#define CAP_MUTEX_INIT_FAILED                    \
        (GA_CAP_ERR_ID | GA_MUTEX_INIT_FAILED)
/**
 * Common Audio Profile Error Code ID - Conditional Variable Initialization
 * Failure
 */
#define CAP_COND_INIT_FAILED                     \
        (GA_CAP_ERR_ID | GA_COND_INIT_FAILED)
/** Common Audio Profile Error Code ID - MUTEX Lock Failure */
#define CAP_MUTEX_LOCK_FAILED                    \
        (GA_CAP_ERR_ID | GA_MUTEX_LOCK_FAILED)
/** Common Audio Profile Error Code ID - MUTEX Unlock Failure */
#define CAP_MUTEX_UNLOCK_FAILED                  \
        (GA_CAP_ERR_ID | GA_MUTEX_UNLOCK_FAILED)
/** Common Audio Profile Error Code ID - Memory Allocation Failure */
#define CAP_MEMORY_ALLOCATION_FAILED             \
        (GA_CAP_ERR_ID | GA_MEMORY_ALLOCATION_FAILED)

/** \} */

/**
 * \name CAS - Implementation Error Codes
 * \{
 * \brief This section lists Implementation Error Codes for CAS.
 */

/** Common Audio Profile Error Code ID - Invalid State to perform the operation */
#define GA_CAP_INVALID_STATE                            (GA_CAP_ERR_ID | 0x0011U)
/** Common Audio Profile Error Code ID - Invalid Parameters provided */
#define GA_CAP_INVALID_PARAMS                           (GA_CAP_ERR_ID | 0x0012U)
/** Common Audio Profile Error Code ID - New Context allocation failed */
#define GA_CAP_CNTX_ALLOC_FAILED                        (GA_CAP_ERR_ID | 0x0013U)
/** Common Audio Profile Error Code ID - Another operation already in progress */
#define GA_CAP_IN_BUSY_STATE                            (GA_CAP_ERR_ID | 0x0014U)
/** Common Audio Profile Error Code ID - Invalid Handle to perform the operation */
#define GA_CAP_INVALID_HANDLE                           (GA_CAP_ERR_ID | 0x0015U)
/** Common Audio Profile Error Code ID - CSIP Member Lock Timeout status */
#define GA_CAP_MEMBER_LOCK_TIMEOUT                      (GA_CAP_ERR_ID | 0x0020U)
/** Common Audio Profile Error Code ID - CSIP Member Lock Timeout status */
#define GA_CAP_ERROR_OUTOFBOUNDS                        (GA_CAP_ERR_ID | 0x0021U)

/** \} */
/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_bap_module
 * \{
 */

/**
 * \addtogroup ga_bap_common_module
 * \{
 */

/**
 * \addtogroup ga_bap_common_defines
 * \{
 */

/**
 * \addtogroup ga_bap_common_error_code
 * \{
 */

/**
 * \name BAP - OSAL Error Codes
 * \{
 * \brief This section lists OSAL Error Codes for BAP.
 */

/** Basic Audio Profile Error Code ID - MUTEX Initialization Failure */
#define BAP_MUTEX_INIT_FAILED                    \
        (GA_BAP_ERR_ID | GA_MUTEX_INIT_FAILED)
/**
 * Basic Audio Profile Error Code ID - Conditional Variable Initialization
 * Failure
 */
#define BAP_COND_INIT_FAILED                     \
        (GA_BAP_ERR_ID | GA_COND_INIT_FAILED)
/** Basic Audio Profile Error Code ID - MUTEX Lock Failure */
#define BAP_MUTEX_LOCK_FAILED                    \
        (GA_BAP_ERR_ID | GA_MUTEX_LOCK_FAILED)
/** Basic Audio Profile Error Code ID - MUTEX Unlock Failure */
#define BAP_MUTEX_UNLOCK_FAILED                  \
        (GA_BAP_ERR_ID | GA_MUTEX_UNLOCK_FAILED)
/** Basic Audio Profile Error Code ID - Memory Allocation Failure */
#define BAP_MEMORY_ALLOCATION_FAILED             \
        (GA_BAP_ERR_ID | GA_MEMORY_ALLOCATION_FAILED)

/** \} */

/**
 * \name BAP - Implementation Error Codes
 * \{
 * \brief This section lists Implementation Error Codes for BAP.
 */

/** Basic Audio Profile Error Code ID - Invalid State to perform the operation */
#define GA_BAP_INVALID_STATE                            (GA_BAP_ERR_ID | 0x0011U)
/** Basic Audio Profile Error Code ID - Invalid Parameters provided */
#define GA_BAP_INVALID_PARAMS                           (GA_BAP_ERR_ID | 0x0012U)
/** Basic Audio Profile Error Code ID - New Context allocation failed */
#define GA_BAP_CNTX_ALLOC_FAILED                        (GA_BAP_ERR_ID | 0x0013U)
/** Basic Audio Profile Error Code ID - Another operation already in progress */
#define GA_BAP_IN_BUSY_STATE                            (GA_BAP_ERR_ID | 0x0014U)
/** Basic Audio Profile Error Code ID - Invalid Handle to perform the operation */
#define GA_BAP_INVALID_HANDLE                           (GA_BAP_ERR_ID | 0x0015U)

/** \} */
/** \} */
/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_vcp_module
 * \{
 */

/**
 * \addtogroup ga_vcp_defines
 * \{
 */

/**
 * \addtogroup ga_vcp_error_code
 * \{
 */

/**
 * \name VCP - OSAL Error Codes
 * \{
 * \brief This section lists OSAL Error Codes for VCP.
 */

/** Volume Control Profile Error Code ID - MUTEX Initialization Failure */
#define VCP_MUTEX_INIT_FAILED                    \
        (GA_VCP_ERR_ID | GA_MUTEX_INIT_FAILED)
/**
 * Volume Control Profile Error Code ID - Conditional Variable Initialization
 * Failure
 */
#define VCP_COND_INIT_FAILED                     \
        (GA_VCP_ERR_ID | GA_COND_INIT_FAILED)
/** Volume Control Profile Error Code ID - MUTEX Lock Failure */
#define VCP_MUTEX_LOCK_FAILED                    \
        (GA_VCP_ERR_ID | GA_MUTEX_LOCK_FAILED)
/** Volume Control Profile Error Code ID - MUTEX Unlock Failure */
#define VCP_MUTEX_UNLOCK_FAILED                  \
        (GA_VCP_ERR_ID | GA_MUTEX_UNLOCK_FAILED)
/** Volume Control Profile Error Code ID - Memory Allocation Failure */
#define VCP_MEMORY_ALLOCATION_FAILED             \
        (GA_VCP_ERR_ID | GA_MEMORY_ALLOCATION_FAILED)

/** \} */

/**
 * \name VCP - Implementation Error Codes
 * \{
 * \brief This section lists Implementation Error Codes for VCP.
 */

/** Volume Control Profile Error Code ID - Invalid State to perform the operation */
#define GA_VCP_INVALID_STATE                            (GA_VCP_ERR_ID | 0x0011U)
/** Volume Control Profile Error Code ID - Invalid Parameters provided */
#define GA_VCP_INVALID_PARAMS                           (GA_VCP_ERR_ID | 0x0012U)
/** Volume Control Profile Error Code ID - New Context allocation failed */
#define GA_VCP_CNTX_ALLOC_FAILED                        (GA_VCP_ERR_ID | 0x0013U)
/** Volume Control Profile Error Code ID - Another operation already in progress */
#define GA_VCP_IN_BUSY_STATE                            (GA_VCP_ERR_ID | 0x0014U)
/** Volume Control Profile Error Code ID - Invalid Handle to perform the operation */
#define GA_VCP_INVALID_HANDLE                           (GA_VCP_ERR_ID | 0x0015U)
/**
 * Volume Control Profile Error Code ID - Operation Not Supported
 * Property not set for this Char by the remote.
 */
#define GA_VCP_OPERATION_NOT_SUPPORTED_BY_REMOTE_DEVICE (GA_VCP_ERR_ID | 0x0016U)
/**
 * Volume Control Profile Error Code ID - Service not registered by Local
 * Server.
 */
#define GA_VCP_SERVICE_ID_NOT_FOUND                     (GA_VCP_ERR_ID | 0x0017U)
/**
 * Volume Control Profile Error Code ID - Unknown Service Type other than
 * VCS, VOCS, AICS.
 */
#define GA_VCP_INVALID_SERVICE_TYPE                     (GA_VCP_ERR_ID | 0x0018U)

/** \} */
/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_micp_module
 * \{
 */

/**
 * \addtogroup ga_micp_defines
 * \{
 */

/**
 * \addtogroup ga_micp_error_code
 * \{
 */

/**
 * \name MICP - OSAL Error Codes
 * \{
 * \brief This section lists OSAL Error Codes for MICP.
 */

/** Microphone Control Profile Error Code ID - MUTEX Initialization Failure */
#define MICP_MUTEX_INIT_FAILED                    \
        (GA_MICP_ERR_ID | GA_MUTEX_INIT_FAILED)
/**
 * Microphone Control Profile Error Code ID - Conditional Variable
 * Initialization Failure
 */
#define MICP_COND_INIT_FAILED                     \
        (GA_MICP_ERR_ID | GA_COND_INIT_FAILED)
/** Microphone Control Profile Error Code ID - MUTEX Lock Failure */
#define MICP_MUTEX_LOCK_FAILED                    \
        (GA_MICP_ERR_ID | GA_MUTEX_LOCK_FAILED)
/** Microphone Control Profile Error Code ID - MUTEX Unlock Failure */
#define MICP_MUTEX_UNLOCK_FAILED                  \
        (GA_MICP_ERR_ID | GA_MUTEX_UNLOCK_FAILED)
/** Microphone Control Profile Error Code ID - Memory Allocation Failure */
#define MICP_MEMORY_ALLOCATION_FAILED             \
        (GA_MICP_ERR_ID | GA_MEMORY_ALLOCATION_FAILED)

/** \} */

/**
 * \name MICP - Implementation Error Codes
 * \{
 * \brief This section lists Implementation Error Codes for MICP.
 */

/**
 * Microphone Control Profile Error Code ID - Invalid State to perform the
 * operation
 */
#define GA_MICP_INVALID_STATE                            (GA_MICP_ERR_ID | 0x0011U)
/** Microphone Control Profile Error Code ID - Invalid Parameters provided */
#define GA_MICP_INVALID_PARAMS                           (GA_MICP_ERR_ID | 0x0012U)
/** Microphone Control Profile Error Code ID - New Context allocation failed */
#define GA_MICP_CNTX_ALLOC_FAILED                        (GA_MICP_ERR_ID | 0x0013U)
/**
 * Microphone Control Profile Error Code ID - Another operation already in
 * progress.
 */
#define GA_MICP_IN_BUSY_STATE                            (GA_MICP_ERR_ID | 0x0014U)
/**
 * Microphone Control Profile Error Code ID - Invalid Handle to perform the
 * operation.
 */
#define GA_MICP_INVALID_HANDLE                           (GA_MICP_ERR_ID | 0x0015U)
/**
 * Microphone Control Profile Error Code ID - Operation Not Supported
 * Property not set for this Char by the remote.
 */
#define GA_MICP_OPERATION_NOT_SUPPORTED_BY_PEER_DEVICE   (GA_MICP_ERR_ID | 0x0016U)
/**
 * Microphone Control Profile Error Code ID - Service not registered by Local
 * Server.
 */
#define GA_MICP_SERVICE_ID_NOT_FOUND                     (GA_MICP_ERR_ID | 0x0017U)
/**
 * Microphone Control Profile Error Code ID - Unknown Service Type other than
 * MICS, AICS.
 */
#define GA_MICP_INVALID_SERVICE_TYPE                     (GA_MICP_ERR_ID | 0x0018U)

/** \} */
/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_csip_module
 * \{
 */

/**
 * \addtogroup ga_csip_defines
 * \{
 */

/**
 * \addtogroup ga_csip_error_code
 * \{
 */

/**
 * \name CSIP - OSAL Error Codes
 * \{
 * \brief This section lists OSAL Error Codes for CSIP.
 */

/**
 * Coordinated Set Identification Profile Error Code ID - MUTEX
 * Initialization Failure
 */
#define CSIP_MUTEX_INIT_FAILED                    \
        (GA_CSIP_ERR_ID | GA_MUTEX_INIT_FAILED)
/**
 * Coordinated Set Identification Profile Error Code ID - Conditional Variable
 * Initialization Failure
 */
#define CSIP_COND_INIT_FAILED                     \
        (GA_CSIP_ERR_ID | GA_COND_INIT_FAILED)
/**
 * Coordinated Set Identification Profile Error Code ID - MUTEX
 * Lock Failure
 */
#define CSIP_MUTEX_LOCK_FAILED                    \
        (GA_CSIP_ERR_ID | GA_MUTEX_LOCK_FAILED)
/**
 * Coordinated Set Identification Profile Error Code ID - MUTEX
 * Unlock Failure
 */
#define CSIP_MUTEX_UNLOCK_FAILED                  \
        (GA_CSIP_ERR_ID | GA_MUTEX_UNLOCK_FAILED)
/**
 * Coordinated Set Identification Profile Error Code ID - Memory
 * Allocation Failure
 */
#define CSIP_MEMORY_ALLOCATION_FAILED             \
        (GA_CSIP_ERR_ID | GA_MEMORY_ALLOCATION_FAILED)

/** \} */

/**
 * \name CSIP - Implementation Error Codes
 * \{
 * \brief This section lists Implementation Error Codes for CSIP.
 */

/**
 * Coordinated Set Identification Profile Error Code ID - Invalid State to
 * perform the operation.
 */
#define GA_CSIP_INVALID_STATE                            (GA_CSIP_ERR_ID | 0x0011U)
/**
 * Coordinated Set Identification Profile Error Code ID - Invalid
 * Parameters provided
 */
#define GA_CSIP_INVALID_PARAMS                           (GA_CSIP_ERR_ID | 0x0012U)
/**
 * Coordinated Set Identification Profile Error Code ID - New Context
 * allocation failed
 */
#define GA_CSIP_CNTX_ALLOC_FAILED                        (GA_CSIP_ERR_ID | 0x0013U)
/**
 * Coordinated Set Identification Profile Error Code ID - Another operation
 * already in progress.
 */
#define GA_CSIP_IN_BUSY_STATE                            (GA_CSIP_ERR_ID | 0x0014U)
/**
 * Coordinated Set Identification Profile Error Code ID - Invalid Handle to
 * perform the operation.
 */
#define GA_CSIP_INVALID_HANDLE                           (GA_CSIP_ERR_ID | 0x0015U)
/**
 * Coordinated Set Identification Profile Error Code ID - Operation Not
 * Supported Property not set for this Char by the remote.
 */
#define GA_CSIP_OPERATION_NOT_SUPPORTED_BY_PEER_DEVICE   (GA_CSIP_ERR_ID | 0x0016U)
/**
 * Coordinated Set Identification Profile Error Code ID - Service not
 * registered by Local Server.
 */
#define GA_CSIP_SERVICE_ID_NOT_FOUND                     (GA_CSIP_ERR_ID | 0x0017U)

/** \} */
/** \} */
/** \} */
/** \} */

/** \} */
/** \} */

/**
 * \addtogroup bt_ga_profiles
 * \{
 */

/**
 * \addtogroup bt_ga_content_control
 * \{
 */

/**
 * \addtogroup bt_ga_ccp
 * \{
 */

/**
 * \addtogroup ga_ccp_defines
 * \{
 */

/**
 * \addtogroup ga_ccp_common
 * \{
 */

/**
 * \addtogroup ga_ccp_error_code
 * \{
 */

/**
 * \name CCP - OSAL Error Codes
 * \{
 * \brief This section lists OSAL Error Codes for CCP.
 */

/** Call Control Profile Error Code ID - MUTEX Initialization Failure */
#define CCP_MUTEX_INIT_FAILED                    \
        (GA_CCP_ERR_ID | GA_MUTEX_INIT_FAILED)
/**
 * Call Control Profile Error Code ID - Conditional Variable
 * Initialization Failure
 */
#define CCP_COND_INIT_FAILED                     \
        (GA_CCP_ERR_ID | GA_COND_INIT_FAILED)
/** Call Control Profile Error Code ID - MUTEX Lock Failure */
#define CCP_MUTEX_LOCK_FAILED                    \
        (GA_CCP_ERR_ID | GA_MUTEX_LOCK_FAILED)
/** Call Control Profile Error Code ID - MUTEX Unlock Failure */
#define CCP_MUTEX_UNLOCK_FAILED                  \
        (GA_CCP_ERR_ID | GA_MUTEX_UNLOCK_FAILED)
/** Call Control Profile Error Code ID - Memory Allocation Failure */
#define CCP_MEMORY_ALLOCATION_FAILED             \
        (GA_CCP_ERR_ID | GA_MEMORY_ALLOCATION_FAILED)

/** \} */

/**
 * \name CCP - Implementation Error Codes
 * \{
 * \brief This section lists Implementation Error Codes for CCP.
 */

/**
 * Call Control Profile Error Code ID - Invalid State to perform the
 * operation.
 */
#define GA_CCP_INVALID_STATE                             (GA_CCP_ERR_ID | 0x0011U)
/** Call Control Profile Error Code ID - Invalid Parameters provided */
#define GA_CCP_INVALID_PARAMS                            (GA_CCP_ERR_ID | 0x0012U)
/** Call Control Profile Error Code ID - New Context allocation failed GTBS */
#define GA_CCP_CNTX_ALLOC_FAILED                         (GA_CCP_ERR_ID | 0x0013U)
/** Call Control Profile Error Code ID - New Context allocation failed TBS */
#define GA_CCP_TBS_CNTX_ALLOC_FAILED                     (GA_CCP_ERR_ID | 0x0014U)
/**
 * Call Control Profile Error Code ID - Another operation already in
 * progress.
 */
#define GA_CCP_IN_BUSY_STATE                             (GA_CCP_ERR_ID | 0x0015U)
/**
 * Call Control Profile Error Code ID - Context not found for this
 * request/event.
 */
#define GA_CCP_CNTX_NOT_FOUND                            (GA_CCP_ERR_ID | 0x0016U)
/**
 * Call Control Profile Error Code ID - Invalid Handle to perform the
 * operation.
 */
#define GA_CCP_INVALID_HANDLE                            (GA_CCP_ERR_ID | 0x0017U)

/** \} */
/** \} */
/** \} */
/** \} */
/** \} */

/**
 * \addtogroup bt_ga_mcp
 * \{
 */

/**
 * \addtogroup ga_mcp_defines
 * \{
 */

/**
 * \addtogroup ga_mcp_common
 * \{
 */

/**
 * \addtogroup ga_mcp_and_otp_error_code
 * \{
 */

/**
 * \name MCP - OSAL Error Codes
 * \{
 * \brief This section lists OSAL Error Codes for MCP.
 */

/** Media Control Profile Error Code ID - MUTEX Initialization Failure */
#define MCP_MUTEX_INIT_FAILED                    \
        (GA_MCP_ERR_ID | GA_MUTEX_INIT_FAILED)
/**
 * Media Control Profile Error Code ID - Conditional Variable
 * Initialization Failure
 */
#define MCP_COND_INIT_FAILED                     \
        (GA_MCP_ERR_ID | GA_COND_INIT_FAILED)
/** Media Control Profile Error Code ID - MUTEX Lock Failure */
#define MCP_MUTEX_LOCK_FAILED                    \
        (GA_MCP_ERR_ID | GA_MUTEX_LOCK_FAILED)
/** Media Control Profile Error Code ID - MUTEX Unlock Failure */
#define MCP_MUTEX_UNLOCK_FAILED                  \
        (GA_MCP_ERR_ID | GA_MUTEX_UNLOCK_FAILED)
/** Media Control Profile Error Code ID - Memory Allocation Failure */
#define MCP_MEMORY_ALLOCATION_FAILED             \
        (GA_MCP_ERR_ID | GA_MEMORY_ALLOCATION_FAILED)

/** \} */

/**
 * \name MCP - Implementation Error Codes
 * \{
 * \brief This section lists the Error Codes that are provided as part of
 * return of functionalities of MCP \ref ga_mcp_ce_api_defs,
 * \ref ga_mcp_se_api_defs
 */

/**
 * Media Control Profile Error Code ID - Invalid State to perform the
 * operation.
 */
#define GA_MCP_INVALID_STATE                             (GA_MCP_ERR_ID | 0x0011U)
/** Media Control Profile Error Code ID - Invalid Parameters provided */
#define GA_MCP_INVALID_PARAMS                            (GA_MCP_ERR_ID | 0x0012U)
/** Media Control Profile Error Code ID - New Context allocation failed */
#define GA_MCP_CNTX_ALLOC_FAILED                         (GA_MCP_ERR_ID | 0x0013U)
/**
 * Media Control Profile Error Code ID - Another operation already in
 * progress.
 */
#define GA_MCP_IN_BUSY_STATE                             (GA_MCP_ERR_ID | 0x0014U)
/**
 * Media Control Profile Error Code ID - Context not found for this
 * request/event.
 */
#define GA_MCP_CNTX_NOT_FOUND                            (GA_MCP_ERR_ID | 0x0015U)
/**
 * Media Control Profile Error Code ID - Invalid Handle to perform the
 * operation.
 */
#define GA_MCP_INVALID_HANDLE                            (GA_MCP_ERR_ID | 0x0016U)

/** \} */

/**
 * \name OTP - Implementation Error Codes
 * \{
 * \brief This section lists the Error Codes that are provided as part of
 * return of functionalities of OTP \ref ga_mcp_ce_api_defs,
 * \ref ga_mcp_se_api_defs
 */

/**
 * Object Transfer Profile Error Code ID - Invalid State to perform the
 * operation.
 */
#define GA_OTP_INVALID_STATE                             (GA_OTP_ERR_ID | 0x0011U)
/** Object Transfer Profile Error Code ID - Invalid Parameters provided */
#define GA_OTP_INVALID_PARAMS                            (GA_OTP_ERR_ID | 0x0012U)
/** Object Transfer Profile Error Code ID - New Context allocation failed */
#define GA_OTP_CNTX_ALLOC_FAILED                         (GA_OTP_ERR_ID | 0x0013U)
/**
 * Object Transfer Profile Error Code ID - Another operation already in
 * progress.
 */
#define GA_OTP_IN_BUSY_STATE                             (GA_OTP_ERR_ID | 0x0014U)
/**
 * Object Transfer Profile Error Code ID - Context not found for this
 * request/event.
 */
#define GA_OTP_CNTX_NOT_FOUND                            (GA_OTP_ERR_ID | 0x0015U)
/**
 * Object Transfer Profile Error Code ID - OTP Session already exists for
 * this handle.
 */
#define GA_OTP_SESSION_EXISTS                            (GA_OTP_ERR_ID | 0x0016U)

/** \} */

/** \} */
/** \} */
/** \} */
/** \} */

/** \} */

/**
 * \addtogroup bt_ga_appl_profiles
 * \{
 */

/**
 * \addtogroup hap_module
 * \{
 */

/**
 * \addtogroup hap_defines
 * \{
 */

/**
 * \addtogroup hap_error_code
 * \{
 */

/**
 * \name HAP - OSAL Error Codes
 * \{
 * \brief This section lists OSAL Error Codes for HAP.
 */

/** Hearing Access Profile Error Code ID - MUTEX Initialization Failure */
#define HAP_MUTEX_INIT_FAILED                    \
        (GA_HAP_ERR_ID | GA_MUTEX_INIT_FAILED)
/**
 * Hearing Access Profile Error Code ID - Conditional Variable
 * Initialization Failure
 */
#define HAP_COND_INIT_FAILED                     \
        (GA_HAP_ERR_ID | GA_COND_INIT_FAILED)
/** Hearing Access Profile Error Code ID - MUTEX Lock Failure */
#define HAP_MUTEX_LOCK_FAILED                    \
        (GA_HAP_ERR_ID | GA_MUTEX_LOCK_FAILED)
/** Hearing Access Profile Error Code ID - MUTEX Unlock Failure */
#define HAP_MUTEX_UNLOCK_FAILED                  \
        (GA_HAP_ERR_ID | GA_MUTEX_UNLOCK_FAILED)
/** Hearing Access Profile Error Code ID - Memory Allocation Failure */
#define HAP_MEMORY_ALLOCATION_FAILED             \
        (GA_HAP_ERR_ID | GA_MEMORY_ALLOCATION_FAILED)

/** \} */

/**
 * \name HAP - Implementation Error Codes
 * \{
 * \brief This section lists the Error Codes that are provided as part of
 * return of functionalities of HAP \ref hap_api_defs
 */

/**
 * Hearing Access Profile Error Code ID - Invalid State to perform the
 * operation.
 */
#define GA_HAP_INVALID_STATE                             (GA_HAP_ERR_ID | 0x0011U)
/**
 * Hearing Access Profile Error Code ID - Invalid Parameters provided.
 */
#define GA_HAP_INVALID_PARAMS                            (GA_HAP_ERR_ID | 0x0012U)
/**
 * Hearing Access Profile Error Code ID - New Context allocation failed.
 */
#define GA_HAP_CNTX_ALLOC_FAILED                         (GA_HAP_ERR_ID | 0x0013U)
/**
 * Hearing Access Profile Error Code ID - Another operation already in
 * progress.
 */
#define GA_HAP_IN_BUSY_STATE                             (GA_HAP_ERR_ID | 0x0014U)
/**
 * Hearing Access Profile Error Code ID - Context not found for this
 * request/event.
 */
#define GA_HAP_CNTX_NOT_FOUND                            (GA_HAP_ERR_ID | 0x0015U)
/**
 * Hearing Access Profile Error Code ID - Invalid Handle to perform
 * the operation.
 */
#define GA_HAP_INVALID_HANDLE                            (GA_HAP_ERR_ID | 0x0016U)

/** \} */
/** \} */
/** \} */
/** \} */

/**
 * \addtogroup tmap_module
 * \{
 */

/**
 * \addtogroup tmap_defines
 * \{
 */

/**
 * \addtogroup tmap_error_code
 * \{
 */

/**
 * \name TMAP - OSAL Error Codes
 * \{
 * \brief This section lists OSAL Error Codes for TMAP.
 */

/**
 * Telephony and Media Audio Profile Error Code ID - MUTEX
 * Initialization Failure
 */
#define TMAP_MUTEX_INIT_FAILED                    \
        (GA_TMAP_ERR_ID | GA_MUTEX_INIT_FAILED)
/**
 * Telephony and Media Audio Profile Error Code ID - Conditional Variable
 * Initialization Failure
 */
#define TMAP_COND_INIT_FAILED                     \
        (GA_TMAP_ERR_ID | GA_COND_INIT_FAILED)
/** Telephony and Media Audio Profile Error Code ID - MUTEX Lock Failure */
#define TMAP_MUTEX_LOCK_FAILED                    \
        (GA_TMAP_ERR_ID | GA_MUTEX_LOCK_FAILED)
/** Telephony and Media Audio Profile Error Code ID - MUTEX Unlock Failure */
#define TMAP_MUTEX_UNLOCK_FAILED                  \
        (GA_TMAP_ERR_ID | GA_MUTEX_UNLOCK_FAILED)
/**
 * Telephony and Media Audio Profile Error Code ID - Memory
 * Allocation Failure
 */
#define TMAP_MEMORY_ALLOCATION_FAILED             \
        (GA_TMAP_ERR_ID | GA_MEMORY_ALLOCATION_FAILED)

/** \} */

/**
 * \name TMAP - Implementation Error Codes
 * \{
 * \brief This section lists the Error Codes that are provided as part of
 * return of functionalities of TMAP \ref tmap_api_defs
 */

/**
 * Telephony and Media Audio Profile Error Code ID - Invalid State to perform
 * the operation.
 */
#define GA_TMAP_INVALID_STATE                            (GA_TMAP_ERR_ID | 0x0011U)
/**
 * Telephony and Media Audio Profile Error Code ID - Invalid Parameters
 * provided.
 */
#define GA_TMAP_INVALID_PARAMS                           (GA_TMAP_ERR_ID | 0x0012U)
/**
 * Telephony and Media Audio Profile Error Code ID - New Context allocation
 * failed.
 */
#define GA_TMAP_CNTX_ALLOC_FAILED                        (GA_TMAP_ERR_ID | 0x0013U)
/**
 * Telephony and Media Audio Profile Error Code ID - Another operation already
 * in progress.
 */
#define GA_TMAP_IN_BUSY_STATE                            (GA_TMAP_ERR_ID | 0x0014U)
/**
 * Telephony and Media Audio Profile Error Code ID - Context not found for this
 * request/event.
 */
#define GA_TMAP_CNTX_NOT_FOUND                           (GA_TMAP_ERR_ID | 0x0015U)
/**
 * Telephony and Media Audio Profile Error Code ID - Invalid Handle to perform
 * the operation.
 */
#define GA_TMAP_INVALID_HANDLE                           (GA_TMAP_ERR_ID | 0x0016U)

/** \} */

/** \} */
/** \} */
/** \} */

/** \} */
/** \} */

/**
 * \addtogroup bt_ga_core
 * \{
 */

/**
 * \addtogroup ga_cap_module
 * \{
 */

/**
 * \addtogroup ga_bap_module
 * \{
 */

/**
 * \addtogroup ga_bap_bc_module
 * \{
 */

/**
 * \addtogroup ga_bap_bc_defines
 * \{
 */

/**
 * \addtogroup ga_bap_bc_bass_ce_se_common_def
 * \{
 */

/**
 * \addtogroup ga_bap_bc_bass_ce_se_common_error_code
 * \{
 */

/**
 * \name BASS - OSAL Error Codes
 * \{
 * \brief This section lists OSAL Error Codes for BASS.
 */

/**
 * Broadcast Audio Scan Service Error Code ID - MUTEX
 * Initialization Failure
 */
#define BASS_MUTEX_INIT_FAILED                    \
        (GA_BASS_ERR_ID | GA_MUTEX_INIT_FAILED)
/**
 * Broadcast Audio Scan Service Error Code ID - Conditional Variable
 * Initialization Failure
 */
#define BASS_COND_INIT_FAILED                     \
        (GA_BASS_ERR_ID | GA_COND_INIT_FAILED)
/** Broadcast Audio Scan Service Error Code ID - MUTEX Lock Failure */
#define BASS_MUTEX_LOCK_FAILED                    \
        (GA_BASS_ERR_ID | GA_MUTEX_LOCK_FAILED)
/** Broadcast Audio Scan Service Error Code ID - MUTEX Unlock Failure */
#define BASS_MUTEX_UNLOCK_FAILED                  \
        (GA_BASS_ERR_ID | GA_MUTEX_UNLOCK_FAILED)
/** Broadcast Audio Scan Service Error Code ID - Memory Allocation Failure */
#define BASS_MEMORY_ALLOCATION_FAILED             \
        (GA_BASS_ERR_ID | GA_MEMORY_ALLOCATION_FAILED)

/** \} */

/**
 * \name BASS - Implementation Error Codes
 * \{
 * \brief This section lists the Error Codes that are provided as part of
 * return of functionalities of BASS \ref ga_bap_bc_bass_ce_api_defs,
 * \ref ga_bap_bc_bass_se_api_defs
 */

/**
 * Broadcast Audio Scan Service Error Code ID - Invalid State to perform
 * the operation.
 */
#define GA_BASS_INVALID_STATE                            (GA_BASS_ERR_ID | 0x0011U)

/**
 * Broadcast Audio Scan Service Error Code ID - Invalid Parameters
 * provided.
 */
#define GA_BASS_INVALID_PARAMS                           (GA_BASS_ERR_ID | 0x0012U)

/**
 * Broadcast Audio Scan Service Error Code ID - New Context allocation
 * failed.
 */
#define GA_BASS_CNTX_ALLOC_FAILED                        (GA_BASS_ERR_ID | 0x0013U)

/**
 * Broadcast Audio Scan Service Error Code ID - Another operation already
 * in progress.
 */
#define GA_BASS_IN_BUSY_STATE                            (GA_BASS_ERR_ID | 0x0014U)

/**
 * Broadcast Audio Scan Service Error Code ID - Context not found for this
 * request/event.
 */
#define GA_BASS_CNTX_NOT_FOUND                           (GA_BASS_ERR_ID | 0x0015U)

/**
 * Broadcast Audio Scan Service Error Code ID - Invalid Handle to perform
 * the operation.
 */
#define GA_BASS_INVALID_HANDLE                           (GA_BASS_ERR_ID | 0x0016U)

/** \} */
/** \} */
/** \} */

/** \} */
/** \} */
/** \} */
/** \} */
/** \} */

#endif /* _H_GA_ERROR_ */
