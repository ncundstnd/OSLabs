#include <iostream>
#include "FirstTask.h"
#include "SecondTask.h"
#include "ThirdTask.h"

using namespace std;
int LaunchProcesses();

int main()
{
	int choice;
	setlocale(LC_ALL, "rus");

	while (true) {
		cout << "Введите номер задания (1-3)\n";
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			int count;
			cout << "Введите количество итераций\n";
			cin >> count;
			FirstTask::ShowPidCycle(count);
		} break;

		case 2:
		{
			LaunchProcesses();
			SecondTask::ShowPidCycle();
		} break;

		case 3:
		{
			LaunchProcesses();
			ThirdTask::ShowWindowsProcesses();
		} break;

		case 0:
		{
			exit(0);
		} break;

		default:
		{
		} break;
		}
	}

	return 0;
}

int LaunchProcesses() {
	LPCWSTR FirstProcessPath = L"STFP.exe";
	LPCWSTR SecondProcessPath = L"STSP.exe";

	PROCESS_INFORMATION FirstProcess;
	PROCESS_INFORMATION SecondProcess;

	SecondTask::StartProcess(FirstProcessPath, &FirstProcess);
	SecondTask::StartProcess(SecondProcessPath, &SecondProcess);

	return 0;
}