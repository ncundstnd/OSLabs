#include <Windows.h>
#include <iostream>
#include <ctime>

int main() {
	int start = clock();

	DWORD pid = GetCurrentProcessId();
	HANDLE hm = OpenMutex(SYNCHRONIZE, FALSE, L"Mutex");

	if (hm == NULL) {
		std::cout << "Second: Open Error Mutex\n";
	}
	else {
		std::cout << "Second: Open Mutex\n";
	}
 
	for (int i = 1; i < 91; i++) {
		if (i == 30) {
			WaitForSingleObject(hm, INFINITE);
		}
		if (i == 60) {
			ReleaseMutex(hm);
		}

		std::cout << i << " Second pid = " << pid << ", time: " << clock() - start << std::endl;
		Sleep(100);
	}

	CloseHandle(hm);

	system("pause");
	return 0;
}