#include "FifthTask.h"
#include "FifthTask.h"
#include <iostream>

DWORD FifthTask::pid = GetCurrentProcessId();

DWORD WINAPI FifthTaskFirstThread()
{
	for (int i = 0; i < 50; i++)
	{
		std::cout << i << ". FirstThread PID = " << GetCurrentProcessId() << "\tTID = " << GetCurrentThreadId() << "\n";
		Sleep(1000);
	}

	return 0;
}

DWORD WINAPI FifthTaskSecondThread()
{
	for (int i = 0; i < 125; i++)
	{
		std::cout << i << ". SecondThread PID = " << GetCurrentProcessId() << "\tTID = " << GetCurrentThreadId() << "\n";
		Sleep(1000);
	}

	return 0;
}

int FifthTask::ShowPidTidCycle() {
	HANDLE FirstChildThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FifthTaskFirstThread, NULL, 0, NULL);
	HANDLE SecondChildThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FifthTaskSecondThread, NULL, 0, NULL);

	for (int i = 0; i < 100; i++)
	{
		if (i == 39)
			TerminateThread(SecondChildThread, 0);
		std::cout << i << ". MainThread PID = " << pid << "\tTID = " << GetCurrentThreadId() << "\n";
		Sleep(1000);
	}

	WaitForSingleObject(FirstChildThread, INFINITE);
	CloseHandle(FirstChildThread);

	WaitForSingleObject(SecondChildThread, INFINITE);
	CloseHandle(SecondChildThread);

	return 0;
}