#include "FourthTask.h"
#include <iostream>

DWORD FourthTask::pid = GetCurrentProcessId();

DWORD WINAPI FourthTaskFirstThread()
{
	for (int i = 0; i < 50; i++)
	{
		if (i == 24) {
			Sleep(10000);
		}
		std::cout << i << ". FirstThread PID = " << GetCurrentProcessId() << "\tTID = " << GetCurrentThreadId() << "\n";
		Sleep(1000);
	}

	return 0;
}

DWORD WINAPI FourthTaskSecondThread()
{
	for (int i = 0; i < 125; i++)
	{
		if (i == 79) {
			Sleep(15000);
		}
		std::cout << i << ". SecondThread PID = " << GetCurrentProcessId() << "\tTID = " << GetCurrentThreadId() << "\n";
		Sleep(1000);
	}

	return 0;
}

int FourthTask::ShowPidTidCycle() {
	HANDLE FirstChildThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FourthTaskFirstThread, NULL, 0, NULL);
	HANDLE SecondChildThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FourthTaskSecondThread, NULL, 0, NULL);

	for (int i = 0; i < 100; i++)
	{
		if (i == 29) {
			Sleep(10000);
		}
		std::cout << i << ". MainThread PID = " << pid << "\tTID = " << GetCurrentThreadId() << "\n";
		Sleep(1000);
	}
	return 0;
}
