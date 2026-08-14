#include "../include/utils.h"

void print_processes(const std::vector<PROCESS_ENTRY>& entries) {
    for (auto const& entry : entries) {
        std::wcout << "PID: " << entry.pid << "\t ImageName: " << entry.image_name << "\tKernel Time: " << entry.kernel_time << std::endl;
    }
}

void print_modules(const std::vector<MODULE_ENTRY>& entries) {
    if (entries.empty()) {
        std::cerr << "entries empty\n";
        return;
    }
    for (auto const& entry : entries) {
        std::wcout << "Name: " << entry.name << "\tPath: " << entry.path << std::endl;
    }
}
