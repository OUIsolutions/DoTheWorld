# Unix Timestamp and File Modification Time

This section provides information on how to retrieve the last modification time of a file using the `doTheWorld` library. The library offers functions to get this information in both Unix timestamp format (as an integer) and human-readable string format.

## Overview

The `doTheWorld` library includes utilities to interact with file metadata on Unix-based systems. Two primary functions are provided for retrieving the last modification time of a file:
- `dtw_get_entity_last_motification_in_unix`: Returns the last modification time as a Unix timestamp (integer).
- `dtw_get_entity_last_motification_in_string`: Returns the last modification time as a formatted string.

These functions are useful for tracking file changes, logging, or displaying file metadata in a user-friendly format.

## Prerequisites

- Ensure that the `doTheWorldOne.c` library is included in your project.
- The target file must exist and be accessible for reading metadata.
- For functions returning dynamically allocated memory (e.g., strings), remember to free the memory to prevent memory leaks.

## Functions

### 1. Get Last Modification Time in Unix Timestamp Format

#### Function Signature
```c
int dtw_get_entity_last_motification_in_unix(const char *path);
```

#### Description
This function retrieves the last modification time of a specified file and returns it as a Unix timestamp (an integer representing the number of seconds since January 1, 1970, 00:00:00 UTC).

#### Parameters
- `path` (const char *): The path to the file whose modification time is to be retrieved.

#### Return Value
- `int`: The Unix timestamp of the last modification time. Returns `-1` if an error occurs (e.g., file not found or permission denied).

#### Example
```c
#include "doTheWorldOne.c"
#include <stdio.h>

int main(int argc, char *argv[]) {
    // Specify the path to the target file
    const char *file_path = "tests/target/a.txt";
    
    // Retrieve the last modification time as a Unix timestamp
    int last_modification_in_unix = dtw_get_entity_last_motification_in_unix(file_path);
    
    if (last_modification_in_unix == -1) {
        printf("Error: Unable to retrieve modification time for %s\n", file_path);
    } else {
        printf("Last modification (Unix timestamp): %d\n", last_modification_in_unix);
    }
    
    return 0;
}
```

#### Notes
- Ensure the file exists at the specified path; otherwise, the function will return an error.
- The Unix timestamp can be used for comparisons or further processing in your application.

### 2. Get Last Modification Time in String Format

#### Function Signature
```c
char *dtw_get_entity_last_motification_in_string(const char *path);
```

#### Description
This function retrieves the last modification time of a specified file and returns it as a human-readable string. The format of the string is typically based on the system's locale settings (e.g., "Wed Oct 11 14:32:52 2023").

#### Parameters
- `path` (const char *): The path to the file whose modification time is to be retrieved.

#### Return Value
- `char *`: A dynamically allocated string containing the formatted last modification time. Returns `NULL` if an error occurs (e.g., file not found or permission denied). The caller is responsible for freeing the memory.

#### Example
```c
#include "doTheWorldOne.c"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Specify the path to the target file
    const char *file_path = "tests/target/a.txt";
    
    // Retrieve the last modification time as a formatted string
    char *last_modification = dtw_get_entity_last_motification_in_string(file_path);
    
    if (last_modification == NULL) {
        printf("Error: Unable to retrieve modification time for %s\n", file_path);
    } else {
        printf("Last modification: %s\n", last_modification);
        // Free the dynamically allocated memory
        free(last_modification);
    }
    
    return 0;
}
```

#### Notes
- Always free the returned string using `free()` to avoid memory leaks.
- The exact format of the returned string may depend on the system's locale and time settings.

## Error Handling

Both functions include basic error handling:
- If the specified file does not exist or is inaccessible, `dtw_get_entity_last_motification_in_unix` returns `-1`, and `dtw_get_entity_last_motification_in_string` returns `NULL`.
- Ensure proper checks are in place in your code to handle these error conditions, as shown in the examples above.

## Limitations

- These functions are designed for Unix-based systems and may not behave as expected on other operating systems.
- The functions rely on the underlying system's file metadata, which may not always be accurate if the system clock or file system is misconfigured.

## Additional Resources

For more information on the `doTheWorld` library and other file manipulation utilities, refer to the main project documentation or other relevant sections.