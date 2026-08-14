#include "../include/utils.h"

void print_processes(const std::vector<Process>& entries) {
    for (auto const& entry : entries) {
        std::wcout << "PID: " << entry.pid << "\t ImageName: " << entry.image_name << "\tKernel Time: " << entry.kernel_time << std::endl;
    }
}

void print_modules(const std::vector<Process>& entries) {
    if (entries.empty()) {
        std::cerr << "entries empty\n";
        return;
    }
    for (auto const& entry : entries) {
        std::wcout << "Name: " << entry.image_name << std::endl;
    }
}

void print_threads(const std::vector<Thread> &entries) {
    for (auto const& thread : entries) {
        std::cout << "TID: " << thread.tid
            << "\tCtx switches: " << thread.context_switches
            << "\tPrio: " << thread.priority
            << "\tBase Prio: " << thread.base_priority
            << "\tKrnl time: " << thread.kernel_time << "\n";
    }

}
