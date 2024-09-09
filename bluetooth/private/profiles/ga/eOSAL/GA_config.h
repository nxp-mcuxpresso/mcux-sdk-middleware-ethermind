
/**
 *  \file GA_config.h
 *
 *  This Header File contains the mapping to generic OSAL APIs.
 */

/*
 *  Copyright (C) 2015. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_GA_CONFIG_
#define _H_GA_CONFIG_

/* --------------------------------------------- Header File Inclusion */
#include "EM_config.h"

/* --------------------------------------------- Global Definitions */
/** Maximum Characters per line in Config File */
#define GA_CONFIG_MAX_CHARS_PER_LINE            EM_CONFIG_MAX_CHARS_PER_LINE

/* --------------------------------------------- Structures/Data Types */

/* --------------------------------------------- Macros */
#define GA_config_read(fn, tf, buf)             EM_config_read((fn), (tf), (buf))

/* --------------------------------------------- Internal Functions */

/* --------------------------------------------- API Declarations */

#endif /* _H_GA_CONFIG_ */

