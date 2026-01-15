.section .bss 
write_buff: .space 1024 #used in the write function
write_len = . - write_buff

#execve 
path:
    .space 1024 
command:
    .space 1024

.section .data 
cmpmsg:
    .ascii ""

.section .text 
.globl write_stdout
.globl stdin_read
.globl cmp_str
.globl cp_str
.globl writestr
.globl system
.globl writeint
.globl memalloc
.global _start

.type write_stdout, @function
.type stdin_read, @function
.type cmp_str, @function
.type cp_str, @function
.type writestr, @function 
.type system, @function 
.type writeint, @function
.type memalloc, @function

write_stdout:
    mov %rdi, %r8
    mov %rsi, %r9

    mov $1, %rax 
    mov $1, %rdi 
    mov %r8, %rsi 
    mov %r9, %rdx 
    .byte 0x0F, 0x05 #syscall 
    ret

stdin_read:
    mov %rdi, %r8
    mov %rsi, %r9 

    mov $0, %rax 
    mov $0, %rdi 
    mov %r8, %rsi 
    mov %r9, %rdx 
    .byte 0x0F, 0x05
    cmp $0, %rax
    je stdin_read_done
    mov -1(%r8, %rax, 1), %cl
    cmp $10, %cl            
    jne stdin_read_no_nl
    movb $0, -1(%r8, %rax, 1)
    ret
stdin_read_no_nl:
    movb $0, (%r8, %rax, 1)
stdin_read_done:
    ret
writestr:
    mov %rdi, %r8 
ptr_strLoop:
    mov (%r8), %al 
    test %al, %al
    mov %al, write_buff(%rip)
    mov $1, %rax 
    mov $1, %rdi 
    lea write_buff(%rip), %rsi 
    mov $write_len, %rdx 
    syscall 
    je ptrdone 
    inc %r8
    jmp ptr_strLoop
ptrdone:
    xor %rax, %rax 
    ret 

#System section 

system:
    push $0          # NULL 
    push %rsi        # command
    push %rdi        # path
    mov %rsp, %rsi   # rsi = argv
    
    # rdi already holds path
    xor %rdx, %rdx   
    mov $59, %rax
    syscall

memalloc:
    mov %rdi, %r8 #start heap 
    mov %rsi, %r9 #size to alloc

    mov $12, %rax 
    mov $0, %rdi 
    syscall 

    mov %r8, %rax 

    mov $12, %rax 
    mov %r8, %rdi
    add %r9, %rdi 
    syscall 

    mov %r8, %rbx
    mov $42, (%rbx)

#STRING SECTION 
cmp_str:
    mov %rdi, %r8 
    mov %rsi, %r9 
compare_loop:
    movb (%r8), %al 
    movb (%r9), %bl 
    cmp %al, %bl 
    jne notequal_cmp 
    test %al, %al
    je equal 
    inc %r8
    inc %r9
    jmp compare_loop
equal:
    xor %rax, %rax
    ret
notequal_cmp:
    mov $1, %rax 
    ret

cp_str:
    #arguments 
    mov %rdi, %r8 
    mov %rsi, %r9 
copy_loop:
    mov (%r8), %al 
    mov %al, (%r9)
    test %al, %al 
    je done 
    inc %r8 
    inc %r9 
    jmp copy_loop
done: 
    xor %rax, %rax 
    ret 

_start:
    call main 
    mov %rax, %rdi 
    mov $60, %rax 
    syscall 

#END OF FILE
