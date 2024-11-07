#pragma once
#include <core.h>

structdecl(TypeX);

structdef(hkArray_TypeX) {
    TypeX *data;
    u64 len;
    u64 cap;
};

void hkArray_TypeX_create(TypeX *tx, u32 id, char *name);
