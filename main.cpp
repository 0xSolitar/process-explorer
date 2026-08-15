#include "include/utils.h"
#include "include/enum_process.h"
#include "include/enum_module.h"

int main(int argc, char* argv[]) {
    std::vector<Process> processes = enum_processes();

    for (auto const& p : processes) {
        if (p.pid == (DWORD)atoi(argv[1])) {
            print_modules(p.modules);
            break;
        }
    }
}
