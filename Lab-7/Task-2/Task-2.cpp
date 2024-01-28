#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	int i = 0;
	clock_t t1 = clock();
	while (true)
	{
		i++;
		clock_t t2 = clock();
		if ((t2 - t1) == 5000 || (t2 - t1) == 10000)
		{
			cout << "Номер итерации: " << i << endl;
		}
		if ((t2 - t1) == 15000) break;
	}
	cout << "Окончательное число итераций: " << i << endl;
}