#pragma once
#include <Windows.h>
#include <iostream>

static class FirstTask
{
private:
    static DWORD pid;

public:
    static int ShowPidCycle(int count);
};
