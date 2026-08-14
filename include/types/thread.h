#pragma once

#include <windows.h>
#include <winternl.h>
#include "../nt/ntdll_defs.h"
#include <vector>

struct Thread {
    DWORD tid = 0;

    ULONG context_switches;
    LONGLONG kernel_time = 0;
    LONGLONG user_time = 0;
    LONGLONG create_time = 0;

    KPRIORITY base_priority;
    KPRIORITY priority;

    PVOID start_address = nullptr;
    KTHREAD_STATE state;
    KWAIT_REASON wait_reason;

};
