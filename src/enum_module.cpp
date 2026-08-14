#include "../include/enum_module.h"

std::vector<Module> get_module_list(DWORD pid) {
    auto NtReadVirtualMemory = (PNtReadVirtualMemory)GetProcAddress(GetModuleHandleW(L"ntdll"), "NtReadVirtualMemory");
    if (!NtReadVirtualMemory) return {};

    HANDLE hProcess = open_process_by_id(pid);
    if (!hProcess) {
        std::cerr << "invalid handle\n";
        return {};
    }

    LIST_ENTRY entry{};
    LPVOID ldr = get_ldr_addr(pid);
    if (!ldr) {
        std::cerr << "invalid ldr addr\n";
        return {};
    };

    NTSTATUS status = NtReadVirtualMemory(
        hProcess,
        static_cast<BYTE*>(ldr) + IN_LOAD_ORDER_MODULE_LIST_OFFSET,
        &entry,
        sizeof(entry),
        nullptr
    );

    if (!NT_SUCCESS(status)) return {};

    PLIST_ENTRY head = reinterpret_cast<PLIST_ENTRY>(
        static_cast<BYTE*>(ldr) + IN_LOAD_ORDER_MODULE_LIST_OFFSET
    );
    PLIST_ENTRY current = entry.Flink;

    std::vector<MODULE_ENTRY> entries {};

    while (current != head) {
        LDR_DATA_TABLE_ENTRY64 table_entry {};
        Module module_entry {};

        status = NtReadVirtualMemory(hProcess, reinterpret_cast<BYTE*>(current), &table_entry, sizeof(LDR_DATA_TABLE_ENTRY64), nullptr);
        if (!NT_SUCCESS(status)) continue;

        UNICODE_STRING dll_path = table_entry.FullDllName; // full path
        UNICODE_STRING dll_name = table_entry.BaseDllName; // base name

        if (dll_path.Buffer && dll_path.Length) {
            std::vector<wchar_t> buffer (dll_path.Length / sizeof(wchar_t));
            status = NtReadVirtualMemory(hProcess, dll_path.Buffer, buffer.data(), buffer.size() * sizeof(wchar_t), nullptr);
            if (!NT_SUCCESS(status)) continue;

            std::wstring path;
            path.assign(buffer.begin(), buffer.end());

            module_entry.path = path;
        }

        if (dll_name.Buffer && dll_name.Length) {
            std::vector<wchar_t> buffer (dll_name.Length / sizeof(wchar_t));
            status = NtReadVirtualMemory(hProcess, dll_name.Buffer, buffer.data(), buffer.size() * sizeof(wchar_t), nullptr);
            if (!NT_SUCCESS(status)) continue;

            std::wstring name;
            name.assign(buffer.begin(), buffer.end());

            module_entry.name = name;
        }
        entries.push_back(module_entry);
        current = table_entry.InLoadOrderLinks.Flink;
    }

    return entries;
}
