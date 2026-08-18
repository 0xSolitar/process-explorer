#pragma once

#include <windows.h>
#include "nt/ntdll_defs.h"
#include <vector>
#include "types/handle.h"

std::vector<HANDLE> enum_handle();
std::vector<Handle> filter_by_pid(DWORD pid);
