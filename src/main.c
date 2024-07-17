#include <core.h>

#include "vec3.h"

#define HKARRAY_IMPL
#include <hkArray.h>

#define HKNODE_IMPL
#include <hkNode.h>

#define HKLIST_IMPL
#include <hkList.h>

// #include "Component.h"

int main(int argc, char *argv[]) {
    //haikal@hkArray:i8
    hkArray_i8 string = hkArray_i8_create(27);
    for (int i = 0; i < string.length; ++i) {
        string.data[i] = 0b01100000 | i + 1;
    }
    string.data[string.length - 1] = '\0';
    // printf("string: %s\n", string.data);
    hkArray_i8_destroy(&string);

    //haikal@hkArray:vec3
    hkArray_vec3 *vectors = malloc(sizeof(hkArray_vec3));
    *vectors = hkArray_vec3_create(21);
    for (int i = 0; i < vectors->length; ++i) {
        vectors->data[i].x = 1.0f;
        vectors->data[i].y = (f32)i;
        vectors->data[i].z = 3.141592f;
    }
    // for (int i = 0; i < vectors->length; ++i) { printf("vectors[%d] = {%f, %f, %f}\n", i, vectors->data[i].x, vectors->data[i].y, vectors->data[i].z); }
    hkArray_vec3_destroy(vectors);

    //haikal@hkArray:i8
    hkArray_i8 arr = hkArray_i8_create(8);
    hkArray_i8_destroy(&arr);

    //haikal@hkNode:i32
    //haikal@hkList:i32
    hkList_i32 *loi = hkList_i32_create();
    hkNode_i32 *iter = NULL;
    hkNode_i32 *node = NULL;
    hkList_i32_append(loi, 11);
    hkList_i32_append(loi, 22);
    hkList_i32_append(loi, 33);
    hkList_i32_append(loi, 44);
    iter = loi->head; while (iter != NULL) { printf("loi: {%d, %p}\n", iter->data, iter->next); iter = iter->next; } printf("\n");
    node = hkList_i32_remove_at(loi, 0); if (node) { hkNode_i32_destroy(&node); }
    iter = loi->head; while (iter != NULL) { printf("loi: {%d, %p}\n", iter->data, iter->next); iter = iter->next; } printf("\n");
    node = hkList_i32_remove_at(loi, 1); if (node) { hkNode_i32_destroy(&node); }
    iter = loi->head; while (iter != NULL) { printf("loi: {%d, %p}\n", iter->data, iter->next); iter = iter->next; } printf("\n");
    node = hkList_i32_remove_at(loi, 1); if (node) { hkNode_i32_destroy(&node); }
    iter = loi->head; while (iter != NULL) { printf("loi: {%d, %p}\n", iter->data, iter->next); iter = iter->next; } printf("\n");
    hkList_i32_destroy(&loi);

    // for this to work, we need to read all the included files
    // compile_commands.json should be enough...
    // or, use a unity build and just include everything in main.c 
    // but LSP will die in Component.h...
    // Component comp = Component_create(10);
    // printf("comp.id = %d\n", comp.id);
    // Component_destroy(&comp);

    return 0;
}
