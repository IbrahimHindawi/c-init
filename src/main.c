#define CORE_IMPL
#include <core.h>

#include <Arena.h>
#include "StateMachine/statemachine.h"


// #include "hkArray_TypeX.h"
// #include "TypeX.h"
// #include "TypeX.c"
// #include "hkArray_TypeX.c"

// codegen note:
// for containers that have value types eg `T`, 
// the type must be included before the headers.
// this is because the container expects to know the type in it's struct.
//
// for containers that have pointer types eg `T *`, 
// the type can be included before or after the headers.
// this is because the container has `T` forward declared.
//
// for types that include a container eg `struct T { hkArray_T arr; };`
// the type must be included after the header.
// this is because the type needs to know the container definition.

#include "vec3.h"

#include <hkArray.h>
#include <hkBiNode.h>
#include <hkDList.h>
#include <hkList.h>
#include <hkNode.h>
#include <hkStack.h>
#include <hkQueue.h>

// haikal@hkArray:Rec:s
// haikal@hkHashMap:Rec:s
#include "Rec.h"
#include <hkHashMap.h>

#include <hkArray.c>
#include <hkBiNode.c>
#include <hkDList.c>
#include <hkHashMap.c>
#include <hkList.c>
#include <hkNode.c>
#include <hkStack.c>
#include <hkQueue.c>

#include "Component.h"

// haikal@hkHashMap:i32:p
// haikal@hkHashMap:vec3:s

void hkArray_test() {
    printf("hkArray_test:\n");
    //haikal@hkArray:i8:p
    hkArray_i8 string = hkArray_i8_create(27);
    for (int i = 0; i < string.length; ++i) {
        string.data[i] = 0b01100000 | i + 1;
    }
    string.data[string.length - 1] = '\0';
    printf("string: %s\n", string.data);
    hkArray_i8_destroy(&string);

    //haikal@hkArray:vec3:s
    hkArray_vec3 vectors = hkArray_vec3_create(10);
    for (int i = 0; i < vectors.length; ++i) {
        vectors.data[i].x = 1.0f;
        vectors.data[i].y = (f32)i;
        vectors.data[i].z = 3.141592f;
    }
    for (int i = 0; i < vectors.length; ++i) { 
        printf("vectors[%d] = {%f, %f, %f}\n", i, vectors.data[i].x, vectors.data[i].y, vectors.data[i].z); 
    }
    hkArray_vec3_destroy(&vectors);

    hkArray_i8 arr = {0};
    hkArray_i8_append(&arr, 127);
    hkArray_i8_append(&arr, 23);
    hkArray_i8_append(&arr, 11);
    hkArray_i8_append(&arr, 8);
    for (int i = 0; i < arr.length; ++i) { 
        printf("arr[%d] = %d\n", i, arr.data[i]); 
    }
    hkArray_i8_destroy(&arr);
    printf("\n");
}

void hkList_test() {
    printf("hkList_test:\n");
    // haikal@hkNode:i32:p
    // haikal@hkList:i32:p
    hkList_i32 *loi = hkList_i32_create();
    hkNode_i32 *iter = NULL;
    hkNode_i32 *node = NULL;
    hkList_i32_append(loi, 11);
    hkList_i32_append(loi, 22);
    hkList_i32_append(loi, 33);
    hkList_i32_append(loi, 44);
    hkList_i32_print(loi);
    node = hkList_i32_remove_at(loi, 0); if (node) { hkNode_i32_destroy(&node); }
    hkList_i32_print(loi);
    node = hkList_i32_remove_at(loi, 1); if (node) { hkNode_i32_destroy(&node); }
    hkList_i32_print(loi);
    node = hkList_i32_remove_at(loi, 1); if (node) { hkNode_i32_destroy(&node); }
    hkList_i32_print(loi);
    hkList_i32_destroy(&loi);
    printf("\n");
}

void hkDList_test() {
    printf("hkDList_test:\n");
    // haikal@hkBiNode:i32:p
    // haikal@hkDList:i32:p
    hkDList_i32 *loi = hkDList_i32_create();
    hkBiNode_i32 *node = NULL;
    hkDList_i32_append(loi, 11);
    hkDList_i32_append(loi, 22);
    hkDList_i32_append(loi, 33);
    hkDList_i32_append(loi, 44);
    hkDList_i32_print(loi);
    node = hkDList_i32_remove_at(loi, 0); if (node) { hkBiNode_i32_destroy(&node); }
    hkDList_i32_print(loi);
    node = hkDList_i32_remove_at(loi, 1); if (node) { hkBiNode_i32_destroy(&node); }
    hkDList_i32_print(loi);
    node = hkDList_i32_remove_at(loi, 1); if (node) { hkBiNode_i32_destroy(&node); }
    hkDList_i32_print(loi);
    hkDList_i32_destroy(&loi);
    printf("\n");
}

