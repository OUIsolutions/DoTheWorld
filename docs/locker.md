# Locker Mechanism

The **Locker** is a utility designed to manage file access in a multi-process environment. It ensures that files are locked during operations to prevent concurrent access issues, thereby maintaining data integrity and enforcing orderly execution of file operations across multiple processes.

## Overview

When multiple processes attempt to access or modify the same file simultaneously, race conditions can occur, leading to data corruption or inconsistent results. The Locker mechanism provides a simple way to lock a file, ensuring that only one process can operate on it at a time. This is particularly useful in scenarios involving file I/O operations in multi-process applications.

## Key Features

- **File Locking**: Prevents multiple processes from accessing the same file concurrently.
- **Process Ownership**: Identifies which process currently holds the lock.
- **Safe File Operations**: Ensures data integrity during read/write operations in a multi-process context.

## Usage

The Locker is implemented through the `DtwLocker` structure and associated functions provided by the `doTheWorld` library. Below is an example demonstrating how to use the Locker to safely append text to a file in a multi-process environment.

### Example: Appending Text to a File with Locker

This example shows how to use the Locker to append text to a file safely across multiple processes. The code creates multiple child processes, each attempting to append a unique message to the same file. The Locker ensures that the file operations are performed sequentially.

```c
#include "doTheWorldOne.c"

void append_text(const char *file, char *text) {
    // Initialize a new Locker instance
    DtwLocker *locker = newDtwLocker();
    
    // Attempt to lock the file; loop until the lock is acquired
    while (DtwLocker_lock(locker, file));
    
    // Once locked, the current process has ownership
    // Uncomment the line below for debugging purposes
    // printf("Process %d has acquired the lock\n", locker->process);
    
    // Read the current content of the file
    char *content = dtw_load_string_file_content(file);
    
    // Reallocate memory to accommodate the new text
    content = realloc(content, strlen(content) + strlen(text) + 2);
    strcat(content, text);
    
    // Write the updated content back to the file
    dtw_write_string_file_content(file, content);
    
    // Free the allocated memory for content
    free(content);
    
    // Release the lock and free the Locker instance
    DtwLocker_free(locker);
}

int main(int argc, char *argv[]) {
    const char *file = "tests/target/append.txt";
    int total_processes = 10;
    
    // Reset the file by removing it and creating a new empty file
    dtw_remove_any(file);
    dtw_write_string_file_content(file, "");
    
    // Create multiple child processes
    for (int i = 0; i < total_processes; i++) {
        if (fork() == 0) {
            // Child process: Append a unique message to the file
            char formatted_content[1000] = {0};
            sprintf(formatted_content, "Text from process %d (PID: %d)\n", i, getpid());
            append_text(file, formatted_content);
            exit(0);
        }
    }
    
    // Parent process: Wait for all child processes to complete
    for (int i = 0; i < total_processes; i++) {
        int status;
        wait(&status);
    }
    
    return 0;
}
```

### Explanation of the Example

1. **Locker Initialization**:
   - A new `DtwLocker` instance is created using `newDtwLocker()`. This object manages the locking mechanism for a specific file.

2. **Locking the File**:
   - The `DtwLocker_lock(locker, file)` function is called in a loop to attempt to acquire the lock on the specified file. The loop continues until the lock is successfully obtained.
   - Once the lock is acquired, the current process gains exclusive access to the file.

3. **File Operations**:
   - After acquiring the lock, the process reads the file content using `dtw_load_string_file_content(file)`.
   - It then appends new text to the content and writes it back to the file using `dtw_write_string_file_content(file, content)`.

4. **Releasing the Lock**:
   - After completing the file operations, the lock is implicitly released by freeing the `DtwLocker` instance with `DtwLocker_free(locker)`.

5. **Multi-Process Handling**:
   - The `main` function creates multiple child processes using `fork()`. Each child process attempts to append text to the same file.
   - The parent process waits for all child processes to complete using `wait()`.

### Notes

- Ensure that the `doTheWorldOne.c` header or library file is included to access the `DtwLocker` structure and related functions.
- Always free the `DtwLocker` instance after use to avoid memory leaks and to release the lock for other processes.
- If a process fails to acquire a lock, it will retry until successful. Be cautious of potential deadlocks or long waiting times in high-contention scenarios.
- This example assumes a Unix-like environment due to the use of `fork()` and `wait()`. For other environments, adapt the multi-process handling accordingly.

## Limitations

- The Locker mechanism may not be suitable for high-performance applications requiring frequent file access due to potential delays in acquiring locks.
- The current implementation does not provide a timeout mechanism for lock acquisition, which could lead to indefinite waiting in some cases.

## See Also

- For more details on the `doTheWorld` library and its functions, refer to the main project documentation.
- Additional examples of multi-process file handling can be found in the project's example directory.