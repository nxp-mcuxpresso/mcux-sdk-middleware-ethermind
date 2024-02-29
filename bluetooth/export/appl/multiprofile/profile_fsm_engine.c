
/**
 *  \file profile_fsm_engine.c
 *
 *  This file implement the Routines to Invoke FSM Event Handlers.
 */

/*
 *  Copyright (C) 2012. MindTree Ltd.
 *  All rights reserved.
 */
/* ----------------------------------------- Header File Inclusion */
#include "profile_fsm_engine.h"
#ifdef MULTI_PROFILE_FSM_SUPPORT
/* ----------------------------------------- External Global Variables */
PROFILE_SESSION multiprofile_inst[PROFILE_MAX_INSTANCES];
/* ----------------------------------------- Exported Global Variables */

/* ----------------------------------------- Static Global Variables */

/**
 *  \fn profile_fsm_post_event
 *
 *  \brief
 *
 *  \Description
 *
 *
 *  \param profile_event
 *
 *  \return None
 */
API_RESULT profile_fsm_post_event (PROFILE_EVENT_INFO * profile_event)
{
    /*
     * Store the previous state of session for rollback on error to response
     * for all local events other than Error Response
     */
    if ((PROFILE_FSM_LOCAL_EVENT == profile_event->event_info) &&
        (profile_event->event_type != ev_pro_error_rsp))
    {
        /* Update the session previous state */
        multiprofile_inst[profile_event->profile_fsm_handle].prev_state = multiprofile_inst[profile_event->profile_fsm_handle].state;
    }

    /* Post event to FSM */
    return fsm_post_event (profile_fsm_id, profile_event->event_type, profile_event);
}


/**
 *  \fn profile_access_state_handler
 *
 *  \brief
 *
 *  \Description
 *
 *
 *  \param param
 *  \param state
 *
 *  \return None
 */
API_RESULT profile_access_state_handler
           (
                void       * param,
                STATE_T    * state
           )
{
    *state = PROFILE_ACCESS_STATE((((PROFILE_EVENT_INFO *)param)->profile_fsm_handle));
    return API_SUCCESS;
}

/**
 *  \fn profile_access_state_handler
 *
 *  \brief
 *
 *  \Description
 *
 *
 *  \param param
 *  \param state
 *
 *  \return None
 */
API_RESULT profile_set_state_handler
           (
                void       * param,
                STATE_T    state
           )
{
    PROFILE_SET_STATE((((PROFILE_EVENT_INFO *)param)->profile_fsm_handle), state);
    return API_SUCCESS;
}
#endif /* MULTI_PROFILE_FSM_SUPPORT */
