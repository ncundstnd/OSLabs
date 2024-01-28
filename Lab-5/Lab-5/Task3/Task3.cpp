#include <iostream>
#include <string>
#include <bitset>
#include <Windows.h>
#include <chrono>

int ThreadFunction()
{
	auto start_time = std::chrono::high_resolution_clock::now();

	HANDLE CurrentProcess = GetCurrentProcess();
	HANDLE CurrentThread = GetCurrentThread();

	DWORD_PTR ProcessAffinityMask = NULL, SystemAffinityMask = NULL;
	GetProcessAffinityMask(CurrentProcess, &ProcessAffinityMask, &SystemAffinityMask);
	std::bitset<16> pa_bits(ProcessAffinityMask);

	for (int index = 0; index < 1000000; index++)
	{
		if (index % 1000 == 0 && index != 0) {
			Sleep(200);
			std::cout << "------------------------------------------------" << std::endl;
			std::cout << "Iteration number:\t" << index << std::endl;
			std::cout << "Process ID:\t\t" << GetProcessId(CurrentProcess) << std::endl;
			std::cout << "Thread ID:\t\t" << GetThreadId(CurrentThread) << std::endl;
			std::cout << "Process priority:\t" << GetPriorityClass(CurrentProcess) << std::endl;
			std::cout << "Thread priority:\t" << GetThreadPriority(CurrentThread) << std::endl;
			std::cout << "Available processors:\t" << pa_bits.count() << std::endl;
			std::cout << "Current processor:\t" << GetCurrentProcessorNumber() << std::endl;
			std::cout << "------------------------------------------------" << std::endl;
		}
	}

	auto end_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

	std::cout << "Executing time: " << duration.count() / 1000 << "milliseconds " << GetThreadId(CurrentThread) << std::endl;

	system("pause");
	return 0;
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "rus");
	if (argc != 5) {
		return 1;
	}
	else {
		int AvailableProcessors = std::stoi(argv[1]);
		int ProcessPriority = std::stoi(argv[2]);
		int FirstChildThreadPriority = std::stoi(argv[3]);
		int SecondChildThreadPriority = std::stoi(argv[4]);

		// Проверка приоритета текущего процесса
		switch (ProcessPriority) {
		case 128:
			SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
			break;
		case 32768:
			SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);
			break;
		case 32:
			SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
			break;
		case 16384:
			SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);
			break;
		default:
			std::cerr << "Недопустимое значение приоритета для текущего процесса." << std::endl;
			return 1;
		}

		// Проверка приоритетов дочерних потоков
		switch (FirstChildThreadPriority) {
		case 2:
			FirstChildThreadPriority = THREAD_PRIORITY_HIGHEST;
			break;
		case 0:
			FirstChildThreadPriority = THREAD_PRIORITY_NORMAL;
			break;
		case -2:
			FirstChildThreadPriority = THREAD_PRIORITY_LOWEST;
			break;
		default:
			std::cerr << "Недопустимое значение приоритета для первого дочернего потока." << std::endl;
			return 1;
		}

		switch (SecondChildThreadPriority) {
		case 2:
			SecondChildThreadPriority = THREAD_PRIORITY_HIGHEST;
			break;
		case 0:
			SecondChildThreadPriority = THREAD_PRIORITY_NORMAL;
			break;
		case -2:
			SecondChildThreadPriority = THREAD_PRIORITY_LOWEST;
			break;
		default:
			std::cerr << "Недопустимое значение приоритета для второго дочернего потока." << std::endl;
			return 1;
		}

		// Установка количества доступных процессоров
		DWORD_PTR processAffinityMask = (1ULL << AvailableProcessors) - 1;
		if (SetProcessAffinityMask(GetCurrentProcess(), processAffinityMask) == 0) {
			std::cerr << "Ошибка при установке маски доступности процессоров." << std::endl;
		}

		// Создание потоков
		HANDLE FirstChildThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFunction, NULL, 0, NULL);
		SetThreadPriority(FirstChildThread, FirstChildThreadPriority);

		HANDLE SecondChildThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFunction, NULL, 0, NULL);
		SetThreadPriority(SecondChildThread, SecondChildThreadPriority);

		ThreadFunction();

		// Ожидание завершения
		WaitForSingleObject(FirstChildThread, 1000);
		WaitForSingleObject(SecondChildThread, 1000);
	}

	return 0;
}