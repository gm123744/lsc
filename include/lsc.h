// lsc.h - v0.04 - public domain
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
//   This library provides a low level interface to linux syscalls for
//   x86-64 and x86-32 architectures. It is made to be as clear as possible
//
// CONTRIBUTORS
// VERSION HISTORY
//   (0.01) 14/1/2026 First public release
//   (0.02) 16/1/2026 Printing added (stable) i/o added (unstable)
//   Full history can be found at the end of this file.
//   (0.03) 17/1/2026 Complete rework of the i/o (stable) + execve (unstable) new function exit_success (prevents i/o operations from segaulting)
//   (0.03) 18/1/2026 Execve (Stable) 
//   (0.04) 21/1/2026 Added socket syscalls (unstable) 
//   (0.04) 22/1/2026 integer handling (unstable) file i/o syscalls (unstable)
//   (0.04) 23/1/2026 Made socket syscalls stable + integer handling stable + file i/o syscalls stable
//   (0.04) 24/1/2026 added 32bit support for write and read syscalls
//   (0.04) 25/1/2026 added 32bit support for execve syscall
//   (0.04) 26/1/2026 added 32bit support for file i/o syscalls
//   (0.04) 27/1/2026 added 32bit support for socket syscalls
//   (0.04) 28/1/2026 added 32bit support for integer handling
//   (0.04) 29/1/2026 32bit support bug fixes 
//   (0.04) 30/1/2026 Complete 32bit support for all syscalls
//   (0.04) 31/1/2026 testing (sockets unstable)
//
//   LICENSE
//   See license file for information.~
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

/* ==================== BASE TYPES ==================== */

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

typedef struct lsc_execve {
    int etype;
    const char* filename;
    const char* arg;
} lsc_execve;

/* ==================== FILE I/O TYPES ==================== */

typedef struct lsc_open {
    int otype;
    const char* path;
    int flags;
    int mode;
} lsc_open;

typedef struct lsc_close {
    int ctype;
    int fd;
} lsc_close;

typedef struct lsc_lseek {
    int ltype;
    int fd;
    long offset;
    int whence;
} lsc_lseek;

typedef struct lsc_stat {
    int stype;
    const char* path;
    void* statbuf;  /* struct stat* */
} lsc_stat;

/* ==================== SOCKET TYPES ==================== */

typedef struct lsc_socket {
    int stype;
    int domain;
    int type;
    int protocol;
} lsc_socket;

typedef struct lsc_bind {
    int btype;
    int sockfd;
    const void* addr;
    int addrlen;
} lsc_bind;

typedef struct lsc_connect {
    int ctype;
    int sockfd;
    const void* addr;
    int addrlen;
} lsc_connect;

typedef struct lsc_listen {
    int ltype;
    int sockfd;
    int backlog;
} lsc_listen;

typedef struct lsc_accept {
    int atype;
    int sockfd;
    void* addr;
    int* addrlen;
} lsc_accept;

typedef struct lsc_send {
    int stype;
    int sockfd;
    const void* buf;
    long len;
    int flags;
} lsc_send;

typedef struct lsc_recv {
    int rtype;
    int sockfd;
    void* buf;
    long len;
    int flags;
} lsc_recv;

/* ==================== INTEGER HANDLING ==================== */

typedef struct lsc_int {
    int itype;
    long value;
    char* buffer;  /* For string conversion output */
    int base;      /* Base for conversion (10, 16, etc) */
} lsc_int;

/* ==================== CONSTANTS ==================== */

/* File descriptors */
#define STDIN 0
#define STDOUT 1
#define STDERR 2

/* File open flags (simplified) */
#define O_RDONLY  0
#define O_WRONLY  1
#define O_RDWR    2
#define O_CREAT   64
#define O_TRUNC   512
#define O_APPEND  1024

/* Seek whences */
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

/* Socket domains */
#define AF_INET  2
#define AF_INET6 10

/* Socket types */
#define SOCK_STREAM 1
#define SOCK_DGRAM  2

/* Socket protocols */
#define IPPROTO_TCP 6
#define IPPROTO_UDP 17

/* Integer conversion types */
#define INT_TO_STRING 1
#define INT_FROM_STRING 2
#define INT_PRINT 3
/*EXECVE*/
#define EXECVE 59

