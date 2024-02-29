
/**
 *  \file appl_hci.h
 *
 *  Header File for HCI Command Line Application
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_APPL_HCI_LE_
#define _H_APPL_HCI_LE_

/* ----------------------------------------- Header File Inclusion */
#include "appl_le.h"
#include "appl_utils.h"

#ifdef APPL_FSM_SUPPORT
#include "appl_fsm.h"
#endif /* APPL_FSM_SUPPORT */

#ifdef AES_CMAC_UTIL
#include "aes_cmac_pl.h"
#endif /* AES_CMAC_UTIL */

/* ----------------------------------------- Global Definitions */


/* ----------------------------------------- Structures/Data Types */
typedef struct
{
    UINT16    opcode;
    char *    command_name;
} APPL_HCI_LE_OPCODE_NAME;

/* ----------------------------------------- Macros */

/* ----------------------------------------- Function Declarations */
/* HCI Application Event Indication Callback */
API_RESULT appl_hci_le_event_indication_callback
           (
               UCHAR  event_type,
               UCHAR  * event_data,
               UCHAR  event_datalen
           );

char *appl_hci_le_get_command_name(UINT16 opcode);

#endif /* _H_APPL_HCI_LE_ */

