#include "FirstTask.h"
#include <iostream>

DWORD FirstTask::pid = GetCurrentProcessId();
DWORD FirstTask::tid = GetCurrentThreadId();

int FirstTask::ShowPidTidCycle() {
	for (int i = 0; i < 100; i++)
	{
		std::cout << i << ". CurrentThread PID = " << pid << "\tTID = " << tid << "\n";
		Sleep(1000);
	}
	return 0;
}