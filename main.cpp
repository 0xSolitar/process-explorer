#include "include/utils.h"
#include "include/enum_process.h"
#include "include/enum_module.h"

int main(int argc, char* argv[]) {
    std::vector<Process> processes = enum_processes();

    for (auto const& p : processes) {
        if (p.pid == (DWORD)atoi(argv[1])) {
            std::cout << "Threads count: " << p.thread_count << "\tThread arr size: " << p.threads.size() << "\n";
            print_threads(p.threads);
            break;
        }
    }
}
