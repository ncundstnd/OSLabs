#include <iostream>
#include <Windows.h>
#define SECOND 10000000

clock_t start;
int iteration;
bool finish = false;

VOID CALLBACK MyTimerFunction(LPVOID lpArg, DWORD dwTimerLowValue, DWORD dwTimerHighValue)
{
	printf("Итерация: %d, миллисекунды: %ld\n", iteration, clock() - start);
	if ((clock() - start) / CLOCKS_PER_SEC >= 15)
		finish = true;
}

int main(void)
{
	setlocale(LC_ALL, "");

	HANDLE hTimer = CreateWaitableTimer(NULL, FALSE, NULL);

	LARGE_INTEGER liDueTime;
	liDueTime.QuadPart = -3 * SECOND;

	start = clock();
	if (SetWaitableTimer(hTimer, &liDueTime, 3000, MyTimerFunction, NULL, FALSE))
	{
		while (true) {
			iteration++;
			SleepEx(0, TRUE);
			if (finish)
				break;
		}
	}

	CloseHandle(hTimer);

	return 0;
}