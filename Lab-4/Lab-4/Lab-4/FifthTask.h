#pragma once
#include <Windows.h>
#include <thread>
#include <condition_variable>

static class FifthTask
{
private:
	static DWORD pid;
public:
	static int ShowPidTidCycle();
};