/* ==================== SYSCALL MACROS ==================== */
#ifdef X86_64_LINUX
#define lsc64_stdout(str_struct) do { \
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

#define lsc64_stdin(read_struct) do { \
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

#define lsc64_execve(execstruct) do { \
    lsc_execve __data = (execstruct); \
    asm volatile ( \
        "sub $32, %%rsp\n\t"\
        "movq $0, 24(%%rsp)\n\t" \
        "movq %1, 16(%%rsp)\n\t" \
        "movq %0, 8(%%rsp)\n\t" \
        "lea 8(%%rsp), %%rsi\n\t"\
        "mov %0, %%rdi\n\t" \
        "xor %%rdx, %%rdx\n\t" \
        "mov $59, %%rax\n\t"\
        "syscall\n\t" \
        "add $32, %%rsp\n\t"\
        : /* no outputs */ \
        : "r"(__data.filename), "r"(__data.arg) \
        : "rax", "rdi", "rsi", "rdx", "memory", "cc" \
    ); \
} while (0)

/* ==================== FILE I/O SYSCALLS ==================== */

/* Open file */
#define lsc64_open(file_struct) do { \
    lsc_open __data = (file_struct); \
    asm volatile ( \
        "mov $2, %%rax\n\t" \
        "mov %0, %%rdi\n\t" \
        "mov %1, %%rsi\n\t" \
        "mov %2, %%rdx\n\t" \
        "syscall\n\t" \
        : "=a" (__data.otype) \
        : "r" (__data.path), "r" ((long)__data.flags), "r" ((long)__data.mode) \
        : "rdi", "rsi", "rdx", "rcx", "r11", "memory" \
    ); \
    (void)__data.otype; \
} while (0)

/* Close file */
#define lsc64_close(close_struct) do { \
    lsc_close __data = (close_struct); \
    asm volatile ( \
        "mov $3, %%rax\n\t" \
        "mov %0, %%rdi\n\t" \
        "syscall\n\t" \
        : /* no outputs */ \
        : "r" ((long)__data.fd) \
        : "rax", "rdi", "rcx", "r11", "memory" \
    ); \
} while (0)

/* File seek */
#define lsc64_lseek(seek_struct) do { \
    lsc_lseek __data = (seek_struct); \
    long result; \
    asm volatile ( \
        "mov $8, %%rax\n\t" \
        "mov %1, %%rdi\n\t" \
        "mov %2, %%rsi\n\t" \
        "mov %3, %%rdx\n\t" \
        "syscall\n\t" \
        : "=a" (result) \
        : "r" ((long)__data.fd), "r" (__data.offset), "r" ((long)__data.whence) \
        : "rdi", "rsi", "rdx", "rcx", "r11", "memory" \
    ); \
    (void)result; \
} while (0)

/* Read from file */
#define lsc64_readfile(read_struct) do { \
    lsc_read __data = (read_struct); \
    asm volatile ( \
        "mov $0, %%rax\n\t" \
        "mov %0, %%rdi\n\t" \
        "mov %1, %%rsi\n\t" \
        "mov %2, %%rdx\n\t" \
        "syscall\n\t" \
        : /* no outputs */ \
        : "r" ((long)__data.rtype), "r" (__data.dataptr), "r" (__data.datalen) \
        : "rax", "rdi", "rsi", "rdx", "rcx", "r11", "memory" \
    ); \
} while (0)

/* Write to file */
#define lsc64_writefile(write_struct) do { \
    lsc_write __data = (write_struct); \
    asm volatile ( \
        "mov $1, %%rax\n\t" \
        "mov %0, %%rdi\n\t" \
        "mov %1, %%rsi\n\t" \
        "mov %2, %%rdx\n\t" \
        "syscall\n\t" \
        : /* no outputs */ \
        : "r" ((long)__data.wtype), "r" (__data.dataptr), "r" (__data.datalen) \
        : "rax", "rdi", "rsi", "rdx", "rcx", "r11", "memory" \
    ); \
} while (0)

/* ==================== SOCKET SYSCALLS ==================== */

/* Create socket */
#define lsc64_socket(socket_struct) do { \
    lsc_socket __data = (socket_struct); \
    asm volatile ( \
        "mov $41, %%rax\n\t" \
        "mov %0, %%rdi\n\t" \
        "mov %1, %%rsi\n\t" \
        "mov %2, %%rdx\n\t" \
        "syscall\n\t" \
        : "=a" (__data.stype) \
        : "r" ((long)__data.domain), "r" ((long)__data.type), "r" ((long)__data.protocol) \
        : "rdi", "rsi", "rdx", "rcx", "r11", "memory" \
    ); \
    (void)__data.stype; \
} while (0)

