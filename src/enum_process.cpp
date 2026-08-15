#include "../include/enum_process.h"
#include "../include/enum_thread.h"
#include "../include/enum_module.h"

std::vector<Process> enum_processes() {
    std::vector<Process> processes;

    auto NtQuerySystemInformation = (PNtQuerySystemInformation)GetProcAddress(GetModuleHandleW(L"ntdll"), "NtQuerySystemInformation");
    auto NtQueryInformationProcess = (PNtQueryInformationProcess)GetProcAddress(GetModuleHandleW(L"ntdll"), "NtQueryInformationProcess");
    auto NtClose = (PNtClose)GetProcAddress(GetModuleHandleW(L"ntdll"), "NtClose");

    if (!NtQuerySystemInformation || !NtQueryInformationProcess || !NtClose) {
        return {};
    }

    ULONG bufferSize = 1 << 16;
    std::vector<BYTE> buffer(bufferSize);
    ULONG returnLength = 0;
    NTSTATUS status;

    while ((status = NtQuerySystemInformation(static_cast<SYSTEM_INFORMATION_CLASS>(SystemProcessInformation), buffer.data(), buffer.size(), &returnLength))
        == STATUS_INFO_LENGTH_MISMATCH) {
        bufferSize = returnLength + 4096;
        buffer.resize(bufferSize);
    }

    if (status != STATUS_SUCCESS) {
        printf("NtQuerySystemInformation failed: 0x%X\n", status);
        return {};
    }

    auto* process = reinterpret_cast<PSYSTEM_PROCESS_INFO>(buffer.data());

    while (true) {

        DWORD pid = static_cast<DWORD>(
            reinterpret_cast<ULONG_PTR>(process->UniqueProcessId)
        );

        Process entry = {
            .pid = pid,
            .session_id = process->SessionId,
            .image_name = std::wstring(process->ImageName.Buffer, process->ImageName.Length / sizeof(WCHAR)),
            .thread_count = process->NumberOfThreads,
            .handle_count = process->HandleCount,
            .kernel_time = process->KernelTime.QuadPart,
            .user_time = process->UserTime.QuadPart,
            .threads = enum_threads_from_process_info(process),
            .modules = get_module_list(entry.pid)
        };

        processes.push_back(entry);

        if (process->NextEntryOffset == 0) break;
        process = reinterpret_cast<PSYSTEM_PROCESS_INFO>(
            reinterpret_cast<BYTE*>(process) +
            process->NextEntryOffset);
    }

    return processes;
}
