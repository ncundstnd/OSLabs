#include <iostream>
#include <Windows.h>

void sh(HANDLE pheap)
{
	PROCESS_HEAP_ENTRY phe;
	phe.lpData = NULL;
	while (HeapWalk(pheap, &phe))
		std::cout << "Адрес: " << phe.lpData
		<< ", Размер: " << phe.cbData
		<< ((phe.wFlags & PROCESS_HEAP_REGION) ? " R" : "")
		<< ((phe.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) ? " U" : "")
		<< ((phe.wFlags & PROCESS_HEAP_ENTRY_BUSY) ? " B" : "")
		<< "\n";
}

int main()
{
	setlocale(LC_ALL, "");
	HANDLE heap = GetProcessHeap();

	sh(heap);

	int* array = new int[300000];
	std::cout << "====================================Адрес: " << array << ", Размер: 300000\n";

	sh(heap);
}