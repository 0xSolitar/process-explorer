#pragma once

#include "types/process.h"
#include <iostream>

void print_processes(const std::vector<PROCESS_ENTRY>& entries);
void print_modules(const std::vector<MODULE_ENTRY>& entries);
