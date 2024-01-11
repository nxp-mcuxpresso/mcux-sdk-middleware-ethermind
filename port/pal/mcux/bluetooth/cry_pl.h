
/**
 *  \file cry_pl.h
 *
 *  This Header File contains the platform specific interfaces
 *  for Cyclic Redundancy Check module.
 */

 /*
  *  Copyright (C) 2013. Mindtree Ltd.
  *  All rights reserved.
  */

#ifndef _H_CRY_PL_
#define _H_CRY_PL_
/* --------------------------------------------- Header File Inclusion */
#include "BT_common.h"

/* --------------------------------------------- Global Definitions */

/* --------------------------------------------- Structures/Data Types */

/* --------------------------------------------- Macros */

/* --------------------------------------------- Internal Functions */

/* --------------------------------------------- API Declarations */

/**
 * \brief Calculate 16bit CRC on the input buffer
 *
 * \par Description:
 *      This function calculates the 16bit CRC on the given buffer
 *
 * \param [in] input_buf  Buffer of data on which CRC needs to be calculated
 * \param [in] input_len  Length of Input Buffer
 * \param [inout] crc     CRC calculated on the input buffer
 *
 * \return API_SUCCESS if Successful else an Error code describing
 * cause of failure.
 */
API_RESULT cry_perform_crc16_op(void* input_buf, UINT32 input_len, UINT16* crc);

/**
 * \brief Calculate 32bit CRC on the input buffer
 *
 * \par Description:
 *      This function calculates the 32bit CRC on the given buffer
 *
 * \param [in] input_buf  Buffer of data on which CRC needs to be calculated
 * \param [in] input_len  Length of Input Buffer
 * \param [inout] crc     CRC calculated on the input buffer
 *
 * \return API_SUCCESS if Successful else an Error code describing
 * cause of failure.
 */
API_RESULT cry_perform_crc32_op(void* input_buf, UINT32 input_len, UINT32* crc);

#endif /* _H_CRY_PL_ */