/* Bind socket */
#define lsc64_bind(bind_struct) do { \
    lsc_bind __data = (bind_struct); \
    asm volatile ( \
        "mov $49, %%rax\n\t" \
        "mov %0, %%rdi\n\t" \
        "mov %1, %%rsi\n\t" \
        "mov %2, %%rdx\n\t" \
        "syscall\n\t" \
        : /* no outputs */ \
        : "r" ((long)__data.sockfd), "r" (__data.addr), "r" ((long)__data.addrlen) \
        : "rax", "rdi", "rsi", "rdx", "rcx", "r11", "memory" \
    ); \
} while (0)

/* Connect socket */
#define lsc64_connect(connect_struct) do { \
    lsc_connect __data = (connect_struct); \
    asm volatile ( \
        "mov $42, %%rax\n\t" \
        "mov %0, %%rdi\n\t" \
        "mov %1, %%rsi\n\t" \
        "mov %2, %%rdx\n\t" \
        "syscall\n\t" \
        : /* no outputs */ \
        : "r" ((long)__data.sockfd), "r" (__data.addr), "r" ((long)__data.addrlen) \
        : "rax", "rdi", "rsi", "rdx", "rcx", "r11", "memory" \
    ); \
} while (0)

/* Listen on socket */
#define lsc64_listen(listen_struct) do { \
    lsc_listen __data = (listen_struct); \
    asm volatile ( \
        "mov $50, %%rax\n\t" \
        "mov %0, %%rdi\n\t" \
        "mov %1, %%rsi\n\t" \
        "syscall\n\t" \
        : /* no outputs */ \
        : "r" ((long)__data.sockfd), "r" ((long)__data.backlog) \
        : "rax", "rdi", "rsi", "rcx", "r11", "memory" \
    ); \
} while (0)

/* Accept connection */
#define lsc64_accept(accept_struct) do { \
    lsc_accept __data = (accept_struct); \
    asm volatile ( \
        "mov $43, %%rax\n\t" \
        "mov %0, %%rdi\n\t" \
        "mov %1, %%rsi\n\t" \
        "mov %2, %%rdx\n\t" \
        "syscall\n\t" \
        : "=a" (__data.atype) \
        : "r" ((long)__data.sockfd), "r" (__data.addr), "r" (__data.addrlen) \
        : "rdi", "rsi", "rdx", "rcx", "r11", "memory" \
    ); \
    (void)__data.atype; \
} while (0)

/* Send data */
#define lsc64_send(send_struct) do { \
    lsc_send __data = (send_struct); \
    asm volatile ( \
        "mov $44, %%rax\n\t" \
        "mov %0, %%rdi\n\t" \
        "mov %1, %%rsi\n\t" \
        "mov %2, %%rdx\n\t" \
        "mov %3, %%r10\n\t" \
        "syscall\n\t" \
        : /* no outputs */ \
        : "r" ((long)__data.sockfd), "r" (__data.buf), "r" (__data.len), "r" ((long)__data.flags) \
        : "rax", "rdi", "rsi", "rdx", "r10", "rcx", "r11", "memory" \
    ); \
} while (0)

/* Receive data */
#define lsc64_recv(recv_struct) do { \
    lsc_recv __data = (recv_struct); \
    asm volatile ( \
        "mov $45, %%rax\n\t" \
        "mov %0, %%rdi\n\t" \
        "mov %1, %%rsi\n\t" \
        "mov %2, %%rdx\n\t" \
        "mov %3, %%r10\n\t" \
        "syscall\n\t" \
        : /* no outputs */ \
        : "r" ((long)__data.sockfd), "r" (__data.buf), "r" (__data.len), "r" ((long)__data.flags) \
        : "rax", "rdi", "rsi", "rdx", "r10", "rcx", "r11", "memory" \
    ); \
} while (0)

/* ==================== INTEGER HANDLING ==================== */

