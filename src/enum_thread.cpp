#include "../include/enum_thread.h"

std::vector<Thread> enum_threads_from_process_info(PSYSTEM_PROCESS_INFO psi) {
    if (!psi) return {};

    std::vector<Thread> thread_list;

    for (ULONG i = 0; i < psi->NumberOfThreads; i++) {
        PSYSTEM_THREAD_INFO threads = (PSYSTEM_THREAD_INFO)psi->Threads;

        Thread t = {
            .tid = static_cast<DWORD>(
                reinterpret_cast<ULONG_PTR>(threads[i].ClientId.UniqueThread)
            ),
            .context_switches = threads[i].ContextSwitches,
            .kernel_time = threads[i].KernelTime.QuadPart,
            .user_time = threads[i].UserTime.QuadPart,
            .create_time = threads[i].CreateTime.QuadPart,
            .base_priority = threads[i].BasePriority,
            .priority = threads[i].Priority,
            .start_address = threads[i].StartAddress,
            .state = threads[i].ThreadState,
            .wait_reason = threads[i].WaitReason
        };

        thread_list.push_back(t);
    }

    return thread_list;
}
