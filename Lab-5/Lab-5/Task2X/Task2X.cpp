#include <iostream>
#include <Windows.h>
#include <bitset>
#include <chrono>

int main()
{
	auto start_time = std::chrono::high_resolution_clock::now();

	HANDLE CurrentProcess = GetCurrentProcess();
	HANDLE CurrentThread = GetCurrentThread();

	DWORD_PTR ProcessAffinityMask = NULL, SystemAffinityMask = NULL;
	GetProcessAffinityMask(CurrentProcess, &ProcessAffinityMask, &SystemAffinityMask);
	std::bitset<16> pa_bits(ProcessAffinityMask);

	DWORD PID = GetProcessId(CurrentProcess);
	DWORD TID = GetThreadId(CurrentThread);
	DWORD ProcessPriority = GetPriorityClass(CurrentProcess);
	DWORD ThreadPriority = GetThreadPriority(CurrentThread);
	int AvailableProcessors = pa_bits.count();

	for (int index = 0; index < 1000000; index++)
	{
		if (index % 1000 == 0 && index != 0) {
			Sleep(200);
			std::cout << "Iteration number:\t" << index << std::endl;
			std::cout << "Process ID:\t\t" << PID << std::endl;
			std::cout << "Thread ID:\t\t" << TID << std::endl;
			std::cout << "Process priority:\t" << ProcessPriority << std::endl;
			std::cout << "Thread priority:\t" << ThreadPriority << std::endl;
			std::cout << "Available processors:\t" << AvailableProcessors << std::endl;
			std::cout << "Current processor:\t" << GetCurrentProcessorNumber() << std::endl;
		}
	}

	auto end_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

	std::cout << "Executing time: " << duration.count() / 1000 << "milliseconds" << std::endl;

	system("pause");

	return 0;
}