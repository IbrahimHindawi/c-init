#define CORE_IMPL
#include <core.h>

#include <Arena.h>

#include "vec3.h"

#define HKARRAY_IMPL
#include <hkArray.h>

#define HKNODE_IMPL
#include <hkNode.h>

#define HKLIST_IMPL
#include <hkList.h>

#define HKBINODE_IMPL
#include <hkBiNode.h>

#define HKDLIST_IMPL
#include <hkDList.h>

#define HKQUEUE_IMPL
#include <hkQueue.h>

#define HKSTACK_IMPL
#include <hkStack.h>

// #include "Component.h"

void hkArray_test() {
    //haikal@hkArray:i8:p
    hkArray_i8 string = hkArray_i8_create(27);
    for (int i = 0; i < string.length; ++i) {
        string.data[i] = 0b01100000 | i + 1;
    }
    string.data[string.length - 1] = '\0';
    printf("string: %s\n", string.data);
    hkArray_i8_destroy(&string);

    //haikal@hkArray:vec3:s
    hkArray_vec3 vectors = hkArray_vec3_create(21);
    for (int i = 0; i < vectors.length; ++i) {
        vectors.data[i].x = 1.0f;
        vectors.data[i].y = (f32)i;
        vectors.data[i].z = 3.141592f;
    }
    for (int i = 0; i < vectors.length; ++i) { printf("vectors[%d] = {%f, %f, %f}\n", i, vectors.data[i].x, vectors.data[i].y, vectors.data[i].z); }
    hkArray_vec3_destroy(&vectors);

    //haikal@hkArray:i8:p
    hkArray_i8 arr = hkArray_i8_create(8);
    hkArray_i8_destroy(&arr);
}

void hkList_test() {
    //haikal@hkNode:i32:p
    //haikal@hkList:i32:p
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
}

void hkDList_test() {
    //haikal@hkBiNode:i32:p
    //haikal@hkDList:i32:p
    hkDList_i32 *loi = hkDList_i32_create();
    hkBiNode_i32 *iter = NULL;
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
}

void hkQueue_test() {
    //haikal@hkQueue:i32:p
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
}

void hkStack_test() {
    //haikal@hkStack:i32:p
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

int main(int argc, char *argv[]) {
    hkArray_test();
    // hkList_test();
    // hkDList_test();
    // hkQueue_test();
    // hkStack_test();
    // Arena_test();
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
