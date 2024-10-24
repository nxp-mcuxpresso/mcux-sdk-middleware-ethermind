
/**
 *  \file GA_fops.h
 *
 *  This Header File contains the APIs for FOPS library
 */

/*
 *  Copyright (C) 2015. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_GA_FOPS_
#define _H_GA_FOPS_

/* --------------------------------------------- Header File Inclusion */
#include "EM_fops.h"

/* --------------------------------------------- Global Definitions */
#define GA_TIMER_HANDLE_INIT_VAL            EM_TIMER_HANDLE_INIT_VAL

#define GA_FOPS_MASK_READONLY               EM_FOPS_MASK_READONLY
#define GA_FOPS_MASK_HIDDEN                 EM_FOPS_MASK_HIDDEN
#define GA_FOPS_MASK_SYSTEM                 EM_FOPS_MASK_SYSTEM
#define GA_FOPS_MASK_FOLDER                 EM_FOPS_MASK_FOLDER
#define GA_FOPS_MASK_ARCHIVE                EM_FOPS_MASK_ARCHIVE

#define GA_FOPS_SEEK_SET                    EM_FOPS_SEEK_SET
#define GA_FOPS_SEEK_CUR                    EM_FOPS_SEEK_CUR
#define GA_FOPS_SEEK_END                    EM_FOPS_SEEK_END

#define GA_FOPS_BASE                        EM_FOPS_BASE
#define GA_FOPS_PATH_SEP                    EM_FOPS_PATH_SEP
#define GA_FOPS_MAX_DIRECTORY_SIZE          EM_FOPS_MAX_DIRECTORY_SIZE
#define GA_FOPS_MAX_FN_SIZE                 EM_FOPS_MAX_FN_SIZE


/* --------------------------------------------- Structures/Data Types */
#define GA_fops_file_handle                 EM_fops_file_handle
#define GA_fops_object_handle               EM_fops_object_handle

/* --------------------------------------------- Macros */
#define GA_FOPS_PATH_JOIN                   EM_FOPS_PATH_JOIN

#define GA_FOPS_SET_BIT                     EM_FOPS_SET_BIT
#define GA_FOPS_GET_BIT                     EM_FOPS_GET_BIT
#define GA_FOPS_RESET_BIT                   EM_FOPS_RESET_BIT

/* --------------------------------------------- Macros */

/* --------------------------------------------- Data Structures */
#define GA_FOPS_FILINFO                     EM_FOPS_FILINFO

/* --------------------------------------------- API Declarations */
#define GA_fops_get_current_directory       EM_fops_get_current_directory
#define GA_fops_get_file_attributes         EM_fops_get_file_attributes
#define GA_fops_set_file_attributes         EM_fops_set_file_attributes
#define GA_fops_access_first                EM_fops_access_first
#define GA_fops_access_next                 EM_fops_access_next
#define GA_fops_access_close                EM_fops_access_close
#define GA_fops_set_path_forward            EM_fops_set_path_forward
#define GA_fops_set_path_backward           EM_fops_set_path_backward
#define GA_fops_create_folder               EM_fops_create_folder
#define GA_fops_file_open                   EM_fops_file_open
#define GA_fops_file_write                  EM_fops_file_write
#define GA_fops_file_read                   EM_fops_file_read
#define GA_fops_file_print                  EM_fops_file_print
#define GA_fops_file_put                    EM_fops_file_put
#define GA_fops_file_get                    EM_fops_file_get
#define GA_fops_file_get_formatted          EM_fops_file_get_formatted
#define GA_fops_file_close                  EM_fops_file_close
#define GA_fops_object_delete               EM_fops_object_delete
#define GA_fops_file_size                   EM_fops_file_size
#define GA_fops_file_seek                   EM_fops_file_seek
#define GA_fops_file_copy                   EM_fops_file_copy
#define GA_fops_file_move                   EM_fops_file_move
#define GA_vfops_create_object_name         EM_vfops_create_object_name
#define GA_vfops_set_path_backward          EM_vfops_set_path_backward
#define GA_vfops_set_path_forward           EM_vfops_set_path_forward
#define GA_fops_list_directory              EM_fops_list_directory

#endif /* _H_GA_FOPS_ */

