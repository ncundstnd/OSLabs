#include "FirstTask.h"

using namespace std;

int main()
{
	int choice;
	setlocale(LC_ALL, "rus");

	while (true) {
		cout << "Введите номер задания (1)\n";
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			FirstTask::ShowInfo();
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