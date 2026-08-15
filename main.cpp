// #include "include/utils.h"
// #include "include/enum_process.h"
// #include "include/enum_module.h"

#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_VM_READ, false, (DWORD)atoi(argv[1]));
    if (!hProcess) {
        std::cerr << "faield to get handle to process\n";
        return 1;
    }

    DWORD sizeNeeded = 0;
    bool ok = EnumProcessModulesEx(hProcess, nullptr, 0, &sizeNeeded, LIST_MODULES_ALL);
    std::vector<HMODULE> modules (sizeNeeded / sizeof(HMODULE));
    EnumProcessModulesEx(hProcess, modules.data(), sizeNeeded, &sizeNeeded, LIST_MODULES_ALL);
    std::cout << "number of modules: " << sizeNeeded / sizeof(HMODULE) << "\n";
}
