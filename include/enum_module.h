#include "types/modules.h"
#include "nt/ntdll_defs.h"
#include "functions.h"
#include <vector>
#include <string>

std::vector<MODULE_ENTRY> get_module_list(DWORD pid);
