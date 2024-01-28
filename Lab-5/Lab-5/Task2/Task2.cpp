#include <iostream>
#include <string>
#include <Windows.h>

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "rus");
	if (argc != 4) {
		return 1;
	}
	else {
		int AvailableProcessors = std::stoi(argv[1]);
		int FirstChildProcessPriority = std::stoi(argv[2]);
		int SecondChildProcessPriority = std::stoi(argv[3]);

		int firstPriority, secondPriority;

		switch (FirstChildProcessPriority) {
		case 128:
			firstPriority = HIGH_PRIORITY_CLASS;
			break;
		case 32786:
			firstPriority = ABOVE_NORMAL_PRIORITY_CLASS;
			break;
		case 32:
			firstPriority = NORMAL_PRIORITY_CLASS;
			break;
		case 16384:
			firstPriority = BELOW_NORMAL_PRIORITY_CLASS;
			break;
		default:
			std::cerr << "Недопустимое значение приоритета для первого дочернего процесса." << std::endl;
			return 1;
		}

		switch (SecondChildProcessPriority) {
		case 128:
			secondPriority = HIGH_PRIORITY_CLASS;
			break;
		case 32786:
			secondPriority = ABOVE_NORMAL_PRIORITY_CLASS;
			break;
		case 32:
			secondPriority = NORMAL_PRIORITY_CLASS;
			break;
		case 16384:
			secondPriority = BELOW_NORMAL_PRIORITY_CLASS;
			break;
		default:
			std::cerr << "Недопустимое значение приоритета для второго дочернего процесса." << std::endl;
			return 1;
		}

		// Установка количества доступных процессоров
		DWORD_PTR processAffinityMask = (1ULL << AvailableProcessors) - 1;
		if (SetProcessAffinityMask(GetCurrentProcess(), processAffinityMask) == 0) {
			std::cerr << "Ошибка при установке маски доступности процессоров." << std::endl;
		}

		// Создание и запуск дочерних процессов с установленными приоритетами и количеством доступных процессоров
		STARTUPINFO startupInfo;
		PROCESS_INFORMATION processInfo;

		if (CreateProcess(L"Task2X.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | firstPriority, NULL, NULL, &startupInfo, &processInfo)) {
			CloseHandle(processInfo.hProcess);
			CloseHandle(processInfo.hThread);
		}
		else {
			return 1;
		}

		if (CreateProcess(L"Task2X.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | secondPriority, NULL, NULL, &startupInfo, &processInfo)) {
			CloseHandle(processInfo.hProcess);
			CloseHandle(processInfo.hThread);
		}
		else {
			return 1;
		}
	}
	system("pause");
}