# Retrieving Values from Resources using DtwResource

## Overview
This document provides a detailed guide on how to retrieve values from resources using the `DtwResource` API. It includes methods to list resource elements, access different data types (strings, binaries, numbers, and booleans), and handle potential errors. This is a fragment of a larger documentation set, focusing specifically on value retrieval operations.

## Prerequisites
- Familiarity with the `DtwResource` library and its setup (refer to the main README.md for installation and initialization instructions).
- A valid resource directory or file structure to work with (e.g., `tests/target` as used in the example).

## Table of Contents
1. [Creating a Resource Instance](#creating-a-resource-instance)
2. [Listing Resource Elements](#listing-resource-elements)
3. [Retrieving Different Data Types](#retrieving-different-data-types)
   - [String Values](#string-values)
   - [Binary Data](#binary-data)
   - [Numerical Values](#numerical-values)
   - [Boolean Values](#boolean-values)
4. [Error Handling](#error-handling)
5. [Cleaning Up Resources](#cleaning-up-resources)
6. [Complete Example Code](#complete-example-code)

---

## Creating a Resource Instance
To begin working with resources, you need to create a `DtwResource` instance pointing to a specific directory or file. This serves as the root for all subsequent operations.

```c
DtwResource *values = new_DtwResource("tests/target");
```
- **Parameter**: The path to the resource directory (`tests/target` in this case).
- **Purpose**: Initializes a resource object to interact with files and subdirectories within the specified path.

---

## Listing Resource Elements
You can list the names of all sub-elements (files or directories) within a resource using `DtwResource_list_names`. This returns a `DtwStringArray` containing the names of the elements.

```c
DtwStringArray *sub_elements = DtwResource_list_names(values);
DtwStringArray_sort(sub_elements);
if (!DtwResource_error(values)) {
    DtwStringArray_represent(sub_elements);
    DtwStringArray_free(sub_elements);
}
```
- **Steps**:
  1. Retrieve the list of element names.
  2. Optionally sort the list for better readability.
  3. Check for errors using `DtwResource_error`.
  4. Display the list using `DtwStringArray_represent`.
  5. Free the string array to prevent memory leaks.
- **Purpose**: Useful for exploring the contents of a resource directory.

---

## Retrieving Different Data Types
The `DtwResource` API provides methods to retrieve data of various types from resources. Below are the supported data types with examples.

### String Values
To retrieve a string value from a text file within the resource:

```c
DtwResource *string_r = DtwResource_sub_resource(values, "a.txt");
char *string_r_value = DtwResource_get_string(string_r);
```
- **Steps**:
  1. Access the specific sub-resource (`a.txt`) using `DtwResource_sub_resource`.
  2. Retrieve the string content using `DtwResource_get_string`.
- **Purpose**: Reads the content of a text file as a null-terminated string.

### Binary Data
To retrieve binary data (e.g., from an image or other non-text file):

```c
DtwResource *blob_r = DtwResource_sub_resource(values, "blob.png");
long blob_size;
unsigned char *blob_r_value = DtwResource_get_binary(blob_r, &blob_size);
```
- **Steps**:
  1. Access the binary sub-resource (`blob.png`).
  2. Retrieve the binary data and its size using `DtwResource_get_binary`.
- **Purpose**: Reads raw binary data, useful for files like images or executables.
- **Note**: The `blob_size` variable is populated with the size of the binary data for further processing.

### Numerical Values
Numerical values (doubles and longs) can be retrieved from text files containing numeric data. These are typically stored under a subdirectory for organization.

```c
DtwResource *numerical = DtwResource_sub_resource(values, "numerical");
DtwResource *double_r = DtwResource_sub_resource(numerical, "double.txt");
double double_r_value = DtwResource_get_double(double_r);

DtwResource *long_r = DtwResource_sub_resource(numerical, "integer.txt");
long long_r_value = DtwResource_get_long(long_r);
```
- **Steps**:
  1. Access the parent directory (`numerical`).
  2. Access specific files for double (`double.txt`) or long (`integer.txt`) values.
  3. Retrieve the values using `DtwResource_get_double` or `DtwResource_get_long`.
- **Purpose**: Converts text content into numerical values for computation.

### Boolean Values
Boolean values can be retrieved from text files representing `true` or `false`.

```c
DtwResource *bool_r = DtwResource_sub_resource(numerical, "true_normal.txt");
bool bool_r_value = DtwResource_get_bool(bool_r);
```
- **Steps**:
  1. Access the specific file containing the boolean value.
  2. Retrieve the boolean using `DtwResource_get_bool`.
- **Purpose**: Interprets text content as a boolean (`true` or `false`).

---

## Error Handling
Always check for errors after performing operations on a `DtwResource`. If an error occurs, retrieve and display the error message.

```c
if (DtwResource_error(values)) {
    char *message = DtwResource_get_error_message(values);
    printf("%s", message);
}
```
- **Steps**:
  1. Use `DtwResource_error` to check if an error occurred.
  2. Retrieve the error message using `DtwResource_get_error_message`.
- **Purpose**: Ensures robust error handling and debugging.

---

## Cleaning Up Resources
To prevent memory leaks, always free the `DtwResource` instance when done.

```c
DtwResource_free(values);
```
- **Purpose**: Releases all memory associated with the resource and its sub-resources.

---

## Complete Example Code
Below is the complete example demonstrating the retrieval of various data types, listing elements, and error handling.

```c
#include "doTheWorldOne.c"

int main() {
    // Initialize the resource
    DtwResource *values = new_DtwResource("tests/target");

    // List sub-elements
    printf("elements:---------------------------------\n");
    DtwStringArray *sub_elements = DtwResource_list_names(values);
    DtwStringArray_sort(sub_elements);
    if (!DtwResource_error(values)) {
        DtwStringArray_represent(sub_elements);
        DtwStringArray_free(sub_elements);
    }

    // Retrieve different data types
    printf("types:--------------------------------------\n");
    DtwResource *string_r = DtwResource_sub_resource(values, "a.txt");
    char *string_r_value = DtwResource_get_string(string_r);
    
    DtwResource *blob_r = DtwResource_sub_resource(values, "blob.png");
    long blob_size;
    unsigned char *blob_r_value = DtwResource_get_binary(blob_r, &blob_size);

    DtwResource *numerical = DtwResource_sub_resource(values, "numerical");
    DtwResource *double_r = DtwResource_sub_resource(numerical, "double.txt");
    double double_r_value = DtwResource_get_double(double_r);

    DtwResource *long_r = DtwResource_sub_resource(numerical, "integer.txt");
    long long_r_value = DtwResource_get_long(long_r);
    
    DtwResource *bool_r = DtwResource_sub_resource(numerical, "true_normal.txt");
    bool bool_r_value = DtwResource_get_bool(bool_r);

    // Display retrieved values if no error
    if (!DtwResource_error(values)) {
        printf("value string: %s\n", string_r_value);
        printf("blob size: %ld\n", blob_r->value_size);
        printf("double value: %lf\n", double_r_value);
        printf("long value: %ld\n", long_r_value);
        printf("bool value: %d\n", bool_r_value);
    }

    // Handle errors
    if (DtwResource_error(values)) {
        char *message = DtwResource_get_error_message(values);
        printf("%s", message);
    }

    // Clean up
    DtwResource_free(values);
    return 0;
}
```