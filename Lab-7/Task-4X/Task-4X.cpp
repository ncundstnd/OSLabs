#include <Windows.h>
#include <iostream>
#include <ctime>

int main()
{
	for (int i = 2; i < INFINITE; i++)
	{
		for (int j = 2; j < i; j++)
		{
			if (i % j == 0)
				break;
			else if (i == j + 1)
				std::cout << i << std::endl;
		}
	}
	system("pause");
	return 0;
}