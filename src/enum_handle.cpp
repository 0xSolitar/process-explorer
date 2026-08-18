#include "../include/enum_handle.h"

std::vector<HANDLE> enum_handle() {
    auto NtQuerySystemInformation = (PNtQuerySystemInformation)GetProcAddress(GetModuleHandleW(L"ntdll"), "NtQuerySystemInformation");
    if (!NtQuerySystemInformation) return {};

    ULONG bufferSize = 1 << 16;
    std::vector<BYTE> buffer(bufferSize);
    ULONG returnLength = 0;
    NTSTATUS status;

    while ((status = NtQuerySystemInformation(static_cast<SYSTEM_INFORMATION_CLASS>(SystemExtendedHandleInformation), buffer.data(), buffer.size(), &returnLength))
        == STATUS_INFO_LENGTH_MISMATCH) {
            bufferSize = returnLength + 4096;
            buffer.resize(bufferSize);
    }

    if (!NT_SUCCESS(status)) return {};


}
