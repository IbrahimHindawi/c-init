#pragma once
#include <core.h>

enum {
    event_ignored = 0xFE,
    cannot_happen = 0xFF
};

typedef void NoEventData;

structdecl(StateMachine);
typedef void (*StateProc)(StateMachine *statemachine, void *eventdata);
typedef bool (*GuardProc)(StateMachine *statemachine, void *eventdata);
typedef void (*EntryProc)(StateMachine *statemachine, void *eventdata);
typedef void (*ExitProc)(StateMachine *statemachine);

structdef(State) {
    StateProc stateproc;
};

structdef(StateEx) {
    StateProc stateproc;
    GuardProc guardproc;
    EntryProc entryproc;
    ExitProc exitproc;
};

structdef(StateMachineImmut) {
    const char *name;
    const u8 maxstates;
    const State *statemap;
    const StateEx *statemapex;
};

structdef(StateMachine) {
    const char *name;
    void *instance;
    u8 newstate;
    u8 currentstate;
    bool eventgenerated;
    void *eventdata;
};

#define statemachineEvent(statemachinename, eventproc, eventdataname) \
    eventproc(&statemachinename##object, eventdataname)
#define statemachineGet(statemachinename, procname) \
    procname(&statemachinename##object)

#define statemachineInternalEvent(newstate, eventdataname) \
    statemachineInternalEvent_(statemachine, newstate, eventdataname)
#define statemachineGetInstance(instancename) \
    (instancename *)(statemachine->instance)

void statemachineExternalEvent_(StateMachine *statemachine, const StateMachineImmut *statemachineimmut, u8 newstate, void *eventdata);
void statemachineInternalEvent_(StateMachine *statemachine, u8 newstate, void *eventdata);
void statemachineStateEngine_(StateMachine *statemachine, const StateMachineImmut* statemachineimmut);
void statemachineStateEngineEx_(StateMachine *statemachine, const StateMachineImmut* statemachineimmut);

#define statemachineDeclare(statemachinename) \
    extern StateMachine statemachinename##object;
#define statemachineDefine(statemachinename, instance) \
    StateMachine statemachinename##object = { #statemachinename, instance, 0, 0, 0, 0 };

#define eventDeclare(eventproc, eventdataname) \
    void eventproc(StateMachine *statemachine, eventdataname *eventdata)
#define eventDefine(eventproc, eventdataname) \
    void eventproc(StateMachine *statemachine, eventdataname *eventdata)

#define stateDeclare(statename, eventdataname) \
    static void state##statename(StateMachine *statemachine, eventdataname *eventdata)
#define stateDefine(statename, eventdataname) \
    static void state##statename(StateMachine *statemachine, eventdataname *eventdata)

#define statemapBegin(name) static const State name##StateMap[] = { 

#define statemapEntry(_stateFunc_) { (StateProc)_stateFunc_ },

#define statemapEnd(name) \
}; static const StateMachineImmut name##Immut = { #name, \
    (sizeofarray(name##StateMap)), name##StateMap, {0} };

#define transitionmapBegin \
    static const u8 transitions[] = { 

#define transitionmapEntry(_entry_)  _entry_,

#define transitionmapEnd(name, eventdata) \
    }; \
    statemachineExternalEvent_(statemachine, &name##Immut, transitions[statemachine->currentstate], eventdata); \
    assert((sizeof(transitions)/sizeof(u8)) == (sizeof(name##StateMap)/sizeof(name##StateMap[0])));

#define getdecl(_getFunc_, _getData_) \
    _getData_ _getFunc_(StateMachine* statemachine);

#define getdef(_getFunc_, _getData_) \
    _getData_ _getFunc_(StateMachine* statemachine)


void statemachineExternalEvent_(StateMachine* statemachine, const StateMachineImmut* statemachineimmut, u8 newstate, void* eventdata);
void statemachineInternalEvent_(StateMachine* statemachine, u8 newstate, void* eventdata);
void statemachineStateEngine_(StateMachine* statemachine, const StateMachineImmut* statemachineimmut);
