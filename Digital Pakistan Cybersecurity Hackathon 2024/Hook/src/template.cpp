#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <windef.h>
#include <psapi.h>
#include <TlHelp32.h>
#include "cryptlib.h"
#include "hex.h"
#include "filters.h"
#include "aes.h"
#include "ccm.h"

#define FLAG_SIZE 48
#define BUFFER_SIZE 0x1000

using namespace std;
using CryptoPP::Exception;
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::AES;
using CryptoPP::CBC_Mode;

const BYTE IV[AES::BLOCKSIZE] = "_IV";
const BYTE KEY[AES::MAX_KEYLENGTH] = "__KEY";
const BYTE himitsu[FLAG_SIZE] = "_FLAG";
const WCHAR SharedMemoryName[] = L"_GLOBAL_MEM";
HANDLE hSharedFile;

BOOL OpenSharedMemory()
{
    hSharedFile = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, (LPCWSTR)&SharedMemoryName);
    if (hSharedFile == NULL)
    {
        {
            hSharedFile = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUFFER_SIZE, (LPCWSTR)&SharedMemoryName);
            if (hSharedFile == NULL)
            {
                return false;
            }
        }
    }

    return true;
}

BOOL Decrypt()
{
    LPTSTR pBuffer;

    pBuffer = (LPTSTR)MapViewOfFile(hSharedFile, FILE_MAP_ALL_ACCESS, 0, 0, FLAG_SIZE);
    if (pBuffer == NULL)
    {
        CloseHandle(hSharedFile);
        return false;
    }
    string cipher((char*)himitsu);
    string plain;

    try
    {
        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV(KEY, sizeof(KEY), IV);
        StringSource s(cipher, true,
            new StreamTransformationFilter(d,
                new StringSink(plain)
            )
        );
    }
    catch (const CryptoPP::Exception& e)
    {
        cerr << e.what() << endl;
        exit(1);
    }

    memcpy((PVOID)pBuffer, plain.c_str(), FLAG_SIZE);
    UnmapViewOfFile(pBuffer);

    return true;
}

void Win()
{
    if (!OpenSharedMemory())
    {
        MessageBoxA(NULL, "umm what?", "Try Again", MB_ICONEXCLAMATION);
        return;
    }

    if (!Decrypt()) {
        MessageBoxA(NULL, "Failed to decrypt flag. Please contact Author", "ERR", MB_ICONSTOP);
    }
    else {
        MessageBoxA(NULL, "Congrats I guess?", "Totally not sus DLL", MB_ICONINFORMATION);
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        MessageBoxA(NULL, "Hmmmm?", "Hm?", MB_ICONINFORMATION);
        Win();
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;

    case DLL_PROCESS_DETACH:
        break;
    }


    return TRUE;
}