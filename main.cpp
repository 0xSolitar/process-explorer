#include "include/types/process.h"
#include "include/utils.h"
#include "include/enum_process.h"

int main() {
    std::vector<PROCESS_ENTRY> entries = enum_processes();
    if (entries.empty()) {
        std::cout << "empty entries, something went wrong\n";
        return 1;
    }

    print_processes(entries);
}
