#pragma once
#include <Windows.h>

static class ThirdTask
{
private:
	static DWORD pid;
public:
	static int ShowWindowsProcesses();
};

