#pragma once

#include <windows.h>
#include <winternl.h>
#include "nt_structs.h"

#ifndef STATUS_INFO_LENGTH_MISMATCH
#define STATUS_INFO_LENGTH_MISMATCH ((NTSTATUS)0xC0000004)
#endif

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS 0
#endif

#ifndef STATUS_ACCESS_DENIED
#define STATUS_ACCESS_DENIED ((NTSTATUS)0xC0000022)
#endif

#ifndef STATUS_INVALID_CID
#define STATUS_INVALID_CID ((NTSTATUS)0xC000000B)
#endif

#ifndef SystemProcessInformation
#define SystemProcessInformation 5
#endif

#ifndef ProcessProtectionInformation
#define ProcessProtectionInformation 61
#endif

#ifndef SystemExtendedHandleInformation
#define SystemExtendedHandleInformation  0x40
#endif

#ifndef ObjectBasicInformation
#define ObjectBasicInformation 0
#endif

#ifndef ObjectNameInformation
#define ObjectNameInformation 1
#endif

#ifndef ObjectTypeInformation
#define ObjectTypeInformation 2
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

typedef NTSTATUS (NTAPI* PNtClose)(
    _In_ _Post_ptr_invalid_ HANDLE Handle
    );

typedef NTSTATUS (NTAPI* PNtQueryObject)(
    _In_opt_ HANDLE Handle,
    _In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
    _Out_writes_bytes_opt_(ObjectInformationLength) PVOID ObjectInformation,
    _In_ ULONG ObjectInformationLength,
    _Out_opt_ PULONG ReturnLength);

typedef NTSTATUS (NTAPI* PNtDuplicateObject)(
    _In_ HANDLE SourceProcessHandle,
    _In_ HANDLE SourceHandle,
    _In_opt_ HANDLE TargetProcessHandle,
    _Out_opt_ PHANDLE TargetHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Options
    );
