#define X86_64_LINUX 1
#include "lsc.h"

int main() {
    lsc_write write;
    write.wtype = WRITE_STDOUT;
    write.dataptr = "Hello, World!\n";
    write.datalen = 14;  
    lsc_stdout(&write);
    return 0;
}
