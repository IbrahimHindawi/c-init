#pragma once
#include <core.h>
#include "StateMachine/statemachine.h"

structdef(Motor) { 
    i32 currentspeed; 
};
structdef(MotorData) { 
    i32 speed; 
};
eventDeclare(motorSetSpeed, MotorData);
eventDeclare(motorHalt, NoEventData);

enum States { 
    Idle,
    Stop,
    Start,
    ChangeSpeed,
    StateLength
};

stateDeclare(Idle, NoEventData);
// static void stateIdle(StateMachine *statemachine, NoEventData *eventdata);
stateDeclare(Stop, NoEventData);
// static void stateStop(StateMachine *statemachine, NoEventData *eventdata);
stateDeclare(Start, MotorData);
// static void stateStart(StateMachine *statemachine, MotorData *eventdata);
stateDeclare(ChangeSpeed, MotorData);
// static void stateChangeSpeed(StateMachine *statemachine, MotorData *eventdata);

statemapBegin(Motor)
// static const State MotorStateMap[] = { 
    statemapEntry(stateIdle)
    // { (StateProc)stateIdle },
    statemapEntry(stateStop)
    // { (StateProc)stateStop },
    statemapEntry(stateStart)
    // { (StateProc)stateStart },
    statemapEntry(stateChangeSpeed)
    // { (StateProc)stateChangeSpeed },
statemapEnd(Motor)
// }; 
// static const StateMachineImmut MotorImmut = { 
//     "Motor", (sizeofarray(MotorStateMap)), MotorStateMap, {0} 
// };

eventDefine(motorSetSpeed, MotorData) {
// void motorSetSpeed(StateMachine *statemachine, MotorData* eventdata) {
    transitionmapBegin
    // static const u8 transitions[] = {
        transitionmapEntry(Start)
        // stateStart,
        transitionmapEntry(cannot_happen)
        // cannot_happen,
        transitionmapEntry(ChangeSpeed)
        // stateStop,
        transitionmapEntry(ChangeSpeed)
        // stateStart,
    transitionmapEnd(Motor, eventdata)
    // };
    // statemachineExternalEvent(statemachine, &MotorImmut, transitions[statemachine->currentstate], eventdata);
}

eventDefine(motorHalt, NoEventData) {
    transitionmapBegin
        transitionmapEntry(Start)
        transitionmapEntry(cannot_happen)
        transitionmapEntry(ChangeSpeed)
        transitionmapEntry(ChangeSpeed)
    transitionmapEnd(Motor, eventdata)
}

stateDefine(Idle, NoEventData) {
    printf("%s Idle\n", statemachine->name);
}

stateDefine(Stop, NoEventData) {
    // Get pointer to the instance data and update currentspeed
    Motor* instance = statemachineGetInstance(Motor);
    instance->currentspeed = 0;

    // Perform the stop motor processing here
    printf("%s Stop: %d\n", statemachine->name, instance->currentspeed);

    // Transition to ST_Idle via an internal event
    statemachineInternalEvent(Idle, NULL);
}

stateDefine(Start, MotorData) {
    // ASSERT_TRUE(eventdata);

    // Get pointer to the instance data and update currentSpeed
    Motor* instance = statemachineGetInstance(Motor);
    instance->currentspeed = eventdata->speed;

    // Set initial motor speed processing here
    printf("%s Start: %d\n", statemachine->name, instance->currentspeed);
}

stateDefine(ChangeSpeed, MotorData) {
    // ASSERT_TRUE(eventdata);

    // Get pointer to the instance data and update currentSpeed
    Motor* instance = statemachineGetInstance(Motor);
    instance->currentspeed = eventdata->speed;

    // Perform the change motor speed here
    printf("%s ChangeSpeed: %d\n", statemachine->name, instance->currentspeed);
}

// Get current speed
getdecl(motorGetSpeed, i32);
getdef(motorGetSpeed, i32) {
    Motor* instance = statemachineGetInstance(Motor);
    return instance->currentspeed;
}


static Motor motor0;
static Motor motor1;

statemachineDefine(motor0statemachine, &motor0);
statemachineDefine(motor1statemachine, &motor1);

// stateDefine(motor0statemachine, &motor0);
// stateDefine(motor1statemachine, &motor1);
