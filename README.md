# Process explorer: Using the Nt api

Enumerate processes and their threads, modules.

# Usage

```cpp
int main(int argc, char* argv[]) {
    auto processes = enum_processes();
    for (auto const& p : processes) {
        std::wcout << "Pid: " << p.pid << "\tName: " << p.image_name << "\n";
    }
}
```

## TO DO

Memory stuffs (like VAD tree), handles enumeration, finding a way to enumerate modules of PPL and protected processes.
