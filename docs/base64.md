# Base64 Encoding and Decoding

This guide provides instructions on how to handle Base64 encoding and decoding of binary data using the provided library functions. Base64 is a binary-to-text encoding scheme that represents binary data in an ASCII string format, which is useful for embedding binary data in text-based formats like JSON or XML, or for transmitting data over systems that handle text.

## Table of Contents
- [Overview](#overview)
- [Encoding a Binary File to Base64](#encoding-a-binary-file-to-base64)
- [Decoding a Base64 String to Binary](#decoding-a-base64-string-to-binary)
- [Important Notes](#important-notes)

## Overview
The library provides two primary functionalities for Base64 operations:
1. **Encoding**: Convert binary files (e.g., images, documents) into a Base64 string.
2. **Decoding**: Convert a Base64 string back into its original binary form.

These operations are essential for scenarios where binary data needs to be safely stored or transmitted as text.

## Encoding a Binary File to Base64
You can convert a binary file (such as an image or any other file type) into a Base64-encoded string using the `dtw_convert_binary_file_to_base64` function. This function reads the file content and returns a dynamically allocated string containing the Base64 representation.

### Example: Encoding a Binary File
The following example demonstrates how to encode a binary file (e.g., a PNG image) into a Base64 string and print it.

```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]) {
    // Specify the path to the binary file
    const char *file_path = "tests/target/blob.png";
    
    // Convert the binary file to a Base64 string
    char *base64_string = dtw_convert_binary_file_to_base64(file_path);
    
    if (base64_string == NULL) {
        printf("Error: Failed to encode the file to Base64.\n");
        return 1;
    }
    
    // Print the Base64 string
    printf("Base64 encoded data: %s\n", base64_string);
    
    // Free the dynamically allocated memory
    free(base64_string);
    
    return 0;
}
```

### Explanation
- **Input**: The path to the binary file (`file_path`) that you want to encode.
- **Output**: A dynamically allocated string (`base64_string`) containing the Base64-encoded data.
- **Memory Management**: The caller is responsible for freeing the allocated memory using `free()` to prevent memory leaks.
- **Error Handling**: If the file cannot be read or encoded, the function returns `NULL`. Always check for this condition.

## Decoding a Base64 String to Binary
You can convert a Base64-encoded string back to its original binary form using the `dtw_base64_decode` function. This function decodes the Base64 string and returns the binary data as an array of bytes, along with the size of the decoded data.

### Example: Decoding a Base64 String
The following example demonstrates how to encode a binary file to Base64, then decode it back to binary, and save the result to a new file.

```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]) {
    // Step 1: Encode a binary file to Base64
    const char *input_file_path = "tests/target/blob.png";
    char *base64_string = dtw_convert_binary_file_to_base64(input_file_path);
    
    if (base64_string == NULL) {
        printf("Error: Failed to encode the file to Base64.\n");
        return 1;
    }
    
    // Step 2: Decode the Base64 string back to binary
    long decoded_size;
    unsigned char *decoded_data = dtw_base64_decode(base64_string, &decoded_size);
    
    if (decoded_data == NULL) {
        printf("Error: Failed to decode the Base64 string.\n");
        free(base64_string);
        return 1;
    }
    
    // Step 3: Write the decoded binary data to a new file
    const char *output_file_path = "tests/target/blob2.png";
    dtw_write_any_content(output_file_path, decoded_data, decoded_size);
    
    // Step 4: Clean up allocated memory
    free(base64_string);
    free(decoded_data);
    
    printf("File successfully decoded and saved as %s\n", output_file_path);
    return 0;
}
```

### Explanation
- **Input**: A Base64-encoded string (`base64_string`) and a pointer to store the size of the decoded data (`decoded_size`).
- **Output**: A dynamically allocated array of bytes (`decoded_data`) containing the original binary data, and the size of this data stored in `decoded_size`.
- **Memory Management**: The caller must free the allocated memory for both the Base64 string and the decoded data using `free()` to avoid memory leaks.
- **Error Handling**: If decoding fails, the function returns `NULL`. Always check for this condition.
- **File Writing**: Use `dtw_write_any_content` to save the decoded binary data to a file, passing the file path, data buffer, and size.

## Important Notes
- **File Paths**: Ensure that the file paths provided for reading and writing are valid and accessible. The library does not create directories automatically; parent directories must exist.
- **Memory Management**: Always free dynamically allocated memory (e.g., Base64 strings and decoded data) to prevent memory leaks.
- **Error Checking**: Both encoding and decoding functions can return `NULL` if an error occurs (e.g., file not found, invalid Base64 string). Implement proper error handling in your code.
- **Performance**: Encoding and decoding large files may consume significant memory and processing time. Consider processing very large files in chunks if necessary (if supported by the library in future updates).
