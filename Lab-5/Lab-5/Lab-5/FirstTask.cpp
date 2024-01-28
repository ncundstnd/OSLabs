#include "FirstTask.h"

void FirstTask::ShowInfo() {
	HANDLE CurrentProcess = GetCurrentProcess();
	HANDLE CurrentThread = GetCurrentThread();

	DWORD_PTR ProcessAffinityMask = NULL, SystemAffinityMask = NULL;
	GetProcessAffinityMask(CurrentProcess, &ProcessAffinityMask, &SystemAffinityMask);
	std::bitset<16> pa_bits(ProcessAffinityMask);
	std::bitset<16> sa_bits(SystemAffinityMask);
	//test
	//STARTUPINFO startupInfo;
	//PROCESS_INFORMATION processInfo;
	//if (CreateProcess(L"Task2X.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | 0x7283, NULL, NULL, &startupInfo, &processInfo)) {
	//	CloseHandle(processInfo.hProcess);
	//	CloseHandle(processInfo.hThread);
	//}
	//else {
	//	std::cout << "gg";
	//}
	std::cout << "Process ID:\t\t" << GetProcessId(CurrentProcess) << std::endl;
	std::cout << "Thread ID:\t\t" << GetThreadId(CurrentThread) << std::endl;
	std::cout << "Process priority:\t" << GetPriorityClass(CurrentProcess) << std::endl;
	std::cout << "Thread priority:\t" << GetThreadPriority(CurrentThread) << std::endl;
	std::cout << "Affinity mask:\t\t" << pa_bits << std::endl;
	std::cout << "Available processors:\t" << sa_bits.count() << std::endl;
	std::cout << "Current processor:\t" << GetCurrentProcessorNumber() << std::endl;
}