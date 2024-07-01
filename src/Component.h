#pragma once
#include <core.h>
// #include "vec3.h"
#include <hkArray_i32.h>

structdef(Component) {
    i32 id;
    hkArray_i32 points;
};

Component componentCreate(int id);
void componentDestroy(Component *comp);
