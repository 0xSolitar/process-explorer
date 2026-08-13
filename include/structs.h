#ifndef STRUCTS_H
#define STRUCTS_H

#include <windows.h>
#include <string>
#include <vector>

struct HANDLE_ENTRY {
    HANDLE value = nullptr;
};

struct THREAD_ENTRY {
    DWORD tid = 0;
};

// dll
struct MODULE_ENTRY {
    std::wstring name;
};

struct PROCESS_ENTRY
{
    DWORD pid = 0;
    DWORD ppid = 0;
    std::wstring image_name;

    ULONG thread_count = 0;
    ULONG handle_count = 0;

    std::vector<HANDLE_ENTRY> handles;
    std::vector<THREAD_ENTRY> threads;
    std::vector<MODULE_ENTRY> mudules;
};

std::vector<PROCESS_ENTRY> enum_processes();
#endif
