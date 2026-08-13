#include "../include/utils.h"

void print_processes(const std::vector<PROCESS_ENTRY> entries) {
    for (auto const& entry : entries) {
        std::wcout << "PID: " << entry.pid << "\t ImageName: " << entry.image_name << std::endl;
    }
}
