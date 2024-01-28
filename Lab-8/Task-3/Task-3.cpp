#include <iostream>
#include <Windows.h>

#define PG (4096)
int pg = 256;

int main()
{
	setlocale(LC_ALL, "");

	SYSTEM_INFO system_info;
	GetSystemInfo(&system_info);

	int* virtArray = (int*)VirtualAlloc(NULL, pg * PG, MEM_COMMIT, PAGE_READWRITE);

	for (int i = 0; i < pg * PG / 4; i++)
		virtArray[i] = i;

	int K = 0x4B, U = 0x55, R = 0x54;
	int index = (K * system_info.dwPageSize + ((U << 4) | (R >> 4))) / sizeof(int);

	std::cout << "Значение по адресу " << virtArray + index * sizeof(int) << ": " << virtArray[index] << std::endl;

	VirtualFree(virtArray, NULL, MEM_RELEASE) ?
		printf("Память освобождена\n") : printf("Память не освобождена\n");

	return 0;
}