#define lsc64_print_int(int_struct) do { \
    lsc_int __data = (int_struct); \
    char __buf[32]; \
    long __val = __data.value; \
    int __neg = 0; \
    int __i = 31; \
    __buf[__i--] = '\0'; \
    if (__val < 0) { \
        __neg = 1; \
        __val = -__val; \
    } \
    if (__val == 0) { \
        __buf[__i--] = '0'; \
    } else { \
        while (__val > 0) { \
            __buf[__i--] = '0' + (__val % 10); \
            __val /= 10; \
        } \
    } \
    if (__neg) { \
        __buf[__i--] = '-'; \
    } \
    const char* __output = &__buf[__i + 1]; \
    lsc_write __write_struct = { \
        .wtype = 1, \
        .dataptr = __output, \
        .datalen = 31 - __i \
    }; \
    lsc64_stdout(__write_struct); \
} while (0)
#endif /* X86_64_LINUX */



/* ==================== 32-BIT ==================== */
#ifdef X86_32_LINUX
/* 32-bit syscalls */
#define lsc32_stdout(str_struct) do { \
    lsc_write __data = (str_struct); \
    asm volatile ( \
        "mov $4, %%eax\n\t" \
        "mov $1, %%ebx\n\t" \
        "mov %0, %%ecx\n\t" \
        "mov %1, %%edx\n\t" \
        "int $0x80\n\t" \
        : /* no outputs */ \
        : "r" (__data.dataptr), "r" (__data.datalen) \
        : "eax", "ebx", "ecx", "edx", "memory" \
    ); \
} while (0)

#define lsc32_stdin(read_struct) do { \
    lsc_read __data = (read_struct); \
    asm volatile ( \
        "mov $3, %%eax\n\t" \
        "mov $0, %%ebx\n\t" \
        "mov %0, %%ecx\n\t" \
        "mov %1, %%edx\n\t" \
        "int $0x80\n\t" \
        : /* no outputs */ \
        : "r" (__data.dataptr), "r" (__data.datalen) \
        : "eax", "ebx", "ecx", "edx", "memory" \
    ); \
} while (0)

#define lsc32_execve(execstruct) do { \
    lsc_execve __data = (execstruct); \
    asm volatile ( \
        "sub $12, %%esp\n\t" \
        "movl $0, 8(%%esp)\n\t" \
        "mov %1, %%eax\n\t" \
        "mov %%eax, 4(%%esp)\n\t" \
        "mov %0, %%eax\n\t" \
        "mov %%eax, (%%esp)\n\t" \
        "lea (%%esp), %%ecx\n\t" \
        "mov %0, %%ebx\n\t" \
        "xor %%edx, %%edx\n\t" \
        "mov $11, %%eax\n\t" \
        "int $0x80\n\t" \
        "add $12, %%esp\n\t" \
        : /* no outputs */ \
        : "r"(__data.filename), "r"(__data.arg) \
        : "eax", "ebx", "ecx", "edx", "memory" \
    ); \
} while (0)

/* File I/O Syscalls - 32-bit */
#define lsc32_open(file_struct) do { \
    lsc_open __data = (file_struct); \
    asm volatile ( \
        "mov $5, %%eax\n\t" \
        "mov %0, %%ebx\n\t" \
        "mov %1, %%ecx\n\t" \
        "mov %2, %%edx\n\t" \
        "int $0x80\n\t" \
        : "=a" (__data.otype) \
        : "r" (__data.path), "r" ((long)__data.flags), "r" ((long)__data.mode) \
        : "ebx", "ecx", "edx", "memory" \
    ); \
    (void)__data.otype; \
} while (0)

#define lsc32_close(close_struct) do { \
    lsc_close __data = (close_struct); \
    asm volatile ( \
        "mov $6, %%eax\n\t" \
        "mov %0, %%ebx\n\t" \
        "int $0x80\n\t" \
        : /* no outputs */ \
        : "r" ((long)__data.fd) \
        : "eax", "ebx", "memory" \
    ); \
} while (0)

#define lsc32_lseek(seek_struct) do { \
    lsc_lseek __data = (seek_struct); \
    long result; \
    asm volatile ( \
        "mov $19, %%eax\n\t" \
        "mov %1, %%ebx\n\t" \
        "mov %2, %%ecx\n\t" \
        "mov %3, %%edx\n\t" \
        "int $0x80\n\t" \
        : "=a" (result) \
        : "r" ((long)__data.fd), "r" (__data.offset), "r" ((long)__data.whence) \
        : "ebx", "ecx", "edx", "memory" \
    ); \
    (void)result; \
} while (0)

