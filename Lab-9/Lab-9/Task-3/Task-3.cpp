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

BOOL InsRowFileText(LPWSTR pathToFile, LPWSTR string, DWORD row) {
	HANDLE file = CreateFile(pathToFile, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
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

	int line = 1, k = 0, j = 0;
	for (int i = 0; i < size; i++)
	{
		if (line == row)
		{
			for (int k = 0; k < wcslen(string); k++)
			{
				editedBuf[j] = string[k];
				j++;
				if (string[k + 1] == L'\0')
				{
					editedBuf[j] = '\r';
					j++;
					editedBuf[j] = '\n';
					j++;
					row = 0;
					break;
				}
			}
			i--;
		}
		else
		{
			editedBuf[j] = buf[i];
			j++;
		}

		if (buf[i] == '\n')
			line++;

		if (buf[i + 1] == '\0' && row == -1)
		{
			editedBuf[j - 1] = '\n';
			for (int k = 0; k < wcslen(string); k++)
			{
				editedBuf[j] = string[k];
				j++;
				if (string[k + 1] == L'\0')
				{
					editedBuf[j] = '\r';
					j++;
					editedBuf[j] = '\n';
					j++;
					row = 0;
					break;
				}
			}
		}
	}

	SetFilePointer(file, 0, NULL, FILE_BEGIN);
	SetEndOfFile(file);

	if (!WriteFile(file, editedBuf, j, &size, NULL)) {
		wprintf(L"Ошибка при записи в файл. Код ошибки: %u\n", GetLastError());
		CloseHandle(file);
		return FALSE;
	}

	cout << "\n\tПеред добавлением\n";
	cout << buf << endl;
	cout << "\n\tПосле добавления\n";
	cout << editedBuf << "\n\n\n\n";

	CloseHandle(file);
	return TRUE;
}

int main()
{
	setlocale(LC_ALL, "");

	LPWSTR pathToFile = (LPWSTR)FILE_PATH;

	char str[] = "MegamindMegamindMegamindMegamindMegamind";
	wchar_t wStr[50];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wStr, strlen(str) + 1, str, _TRUNCATE);

	LPWSTR strToIns = wStr;

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

	InsRowFileText(pathToFile, strToIns, 1);
	InsRowFileText(pathToFile, strToIns, -1);
	InsRowFileText(pathToFile, strToIns, 5);
	InsRowFileText(pathToFile, strToIns, 7);

	ReleaseMutex(hMutex);
	CloseHandle(hMutex);

	PrintFileText(pathToFile);

	system("pause");
	return 0;
}