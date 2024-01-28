#include <Windows.h>
#include <iostream>

#define FILE_PATH L"C:\\Study\\ОС\\Lab-9\\Lab-9\\students.txt"
using namespace std;

HANDLE hMutex;

BOOL PrintFileText(LPWSTR pathToFile)
{
	HANDLE file = CreateFile(pathToFile, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	BY_HANDLE_FILE_INFORMATION fileInfo;
	char buf[1024] = {};

	if (!GetFileInformationByHandle(file, &fileInfo)) {
		wprintf(L"Ошибка при получении информации о файле. Код ошибки: %u\n", GetLastError());
		CloseHandle(file);
		return FALSE;
	}
	if (!ReadFile(file, &buf, fileInfo.nFileSizeLow, NULL, NULL)) {
		wprintf(L"Ошибка при чтении файла. Код ошибки: %u\n", GetLastError());
		CloseHandle(file);
		return FALSE;
	}

	cout << endl << buf << endl;

	CloseHandle(file);
	return TRUE;
}

BOOL DelRowFileTxt(LPWSTR pathToFile, DWORD row) {
	HANDLE file = CreateFile(pathToFile, GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	BY_HANDLE_FILE_INFORMATION fileInfo;
	char buf[1024] = {};
	char editedBuf[1024] = {};

	DWORD size = NULL;

	if (!GetFileInformationByHandle(file, &fileInfo)) {
		wprintf(L"Ошибка при получении информации о файле. Код ошибки: %u\n", GetLastError());
		CloseHandle(file);
		return FALSE;
	}
	if (!ReadFile(file, &buf, fileInfo.nFileSizeLow, &size, NULL)) {
		wprintf(L"Ошибка при чтении файла. Код ошибки: %u\n", GetLastError());
		CloseHandle(file);
		return FALSE;
	}

	int line = 1, j = 0;
	bool rowFound = false;
	for (int i = 0; i < size; i++)
	{
		if (line == row)
			rowFound = true;
		else
		{
			editedBuf[j] = buf[i];
			j++;
		}

		if (buf[i] == '\n')
			line++;
	}

	SetFilePointer(file, 0, NULL, FILE_BEGIN);
	SetEndOfFile(file);

	if (!WriteFile(file, editedBuf, j, &size, NULL)) {
		wprintf(L"Ошибка при записи в файл. Код ошибки: %u\n", GetLastError());
		CloseHandle(file);
		return FALSE;
	}

	cout << "\n\tПеред удалением\n";
	cout << buf << endl;
	cout << "\n\tПосле удаления\n";
	cout << editedBuf << "\n\n\n\n";

	CloseHandle(file);
	return TRUE;
}

int main()
{
	setlocale(LC_ALL, "");

	LPWSTR pathToFile = (LPWSTR)FILE_PATH;

	hMutex = CreateMutex(NULL, TRUE, L"MyFileMutex");
	if (hMutex == NULL)
	{
		wprintf(L"Ошибка при создании мьютекса. Код ошибки: %u\n", GetLastError());
		return 1;
	}

	DWORD waitResult = WaitForSingleObject(hMutex, 0);
	if (waitResult != WAIT_OBJECT_0 && waitResult != WAIT_ABANDONED)
	{
		wprintf(L"Ошибка при захвате мьютекса. Код ошибки: %u\n", GetLastError());
		CloseHandle(hMutex);
		return 1;
	}

	DelRowFileTxt(pathToFile, 1);
	DelRowFileTxt(pathToFile, 3);
	DelRowFileTxt(pathToFile, 5);
	DelRowFileTxt(pathToFile, 10);

	ReleaseMutex(hMutex);
	CloseHandle(hMutex);

	PrintFileText(pathToFile);

	system("pause");
	return 0;
}