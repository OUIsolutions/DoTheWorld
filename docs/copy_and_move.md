# Copying and Moving Files and Folders

This guide provides detailed instructions on how to create directories, copy, and move files or folders using the provided functions in the **DoTheWorld** library. Each function is explained with its purpose, parameters, and usage examples.

## Creating Directories Recursively

To create directories, including any necessary parent directories, use the `dtw_create_dir_recursively` function. This function ensures that the entire path up to the target folder is created if it does not already exist.

### Syntax
```c
void dtw_create_dir_recursively(const char *path);
```

### Parameters
- `path`: The full path of the directory to create. If parent directories in the path do not exist, they will be created automatically.

### Example
```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]) {
    // Creates the directory structure tests/target/sub_folder/a/b/c
    dtw_create_dir_recursively("tests/target/sub_folder/a/b/c");
    return 0;
}
```

### Notes
- This function does not return a value. If an error occurs (e.g., due to permissions), it may fail silently. Ensure you have the necessary permissions to create directories in the specified location.

## Copying Files and Folders

The `dtw_copy_any` function allows you to copy files or entire folders (including their contents) from a source path to a destination path. This function is versatile and handles both individual files and directory structures.

### Syntax
```c
void dtw_copy_any(const char *src_path, const char *dest_path, int merge_option);
```

### Parameters
- `src_path`: The source path of the file or folder to copy.
- `dest_path`: The destination path where the file or folder will be copied to.
- `merge_option`: Determines the behavior when the destination already exists. Use `DTW_NOT_MERGE` to prevent overwriting or merging (the operation will fail if the destination exists). Other options may be available depending on library configuration (e.g., `DTW_MERGE` to combine contents if applicable).

### Example
```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]) {
    // Copies a file from one location to another
    dtw_copy_any("tests/target/blob.png", "tests/target/blob3.png", DTW_NOT_MERGE);
    return 0;
}
```

### Additional Example (Copying a Folder)
```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]) {
    // Copies an entire folder and its contents
    dtw_copy_any("tests/target/source_folder", "tests/target/destination_folder", DTW_NOT_MERGE);
    return 0;
}
```

### Notes
- If the destination path already exists and `DTW_NOT_MERGE` is specified, the operation will fail. Ensure the destination path is available or use a different merge option if supported.
- This function does not return a status code. Check the destination path manually to confirm the operation's success if needed.

## Moving Files and Folders

To move files or folders from one location to another, use the `dtw_move_any` function. This operation effectively relocates the source to the destination, removing it from the original location.

### Syntax
```c
void dtw_move_any(const char *src_path, const char *dest_path, int merge_option);
```

### Parameters
- `src_path`: The source path of the file or folder to move.
- `dest_path`: The destination path where the file or folder will be moved to.
- `merge_option`: Similar to `dtw_copy_any`, specifies behavior when the destination exists. Use `DTW_NOT_MERGE` to prevent overwriting or merging.

### Example
```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]) {
    // Moves a folder from one location to another
    dtw_move_any("tests/target/sub_folder", "tests/target/sub_folder2", DTW_NOT_MERGE);
    return 0;
}
```

### Additional Example (Moving a File)
```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]) {
    // Moves a file from one location to another
    dtw_move_any("tests/target/file.txt", "tests/target/new_location/file.txt", DTW_NOT_MERGE);
    return 0;
}
```

### Notes
- Moving a file or folder will delete it from the source location. Ensure you no longer need the data at the original path before performing this operation.
- If the destination exists and `DTW_NOT_MERGE` is used, the operation will fail. Verify the destination path is free or consider alternative merge options if available.
- This function does not return a status. Manually verify the source and destination paths to confirm the move was successful.

## Common Considerations
- **Permissions**: Ensure your application has the necessary read/write permissions for both source and destination paths to avoid operation failures.
- **Path Formats**: Use consistent path separators (e.g., `/` for Unix-like systems or `\` for Windows) as per your operating system's requirements. The library may handle cross-platform paths, but it's best to test on your target environment.
- **Error Handling**: The functions described do not return error codes or status indicators. Implement additional checks (e.g., verifying file existence post-operation) if your application requires robust error handling.
