#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    // Set the size of the structures
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Create a child process
    if (CreateProcess(
            NULL,                // Application name
            "child_process.exe", // Command line
            NULL,                // Process handle not inheritable
            NULL,                // Thread handle not inheritable
            FALSE,               // Set handle inheritance to FALSE
            0,                   // No creation flags
            NULL,                // Use parent's environment block
            NULL,                // Use parent's starting directory
            &si,                 // Pointer to STARTUPINFO structure
            &pi                  // Pointer to PROCESS_INFORMATION structure
        )) {
        // Successfully created the child process

        // Parent process
        printf("Parent process\n");
        printf("Parent PID: %d\n", GetCurrentProcessId());
        printf("Child PID: %d\n", pi.dwProcessId);

        // Wait for the child process to complete
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Close process and thread handles
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        // Error creating the child process
        fprintf(stderr, "CreateProcess failed, error code %lu\n", GetLastError());
        return 1;
    }

    return 0;
}

