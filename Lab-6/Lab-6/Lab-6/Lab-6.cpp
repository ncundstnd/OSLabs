#include <iostream>
#include <ctime>
#include <Windows.h>

int check = 0;

void EnterASM() {
	_asm {
	Cycle:
		lock bts check, 0;
		jc Cycle
	}
}

void LeaveASM() {
	_asm lock btr check, 0
}

DWORD WINAPI First() {
	int start = clock();

	EnterASM();
	for (int i = 1; i < 6; i++) {
		std::cout << "First:" << i << ", time: " << clock() - start << std::endl;
	}
	LeaveASM();

	return 0;
}

DWORD WINAPI Second() {
	int start = clock();

	EnterASM();
	for (int i = 1; i < 6; i++) {
		std::cout << "Second:" << i << ", time: " << clock() - start << std::endl;
	}
	LeaveASM();

	return 0;
}

int main() {
	DWORD FirstId = NULL, SecondId = NULL;

	HANDLE hFirst = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)First, NULL, 0, &FirstId);
	HANDLE hSecond = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Second, NULL, 0, &SecondId);


	WaitForSingleObject(hFirst, INFINITE);
	WaitForSingleObject(hSecond, INFINITE);

	CloseHandle(hFirst);
	CloseHandle(hSecond);

	system("pause");
	return 0;
}