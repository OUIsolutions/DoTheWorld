# I/O Operations

This document covers the input/output (I/O) operations provided by the **DoTheWorld** library for reading and writing various types of content to files. The library offers functions for handling strings, binary data, and numerical values with ease. Each section below includes detailed explanations and example code to demonstrate usage.

## Reading Operations

### Reading String Content
If you are certain that the file content is textual (non-binary), you can use the `dtw_load_string_file_content` function to read the file as a string. This function returns a null-terminated string, which must be freed after use to prevent memory leaks.

**Function Signature:**
```c
char *dtw_load_string_file_content(const char *path);
```
- **Parameters:**
  - `path`: The file path to read from.
- **Returns:**
  - A pointer to the string content if successful, or `NULL` if an error occurs (e.g., file not found or read failure).

**Example:**
```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]) {
    const char *path = "tests/target/a.txt";
    char *content = dtw_load_string_file_content(path);
    if (content == NULL) {
        printf("Error opening %s\n", path);
        return 1;
    }
    printf("Content: %s\n", content);
    free(content); // Important: Free the allocated memory
    return 0;
}
```

### Reading Any Content (Binary or Text)
For files where the content type (binary or text) is unknown, or when dealing with binary data, use the `dtw_load_any_content` function. This function reads the file content as raw bytes and provides metadata about the size and whether the content is binary.

**Function Signature:**
```c
unsigned char *dtw_load_any_content(const char *path, long *size, bool *is_binary);
```
- **Parameters:**
  - `path`: The file path to read from.
  - `size`: A pointer to a `long` variable to store the size of the content in bytes.
  - `is_binary`: A pointer to a `bool` variable to indicate if the content is binary (`true`) or text (`false`).
- **Returns:**
  - A pointer to the content buffer if successful, or `NULL` if an error occurs.

**Example:**
```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]) {
    const char *path = "tests/target/blob.png";
    long size;
    bool is_binary;
    unsigned char *content = dtw_load_any_content(path, &size, &is_binary);
    if (content == NULL) {
        printf("Error opening %s\n", path);
        return 1;
    }
    printf("Size: %ld\n", size);
    printf("Is Binary: %s\n", is_binary ? "true" : "false");
    free(content); // Important: Free the allocated memory
    return 0;
}
```

### Reading Numerical and Boolean Values
The library provides specialized functions to directly read numerical values (`double`, `long`) and boolean values from text files. These functions parse the file content into the respective data types. If the file does not exist or the content cannot be parsed, a default value (typically `0` or `false`) is returned.

**Function Signatures:**
```c
double dtw_load_double_file_content(const char *path);
long dtw_load_long_file_content(const char *path);
bool dtw_load_bool_file_content(const char *path);
```
- **Parameters:**
  - `path`: The file path to read from.
- **Returns:**
  - The parsed value if successful, or a default value if an error occurs.

**Supported Boolean Formats:**
- `true` or `t` for `true`.
- `false` or `f` for `false`.

**Example:**
```c
#include "doTheWorldOne.c"

int main() {
    // Reading a double value
    double double_val = dtw_load_double_file_content("tests/target/numerical/double.txt");
    printf("double.txt: %lf\n", double_val);

    // Reading a double from a non-existent file (returns 0.0)
    double double_not_exist = dtw_load_double_file_content("nothing.txt");
    printf("Double that does not exist: %lf\n", double_not_exist);

    // Reading a long value
    long long_val = dtw_load_long_file_content("tests/target/numerical/integer.txt");
    printf("integer.txt: %ld\n", long_val);

    // Reading boolean values in different formats
    bool false_small = dtw_load_bool_file_content("tests/target/numerical/false_small.txt"); // Content: "f"
    bool false_normal = dtw_load_bool_file_content("tests/target/numerical/false_normal.txt"); // Content: "false"
    bool true_small = dtw_load_bool_file_content("tests/target/numerical/true_small.txt"); // Content: "t"
    bool true_normal = dtw_load_bool_file_content("tests/target/numerical/true_normal.txt"); // Content: "true"
    printf("false_small.txt: %d\n", false_small);
    printf("false_normal.txt: %d\n", false_normal);
    printf("true_small.txt: %d\n", true_small);
    printf("true_normal.txt: %d\n", true_normal);

    return 0;
}
```

## Writing Operations

### Writing String Content
To write a string to a file, use the `dtw_write_string_file_content` function. This function automatically creates the target directory if it does not exist.

**Function Signature:**
```c
bool dtw_write_string_file_content(const char *path, const char *content);
```
- **Parameters:**
  - `path`: The file path to write to.
  - `content`: The string content to write.
- **Returns:**
  - `true` if the write operation is successful, `false` otherwise.

**Example:**
```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]) {
    bool result = dtw_write_string_file_content("tests/target/a.txt", "Hello World!");
    printf("Result: %s\n", result ? "true" : "false");
    return 0;
}
```

### Writing Any Content (Binary or Text)
For writing raw bytes (binary or text) to a file, use the `dtw_write_any_content` function. You must specify the size of the content to write. The target directory is automatically created if it does not exist.

**Function Signature:**
```c
bool dtw_write_any_content(const char *path, unsigned char *content, long size);
```
- **Parameters:**
  - `path`: The file path to write to.
  - `content`: The buffer containing the data to write.
  - `size`: The size of the content in bytes.
- **Returns:**
  - `true` if the write operation is successful, `false` otherwise.

**Example:**
```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]) {
    const char *blob_path = "tests/target/blob.png";
    long blob_size;
    bool is_binary;
    unsigned char *content = dtw_load_any_content(blob_path, &blob_size, &is_binary);
    if (content == NULL) {
        printf("Error opening %s\n", blob_path);
        return 1;
    }
    bool result = dtw_write_any_content("tests/target/blob2.png", content, blob_size);
    printf("Result: %s\n", result ? "true" : "false");
    free(content);
    return 0;
}
```

### Writing Numerical and Boolean Values
The library provides functions to directly write numerical values (`double`, `long`) and boolean values to text files. These functions convert the values to strings before writing.

**Function Signatures:**
```c
bool dtw_write_double_file_content(const char *path, double value);
bool dtw_write_long_file_content(const char *path, long value);
bool dtw_write_bool_file_content(const char *path, bool value);
```
- **Parameters:**
  - `path`: The file path to write to.
  - `value`: The value to write.
- **Returns:**
  - `true` if the write operation is successful, `false` otherwise.

**Example:**
```c
#include "doTheWorldOne.c"

int main() {
    dtw_write_double_file_content("tests/target/numerical2/double.txt", 25.4);
    dtw_write_long_file_content("tests/target/numerical2/long.txt", 12);
    dtw_write_bool_file_content("tests/target/numerical2/bool.txt", true);
    return 0;
}
```

## Notes
- Always free dynamically allocated memory (e.g., content buffers returned by `dtw_load_string_file_content` or `dtw_load_any_content`) to avoid memory leaks.
- Directory paths are automatically created for write operations if they do not exist.
- Error handling is minimal in the examples for brevity; in production code, always check return values and handle errors appropriately.
