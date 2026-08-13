#pragma once

#include <windows.h>
#include <winternl.h>

typedef struct _LDR_DATA_TABLE_ENTRY64 {
    LIST_ENTRY InLoadOrderLinks;          // offset 0x0
    LIST_ENTRY InMemoryOrderLinks;        // offset 0x10
    LIST_ENTRY InInitializationOrderLinks;// offset 0x20
    PVOID DllBase;                        // offset 0x30
    PVOID EntryPoint;                     // offset 0x38
    ULONG SizeOfImage;                    // offset 0x40
    UNICODE_STRING FullDllName;           // offset 0x48
    UNICODE_STRING BaseDllName;           // offset 0x58
} LDR_DATA_TABLE_ENTRY64, *PLDR_DATA_TABLE_ENTRY64;
