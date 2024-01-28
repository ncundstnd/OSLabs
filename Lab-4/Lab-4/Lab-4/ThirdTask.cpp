#include "ThirdTask.h"
#include "ThirdTask.h"
#include <iostream>

DWORD ThirdTask::pid = GetCurrentProcessId();

DWORD WINAPI ThirdTaskFirstThread()
{
	for (int i = 0; i < 50; i++)
	{
		std::cout << i << ". FirstThread PID = " << GetCurrentProcessId() << "\tTID = " << GetCurrentThreadId() << "\n";
		Sleep(1000);
	}

	return 0;
}

DWORD WINAPI ThirdTaskSecondThread()
{
	for (int i = 0; i < 125; i++)
	{
		std::cout << i << ". SecondThread PID = " << GetCurrentProcessId() << "\tTID = " << GetCurrentThreadId() << "\n";
		Sleep(1000);
	}

	return 0;
}

int ThirdTask::ShowPidTidCycle() {
	HANDLE FirstChildThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThirdTaskFirstThread, NULL, 0, NULL);
	HANDLE SecondChildThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThirdTaskSecondThread, NULL, 0, NULL);

	for (int i = 0; i < 100; i++)
	{
		if (i == 19)
			SuspendThread(FirstChildThread);
		if (i == 59)
			ResumeThread(FirstChildThread);

		if (i == 39)
			SuspendThread(SecondChildThread);
		if (i == 99)
			ResumeThread(SecondChildThread);

		std::cout << i << ". MainThread PID = " << pid << "\tTID = " << GetCurrentThreadId() << "\n";
		Sleep(1000);
	}

	WaitForSingleObject(FirstChildThread, INFINITE);
	CloseHandle(FirstChildThread);

	WaitForSingleObject(SecondChildThread, INFINITE);
	CloseHandle(SecondChildThread);

	return 0;
}