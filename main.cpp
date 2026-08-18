#include "include/utils.h"
#include "include/enum_process.h"
#include "include/enum_module.h"

#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    auto processes = enum_processes();
    for (auto const& p : processes) {
        std::wcout << "Pid: " << p.pid << "\tName: " << p.image_name << "\n";
    }
}
