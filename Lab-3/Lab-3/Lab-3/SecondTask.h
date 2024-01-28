#pragma once
#include <Windows.h>
#include <iostream>

static class SecondTask
{
private:
    static DWORD pid;
    static STARTUPINFO info;

public:
    static int ShowPidCycle();
    static int StartProcess(LPCWSTR path, PROCESS_INFORMATION* process);
};
