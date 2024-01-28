#include <Windows.h>
#include <iostream>
#include <ctime>

int main() {
	int start = clock();

	DWORD pid = GetCurrentProcessId();
	HANDLE he = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"Event");

	if (he == NULL) {
		std::cout << "Second: Open Error Event\n";
	}
	else {
		std::cout << "Second: Open Event\n";
	}

	WaitForSingleObject(he, INFINITE);
	for (int i = 1; i < 91; i++) {
		std::cout << i << " Second pid = " << pid << ", time: " << clock() - start << std::endl;
		Sleep(100);
	}

	CloseHandle(he);

	system("pause");
	return 0;
}