#include <stdio.h>
#include <Windows.h>

int main()
{
	int n = 1000;

	for (int i = 0; i < n; i++)
	{
		printf("%d-%d\n", GetCurrentProcessId(), i);
		Sleep(1000);
	}
}