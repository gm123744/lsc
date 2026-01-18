// lsc.h - v0.01 - public domain
// authored from 2025-2026 by GM_11 || gm123744
//
// =======================================================================
//
//    NO SECURITY GUARANTEE -- DO NOT USE THIS TO MAKE DANGEROUS CODE
//
// This library does not have any sefety measures. It is strongly suggested
// to not make malicius code the whole library is made for education and 
// system developers with low level syntax while having a lot of control.
//
// =======================================================================
//
//   This library wraps all of the 467 syscalls the linux kernel has into 
//   a simple single header library that allows the programmer to write 
//   with minimal recourses.
//
// CONTRIBUTORS
// VERSION HISTORY
//   (0.01) 14/1/2026 First public release
//   (0.02) 16/1/2026 Printing added (stable) i/o added (unstable)
//   Full history can be found at the end of this file.
//   (0.03) 17/1/2026 Complete rework of the i/o (stable) + execve (unstable) new function exit_success (prevents i/o operations from segaulting)
//   (0.03) 18/1/2026 Execve (Stable) 
//
//   LICENSE
//   See license file for information.
//
// USAGE
//   Include this file in whatever places need to refer to it. In ONE C/C++
//   #define X86_64_LINUX
//   #define X86_32_LINUX
//   before the #include of this file. This expands out the actual
//   implementation into that C/C++ file.
// NOTES:
//   Have fun learning this low level api!
//   In case you are going to use the struct way to make 
//   your programms make sure to not compile it with lsc.s
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
////
#ifndef LSC_H
#define LSC_H

typedef struct lsc_write {
    int wtype; 
    const char* dataptr;
    long datalen;
} lsc_write;
typedef struct lsc_read {
    int rtype;
    char* dataptr;
    long datalen;
} lsc_read;

#define WRITE_STDOUT 1
#define READ_STDIN 1
#define EXECVE 59
/* For passing struct by VALUE */
#define lsc_stdout(str_struct) do { \
    lsc_write __data = (str_struct); \
    asm volatile ( \
        "mov $1, %%rax\n\t" \
        "mov $1, %%rdi\n\t" \
        "mov %0, %%rsi\n\t" \
        "mov %1, %%rdx\n\t" \
        "syscall\n\t" \
        : /* no outputs */ \
        : "r" (__data.dataptr), "r" (__data.datalen) \
        : "rax", "rdi", "rsi", "rdx", "rcx", "r11", "memory" \
    ); \
} while (0)

/* For passing struct by VALUE */
#define lsc_stdin(read_struct) do { \
    lsc_read __data = (read_struct); \
    asm volatile ( \
        "mov $0, %%rax\n\t" \
        "mov $0, %%rdi\n\t" \
        "mov %0, %%rsi\n\t" \
        "mov %1, %%rdx\n\t" \
        "syscall\n\t" \
        : /* no outputs */ \
        : "r" (__data.dataptr), "r" (__data.datalen) \
        : "rax", "rdi", "rsi", "rdx", "rcx", "r11", "memory" \
    ); \
} while (0)
static inline void exit_success(int zero) {
    asm volatile ( // ignore
        "mov $60, %%rax\n\t"
        "syscall\n\t"
        :
        : "D" ((long)zero)
        : "rax", "rcx", "r11"
    );
}
typedef struct lsc_execve {
    int etype;
    const char* filename;
    const char* arg;
} lsc_execve;

#define execve(execstruct) do { \
    lsc_execve __data = (execstruct); \
    asm volatile ( \
        "sub $32, %%rsp\n\t"\
        "movq $0, 24(%%rsp)\n\t" /*NULL*/\
        "movq %1, 16(%%rsp)\n\t" /* Argument */\
        "movq %0, 8(%%rsp)\n\t" /* Program name */\
        "lea 8(%%rsp), %%rsi\n\t"\
        "mov %0, %%rdi\n\t" /* filename */\
        "xor %%rdx, %%rdx\n\t" /* envp = NULL */\
        "mov $59, %%rax\n\t"\
        "syscall\n\t" \
        "add $32, %%rsp\n\t"\
        : /* no outputs */ \
        : "r"(__data.filename), "r"(__data.arg) \
        : "rax", "rdi", "rsi", "rdx", "memory", "cc" \
    ); \
} while (0)
#ifdef X86_64_LINUX
extern void system(const char* command, const char* path);
extern void write_stdout(const char* buf, int len);
extern void stdin_read(char* buf, int len);
#endif
#endif // LSC_H
// VERSION HISTORY
//   (0.01) 14/1/2026 First public release
//   (0.02) 16/1/2026 Printing added (stable) i/o added (unstable)
//   Full history can be found at the end of this file.
//   (0.03) 17/1/2026 Complete rework of the i/o (stable) + execve (unstable) new function exit_success (prevents i/o operations from segaulting)
//   (0.03) 18/1/2026 Execve (Stable) 

