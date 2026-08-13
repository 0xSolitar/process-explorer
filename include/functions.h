#pragma once

#include <windows.h>
#include "../include/nt/ntdll_defs.h"
#include "../include/nt/nt_structs.h"
#include <iostream>

LPVOID get_peb_addr(HANDLE hProcess);
HANDLE open_process_by_id(DWORD pid);
LPVOID get_ldr_addr(DWORD pid);
