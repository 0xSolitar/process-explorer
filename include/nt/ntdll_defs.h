#pragma once

#include <windows.h>
#include <winternl.h>
#include "nt_structs.h"

#define STATUS_INFO_LENGTH_MISMATCH 0xC0000004
#define STATUS_SUCCESS 0

#ifndef SystemProcessInformation
#define SystemProcessInformation 5
#endif

#define LDR_OFFSET 0x018
#define IN_LOAD_ORDER_MODULE_LIST_OFFSET 0x010

typedef const OBJECT_ATTRIBUTES *PCOBJECT_ATTRIBUTES;

typedef NTSTATUS (NTAPI *PNtQuerySystemInformation)(
    _In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
    _Out_writes_bytes_opt_(SystemInformationLength) PVOID SystemInformation,
    _In_ ULONG SystemInformationLength,
    _Out_opt_ PULONG ReturnLength);

typedef NTSTATUS (NTAPI* PNtOpenProcess)(
    _Out_ PHANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ PCOBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ CLIENT_ID* ClientId);

typedef NTSTATUS (NTAPI *PNtQueryInformationProcess)(
    _In_ HANDLE ProcessHandle,
    _In_ PROCESSINFOCLASS ProcessInformationClass,
    _Out_writes_bytes_(ProcessInformationLength) PVOID ProcessInformation,
    _In_ ULONG ProcessInformationLength,
    _Out_opt_ PULONG ReturnLength);

typedef NTSTATUS (NTAPI *PNtReadVirtualMemory)(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _Out_writes_bytes_to_(NumberOfBytesToRead, *NumberOfBytesRead) PVOID Buffer,
    _In_ SIZE_T NumberOfBytesToRead,
    _Out_opt_ PSIZE_T NumberOfBytesRead);
