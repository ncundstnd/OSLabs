#pragma once
#include <Windows.h>

static class FirstTask
{
private:
	static DWORD tid, pid;
public:
	static int ShowPidTidCycle();
};
