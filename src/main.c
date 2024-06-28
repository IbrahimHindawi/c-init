#include <core.h>
#include <hkArray.h>

#include "fileops.h"

int main(int argc, char *argv[]) {
    hkArray_i8 string = hkarray_i8_create(10);
    for (int i = 0; i < string.length; ++i) {
        string.data[i] = 0b01100000 | i + 1;
    }
    string.data[string.length - 1] = '\0';
    printf("%s\n", string.data);
    hkarray_i8_destroy(&string);
    return 0;
}
