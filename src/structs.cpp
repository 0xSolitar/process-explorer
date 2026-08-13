#include "../include/structs.h"
#include "../include/ntdll_defs.h"

std::vector<PROCESS_ENTRY> enum_processes() {
    std::vector<PROCESS_ENTRY> processes;

    auto NtQuerySystemInformation = (PNtQuerySystemInformation)GetProcAddress(GetModuleHandleW(L"ntdll"), "NtQuerySystemInformation");
    if (!NtQuerySystemInformation) {
        return {};
    }

    ULONG bufferSize = 1 << 16;
    std::vector<BYTE> buffer(bufferSize);
    ULONG returnLength = 0;
    NTSTATUS status;

    while ((status = NtQuerySystemInformation(static_cast<SYSTEM_INFORMATION_CLASS>(SystemProcessInformation), buffer.data(), buffer.size(), &returnLength))
        == STATUS_INFO_LENGTH_MISMATCH) {
        bufferSize = returnLength;
        buffer.resize(bufferSize);
    }

    if (status != STATUS_SUCCESS) {
        printf("NtQuerySystemInformation failed: 0x%X\n", status);
        return {};
    }

    auto* process = reinterpret_cast<PSYSTEM_PROCESS_INFORMATION>(buffer.data());

    while (true) {
        PROCESS_ENTRY entry = {
            .pid = static_cast<DWORD>(
                reinterpret_cast<ULONG_PTR>(process->UniqueProcessId)
            ),
            .image_name = std::wstring(process->ImageName.Buffer, process->ImageName.Length / sizeof(WCHAR)),
            .thread_count = process->NumberOfThreads,
            .handle_count = process->HandleCount
        };

        processes.push_back(entry);

        if (process->NextEntryOffset == 0) break;
        process = reinterpret_cast<PSYSTEM_PROCESS_INFORMATION>(
            reinterpret_cast<BYTE*>(process) +
            process->NextEntryOffset);
    }

    return processes;
}
