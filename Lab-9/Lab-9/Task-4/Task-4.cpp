#include <iostream>
#include <cstdlib>
#include "Windows.h"

#define FILE_PATH L"C:\\Study\\ОС\\Lab-9\\Lab-9\\students.txt"
#define DIR_PATH L"C:\\Study\\ОС\\Lab-9\\Lab-9"

using namespace std;

HANDLE hMutex;

BOOL PrintWatchRowFileText(LPWSTR pathToFile, DWORD mlsec)
{
	HANDLE hChange = FindFirstChangeNotification(DIR_PATH, FALSE, FILE_NOTIFY_CHANGE_SIZE);
	if (hChange == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Ошибка при создании уведомления об изменении файла. Код ошибки: %u\n", GetLastError());
		return FALSE;
	}

	HANDLE hFile = CreateFile(pathToFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Ошибка при открытии файла. Код ошибки: %u\n", GetLastError());
		return FALSE;
	}
	BY_HANDLE_FILE_INFORMATION fileInfo;
	char buf[1024] = {};

	DWORD size = NULL;
	int rows = 0;

	if (!GetFileInformationByHandle(hFile, &fileInfo)) {
		wprintf(L"Ошибка при получении информации о файле. Код ошибки: %u\n", GetLastError());
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, &buf, fileInfo.nFileSizeLow, &size, NULL)) {
		wprintf(L"Ошибка при чтении файла. Код ошибки: %u\n", GetLastError());
		CloseHandle(hFile);
		return FALSE;
	}

	for (int i = 0; i < size; i++)
	{
		if (buf[i] == '\n')
			rows++;
	}

	wprintf(L"Размер файла до изменений: %u байт\n", rows);
	rows = 0;
	CloseHandle(hFile);

	DWORD waitResult = WaitForSingleObject(hChange, mlsec);
	if (waitResult != WAIT_OBJECT_0)
	{
		wprintf(L"Ошибка при ожидании изменения файла или время ожидания истекло. Код ошибки: %u\n", GetLastError());
		CloseHandle(hChange);
		return FALSE;
	}
	else if (waitResult == WAIT_OBJECT_0) {
		WaitForSingleObject(hMutex, INFINITE);
		HANDLE hFile = CreateFile(pathToFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			wprintf(L"Ошибка при открытии файла. Код ошибки: %u\n", GetLastError());
			return FALSE;
		}
		BY_HANDLE_FILE_INFORMATION fileInfo;
		char editedBuf[1024] = {};

		DWORD size = NULL;

		if (!GetFileInformationByHandle(hFile, &fileInfo)) {
			wprintf(L"Ошибка при получении информации о файле. Код ошибки: %u\n", GetLastError());
			CloseHandle(hFile);
			return FALSE;
		}
		if (!ReadFile(hFile, &buf, fileInfo.nFileSizeLow, &size, NULL)) {
			wprintf(L"Ошибка при чтении файла. Код ошибки: %u\n", GetLastError());
			CloseHandle(hFile);
			return FALSE;
		}

		for (int i = 0; i < size; i++)
		{
			if (buf[i] == '\n')
				rows++;
		}

		wprintf(L"Размер файла после изменений: %u байт\n", rows);
		rows = 0;

		CloseHandle(hFile);
	}

	CloseHandle(hChange);
	return TRUE;
}

int main()
{
	setlocale(LC_ALL, "");

	LPWSTR pathToFile = (LPWSTR)FILE_PATH;

	hMutex = CreateMutex(NULL, FALSE, L"MyFileMutex");
	if (hMutex == NULL)
	{
		wprintf(L"Ошибка при создании мьютекса. Код ошибки: %u\n", GetLastError());
		return 1;
	}

	PrintWatchRowFileText(pathToFile, 15000);

	ReleaseMutex(hMutex);
	CloseHandle(hMutex);

	system("pause");
	return 0;
}