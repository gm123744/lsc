/*
 * LSC Hello World Example
 *
 * Copyright (C) 2026 gm123744
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Description:
 *   This program demonstrates printing "Hello, world" to the terminal
 *   using LSC (Linux Syscall Collection), a minimal syscall wrapper.
 *
 * Key Features:
 *   - Works without libc or standard libraries
 *   - Uses direct syscall-based output via lsc_write
 *
 * Usage:
 *   gcc -c -fno-builtin -nostdlib helloworld.c -o helloworld.o
 *   ld --defsym _start=main -nostdlib helloworld.o -o helloworld
 *
 * Output:
 *   Hello, world
 *
 * Notes:
 *   - Both lsc.h and lsc.s must be in the build directory
 *   - This example uses the struct-based interface
 *     (see write_stdout for a simpler shortcut)
 *   - Using shortcuts increases the binary size 
 *   - Compile if shortcuts used with gcc -nostartfiles -nodefaultlibs helloworld.c lsc.s -o hello
 *
 */
#define X86_64_LINUX 1 // specify backend target
#include "lsc.h"
int main(void) {
    //write 1st side of hello world
    lsc_write hello; //call write struct 
    hello.wtype = WRITE_STDOUT; //specify stdout type
    hello.dataptr = "Hello,"; //data pointer to string
    hello.datalen = 6;  //length of string
    lsc_stdout(hello); //call lsc_stdout function with pointer to struct

    //second side of hello world
    lsc_write world;
    world.wtype = WRITE_STDOUT;
    world.dataptr = " world\n";
    world.datalen = 7;  
    lsc_stdout(world);
    exit_success(0); //exit program
}
// Optional: bypass struct and use shortcut:
// write_stdout("Hello, world\n", 13); 