void hkQueue_test() {
    printf("hkQueue_test:\n");
    // haikal@hkQueue:i32:p
    hkQueue_i32 *q = hkQueue_i32_create();
    hkQueue_i32_print(q);
    hkQueue_i32_enqueue(q, 0);
    hkQueue_i32_print(q);
    hkQueue_i32_enqueue(q, 1);
    hkQueue_i32_print(q);
    hkQueue_i32_enqueue(q, 2);
    hkQueue_i32_print(q);

    hkNode_i32 *node_i32 = NULL;
    i32 value = 0;

    node_i32 = hkQueue_i32_dequeue(q);
    value = hkNode_i32_value(node_i32);
    printf("node value: %d\n", value);
    hkNode_i32_destroy(&node_i32);
    hkQueue_i32_print(q);

    node_i32 = hkQueue_i32_dequeue(q);
    value = hkNode_i32_value(node_i32);
    printf("node value: %d\n", value);
    hkNode_i32_destroy(&node_i32);
    hkQueue_i32_print(q);

    node_i32 = hkQueue_i32_dequeue(q);
    value = hkNode_i32_value(node_i32);
    printf("node value: %d\n", value);
    hkNode_i32_destroy(&node_i32);
    hkQueue_i32_print(q);

    node_i32 = hkQueue_i32_dequeue(q);
    value = hkNode_i32_value(node_i32);
    printf("node value: %d\n", value);
    hkNode_i32_destroy(&node_i32);
    hkQueue_i32_print(q);

    hkQueue_i32_destroy(&q);
    printf("\n");
}

void hkStack_test() {
    printf("hkStack_test:\n");
    // haikal@hkStack:i32:p
    hkStack_i32 *stack = hkStack_i32_create();
    hkNode_i32 *node = NULL;
    hkStack_i32_push(stack, 32);
    hkStack_i32_push(stack, 12);
    hkStack_i32_push(stack, 22);
    hkStack_i32_push(stack, 42);
    hkStack_i32_print(stack);

    node = hkStack_i32_pop(stack);
    printf("%d\n", hkNode_i32_value(node));
    hkStack_i32_print(stack);

    node = hkStack_i32_pop(stack);
    printf("%d\n", hkNode_i32_value(node));
    hkStack_i32_print(stack);

    node = hkStack_i32_pop(stack);
    printf("%d\n", hkNode_i32_value(node));
    hkStack_i32_print(stack);

    node = hkStack_i32_pop(stack);
    printf("%d\n", hkNode_i32_value(node));
    hkStack_i32_print(stack);

    node = hkStack_i32_pop(stack);
    printf("%d\n", hkNode_i32_value(node));
    hkStack_i32_print(stack);

    hkStack_i32_destroy(&stack);
    printf("\n");
}

void hkHashMap_test() {
    printf("hkHashMap_test:\n");
    hkHashMap_i32 *hashmap = hkHashMap_i32_create();
    printf("hashmap length = %llu\n", hkHashMap_i32_length(hashmap));
    if (!hashmap) {
        printf("nomem\n");
        exit(-1);
    }
    if (!hkHashMap_i32_set(hashmap, "dog", 3)) {
        printf("nomem\n");
        exit(-1);
    }
    i32 *result = hkHashMap_i32_get(hashmap, "dog");
    if (result) {
        printf("key = %s, val = %d\n", "dog", *result);
    }
    printf("hashmap length = %llu\n", hkHashMap_i32_length(hashmap));
    hkHashMap_i32_destroy(hashmap);

    hkHashMap_vec3 *hashmapvec = hkHashMap_vec3_create();
    printf("hashmapvec length = %llu\n", hkHashMap_vec3_length(hashmapvec));
    if (!hashmapvec) {
        printf("nomem\n");
        exit(-1);
    }
    if (!hkHashMap_vec3_set(hashmapvec, "dog", (vec3){1.f, 0.f, 0.f})) {
        printf("nomem\n");
        exit(-1);
    }
    printf("hashmapvec length = %llu\n", hkHashMap_vec3_length(hashmapvec));
    if (!hkHashMap_vec3_set(hashmapvec, "frog", (vec3){0.f, 1.f, 0.f})) {
        printf("nomem\n");
        exit(-1);
    }
    printf("hashmapvec length = %llu\n", hkHashMap_vec3_length(hashmapvec));
    vec3 *resultvec = hkHashMap_vec3_get(hashmapvec, "dog");
    if (resultvec) {
        printf("key = %s, val = {%f, %f, %f}\n", "dog", resultvec->x, resultvec->y, resultvec->z);
    }
    printf("hashmapvec length = %llu\n", hkHashMap_vec3_length(hashmapvec));
    printf("hash iterator...\n");
    hkHashMapIterator_vec3 itvec = hkHashMapIterator_vec3_create(hashmapvec);
    while (hkHashMapIterator_vec3_next(&itvec)) {
        printf("key = %s, val = {%f, %f, %f}\n", itvec.key, itvec.val.x, itvec.val.y, itvec.val.z);
    }
    hkHashMap_vec3_destroy(hashmapvec);
    printf("\n");
}

