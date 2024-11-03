#pragma once
#include <core.h>

structdef(TypeX) {
    u32 id;
    char *name;
};

void TypeXCreate(TypeX *tx, u32 id, char *name);
TypeX *TypeXCreate2(u32 id, char *name);

// void TypeXCreate(TypeX *, u32, char *);
// TypeX *TypeXCreate2(u32, char *);
