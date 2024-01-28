#include <Windows.h>
#include <iostream>
#include <ctime>

int main() {
	int start = clock();
	DWORD pid = GetCurrentProcessId();
	HANDLE hm = CreateMutex(NULL, FALSE, L"Mutex");

	LPCWSTR FirstProcess = L"C:\\Study\\ОС\\Lab-6\\Lab-6\\x64\\Release\\Task-3-F.exe";
	LPCWSTR SecondProcess = L"C:\\Study\\ОС\\Lab-6\\Lab-6\\x64\\Release\\Task-3-S.exe";

	STARTUPINFO FirstProcessStartInfo; STARTUPINFO SecondProcessStartInfo;

	PROCESS_INFORMATION FirstProcessInfo; PROCESS_INFORMATION SecondProcessInfo;

	ZeroMemory(&FirstProcessStartInfo, sizeof(STARTUPINFO)); ZeroMemory(&SecondProcessStartInfo, sizeof(STARTUPINFO));

	FirstProcessStartInfo.cb = sizeof(STARTUPINFO); SecondProcessStartInfo.cb = sizeof(STARTUPINFO);

	if (CreateProcess(FirstProcess, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &FirstProcessStartInfo, &FirstProcessInfo)) {
		std::cout << "First child process created\n";
	}
	else {
		std::cout << "First child process not created\n";
	}

	if (CreateProcess(SecondProcess, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &SecondProcessStartInfo, &SecondProcessInfo)) {
		std::cout << "Second child process created\n";
	}
	else {
		std::cout << "Second child process not created\n";
	}

	for (int i = 1; i < 91; i++) {
		if (i == 30) {
			WaitForSingleObject(hm, INFINITE);
		}
		if (i == 60) {
			ReleaseMutex(hm);
		}

		std::cout << i << " Main pid = " << pid << ", time: " << clock() - start << std::endl;
		Sleep(100);
	}

	WaitForSingleObject(FirstProcessInfo.hProcess, INFINITE);
	WaitForSingleObject(SecondProcessInfo.hProcess, INFINITE);

	CloseHandle(hm);

	CloseHandle(FirstProcessInfo.hProcess);
	CloseHandle(SecondProcessInfo.hProcess);

	system("pause");
	return 0;
}