#define lsc32_readfile(read_struct) do { \
    lsc_read __data = (read_struct); \
    asm volatile ( \
        "mov $3, %%eax\n\t" \
        "mov %0, %%ebx\n\t" \
        "mov %1, %%ecx\n\t" \
        "mov %2, %%edx\n\t" \
        "int $0x80\n\t" \
        : /* no outputs */ \
        : "r" ((long)__data.rtype), "r" (__data.dataptr), "r" (__data.datalen) \
        : "eax", "ebx", "ecx", "edx", "memory" \
    ); \
} while (0)

#define lsc32_writefile(write_struct) do { \
    lsc_write __data = (write_struct); \
    asm volatile ( \
        "mov $4, %%eax\n\t" \
        "mov %0, %%ebx\n\t" \
        "mov %1, %%ecx\n\t" \
        "mov %2, %%edx\n\t" \
        "int $0x80\n\t" \
        : /* no outputs */ \
        : "r" ((long)__data.wtype), "r" (__data.dataptr), "r" (__data.datalen) \
        : "eax", "ebx", "ecx", "edx", "memory" \
    ); \
} while (0)

#define lsc32_socket(socket_struct) do { \
    lsc_socket __data = (socket_struct); \
    asm volatile ( \
        "mov $102, %%eax\n\t" \
        "mov $1, %%ebx\n\t" \
        "mov %0, %%ecx\n\t" \
        "int $0x80\n\t" \
        : "=a" (__data.stype) \
        : "r" ((long)__data.domain), "r" ((long)__data.type), "r" ((long)__data.protocol) \
        : "ebx", "ecx", "memory" \
    ); \
    (void)__data.stype; \
} while (0)

#define lsc32_bind(bind_struct) do { \
    lsc_bind __data = (bind_struct); \
    asm volatile ( \
        "mov $102, %%eax\n\t" \
        "mov $2, %%ebx\n\t" \
        "mov %0, %%ecx\n\t" \
        "int $0x80\n\t" \
        : /* no outputs */ \
        : "r" ((long)__data.sockfd), "r" (__data.addr), "r" ((long)__data.addrlen) \
        : "eax", "ebx", "ecx", "memory" \
    ); \
} while (0)

#define lsc32_connect(connect_struct) do { \
    lsc_connect __data = (connect_struct); \
    asm volatile ( \
        "mov $102, %%eax\n\t" \
        "mov $3, %%ebx\n\t" \
        "mov %0, %%ecx\n\t" \
        "int $0x80\n\t" \
        : /* no outputs */ \
        : "r" ((long)__data.sockfd), "r" (__data.addr), "r" ((long)__data.addrlen) \
        : "eax", "ebx", "ecx", "memory" \
    ); \
} while (0)

#define lsc32_listen(listen_struct) do { \
    lsc_listen __data = (listen_struct); \
    asm volatile ( \
        "mov $102, %%eax\n\t" \
        "mov $4, %%ebx\n\t" \
        "mov %0, %%ecx\n\t" \
        "int $0x80\n\t" \
        : /* no outputs */ \
        : "r" ((long)__data.sockfd), "r" ((long)__data.backlog) \
        : "eax", "ebx", "ecx", "memory" \
    ); \
} while (0)

#define lsc32_accept(accept_struct) do { \
    lsc_accept __data = (accept_struct); \
    asm volatile ( \
        "mov $102, %%eax\n\t" \
        "mov $5, %%ebx\n\t" \
        "mov %0, %%ecx\n\t" \
        "int $0x80\n\t" \
        : "=a" (__data.atype) \
        : "r" ((long)__data.sockfd), "r" (__data.addr), "r" (__data.addrlen) \
        : "eax", "ebx", "ecx", "memory" \
    ); \
    (void)__data.atype; \
} while (0)

#define lsc32_send(send_struct) do { \
    lsc_send __data = (send_struct); \
    asm volatile ( \
        "mov $102, %%eax\n\t" \
        "mov $9, %%ebx\n\t" \
        "mov %0, %%ecx\n\t" \
        "int $0x80\n\t" \
        : /* no outputs */ \
        : "r" ((long)__data.sockfd), "r" (__data.buf), "r" (__data.len), "r" ((long)__data.flags) \
        : "eax", "ebx", "ecx", "memory" \
    ); \
} while (0)

