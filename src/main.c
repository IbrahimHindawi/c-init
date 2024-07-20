#define CORE_IMPL
#include <core.h>

#include "vec3.h"

#define HKARRAY_IMPL
#include <hkArray.h>

#define HKNODE_IMPL
#include <hkNode.h>

#define HKLIST_IMPL
#include <hkList.h>

#define HKQUEUE_IMPL
#include <hkQueue.h>

#define HKSTACK_IMPL
#include <hkStack.h>

// #include "Component.h"

void hkArray_test() {
    //haikal@hkArray:i8
    hkArray_i8 string = hkArray_i8_create(27);
    for (int i = 0; i < string.length; ++i) {
        string.data[i] = 0b01100000 | i + 1;
    }
    string.data[string.length - 1] = '\0';
    printf("string: %s\n", string.data);
    hkArray_i8_destroy(&string);

    //haikal@hkArray:vec3
    hkArray_vec3 *vectors = malloc(sizeof(hkArray_vec3));
    *vectors = hkArray_vec3_create(21);
    for (int i = 0; i < vectors->length; ++i) {
        vectors->data[i].x = 1.0f;
        vectors->data[i].y = (f32)i;
        vectors->data[i].z = 3.141592f;
    }
    for (int i = 0; i < vectors->length; ++i) { printf("vectors[%d] = {%f, %f, %f}\n", i, vectors->data[i].x, vectors->data[i].y, vectors->data[i].z); }
    hkArray_vec3_destroy(vectors);

    //haikal@hkArray:i8
    hkArray_i8 arr = hkArray_i8_create(8);
    hkArray_i8_destroy(&arr);
}

void hkList_test() {
    //haikal@hkNode:i32
    //haikal@hkList:i32
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

void hkQueue_test() {
    //haikal@hkQueue:i32
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
    //haikal@hkStack:i32
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

int main(int argc, char *argv[]) {
    // tests
    // hkArray_test();
    // hkList_test();
    // hkQueue_test();
    hkStack_test();

    // TODO: fix code generation for external headers
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
