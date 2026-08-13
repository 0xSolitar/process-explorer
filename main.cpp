#include "include/utils.h"
#include "include/enum_process.h"
#include "include/enum_module.h"

int main(int argc, char* argv[]) {
    std::vector<MODULE_ENTRY> modules = get_module_list((DWORD)atoi(argv[1]));
    print_modules(modules);
}
