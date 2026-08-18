#pragma once

#include <windows.h>

struct Handle {
    DWORD pid;
    ULONG_PTR value = 0;
    ULONG access;
};
