#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#define TIMEOUT 60000 // 60s
#define SIZE 0x100

using namespace std;

wstring LocateDLLInModulePath(const WCHAR* DLLName)
{
    // get current execution path
    WCHAR path[MAX_PATH] = { 0 };
    GetModuleFileNameW(NULL, path, MAX_PATH);

    // remove the executable name from the path
    wstring::size_type pos = wstring(path).find_last_of(L"\\");
    wstring directory = wstring(path).substr(0, pos) + L"\\*";

    // list files to find the DLL
    WIN32_FIND_DATA data;
    HANDLE hDirList = FindFirstFileW(directory.c_str(), &data);
    if (INVALID_HANDLE_VALUE == hDirList || !hDirList)
    {
        return wstring(L"");
    }

    wstring ret(L"");
    do {
        wstring name(data.cFileName);
        if (!wcscmp(name.c_str(), DLLName)) // found the DLL
        {
            ret = wstring(path).substr(0, pos) + L"\\" + name;
            break;
        }
    } while (NULL != FindNextFileW(hDirList, &data));

    CloseHandle(hDirList);
    return ret;
}

//inject dll to trigger decrypt
BOOL InjectDLL()
{
    wstring dllpath;
    printf("enter dllpath:");
    wcin >> dllpath;

    DWORD pid = GetCurrentProcessId();
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (INVALID_HANDLE_VALUE == hProcess || !hProcess)
    {
        return NULL;
    }

    DWORD ret = WAIT_FAILED;
    SIZE_T size = (wcslen(dllpath.c_str()) + 1) * sizeof(WCHAR);

    // allocate a virtual memory space in the victim process
    LPVOID lpVirtualAddr = VirtualAllocEx(hProcess, NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!lpVirtualAddr)
    {
        return false;
    }

    // writing the name of the dll to the allocated memory space
    if (WriteProcessMemory(hProcess, lpVirtualAddr, dllpath.c_str(), size, NULL))
    {
        HMODULE hKernel32 = GetModuleHandleW(L"kernel32.dll");
        if (!hKernel32)
        {
            return false;
        }

        FARPROC fpLoadLibrary = GetProcAddress(hKernel32, "LoadLibraryW");
        if (!fpLoadLibrary)
        {
            return false;
        }

        // Inject to the remote process
        HANDLE hInjectedThread = CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)fpLoadLibrary, lpVirtualAddr, NULL, NULL);
        if (hInjectedThread)
        {
            ret = WaitForSingleObject(hInjectedThread, TIMEOUT);
            CloseHandle(hInjectedThread);
            hInjectedThread = NULL;
        }
    }

    // cleanup
    VirtualFreeEx(hProcess, lpVirtualAddr, 0, MEM_RELEASE);

    if (WAIT_OBJECT_0 == ret)
    {
        return true;
    }

    return false;
}

void printFlag()
{
    wstring SharedMemoryName;
    printf("Enter shared memory name:");
    wcin >> SharedMemoryName;

    HANDLE hSharedFile;
    LPTSTR pBuffer;
    CHAR FlagBuf[SIZE + 1] = { 0 };

    hSharedFile = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, (LPWSTR) &SharedMemoryName);
    if (hSharedFile == NULL)
    {
        cout << "Flag file mapping not found" << endl;
        return;
    }

    pBuffer = (LPTSTR)MapViewOfFile(hSharedFile, FILE_MAP_ALL_ACCESS, 0, 0, SIZE);
    if (pBuffer == NULL)
    {
        CloseHandle(hSharedFile);
        cout << "Failed to map view of file" << endl;
        return;
    }

    memcpy(FlagBuf, (PVOID)pBuffer, SIZE);
    UnmapViewOfFile(pBuffer);

    cout << "Flag: " << FlagBuf << endl;
    return;
}

void main()
{
    InjectDLL();
    printFlag();
}