#include <core.h>

void hkArray_TypeX_reserve(hkArray_TypeX *array, u64 len) {
    array->data = calloc(len, sizeof(TypeX));
    array->len = len;
    array->cap = len;
}
