#include <Windows.h>
#include <iostream>
#include <ctime>

int main() {
	int start = clock();

	DWORD pid = GetCurrentProcessId();
	HANDLE hs = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"Semaphore");

	if (hs == NULL) {
		std::cout << "First: Open Error Semaphore\n";
	}
	else {
		std::cout << "First: Open Semaphore\n";
	}

	for (int i = 1; i < 91; i++) {
		if (i == 30) {
			WaitForSingleObject(hs, INFINITE);
		}
		if (i == 60) {
			ReleaseSemaphore(hs, 1, 0);
		}

		std::cout << i << " First pid = " << pid << ", time: " << clock() - start << std::endl;
		Sleep(100);
	}

	CloseHandle(hs);

	system("pause");
	return 0;
}