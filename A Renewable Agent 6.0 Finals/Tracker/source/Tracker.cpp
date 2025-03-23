#include <windows.h>
#include <winternl.h>
#include <regex>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Helper.hpp"
#include "Dictionary.hpp"
#define FLG_HEAP_ENABLE_TAIL_CHECK   0x10
#define FLG_HEAP_ENABLE_FREE_CHECK   0x20
#define FLG_HEAP_VALIDATE_PARAMETERS 0x40
#define NT_GLOBAL_FLAG_DEBUGGED (FLG_HEAP_ENABLE_TAIL_CHECK | FLG_HEAP_ENABLE_FREE_CHECK | FLG_HEAP_VALIDATE_PARAMETERS)

#pragma pack(push, 1)
typedef struct _BASE_RELOCATION_ENTRY {
    WORD Offset : 12;
    WORD Type : 4;
} BASE_RELOCATION_ENTRY, * PBASE_RELOCATION_ENTRY;

typedef struct _BASE_RELOCATION_BLOCK {
    DWORD PageAddress;
    DWORD BlockSize;
} BASE_RELOCATION_BLOCK, * PBASE_RELOCATION_BLOCK;
#pragma pack(pop)

#ifndef _WIN64
PPEB pPeb = (PPEB)__readfsdword(0x30);
DWORD dwNtGlobalFlag = *(PDWORD)((PBYTE)pPeb + 0x68);
#else
PPEB pPeb = (PPEB)__readgsqword(0x60);
DWORD dwNtGlobalFlag = *(PDWORD)((PBYTE)pPeb + 0xBC);
#endif // _WIN64

#pragma section(".note", read, write)
__declspec(allocate(".note")) BYTE dllBytes[] = { 1 };


void fun1(int x) {
    __try {
        exit(1 / x);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        std::cout << "Let's see your tracking abilities" << std::endl;
        DetectMousePatternA();
        DetectMousePatternR();
        DetectMousePatternA();
        DetectMousePattern6();
        DetectMousePatternC();
        DetectMousePatternH();
        DetectMousePatternA();
        DetectMousePatternL();
        DetectMousePatternL();
        DetectMousePattern_();
        DetectMousePatternD();
        DetectMousePatternI();
        DetectMousePatternB();
        DetectMousePatternU();
        DetectMousePatternA();
        DetectMousePatternT();
        DetectMousePattern_();
        DetectMousePatternB();
        DetectMousePatternA();
        DetectMousePatternR();
        DetectMousePatternU();
        DetectMousePattern_();
        DetectMousePatternK();
        DetectMousePatternE();
        DetectMousePatternM();
        DetectMousePatternA();
        DetectMousePatternR();
        DetectMousePatternI();
        DetectMousePatternN();
        DetectMousePattern_();
        DetectMousePatternH();
        DetectMousePatternE();
        DetectMousePatternH();
        DetectMousePatternE();
    }
}

void NTAPI TlsCallback(PVOID DllHandle, DWORD dwReason, PVOID)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        break;

    default:
        return;
    }

    try
    {
        if (!IsDebuggerPresent())
        {
            std::regex invalid_pattern("[L$bUWH");
        }
    }
    catch (std::regex_error)
    {
        __asm
        {
            mov	eax, dword ptr fs : [30h]
            test	dword ptr[eax + 68h], HEAP_REALLOC_IN_PLACE_ONLY or HEAP_TAIL_CHECKING_ENABLED or HEAP_FREE_CHECKING_ENABLED
            je	_no_debugger
            push 0
            call exit

            _no_debugger :
            push 0
                call fun1
        }
    }
}

#ifdef _WIN64
#pragma comment (linker, "/INCLUDE:_tls_used")
#pragma comment (linker, "/INCLUDE:tls_callback_func")
#else
#pragma comment (linker, "/INCLUDE:__tls_used")
#pragma comment (linker, "/INCLUDE:_tls_callback_func")
#endif

#ifdef _WIN64
#pragma const_seg(".CRT$XLF")
EXTERN_C const
#else
#pragma data_seg(".CRT$XLF")
EXTERN_C
#endif
PIMAGE_TLS_CALLBACK tls_callback_func = TlsCallback;
#ifdef _WIN64
#pragma const_seg()
#else
#pragma data_seg()
#endif

int main()
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}