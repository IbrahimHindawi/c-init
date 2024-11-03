#include "TypeX.h"

void TypeXCreate(TypeX *tx, u32 id, char *name) {
    tx->id = id;
    tx->name = name;
}

TypeX *TypeXCreate2(u32 id, char *name) {
    TypeX *tx = malloc(sizeof(TypeX));
    tx->id = id;
    tx->name = name;
    return tx;
}

