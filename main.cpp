#include "include/utils.h"
#include "include/enum_process.h"
#include "include/enum_module.h"

int main(int argc, char* argv[]) {
    std::vector<PROCESS_ENTRY> processes = enum_processes();
    print_processes(processes);
}
