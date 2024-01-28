#include "FirstTask.h"
#include <iostream>
#include <Windows.h>

DWORD FirstTask::pid = GetCurrentProcessId();

int FirstTask::ShowPidCycle(int count)
{
    for (int i = 0; i < count; i++)
    {
        std::cout << pid << " - " << i << std::endl;
        Sleep(1000);
    }

    return 0;
}
