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

struct PROCESS_ENTRY
{
    DWORD pid = 0;
    DWORD ppid = 0;
    std::wstring imageName;
    ULONG threadCount = 0;
    ULONG handleCount = 0;

    std::vector<HANDLE_ENTRY> handleEntry;
    std::vector<THREAD_ENTRY> threadEntry;
};

std::vector<PROCESS_ENTRY> GetProcessEntries();
#endif
