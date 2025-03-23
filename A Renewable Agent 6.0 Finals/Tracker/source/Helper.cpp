#include "Helper.hpp"

VOID RealtimeTrack()
{
    DWORD i = 0x0;
    while (TRUE)
    {
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        std::cout << i << " -> (" << cursorPos.x << ", " << cursorPos.y << ")" << std::endl;
        Sleep(1000);
        i++;
    }
}

VOID Panic(const CHAR* message)
{
    LPVOID lpMsgBuf;
    DWORD err = GetLastError();

    if (FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&lpMsgBuf, 0, NULL) == 0)
    {
        std::cout << message << GetLastError() << std::endl;
    }
    else {
        std::cout << message << (LPSTR)lpMsgBuf << std::endl;
        LocalFree(lpMsgBuf);
    }

    TerminateProcess(GetCurrentProcess(), 1);
}

VOID ValidateCursorPos(DWORD x, DWORD y, DWORD threshold)
{
    Sleep(2000);

    POINT cursorPos;
    if (GetCursorPos(&cursorPos) == 0)
    {
        Panic("Uh oH!: ");
    }

    if (cursorPos.x < x - threshold || cursorPos.x > x + threshold || cursorPos.y < y - threshold || cursorPos.y > y + threshold)
    {
		std::cout << "No Buenos!" << std::endl;
        TerminateProcess(GetCurrentProcess(), 1);
    }

    std::cout << "Good Job! Keep it up!" << std::endl;
}