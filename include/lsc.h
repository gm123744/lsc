// lsc.h - v0.01 - public domain
// authored from 2025-2026 by GM_11 || gm123744
//
// =======================================================================
//
//    NO SECURITY GUARANTEE -- DO NOT USE THIS TO MAKE DANGEROUS CODE
//
// This library does not have any sefety measures. It is strongly suggested
// to not make malicius code the whole library is made for education and 
// system developers with high level syntax while having a lot of control.
//
// =======================================================================
//
//   This library wraps all of the 467 syscalls the linux kernel has into 
//   a simple single header library that allows the programmer to write 
//   with minimal recourses.
//
// CONTRIBUTORS
// VERSION HISTORY
//   (0.01) 14/1/2026 
//   Full history can be found at the end of this file.
//
// LICENSE
//
//   See license file for information.
//
// USAGE
//   Include this file in whatever places need to refer to it. In ONE C/C++
//   #define X86_64_LINUX
//   #define X86_32_LINUX
//   before the #include of this file. This expands out the actual
//   implementation into that C/C++ file.
// NOTES:
// THIS FILE CURRENTLY DOES NOT EXTERN ANY ASM FUNCTIONS THIS IS JUST A PROTOTYPE
//
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
////
#ifndef LSC_H
#define LSC_H
#include <stddef.h>
//keyboard input
#define KEY_A 0x1E
#define KEY_B 0x30
#define KEY_C 0x2E
#define KEY_D 0x20
#define KEY_E 0x12
#define KEY_F 0x21
#define KEY_G 0x22
#define KEY_H 0x23
#define KEY_I 0x17
#define KEY_J 0x24
#define KEY_K 0x25
#define KEY_L 0x26 
#define KEY_M 0x32
#define KEY_N 0x31
#define KEY_O 0x18
#define KEY_P 0x19
#define KEY_Q 0x10
#define KEY_R 0x13
#define KEY_S 0x1F
#define KEY_T 0x14
#define KEY_U 0x16
#define KEY_V 0x2F
#define KEY_W 0x11
#define KEY_X 0x2D
#define KEY_Y 0x15
#define KEY_Z 0x2C
#define KEY_1 0x02
#define KEY_2 0x03
#define KEY_3 0x04
#define KEY_4 0x05
#define KEY_5 0x06
#define KEY_6 0x07
#define KEY_7 0x08
#define KEY_8 0x09
#define KEY_9 0x0A
#define KEY_0 0x0B
#define KEY_ENTER 0x1C
#define KEY_ESC 0x01
#define KEY_BACKSPACE 0x0E
#define KEY_TAB 0x0F
#define KEY_SPACE 0x39
#define KEY_MINUS 0x0C
#define KEY_EQUAL 0x0D
#define KEY_LEFTBRACE 0x1A
#define KEY_RIGHTBRACE 0x1B
#define KEY_BACKSLASH 0x2B
#define KEY_SEMICOLON 0x27
#define KEY_APOSTROPHE 0x28
#define KEY_GRAVE 0x29
#define KEY_COMMA 0x33
#define KEY_DOT 0x34
#define KEY_SLASH 0x35
#define KEY_CAPSLOCK 0x3A
#define KEY_F1 0x3B
#define KEY_F2 0x3C
#define KEY_F3 0x3D
#define KEY_F4 0x3E
#define KEY_F5 0x3F
#define KEY_F6 0x40
#define KEY_F7 0x41
#define KEY_F8 0x42
#define KEY_F9 0x43
#define KEY_F10 0x44
#define KEY_F11 0x57
#define KEY_F12 0x58
#define KEY_LEFTSHIFT    0x2A
#define KEY_RIGHTSHIFT   0x36
#define KEY_LEFTCTRL     0x1D
#define KEY_RIGHTCTRL    0xE0
#define KEY_LEFTALT      0x38
#define KEY_RIGHTALT     0xE0
#define KEY_RIGHTMETA    0xE0
#define KEY_UP           0x48
#define KEY_DOWN         0x50
#define KEY_LEFT         0x4B
#define KEY_RIGHT        0x4D
#define KEY_INSERT       0x52
#define KEY_DELETE       0x53
#define KEY_HOME         0x47
#define KEY_END          0x4F
#define KEY_PAGEUP       0x49
#define KEY_PAGEDOWN     0x51

#define WRITE_STDOUT 1

typedef struct lsc_write {
    int wtype;          
    const char* dataptr;   
    size_t datalen;         
} lsc_write;

// The macro user calls
#define stdout(w) _lsc_write_execute(w)

#ifdef X86_64_LINUX
    extern void system_stdout(const char* buf, size_t len);
    
    static inline void _lsc_write_execute(lsc_write* w) {
        if (w->write == WRITE_STDOUT) {
            system_stdout(w->arg1, w->len); 
        }
    }

#elif defined(X86_32_LINUX)
    // 32-bit assembly function  
    extern void system_stdoutwo(const char* buf, size_t len);
    
    static inline void _lsc_write_execute(lsc_write* w) {
        if (w->write == WRITE_STDOUT) {
            system_stdoutwo(w->arg1, w->len);  
        }
    }
#endif
#endif // LSC_H