#define lsc32_recv(recv_struct) do { \
    lsc_recv __data = (recv_struct); \
    asm volatile ( \
        "mov $102, %%eax\n\t" \
        "mov $10, %%ebx\n\t" \
        "mov %0, %%ecx\n\t" \
        "int $0x80\n\t" \
        : /* no outputs */ \
        : "r" ((long)__data.sockfd), "r" (__data.buf), "r" (__data.len), "r" ((long)__data.flags) \
        : "eax", "ebx", "ecx", "memory" \
    ); \
} while (0)

#define lsc32_print_int(int_struct) do { \
    lsc_int __data = (int_struct); \
    char __buf[32]; \
    long __val = __data.value; \
    int __neg = 0; \
    int __i = 31; \
    __buf[__i--] = '\0'; \
    if (__val < 0) { \
        __neg = 1; \
        __val = -__val; \
    } \
    if (__val == 0) { \
        __buf[__i--] = '0'; \
    } else { \
        while (__val > 0) { \
            __buf[__i--] = '0' + (__val % 10); \
            __val /= 10; \
        } \
    } \
    if (__neg) { \
        __buf[__i--] = '-'; \
    } \
    const char* __output = &__buf[__i + 1]; \
    lsc_write __write_struct = { \
        .wtype = 1, \
        .dataptr = __output, \
        .datalen = 31 - __i \
    }; \
    lsc32_stdout(__write_struct); \
} while (0)
#endif /* X86_32_LINUX */

#define lsc64_http_get(sock_struct, connect_struct, send_struct, recv_struct, close_struct) do { \
    lsc64_socket(sock_struct); \
    lsc64_connect(connect_struct); \
    lsc64_send(send_struct); \
    lsc64_recv(recv_struct); \
    lsc64_close(close_struct); \
} while (0)

#define lsc32_http_get(sock_struct, connect_struct, send_struct, recv_struct, close_struct) do { \
    lsc32_socket(sock_struct); \
    lsc32_connect(connect_struct); \
    lsc32_send(send_struct); \
    lsc32_recv(recv_struct); \
    lsc32_close(close_struct); \
} while (0)

/* ==================== UTILITIES ==================== */

/* Exit with status */
static inline void lsc_exit(int status) {
    asm volatile (
        "mov $60, %%rax\n\t"
        "mov %0, %%rdi\n\t"
        "syscall\n\t"
        :
        : "r" ((long)status)
        : "rax", "rdi", "rcx", "r11"
    );
}

/* Quick print string helper - 64-bit */
#define lsc64_print(str) do { \
    lsc_write __w = {1, str, 0}; \
    while (str[__w.datalen]) __w.datalen++; \
    lsc64_stdout(__w); \
} while (0)

/* Quick print string helper - 32-bit */
#define lsc32_print(str) do { \
    lsc_write __w = {1, str, 0}; \
    while (str[__w.datalen]) __w.datalen++; \
    lsc32_stdout(__w); \
} while (0)

#endif // LSC_H
// VERSION HISTORY
//   (0.01) 14/1/2026 First public release
//   (0.02) 16/1/2026 Printing added (stable) i/o added (unstable)
//   Full history can be found at the end of this file.
//   (0.03) 17/1/2026 Complete rework of the i/o (stable) + execve (unstable) new function exit_success (prevents i/o operations from segaulting)
//   (0.03) 18/1/2026 Execve (Stable) 
//   (0.04) 21/1/2026 Added socket syscalls (unstable) 
//   (0.04) 22/1/2026 integer handling (unstable) file i/o syscalls (unstable)
//   (0.04) 23/1/2026 Made socket syscalls stable + integer handling stable + file i/o syscalls stable
//   (0.04) 24/1/2026 added 32bit support for write and read syscalls
//   (0.04) 25/1/2026 added 32bit support for execve syscall
//   (0.04) 26/1/2026 added 32bit support for file i/o syscalls
//   (0.04) 27/1/2026 added 32bit support for socket syscalls
//   (0.04) 28/1/2026 added 32bit support for integer handling
//   (0.04) 29/1/2026 32bit support bug fixes 
//   (0.04) 30/1/2026 Complete 32bit support for all syscalls
//   (0.04) 31/1/2026 testing (sockets unstable)

