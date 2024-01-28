#pragma once
#include <Windows.h>
#include <condition_variable>

class SecondTask
{
private:
	static DWORD pid;
public:
	static int ShowPidTidCycle();
};
