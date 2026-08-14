#include "types/modules.h"
#include "nt/ntdll_defs.h"
#include "functions.h"
#include <vector>
#include <string>

std::vector<Module> get_module_list(DWORD pid);
