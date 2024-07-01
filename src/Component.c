#include "Component.h"

Component componentCreate(int id) {
    Component result = {0};
    result.id = id;
    result.points = hkArray_i32_create(10);
}

void componentDestroy(Component *comp) {
    hkArray_i32_destroy(&comp->points);
}
