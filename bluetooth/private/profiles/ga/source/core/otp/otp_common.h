
/**
 *  \file otp_common.h
 *
 *  \brief This file handles the context management, handles the callbacks from
 *         the GATT Bearer layer, generates the events to the application
 *         registered.
 */

/*
 *  Copyright (C) 2020. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_OTP_COMMON_
#define _H_OTP_COMMON_

/* --------------------------------------------- Header File Inclusion */
#include "GA_api.h"
#include "GA_bearer_api.h"

#include "l2cap_coc.h"
/* --------------------------------------------- Global Definitions */

/* --------------------------------------------- Data types /Structures */
/* OTP Data Channel Mode - CFBC/ECBFC */
typedef UINT8 OTP_DATA_CHANNEL_MODE;

/* OTP Data Channel State */
typedef UINT8 OTP_DATA_CHANNEL_STATE;

typedef struct
{
    /* Offset of the data to be used for subsequent transfers */
    UINT32 offset;

    /*
     * Length received during subsequent data receive, this becomes equal to
     * rx_len expected if successful data is transferred completely.
     */
    UINT32 rx_len;

    /* Total length of the data expected to be receieved */
    UINT32 rx_len_exp;

    /* Type of object data expected */
    UCHAR  obj_type;
}OTP_DATA_CHANNEL_RX_PARAM;

typedef struct _OTP_DATA_CHANNEL_CONN_PARAMS
{
    /* Total CBFC and ECBFC Channels open */
    UINT8                     active_conn;
    UCHAR                     mode;
    /* CID Valid for CBFC Mode */
    UINT16                    lcid;
    OTP_L2CAP_CBFC_CONNECT_PARAM  cbfc_conn_param;
    OTP_L2CAP_ECBFC_CONNECT_PARAM ecbfc_conn_param;
}OTP_DATA_CHANNEL_CONN_PARAMS;

typedef struct _OTP_DATA_CHANNEL_CTX
{
    OTP_DATA_CHANNEL_STATE       state;
    OTP_DATA_CHANNEL_CONN_PARAMS conn_param;
    OTP_DATA_CHANNEL_RX_PARAM    rx_param;
    UINT16                       tx_param_len;
    UCHAR                        handle;
}OTP_DATA_CHANNEL_CTX;
/* --------------------------------------------- Macros */
#ifndef OTP_NO_DEBUG
#define OTP_ERR(...)          EM_debug_error(GA_MODULE_ID_OTP, __VA_ARGS__)
#else  /* OTP_NO_DEBUG */
#define OTP_ERR               EM_debug_null
#endif /* OTP_NO_DEBUG */

#ifdef OTP_DEBUG

#define OTP_TRC(...)          EM_debug_trace(GA_MODULE_ID_OTP, __VA_ARGS__)
#define OTP_INF(...)          EM_debug_info(GA_MODULE_ID_OTP, __VA_ARGS__)

#else  /* OTP_DEBUG */

#define OTP_TRC               EM_debug_null
#define OTP_INF               EM_debug_null

#endif /* OTP_DEBUG */

/* By default, unused instance before session is established */
#define OTP_INST_UNUSED                           0xFF

/* Invalid Event, Do not trigger a callback to the app */
#define OTP_EVT_INVALID                           0xFF

/* Object Access Control Point Commands */
#define OTP_OACP_CREATE_OPCODE                    0x01
#define OTP_OACP_DELETE_OPCODE                    0x02
#define OTP_OACP_CAL_CHECK_SUM_OPCODE             0x03
#define OTP_OACP_EXECUTE_OPCODE                   0x04
#define OTP_OACP_READ_OPCODE                      0x05
#define OTP_OACP_WRITE_OPCODE                     0x06
#define OTP_OACP_ABORT_OPCODE                     0x07
#define OTP_OACP_RSP_CODE_OPCODE                  0x60

/* Object List Control Point Commands */
#define OTP_OLCP_FIRST_OPCODE                     0x01
#define OTP_OLCP_LAST_OPCODE                      0x02
#define OTP_OLCP_PREVIOUS_OPCODE                  0x03
#define OTP_OLCP_NEXT_OPCODE                      0x04
#define OTP_OLCP_GO_TO_OPCODE                     0x05
#define OTP_OLCP_ORDER_OPCODE                     0x06
#define OTP_OLCP_REQ_NUM_OF_OBJ_OPCODE            0x07
#define OTP_OLCP_CLEAR_MARKING_OPCODE             0x08
#define OTP_OLCP_RSP_CODE_OPCODE                  0x70

/* Object Action Control Point Response Value */
#define OTP_OACP_SUCCESS                          0x01
#define OTP_OACP_OPCODE_NOT_SUPPORTED             0x02
#define OTP_OACP_INVALID_PARAMETER                0x03
#define OTP_OACP_INSUFF_RESOURCES                 0x04
#define OTP_OACP_INVALID_OBJECT                   0x05
#define OTP_OACP_CHANNEL_UNAVAILABLE              0x06
#define OTP_OACP_UNSUPP_TYPE                      0x07
#define OTP_OACP_PROCEDURE_NOT_PERMITTED          0x08
#define OTP_OACP_OBJECT_LOCKED                    0x09
#define OTP_OACP_OPERATION_FAILED                 0x0A

/* Object List Control Point Response Value */
#define OTP_OLCP_SUCCESS                          0x01
#define OTP_OLCP_OPCODE_NOT_SUPPORTED             0x02
#define OTP_OLCP_INVALID_PARAMETER                0x03
#define OTP_OLCP_OPERATION_FAILED                 0x04
#define OTP_OLCP_OUT_OF_BOUNDS                    0x05
#define OTP_OLCP_TOO_MANY_OBJECTS                 0x06
#define OTP_OLCP_NO_OBJECT                        0x07
#define OTP_OLCP_OBJ_ID_NOT_FOUND                 0x08

/* Length of the Object ID */
#define OTP_OBJ_ID_LEN 6

#define OTP_DQ_LINK_NONE                    0x00U
#define OTP_DQ_BR_LINK                      0x01U
#define OTP_DQ_LE_LINK                      0x02U
#define OTP_DQ_LINK_ANY                     0xFFU

/* Error Code: In GA_error.h? */
#define OTP_L2CAP_CREDIT_OVERFLOW           0x2373U

/* --------------------------------------------- APIs */


#endif /* _H_OTP_COMMON_ */