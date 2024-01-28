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

	HANDLE heap = HeapCreate(HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 4096 * 1024, 0);

	std::cout << "\n------------До выделения блока--------------\n";
	sh(heap);

	int* array = (int*)HeapAlloc(heap, HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 300000 * sizeof(int));

	std::cout << "\nАдрес начала массива: " << array << " \n";
	std::cout << "\n------------После выделения блока--------------\n";
	sh(heap);

	HeapFree(heap, HEAP_NO_SERIALIZE, array);

	std::cout << "\n------------После освобождения блока--------------\n";
	sh(heap);

	HeapDestroy(heap);

	return 0;
}