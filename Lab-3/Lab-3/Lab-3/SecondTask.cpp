#include "SecondTask.h"
#include <iostream>
#include <Windows.h>

DWORD SecondTask::pid = GetCurrentProcessId();
STARTUPINFO SecondTask::info;

int SecondTask::ShowPidCycle()
{

    for (int i = 0; i < 1000; i++)
    {
        std::cout << pid << " - " << i << std::endl;
        Sleep(1000);
    }

    return 0;
}

int SecondTask::StartProcess(LPCWSTR path, PROCESS_INFORMATION* process) {
    ZeroMemory(&info, sizeof(STARTUPINFO));
    info.cb = sizeof(STARTUPINFO);

    if (CreateProcess(
        path, //Путь к запускаемой программе
        NULL, //Параметр командой строки
        NULL, //Параметр для защиты процесса
        NULL, //Параметр для защиты зон памяти
        FALSE, //Наследование дескрипторов ввода/вывода
        CREATE_NEW_CONSOLE, //Создание нового окна консоли для дочернего процесса
        NULL, //Смена текущего рабочего каталога
        NULL, //Смена окружения дочернего процесса
        &info, //Структура, содержащая настройки для создания процесса
        process //Структура, которая будет заполнена информацией о созданном процессе
    ))
    {
        std::wcout << path;
        std::cout << " Процесс создан\n";
    }
    else {
        std::wcout << path;
        std::cout << " Процесс не создан\n";
        return -1;
    }

    return 0;
}