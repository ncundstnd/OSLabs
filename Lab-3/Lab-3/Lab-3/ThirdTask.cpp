#include "ThirdTask.h"
#include "tlhelp32.h"
#include <iostream>

DWORD ThirdTask::pid = GetCurrentProcessId();

int ThirdTask::ShowWindowsProcesses() {
	PROCESSENTRY32 ProcessEntry;
	ProcessEntry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE ProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (Process32First(ProcessSnapshot, &ProcessEntry)) {
		std::cout << "PID\t" << "\tИмя процесса\n";
		do {
			std::cout << ProcessEntry.th32ProcessID << '\t';
			std::wcout << L'\t' << ProcessEntry.szExeFile << L'\n';
		} while (Process32Next(ProcessSnapshot, &ProcessEntry));
	}
	else {
		std::cerr << "Ошибка: " << GetLastError() << std::endl;
		return -1;
	}

	return 0;
}