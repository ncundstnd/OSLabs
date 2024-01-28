#pragma once
#include <Windows.h>
#include <thread>

class ThirdTask
{
private:
	static DWORD pid;
public:
	static int ShowPidTidCycle();
};
