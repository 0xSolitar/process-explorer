#include "../include/functions.h"

HANDLE open_process_by_id(DWORD pid) {
    auto NtOpenProcess = (PNtOpenProcess)GetProcAddress(GetModuleHandleW(L"ntdll"), "NtOpenProcess");
    if (!NtOpenProcess) {
        std::cerr << "NtOpenProcess failed\n";
        return nullptr;
    }

    HANDLE hProcess = nullptr;
    OBJECT_ATTRIBUTES oa{};
    oa.Length = sizeof(oa);
    CLIENT_ID cid = {
        .UniqueProcess = reinterpret_cast<HANDLE>(
            static_cast<ULONG_PTR>(pid)),
        .UniqueThread = nullptr
    };

    NTSTATUS status = NtOpenProcess(&hProcess, PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, &oa, &cid);
    if (!NT_SUCCESS(status)) {
        std::cout << "status: " << status << "\n";
    }
    return NT_SUCCESS(status) ? hProcess : nullptr;
}

LPVOID get_peb_addr(HANDLE hProcess) {
    if (!hProcess) {
        std::cerr << "Invalid handle\n";
        return nullptr;
    };

    auto NtQueryInformationProcess = (PNtQueryInformationProcess)GetProcAddress(GetModuleHandleW(L"ntdll"), "NtQueryInformationProcess");
    if (!NtQueryInformationProcess) {
        std::cerr << "failed to resolve NtQueryInformationProcess\n";
        return nullptr;
    };

    PROCESS_BASIC_INFORMATION pbi {};
    NTSTATUS status = NtQueryInformationProcess(
        hProcess,
        ProcessBasicInformation,
        &pbi,
        sizeof(pbi),
        nullptr
    );
    if (!NT_SUCCESS(status)) {
        std::cerr << "return status is an error\n";
        return nullptr;
    };

    return pbi.PebBaseAddress;
}

LPVOID get_ldr_addr(DWORD pid) {
    auto NtReadVirtualMemory = (PNtReadVirtualMemory)GetProcAddress(GetModuleHandleW(L"ntdll"), "NtReadVirtualMemory");
    if (!NtReadVirtualMemory) {
        std::cerr << "Failed to resolve NtReadVirtualMemory\n";
        return nullptr;
    };

    HANDLE hProcess = open_process_by_id(pid);
    if (!hProcess) {
        std::cerr << "Invalid handle\n";
        return nullptr;
    };

    LPVOID peb = get_peb_addr(hProcess);
    if (!peb) {
        std::cerr << "Invalid peb adddr\n";
        return nullptr;
    }

    LPVOID ldr = nullptr;
    SIZE_T bytes_read;
    NTSTATUS status = NtReadVirtualMemory(
        hProcess,
        static_cast<BYTE*>(peb) + LDR_OFFSET,
        &ldr,
        sizeof(ldr),
        nullptr
    );

    if (!NT_SUCCESS(status) || !ldr) {
        std::cerr << "Something went wrong here\n";
        return nullptr;
    };

    return ldr;
}
