#include <Windows.h>
#include <iostream>

LPCWSTR pathToExe = L"C:\\Study\\ОС\\Lab-7\\x64\\Release\\Task-4X.exe";

void CreateAndTerminateProcess(DWORD waitTime, int number)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	if (CreateProcess(pathToExe, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		std::cout << "Процесс " << number << " создан." << std::endl;

		WaitForSingleObject(pi.hProcess, waitTime);
		TerminateProcess(pi.hProcess, 0);

		std::cout << "Процесс " << number << " завершен." << std::endl;
	}
}

DWORD WINAPI ChildThreadProcess1()
{
	CreateAndTerminateProcess(60000, 1);
	return 0;
}

DWORD WINAPI ChildThreadProcess2()
{
	CreateAndTerminateProcess(120000, 2);
	return 0;
}

int main()
{
	setlocale(LC_ALL, "");

	HANDLE hChild1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThreadProcess1, NULL, NULL, NULL);
	HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThreadProcess2, NULL, NULL, NULL);

	WaitForSingleObject(hChild1, INFINITE);
	WaitForSingleObject(hChild2, INFINITE);

	return 0;
}