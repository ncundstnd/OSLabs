#include <iostream>
#include <thread>
#include "FirstTask.h"
#include "SecondTask.h"
#include "ThirdTask.h"
#include "FourthTask.h"
#include "FifthTask.h"

using namespace std;

int main()
{
	int choice;
	setlocale(LC_ALL, "rus");

	while (true) {
		cout << "Введите номер задания (1-5)\n";
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			FirstTask::ShowPidTidCycle();
		} break;

		case 2:
		{
			SecondTask::ShowPidTidCycle();
		} break;

		case 3:
		{
			ThirdTask::ShowPidTidCycle();
		} break;

		case 4:
		{
			FourthTask::ShowPidTidCycle();
		} break;

		case 5:
		{
			FifthTask::ShowPidTidCycle();
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