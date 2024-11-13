#include "statemachine.h"
// @see https://github.com/endurodave/C_StateMachine
//---------------------------------------------------------------------------------------------------
// Generates an external event. Called once per external event 
// to start the state machine executing
void statemachineExternalEvent_(StateMachine* statemachine, const StateMachineImmut* statemachineimmut, u8 newstate, void* eventdata)
{
    // If we are supposed to ignore this event
    if (newstate == event_ignored) {
        // Just delete the event data, if any
        if (eventdata) {
            // SM_XFree(eventdata);
        }
    }
    else {
        // TODO - capture software lock here for thread-safety if necessary

        // Generate the event 
        statemachineInternalEvent_(statemachine, newstate, eventdata);

        // Execute state machine based on type of state map defined
        if (statemachineimmut->statemap) {
            statemachineStateEngine_(statemachine, statemachineimmut);
        } else {
            statemachineStateEngineEx_(statemachine, statemachineimmut);
        }
        // TODO - release software lock here 
    }
}

// Generates an internal event. Called from within a state 
// function to transition to a new state
void statemachineInternalEvent_(StateMachine* statemachine, u8 newstate, void* eventdata) {
    // ASSERT_TRUE(statemachine);

    statemachine->eventdata = eventdata;
    statemachine->eventgenerated = true;
    statemachine->newstate = newstate;
}

// The state engine executes the state machine states
void statemachineStateEngine_(StateMachine* statemachine, const StateMachineImmut* statemachineimmut) {
    void* datatemp = NULL;

    // ASSERT_TRUE(statemachine);
    // ASSERT_TRUE(statemachineimmut);

    // While events are being generated keep executing states
    while (statemachine->eventgenerated)
    {
        // Error check that the new state is valid before proceeding
        // ASSERT_TRUE(statemachine->newstate < statemachineimmut->maxStates);

        // Get the pointers from the state map
        StateProc state = statemachineimmut->statemap[statemachine->newstate].stateproc;

        // Copy of event data pointer
        datatemp = statemachine->eventdata;

        // Event data used up, reset the pointer
        statemachine->eventdata = NULL;

        // Event used up, reset the flag
        statemachine->eventgenerated = false;

        // Switch to the new current state
        statemachine->currentstate = statemachine->newstate;

        // Execute the state action passing in event data
        // ASSERT_TRUE(state != NULL);
        state(statemachine, datatemp);

        // If event data was used, then delete it
        if (datatemp) {
            // SM_XFree(datatemp);
            datatemp = NULL;
        }
    }
}

// The state engine executes the extended state machine states
void statemachineStateEngineEx_(StateMachine* statemachine, const StateMachineImmut* statemachineimmut) {
    bool guardresult = true;
    void *datatemp = NULL;

    // ASSERT_TRUE(statemachine);
    // ASSERT_TRUE(statemachineimmut);

    // While events are being generated keep executing states
    while (statemachine->eventgenerated)
    {
        // Error check that the new state is valid before proceeding
        // ASSERT_TRUE(statemachine->newstate < statemachineimmut->maxStates);

        // Get the pointers from the extended state map
        StateProc state = statemachineimmut->statemapex[statemachine->newstate].stateproc;
        GuardProc guard = statemachineimmut->statemapex[statemachine->newstate].guardproc;
        EntryProc entry = statemachineimmut->statemapex[statemachine->newstate].entryproc;
        ExitProc exit = statemachineimmut->statemapex[statemachine->currentstate].exitproc;

        // Copy of event data pointer
        datatemp = statemachine->eventdata;
        // Event data used up, reset the pointer
        statemachine->eventdata = NULL;

        // Event used up, reset the flag
        statemachine->eventgenerated = false;

        // Execute the guard condition
        if (guard != NULL) {
            guardresult = guard(statemachine, datatemp);
        }

        // If the guard condition succeeds
        if (guardresult == true) {
            // Transitioning to a new state?
            if (statemachine->newstate != statemachine->currentstate) {
                // Execute the state exit action on current state before switching to new state
                if (exit != NULL) {
                    exit(statemachine);
                }

                // Execute the state entry action on the new state
                if (entry != NULL) {
                    entry(statemachine, datatemp);
                }

                // Ensure exit/entry actions didn't call SM_InternalEvent by accident 
                // ASSERT_TRUE(statemachine->eventgenerated == false);
            }

            // Switch to the new current state
            statemachine->currentstate = statemachine->newstate;

            // Execute the state action passing in event data
            // ASSERT_TRUE(state != NULL);
            state(statemachine, datatemp);
        }

        // If event data was used, then delete it
        if (datatemp) {
            // SM_XFree(datatemp);
            datatemp = NULL;
        }
    }
}
