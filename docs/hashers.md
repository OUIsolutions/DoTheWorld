# Hashing Utilities

This document provides an overview of the hashing utilities provided by the library for generating SHA-256 hashes and creating custom hash digests. These tools are useful for tasks such as file integrity verification, dynamic programming, and avoiding recomputation in compilers or bundlers.

## SHA-256 Hash Generation

The library supports generating SHA-256 hashes directly from files. This is particularly useful for verifying file integrity or creating unique identifiers for file contents.

### Example: Generating SHA-256 Hash from a File

The following example demonstrates how to generate an SHA-256 hash from a file using the `dtw_generate_sha_from_file` function.

```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]) {
    // Generate SHA-256 hash from a file
    char *hash = dtw_generate_sha_from_file("tests/target/blob.png");
    printf("SHA: %s\n", hash);
    
    // Free the allocated memory for the hash
    free(hash);
    return 0;
}
```

**Explanation:**
- The `dtw_generate_sha_from_file` function takes a file path as input and returns a dynamically allocated string containing the SHA-256 hash of the file's contents.
- Ensure the file exists at the specified path; otherwise, the function may return `NULL` or an error.
- Always free the returned hash string to prevent memory leaks.

## Custom Hashing with `DtwHash`

The `DtwHash` object provides a flexible way to create custom hash digests by combining various types of data (strings, numbers, booleans, arrays, files, and folders). This is particularly useful in scenarios like dynamic programming or caching, where a unique hash is needed to represent a combination of inputs or states.

### Creating and Freeing a `DtwHash` Object

To use the `DtwHash` object, initialize it with `newDtwHash()` and free it with `DtwHash_free()` when done.

```c
DtwHash *my_hash = newDtwHash();
// Use the hash object for digest operations
DtwHash_free(my_hash);
```

### Digesting Basic Data Types

You can digest various data types into the hash object. Each digest operation updates the internal hash value, which can be accessed via `my_hash->hash`.

#### Example: Digesting Strings, Numbers, and Booleans

```c
#include "doTheWorldOne.c"

int main() {
    DtwHash *my_hash = newDtwHash();

    // Digest a string
    DtwHash_digest_string(my_hash, "my string");
    printf("Value after digesting string: %s\n", my_hash->hash);

    // Digest a long integer
    DtwHash_digest_long(my_hash, 10);
    printf("Value after digesting long: %s\n", my_hash->hash);

    // Digest a double
    DtwHash_digest_double(my_hash, 15.6);
    printf("Value after digesting double: %s\n", my_hash->hash);

    // Digest a boolean
    DtwHash_digest_bool(my_hash, true);
    printf("Value after digesting boolean: %s\n", my_hash->hash);

    // Free the hash object
    DtwHash_free(my_hash);
    return 0;
}
```

**Explanation:**
- Each `DtwHash_digest_*` function updates the internal hash value by incorporating the provided data.
- The `my_hash->hash` field contains the current hash as a string, which can be printed or used for comparisons.

#### Example: Digesting a String Array

```c
#include "doTheWorldOne.c"

int main() {
    DtwHash *my_hash = newDtwHash();

    // Create and populate a string array
    DtwStringArray *test = newDtwStringArray();
    DtwStringArray_append(test, "b");
    DtwStringArray_append(test, "a");

    // Digest the string array
    DtwHash_digest_string_array(my_hash, test);
    printf("Value after digesting string array: %s\n", my_hash->hash);

    // Free resources
    DtwStringArray_free(test);
    DtwHash_free(my_hash);
    return 0;
}
```

**Explanation:**
- The `DtwHash_digest_string_array` function processes all elements in the provided `DtwStringArray` and updates the hash accordingly.
- The order of elements in the array may affect the resulting hash, depending on the implementation.

### Digesting Files and Folders by Content

You can also digest the contents of files and folders to create a hash representing their data.

#### Example: Digesting a File and Folder by Content

```c
#include "doTheWorldOne.c"

int main() {
    DtwHash *my_hash = newDtwHash();

    // Digest a file's content
    DtwHash_digest_file(my_hash, "tests/target/a.txt");
    printf("After digesting a file: %s\n", my_hash->hash);

    // Digest a folder's content recursively
    DtwHash_digest_folder_by_content(my_hash, "tests/target");
    printf("After digesting a folder: %s\n", my_hash->hash);

    // Free the hash object
    DtwHash_free(my_hash);
    return 0;
}
```

**Explanation:**
- `DtwHash_digest_file` reads the content of the specified file and incorporates it into the hash.
- `DtwHash_digest_folder_by_content` recursively processes all files in the specified folder, digesting their contents into the hash. The order of processing may affect the final hash value.

### Digesting Files and Folders by Last Modification Time

Instead of digesting content, you can create a hash based on the last modification times of files and folders. This is useful for detecting changes without reading file contents.

#### Example: Digesting a File and Folder by Last Modification Time

```c
#include "doTheWorldOne.c"

int main() {
    DtwHash *my_hash = newDtwHash();

    // Digest a file's last modification time
    DtwHash_digest_entity_last_modification(my_hash, "tests/target/a.txt");
    printf("After digesting a file's modification time: %s\n", my_hash->hash);

    // Digest a folder's last modification times recursively
    DtwHash_digest_folder_by_last_modification(my_hash, "tests/target");
    printf("After digesting a folder's modification times: %s\n", my_hash->hash);

    // Free the hash object
    DtwHash_free(my_hash);
    return 0;
}
```

**Explanation:**
- `DtwHash_digest_entity_last_modification` incorporates the last modification time of a single file or entity into the hash.
- `DtwHash_digest_folder_by_last_modification` recursively processes all files in the specified folder, digesting their modification times into the hash.

## Best Practices

1. **Memory Management**: Always free dynamically allocated resources like `DtwHash`, `DtwStringArray`, and hash strings returned by functions like `dtw_generate_sha_from_file` to avoid memory leaks.
2. **Error Handling**: Check for `NULL` returns or errors when working with file paths or digest operations, especially when files or folders may not exist.
3. **Hash Consistency**: Be aware that the order of digest operations affects the final hash value. Ensure consistent ordering if reproducibility is required.

## Use Cases

- **File Integrity**: Use SHA-256 hashing to verify that files have not been altered.
- **Caching**: Use `DtwHash` to create unique identifiers for complex data structures or inputs, enabling efficient caching in compilers or bundlers.
- **Change Detection**: Use modification time-based hashing to detect changes in files or directories without reading their contents.
