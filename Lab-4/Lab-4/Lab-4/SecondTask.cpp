#include "SecondTask.h"
#include "ThirdTask.h"
#include <iostream>

DWORD SecondTask::pid = GetCurrentProcessId();

DWORD WINAPI SecondTaskFirstThread()
{
	for (int i = 0; i < 50; i++)
	{
		std::cout << i << ". FirstThread PID = " << GetCurrentProcessId() << "\tTID = " << GetCurrentThreadId() << "\n";
		Sleep(1000);
	}

	return 0;
}

DWORD WINAPI SecondTaskSecondThread()
{
	for (int i = 0; i < 125; i++)
	{
		std::cout << i << ". SecondThread PID = " << GetCurrentProcessId() << "\tTID = " << GetCurrentThreadId() << "\n";
		Sleep(1000);
	}

	return 0;
}

int SecondTask::ShowPidTidCycle() {
	HANDLE FirstChildThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SecondTaskFirstThread, NULL, 0, NULL);
	HANDLE SecondChildThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SecondTaskSecondThread, NULL, 0, NULL);

	for (int i = 0; i < 100; i++)
	{
		std::cout << i << ". MainThread PID = " << pid << "\tTID = " << GetCurrentThreadId() << "\n";
		Sleep(1000);
	}

	WaitForSingleObject(FirstChildThread, INFINITE);
	CloseHandle(FirstChildThread);

	WaitForSingleObject(SecondChildThread, INFINITE);
	CloseHandle(SecondChildThread);

	return 0;
}