structdef(Payload) {
    i32 id;
    i32 mx;
    i8 *str;
};

structdef(vec4i8) { i8 x; i8 y; i8 z; i8 w; };

void Arena_test() {
    Arena arena = {0};
    arenaInit(&arena, store);

    const i32 len = 4;
    const i32 els = sizeof(f32);
    const i32 allocsize = els * len;
    f32 *nums = arenaPush(&arena, allocsize);
    for (i32 i = 0; i < len; ++i) {
        nums[i] = (f32)(i + 1);
    }
    for (i32 i = 0; i < len; ++i) {
        printf("%f ", nums[i]);
    }
    printf("\n");

    u8 *ptr = (u8 *)nums;
    for (i32 i = 0; i < allocsize; ++i) {
        printf("%02x ", ptr[i]);
    }
    printf("\n");

    i8 *str0 = strAlloc(&arena, "this is a te");
    i8 *str1 = strAlloc(&arena, "st string to");
    i8 *str2 = strAlloc(&arena, "alloc bytes.");
    printf("%s\n", str0);
    printf("%s\n", str1);
    printf("%s\n", str2);

    strDealloc(&arena, str2);
    str2 = strAlloc(&arena, "fortitude");
    printf("%s\n", str0);
    printf("%s\n", str1);
    printf("%s\n", str2);

    Payload *pld = arenaPushStruct(&arena, Payload);
    pld->id = 0xDEADBEEF;
    pld->mx = 0xCAFEBABE;
    pld->str = "Name0";
    arenaPop(&arena, sizeof(Payload));
    pld = arenaPushStruct(&arena, Payload);
    pld->id = 0xFFFFFFFF;
    pld->mx = 0xFFFFFFFF;
    pld->str = "Name0";
    arenaPop(&arena, sizeof(Payload));

    arenaClear(&arena);

    // vec4i8 *vs = arenaPushArrayZero(&arena, vec4i8, 32);
    const i32 npts = 32;
    vec4i8 *vs = arenaPushArray(&arena, vec4i8, npts);
    for (i32 i = 0; i < npts; ++i) {
        vs[i].x = 0xAA;
        vs[i].y = 0xBB;
        vs[i].z = 0xCC;
        vs[i].w = 0xDD;
    }
    arenaPopArray(&arena, vec4i8, npts);

    printf("Memory Dump: %d bytes allocated.\n", N);
    printf("%p: ", store);
    for (i32 i = 0; i < N; ++i) {
        if(i % 8 == 0 && i != 0) {
            printf("\n");
            printf("%p: ", &store[i]);
        }
        printf("%02x ", store[i]);
    }
    arenaClear(&arena);
}

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

int main(int argc, char *argv[]) {
    // hkArray_test();
    // hkHashMap_test();
    // hkList_test();
    // hkDList_test();
    // hkQueue_test();
    // hkStack_test();
    // Arena_test();
    // StateMachine_test();

    MotorData *data = {0};
    data = malloc(sizeof(MotorData));
    data->speed = 100;
    statemachineEvent(motor0statemachine, motorSetSpeed, data);

    data->speed = 200;
    statemachineEvent(motor0statemachine, motorSetSpeed, data);

    i32 currentspeed = statemachineGet(motor1statemachine, motorGetSpeed);
    statemachineEvent(motor1statemachine, motorHalt, NULL);

    // TypeX *tx = malloc(sizeof(TypeX));
    // TypeXCreate(tx, 666, "Hades");
    // printf("tx = { %d, %s }\n", tx->id, tx->name);
    // TypeX *tx2 = TypeXCreate2(777, "Zeus");
    // printf("tx2 = { %d, %s }\n", tx2->id, tx2->name);

    // hkArray_TypeX arr = {0};
    // hkArray_TypeX_reserve(&arr, 16);

    // TODO: fix code gen for external files
    // for this to work, we need to read all the included files
    // compile_commands.json should be enough...
    // or, use a unity build and just include everything in main.c 
    // but LSP will die in Component.h...
    // ===========================================================
    // Component comp = Component_create(10);
    // printf("comp.id = %d\n", comp.id);
    // Component_destroy(&comp);

    return 0;
}
