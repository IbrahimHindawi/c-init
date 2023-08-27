#include "core.h"
#include "fileops.h"

// char fops_buffer[1024];

int main(int argc, char *argv[]) {
    fops_read("C:\\devel\\c-init\\test.txt");
    printf("%s", fops_buffer);
    return 0;
}
