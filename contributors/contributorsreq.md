# Contributing

Thank you for wanting to contribute to this project.  
This project focuses on **low-level Linux systems development** and is intended for people who are comfortable working close to the hardware and kernel internals. Not everyone is ready for that kind of work, and that is completely fine.

This project is **not beginner-oriented**. Contributors are expected to have real, practical experience in a few key areas before contributing.

## Assembly Language

You should be comfortable with **at least one assembly dialect**, such as x86_64, ARM, or RISC-V. This includes:

- Understanding calling conventions
- Knowing how stacks and registers work
- Working with inline assembly and ABI boundaries
- Being able to read, debug, and write non-trivial assembly code

This goes beyond simple examples — you should be able to reason about what the assembly is doing and why.

## C for Systems Programming

A solid understanding in **C** is required. This includes:

- Manual memory management (allocation, alignment, lifetimes)
- Avoiding undefined behavior
- Being comftable without using glibc

Without this background, you will likely run into problems very quickly.

## Linux Systems Development

Linux sysdev knowledge is expected to go **well beyond basic syscall usage**. Contributors should be familiar with topics such as:

- Linux ABI 
- How syscalls work and their calling conventions
- Interfaces like `mmap`, `mprotect`, `clone`, `futex`, `epoll`, `ioctl`, `prctl`, `seccomp`, and others
- Process and thread lifecycles
- Virtual memory, page tables, and address space layout
- Signals, context switching, and low-level synchronization
- Debugging using tools like `strace`, `perf`, `gdb`, and inspecting `/proc`

In order to contribute required to be comfortable with **more than just a few syscalls** 

## Code Expectations

- Avoid large or unnecessary abstractions (optional)
- Comments should be minimal and and use simple english 
- Changes should be tested 

## Collaboration

Even with a high technical bar, collaboration is important. Please keep interactions respectful and professional. Constructive discussion and well-supported design decisions are encouraged.

If you are unsure whether your background is a good fit, starting a discussion before opening a pull request is totally fine and can save time for everyone.

---

We really appreciate your interest and effort.  
Good contributions help improve the project for everyone involved.

