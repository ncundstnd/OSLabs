#include <iostream>
#include <Windows.h>

#define FILE_PATH L"C:\\Study\\ОС\\Lab-9\\Lab-9\\students.txt"
using namespace std;

LPCWSTR GetFileTypeString(HANDLE file)
{
	switch (GetFileType(file))
	{
	case FILE_TYPE_UNKNOWN: return L"FILE_TYPE_UNKNOWN";
	case FILE_TYPE_DISK: return L"FILE_TYPE_DISK";
	case FILE_TYPE_CHAR: return L"FILE_TYPE_CHAR";
	case FILE_TYPE_PIPE: return L"FILE_TYPE_PIPE";
	case FILE_TYPE_REMOTE: return L"FILE_TYPE_REMOTE";
	default: return L"UNKNOWN";
	}
}

BOOL PrintFileInfo(LPCWSTR pathToFile)
{
	HANDLE file = CreateFile(pathToFile, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	BY_HANDLE_FILE_INFORMATION fileInfo;

	if (!GetFileInformationByHandle(file, &fileInfo)) {
		CloseHandle(file);
		return FALSE;
	}

	SYSTEMTIME createTime, lastWriteTime;
	wstring ws = (wchar_t*)FILE_PATH;
	string fileName(ws.begin(), ws.end());
	fileName = fileName.substr(fileName.rfind('\\') + 1);

	FileTimeToSystemTime(&fileInfo.ftCreationTime, &createTime);
	FileTimeToSystemTime(&fileInfo.ftLastWriteTime, &lastWriteTime);

	printf("Размер файла: %u\n", fileInfo.nFileSizeLow);
	wcout << "File type: " << GetFileTypeString(file) << endl;
	printf("Дата создания: %04d-%02d-%02d %02d:%02d:%02d\n",
		createTime.wYear, createTime.wMonth, createTime.wDay,
		createTime.wHour + 3, createTime.wMinute, createTime.wSecond);
	printf("Дата последнего изменения: %04d-%02d-%02d %02d:%02d:%02d\n",
		lastWriteTime.wYear, lastWriteTime.wMonth, lastWriteTime.wDay,
		lastWriteTime.wHour + 3, lastWriteTime.wMinute, lastWriteTime.wSecond);
	printf("Имя файла: %s\n", fileName.c_str());

	CloseHandle(file);
	return TRUE;
}

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

int main()
{
	setlocale(LC_ALL, "");

	LPWSTR pathToFile = (LPWSTR)FILE_PATH;

	PrintFileInfo(pathToFile);
	PrintFileText(pathToFile);

	system("pause");
	return 0;
}