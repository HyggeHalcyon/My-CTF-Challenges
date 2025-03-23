#pragma once
#include <Windows.h>
#include <iostream>

VOID RealtimeTrack();
VOID Panic(const CHAR* message);
VOID ValidateCursorPos(DWORD x, DWORD y, DWORD threshold);