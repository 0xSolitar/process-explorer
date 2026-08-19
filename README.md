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

Doing handles enumeration without using kernel driver is really slow, considering there can be thousands of open handles per-process. Not worth it
