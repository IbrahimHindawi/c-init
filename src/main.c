#include <core.h>

#include "vec3.h"

#define HKARRAY_IMPL
#include <hkArray.h>

// #define HKLIST_IMPL
// #include <hkList.h>

// #include "Component.h"

int main(int argc, char *argv[]) {
    //haikal@hkArray:i8
    hkArray_i8 string = hkArray_i8_create(10);
    for (int i = 0; i < string.length; ++i) {
        string.data[i] = 0b01100000 | i + 1;
    }
    string.data[string.length - 1] = '\0';
    printf("%s\n", string.data);
    hkArray_i8_destroy(&string);

    //haikal@hkArray:vec3
    hkArray_vec3 vectors = hkArray_vec3_create(21);
    for (int i = 0; i < vectors.length; ++i) {
        vectors.data[i].x = 1.0f;
        vectors.data[i].y = 0.0f;
        vectors.data[i].z = 3.141592f;
    }
    for (int i = 0; i < vectors.length; ++i) {
        printf("vector[%d] = {%f, %f, %f}\n", 
            i,
            vectors.data[i].x,
            vectors.data[i].y,
            vectors.data[i].z);
    }
    hkArray_vec3_destroy(&vectors);
    //haikal@hkArray:f32

    // Component comp = componentCreate(10);
    // printf("comp.id = %d\n", comp.id);
    // componentDestroy(&comp);

    //haikal@hkArray:i8
    hkArray_i8 arr = hkArray_i8_create(8);
    hkArray_i8_destroy(&arr);
    printf("what");

    return 0;
}
