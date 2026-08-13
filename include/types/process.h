#pragma once

#include <windows.h>
#include <vector>
#include <string>
#include "handle.h"
#include "thread.h"
#include "modules.h"

struct PROCESS_ENTRY
{
    DWORD pid = 0;
    DWORD ppid = 0;
    std::wstring image_name;

    ULONG thread_count = 0;
    ULONG handle_count = 0;

    std::vector<HANDLE_ENTRY> handles;
    std::vector<THREAD_ENTRY> threads;
    std::vector<MODULE_ENTRY> modules;
};
