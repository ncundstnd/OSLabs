#include <iostream>
#include <ctime>
#include <Windows.h>

CRITICAL_SECTION cs;
DWORD processId = NULL;
DWORD WINAPI First() {
	DWORD threadId = GetCurrentThreadId();

	int start = clock();
	for (int i = 1; i < 91; i++) {
		if (i == 30) {
			EnterCriticalSection(&cs);
		}
		if (i == 60) {
			LeaveCriticalSection(&cs);
		}

		std::cout << i << " PID = " << processId << ", First TID = " << threadId << ", time: " << clock() - start << std::endl;
		Sleep(100);
	}

	return 0;
}
DWORD WINAPI Second() {
	DWORD threadId = GetCurrentThreadId();

	int start = clock();
	for (int i = 1; i < 91; i++) {
		if (i == 30) {
			EnterCriticalSection(&cs);
		}
		if (i == 60) {
			LeaveCriticalSection(&cs);
		}

		std::cout << i << " PID = " << processId << ", Second TID = " << threadId << ", time: " << clock() - start << std::endl;
		Sleep(100);
	}

	return 0;
}

int main() {
	processId = GetCurrentProcessId();

	InitializeCriticalSection(&cs);

	DWORD threadId = GetCurrentThreadId();
	DWORD firstThreadId = NULL, secondThreadId = NULL;
	HANDLE hFirst = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)First, NULL, 0, &firstThreadId);
	HANDLE hSecond = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Second, NULL, 0, &secondThreadId);

	int start = clock();
	for (int i = 1; i < 91; i++) {
		if (i == 30) {
			EnterCriticalSection(&cs);
		}
		if (i == 60) {
			LeaveCriticalSection(&cs);
		}

		std::cout << i << " PID = " << processId << ", Main TID = " << threadId << ", time: " << clock() - start << std::endl;
		Sleep(100);
	}

	WaitForSingleObject(hFirst, INFINITE);
	WaitForSingleObject(hSecond, INFINITE);
	LeaveCriticalSection(&cs);

	CloseHandle(hFirst);
	CloseHandle(hSecond);
	DeleteCriticalSection(&cs);

	system("pause");
	return 0;
}