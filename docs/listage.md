# File and Directory Listing Functions

This document outlines the file and directory listing functionalities provided by the `doTheWorld` library. These functions allow you to extract lists of files, directories, or both from a specified folder, either at a single level or recursively through subfolders. The results are returned as `DtwStringArray` objects, which can be sorted and displayed as needed.

**Note**: This is a fragment of the larger documentation. For installation instructions, library setup, or other overarching details, refer to the main `README.md`.

## Overview of Listing Functions

The library provides two categories of listing functions:
1. **Single-Level Listing**: Retrieves items (files, directories, or both) only from the specified directory, ignoring subdirectories.
2. **Recursive Listing**: Retrieves items from the specified directory and all its subdirectories.

Each category includes functions to list files, directories, or all items. Additionally, you can control whether the returned paths are concatenated with the base directory path using the `DTW_CONCAT_PATH` or `DTW_NOT_CONCAT_PATH` options.

## Single-Level Listing

These functions operate only on the immediate contents of the specified directory.

### Listing Files

The `dtw_list_files` function retrieves a list of files in the specified directory.

```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]) {
    // List files in the 'tests/target' directory
    // DTW_CONCAT_PATH includes the base directory in the file paths
    DtwStringArray *files = dtw_list_files("tests/target", DTW_CONCAT_PATH);
    
    // Sort the list alphabetically
    DtwStringArray_sort(files);
    
    // Iterate and print each file path
    for (int i = 0; i < files->size; i++) {
        printf("%s\n", files->strings[i]);
    }
    
    // Free the allocated memory
    DtwStringArray_free(files);
    return 0;
}
```

**Parameters**:
- `path`: The directory path to list files from (e.g., `"tests/target"`).
- `concat_path`: Use `DTW_CONCAT_PATH` to include the base directory in the results, or `DTW_NOT_CONCAT_PATH` to return only the file names.

### Listing Directories

The `dtw_list_dirs` function retrieves a list of directories in the specified directory.

```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]) {
    // List directories in the 'tests/target' directory
    // DTW_NOT_CONCAT_PATH returns only the directory names without the base path
    DtwStringArray *dirs = dtw_list_dirs("tests/target", DTW_NOT_CONCAT_PATH);
    
    // Sort the list alphabetically
    DtwStringArray_sort(dirs);
    
    // Print the list to the console using the represent method
    DtwStringArray_represent(dirs);
    
    // Free the allocated memory
    DtwStringArray_free(dirs);
    return 0;
}
```

**Parameters**:
- `path`: The directory path to list directories from.
- `concat_path`: Use `DTW_CONCAT_PATH` or `DTW_NOT_CONCAT_PATH` to control path concatenation.

### Listing All Items

The `dtw_list_all` function retrieves both files and directories in the specified directory.

```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]) {
    // List all items (files and directories) in the 'tests/target' directory
    DtwStringArray *all = dtw_list_all("tests/target", DTW_CONCAT_PATH);
    
    // Sort the list alphabetically
    DtwStringArray_sort(all);
    
    // Print the list to the console
    DtwStringArray_represent(all);
    
    // Free the allocated memory
    DtwStringArray_free(all);
    return 0;
}
```

**Parameters**:
- `path`: The directory path to list items from.
- `concat_path`: Use `DTW_CONCAT_PATH` or `DTW_NOT_CONCAT_PATH` to control path concatenation.

## Recursive Listing

These functions traverse the specified directory and all its subdirectories to retrieve items.

### Listing Files Recursively

The `dtw_list_files_recursively` function retrieves all files in the specified directory and its subdirectories.

```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]) {
    // List files recursively in the 'tests/target' directory and subdirectories
    DtwStringArray *files = dtw_list_files_recursively("tests/target", DTW_CONCAT_PATH);
    
    // Sort the list alphabetically
    DtwStringArray_sort(files);
    
    // Print the list to the console
    DtwStringArray_represent(files);
    
    // Free the allocated memory
    DtwStringArray_free(files);
    return 0;
}
```

**Parameters**:
- `path`: The directory path to start the recursive search from.
- `concat_path`: Use `DTW_CONCAT_PATH` or `DTW_NOT_CONCAT_PATH` to control path concatenation.

### Listing Directories Recursively

The `dtw_list_dirs_recursively` function retrieves all directories in the specified directory and its subdirectories.

```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]) {
    // List directories recursively in the 'tests/target' directory and subdirectories
    DtwStringArray *dirs = dtw_list_dirs_recursively("tests/target", DTW_CONCAT_PATH);
    
    // Sort the list alphabetically
    DtwStringArray_sort(dirs);
    
    // Print the list to the console
    DtwStringArray_represent(dirs);
    
    // Free the allocated memory
    DtwStringArray_free(dirs);
    return 0;
}
```

**Parameters**:
- `path`: The directory path to start the recursive search from.
- `concat_path`: Use `DTW_CONCAT_PATH` or `DTW_NOT_CONCAT_PATH` to control path concatenation.

### Listing All Items Recursively

The `dtw_list_all_recursively` function retrieves all files and directories in the specified directory and its subdirectories.

```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]) {
    // List all items recursively in the 'tests/target' directory and subdirectories
    DtwStringArray *all = dtw_list_all_recursively("tests/target", DTW_CONCAT_PATH);
    
    // Sort the list alphabetically
    DtwStringArray_sort(all);
    
    // Print the list to the console
    DtwStringArray_represent(all);
    
    // Free the allocated memory
    DtwStringArray_free(all);
    return 0;
}
```

**Parameters**:
- `path`: The directory path to start the recursive search from.
- `concat_path`: Use `DTW_CONCAT_PATH` or `DTW_NOT_CONCAT_PATH` to control path concatenation.

## Additional Notes

- **Memory Management**: Always free the `DtwStringArray` objects after use with `DtwStringArray_free()` to prevent memory leaks.
- **Path Concatenation**: The `DTW_CONCAT_PATH` option prepends the base directory path to each item, while `DTW_NOT_CONCAT_PATH` returns only the item names. Choose the appropriate option based on your needs.
- **Sorting and Representation**: Use `DtwStringArray_sort()` to sort the results alphabetically and `DtwStringArray_represent()` to print the array contents directly to the console.

This documentation focuses solely on the listing functionalities. For other features or library-wide details, refer to the main documentation.