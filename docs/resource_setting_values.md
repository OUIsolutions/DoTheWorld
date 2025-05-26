# Setting Values in DtwResource

This document provides a guide on how to set different types of values to resources using the `DtwResource` API. It covers setting strings, binary data, numeric values, and boolean values, as well as organizing resources into subfolders. The examples provided demonstrate practical usage of the API for creating and managing resources in a specified directory.

## Overview

The `DtwResource` API allows developers to create and manage resources (files and directories) in a structured manner. Resources can store various types of data, including strings, binary content, integers, doubles, and booleans. This API also supports hierarchical organization through sub-resources (subfolders and files).

## Prerequisites

- Include the necessary header file for the `DtwResource` API (e.g., `doTheWorldOne.c`).
- Ensure the target directory exists or is writable for resource creation.

## Setting Different Types of Values

Below are the key methods for setting values to resources, along with detailed explanations and a complete example.

### 1. Initializing a Resource

To start working with resources, initialize a `DtwResource` object by specifying the root directory where the resources will be created or managed.

```c
DtwResource *values = new_DtwResource("tests/target/new_folder");
```

- **Parameter**: The path to the root directory (`tests/target/new_folder` in this case).
- **Note**: If the directory does not exist, it will be created automatically upon committing changes.

### 2. Setting a String Value

You can store a string in a resource (file) using the `DtwResource_set_string` method.

```c
DtwResource *string_element = DtwResource_sub_resource(values, "text.txt");
DtwResource_set_string(string_element, "nothing");
```

- **Steps**:
  1. Create a sub-resource (file) named `text.txt` under the root resource `values`.
  2. Set the string content `"nothing"` to this resource.
- **Result**: A file named `text.txt` will be created with the content `"nothing"`.

### 3. Setting Binary Data

Binary data, such as images or other non-text files, can be stored using the `DtwResource_set_binary` method.

```c
long size;
unsigned char *blob = dtw_load_binary_content("tests/target/blob.png", &size);
DtwResource *blob_element = DtwResource_sub_resource(values, "blob.png");
DtwResource_set_binary(blob_element, blob, size);
free(blob);
```

- **Steps**:
  1. Load binary content from a source file (`blob.png`) into a buffer (`blob`) and retrieve its size.
  2. Create a sub-resource named `blob.png` under the root resource `values`.
  3. Set the binary content to this resource using the buffer and size.
  4. Free the allocated buffer to prevent memory leaks.
- **Result**: A file named `blob.png` will be created with the binary content of the source file.

### 4. Setting Numeric Values

The API supports setting long integers and double-precision floating-point numbers.

#### Setting a Long Integer

```c
DtwResource *bInt = DtwResource_sub_resource(values, "b.txt");
DtwResource_set_long(bInt, 25);
```

- **Steps**:
  1. Create a sub-resource named `b.txt`.
  2. Set the long integer value `25` to this resource.
- **Result**: A file named `b.txt` will be created with the text representation of the value `25`.

#### Setting a Double Value

```c
DtwResource *cDouble = DtwResource_sub_resource(values, "c.txt");
DtwResource_set_double(cDouble, 10.5);
```

- **Steps**:
  1. Create a sub-resource named `c.txt`.
  2. Set the double value `10.5` to this resource.
- **Result**: A file named `c.txt` will be created with the text representation of the value `10.5`.

### 5. Setting a Boolean Value

Boolean values can be stored using the `DtwResource_set_bool` method.

```c
DtwResource *dBool = DtwResource_sub_resource(values, "d.txt");
DtwResource_set_bool(dBool, true);
```

- **Steps**:
  1. Create a sub-resource named `d.txt`.
  2. Set the boolean value `true` to this resource.
- **Result**: A file named `d.txt` will be created with the text representation of the boolean value (e.g., `1` or `true` depending on implementation).

### 6. Organizing Resources in Subfolders

Resources can be organized hierarchically by creating sub-resources as folders.

```c
DtwResource *sub_folder = DtwResource_sub_resource(values, "sub_folder");
DtwResource *string_element2 = DtwResource_sub_resource(sub_folder, "a.txt");
DtwResource_set_string(string_element2, "nothing");
```

- **Steps**:
  1. Create a sub-resource named `sub_folder` under the root resource `values` (this acts as a directory).
  2. Create a sub-resource named `a.txt` under `sub_folder`.
  3. Set the string content `"nothing"` to `a.txt`.
- **Result**: A directory named `sub_folder` will be created, containing a file `a.txt` with the content `"nothing"`.

### 7. Committing Changes

After setting values to resources, commit the changes to ensure they are written to the filesystem.

```c
DtwResource_commit(values);
```

- **Note**: Without committing, the changes may not be persisted to the disk.

### 8. Freeing Resources

To prevent memory leaks, free the `DtwResource` object after use.

```c
DtwResource_free(values);
```

- **Note**: This does not delete the files or directories created; it only releases the memory used by the `DtwResource` structure.

## Complete Example

Below is a complete code example demonstrating the above operations:

```c
#include "doTheWorldOne.c"

int main() {
    // Initialize the root resource
    DtwResource *values = new_DtwResource("tests/target/new_folder");

    // Set a string value
    DtwResource *string_element = DtwResource_sub_resource(values, "text.txt");
    DtwResource_set_string(string_element, "nothing");

    // Set binary data
    long size;
    unsigned char *blob = dtw_load_binary_content("tests/target/blob.png", &size);
    DtwResource *blob_element = DtwResource_sub_resource(values, "blob.png");
    DtwResource_set_binary(blob_element, blob, size);
    free(blob);

    // Set a long integer
    DtwResource *bInt = DtwResource_sub_resource(values, "b.txt");
    DtwResource_set_long(bInt, 25);

    // Set a double value
    DtwResource *cDouble = DtwResource_sub_resource(values, "c.txt");
    DtwResource_set_double(cDouble, 10.5);

    // Set a boolean value
    DtwResource *dBool = DtwResource_sub_resource(values, "d.txt");
    DtwResource_set_bool(dBool, true);

    // Create a subfolder and set a string value inside it
    DtwResource *sub_folder = DtwResource_sub_resource(values, "sub_folder");
    DtwResource *string_element2 = DtwResource_sub_resource(sub_folder, "a.txt");
    DtwResource_set_string(string_element2, "nothing");

    // Commit changes to the filesystem
    DtwResource_commit(values);

    // Free the resource to prevent memory leaks
    DtwResource_free(values);

    return 0;
}
```

## Notes

- Ensure the target directory has appropriate write permissions to avoid errors during resource creation or data writing.
- Overlapping resource names (e.g., setting multiple values to the same file) may result in overwriting data. Be cautious with resource naming.
- The `DtwResource_commit` method must be called to persist changes. Without it, the operations remain in memory and are not written to disk.
- Always free allocated memory (e.g., binary data buffers) and `DtwResource` objects to prevent memory leaks.

## Troubleshooting

- **File Not Created**: Verify that the directory path specified in `new_DtwResource` is accessible and writable.
- **Data Overwritten**: Check for duplicate resource names, as setting a new value to an existing resource may overwrite the previous content.
- **Memory Issues**: Ensure all dynamically allocated memory (e.g., binary data buffers) and `DtwResource` objects are properly freed.