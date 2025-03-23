#include <windows.h>
#include <iostream>
#include <sstream>

#define ARR_SIZE 10
#define BUF_SIZE 0x100
#define SLEEP_MS 60000
#define CMD_SET 0x1
#define CMD_GET 0x2
#define CMD_FEEDBACK 0x3

DWORD WINAPI AlarmThread(LPVOID lpParameter) 
{
    DWORD sleepMs = (DWORD)lpParameter;

    Sleep(sleepMs);
    TerminateProcess(GetCurrentProcess(), 1);

    return 1;
}

BOOL InitChallenge(DWORD sleepMs) 
{
    HANDLE hThread = CreateThread(NULL, 0, &AlarmThread, (LPVOID)sleepMs, 0, NULL);
    if (hThread == NULL) {
        return FALSE;
    }

    setvbuf(stdout, NULL, _IONBF, 0);

    return TRUE;
}

VOID Read_QWORD(DWORD64* out)
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        std::stringstream ss(line);
        if (ss >> *out)
        {
			return;
		}
	}
}

VOID Panic(const CHAR* message)
{
    std::cout << message << GetLastError() << std::endl;
	TerminateProcess(GetCurrentProcess(), 1);
}

HANDLE OpenCreateFile(const CHAR* filename)
{
	HANDLE hFile;
	hFile = CreateFileA(filename, GENERIC_READ|GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, NULL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_SHARING_VIOLATION)
        {
            std::cout << "Hero is already in the world" << std::endl;
            std::cout << "Please call the ohter heroes!" << std::endl;
            return NULL;
        }
        Panic("Failed to create file: ");
	}
	return hFile;
}

HANDLE Authenticate()
{
    std::string username, password;

    std::cout << "We have spawned 5 Heroes to protect the world from the Demon King." << std::endl;
    std::cout << "Which hero are you?" << std::endl;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    HANDLE hFile;
    if (username == "Haruhiro" && password == "Haruhiro7!")
    {
        return OpenCreateFile("Haruhiro.txt");
    }
    else if (username == "Merry" && password == "Merry7!")
    {
		return OpenCreateFile("Merry.txt");
    } 
    else if (username == "Yume" && password == "Yume7!")
	{
        return OpenCreateFile("Yume.txt");
    } 
    else if (username == "Shihoru" && password == "Shihoru7!")
    {
		return OpenCreateFile("Shihoru.txt");
	} 
    else if (username == "Ranta" && password == "Ranta7!")
    {
		return OpenCreateFile("Ranta.txt");
    }
    else {
        std::cout << "You're not Eiyuu Kyun! hmph" << std::endl;
        return NULL;
    }
}

VOID LoadArray(HANDLE hFile, DWORD64* array, DWORD64 size)
{
    DWORD bytesRead;
	CHAR buffer[BUF_SIZE] = { 0x0 };
	std::stringstream ss;

    if (!ReadFile(hFile, buffer, BUF_SIZE, &bytesRead, NULL))
    {
		Panic("Failed to read file: ");
	}

	ss << buffer;
    for (DWORD i = 0; i < size; i++)
    {
		ss >> array[i];
	}
}

VOID SaveArray(HANDLE hFile, DWORD64* array, DWORD64 size)
{
	std::stringstream ss;
    if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
    {
        Panic("Failed to set file pointer: ");
    }

    if (!SetEndOfFile(hFile))
    {
        Panic("Failed to set end of file: ");
    }

    for (DWORD i = 0; i < size; i++)
    {
        ss << array[i] << std::endl;
    }

    if (!WriteFile(hFile, ss.str().c_str(), ss.str().size(), NULL, NULL))
    {
        Panic("Failed to write file: ");
    }
}

int main(DWORD argc, CHAR* argv[], CHAR* env[])
{
	if (!InitChallenge(SLEEP_MS))
	{
		return -1;
	}

    // variables
    DWORD64 c;
    DWORD64 index, num;
    DWORD64 array[ARR_SIZE] = { 0x0 };
    HANDLE hFile;
    CHAR buffer[BUF_SIZE] = { 0x0 };
    
    // authentication
    std::cout << "Welcome to the Eiyuu's Vault!" << std::endl;
    hFile = Authenticate();
    if (!hFile)
    {
		return -1;
	}

    // reading and initializing array
    LoadArray(hFile, array, ARR_SIZE);

    // reading commands
    std::cout << "Command: ";
    Read_QWORD(&c);
    switch (c)
    {
    case CMD_SET:
        std::cout << "Index: ";
        Read_QWORD(&index);
        if (index < 0 || index > ARR_SIZE - 1)
        {
            std::cout << "Invalid index" << std::endl;
            break;
        }

        std::cout << "Value: ";
        Read_QWORD(&num);
        array[index] = num;
        SaveArray(hFile, array, ARR_SIZE);  

        break;

    case CMD_GET:
        std::cout << "Index: ";
        Read_QWORD(&index);
        std::cout << "Value: " << array[index] << std::endl;
        break;

    case CMD_FEEDBACK:
        std::cout << "Do you really wanna go back to your world Eiyuu Kyun? :(" << std::endl;
        //std::cin >> buffer;
        fgets(buffer, 0x190, stdin);
        printf("M-Masaka?! %s", buffer);
        goto ret;

    default:
        std::cout << "Invalid command" << std::endl;
    }

    std::cout << "See you another time Eiyuu Kyun~!" << std::endl;
    
    ret:
    flushall();
    CloseHandle(hFile);
    return 0;
}
