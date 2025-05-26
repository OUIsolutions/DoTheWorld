# Trees and TreeParts

This document provides an overview of the `DtwTree` and `DtwTreePart` concepts in the **doTheWorld** library. These abstractions allow you to manipulate files and directories as tree structures, enabling atomic input/output (IO) operations and massive file modifications with ease. This guide focuses on practical usage with detailed examples.

**Note:** This is a fragment of the larger documentation. For installation, setup, or high-level library details, refer to the main `README.md`.

## Overview of Trees and TreeParts

- **DtwTreePart**: Represents a single file or directory within a tree structure. It provides methods to load, modify, write, or remove content on the hardware (filesystem) with atomic operations.
- **DtwTree**: A collection of `DtwTreePart` objects representing a directory structure. It supports operations like loading from hardware, filtering, mapping, and committing changes atomically.

These concepts are designed to simplify complex file operations by treating the filesystem as a manipulable tree, ensuring safety with transactional commits.

## Working with DtwTreePart

### Loading a TreePart from Hardware

You can load an existing file as a `DtwTreePart` to interact with its content or metadata.

```c
#include "doTheWorldOne.c"

int main() {
    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");
    DtwTreePart_represent(part); // Display the TreePart details
    DtwTreePart_free(part); // Free the allocated memory
    return 0;
}
```

**Explanation**: 
- `newDtwTreePartLoading` loads the file content and metadata from the specified path.
- `DtwTreePart_represent` prints the current state of the `TreePart` (path, content, etc.) for debugging or logging.

### Creating an Empty TreePart

To create a new file as a `DtwTreePart`, use `newDtwTreePartEmpty`. You can then set its content and write it to hardware.

```c
#include "doTheWorldOne.c"

int main() {
    DtwTreePart *part = newDtwTreePartEmpty("tests/target/b.txt");
    DtwTreePart_set_string_content(part, "my message"); // Set content
    DtwTreePart_hardware_write(part, DTW_SET_AS_ACTION); // Mark for writing
    DtwTreePart_hardware_commit(part); // Commit changes to hardware
    DtwTreePart_free(part);
    return 0;
}
```

**Explanation**:
- `DTW_SET_AS_ACTION` marks the operation (write, modify, or remove) to be executed later.
- `DtwTreePart_hardware_commit` applies the marked operation to the filesystem.

### Modifying a TreePart

You can load an existing `TreePart`, modify its content, and commit the changes.

```c
#include "doTheWorldOne.c"

int main() {
    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");
    
    // Retrieve current content
    char *content = DtwTreePart_get_content_string_by_reference(part);
    char new_content[100] = {0};
    strcat(new_content, content);
    strcat(new_content, " New Message");
    DtwTreePart_set_string_content(part, new_content); // Update content
    
    DtwTreePart_hardware_write(part, DTW_SET_AS_ACTION); // Mark for writing
    DtwTreePart_hardware_commit(part); // Commit changes
    DtwTreePart_free(part);
    return 0;
}
```

**Explanation**: 
- `DtwTreePart_get_content_string_by_reference` retrieves the content as a string (non-binary files only).
- The updated content is written to hardware only after committing.

### Removing a TreePart

To delete a file represented by a `TreePart`, use the remove operation.

```c
#include "doTheWorldOne.c"

int main() {
    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");
    DtwTreePart_hardware_remove(part, DTW_EXECUTE_NOW); // Remove immediately
    DtwTreePart_hardware_commit(part); // Commit the removal
    DtwTreePart_free(part);
    return 0;
}
```

**Explanation**:
- `DTW_EXECUTE_NOW` executes the operation immediately rather than marking it for later commit. Use `DTW_SET_AS_ACTION` for delayed execution in transactions.

## Managing Paths with DtwPath

`DtwPath` is a utility structure for handling file paths and extracting or modifying their components.

### Retrieving Path Components

Extract various components (name, extension, directory, full path) from a path.

```c
#include "doTheWorldOne.c"

int main() {
    DtwPath *path = newDtwPath("a/b/c/d.txt");
    char *name = DtwPath_get_full_name(path); // Returns "d.txt"
    char *extension = DtwPath_get_extension(path); // Returns "txt"
    char *dir = DtwPath_get_dir(path); // Returns "a/b/c"
    char *full_path = DtwPath_get_path(path); // Returns "a/b/c/d.txt"
    
    printf("name: %s\n", name);
    printf("extension: %s\n", extension);
    printf("dir: %s\n", dir);
    printf("full_path: %s\n", full_path);
    
    DtwPath_free(path);
    return 0;
}
```

### Modifying Path Attributes

Update path components like name or extension dynamically.

```c
#include "doTheWorldOne.c"

int main() {
    DtwPath *path = newDtwPath("a/b/c/d.txt");
    DtwPath_set_name(path, "test"); // Changes name to "test"
    DtwPath_set_extension(path, "md"); // Changes extension to "md"
    DtwPath_represent(path); // Display updated path
    DtwPath_free(path);
    return 0;
}
```

## Hardware Operations on TreeParts

The library supports atomic operations using `hardware_modify`, `hardware_write`, and `hardware_remove`. These functions allow you to stage changes and commit them later for safety.

### Hardware Modify

Modifies the original file (e.g., renaming by changing extension).

```c
#include "doTheWorldOne.c"

int main() {
    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");
    DtwPath_set_extension(part->path, "md"); // Change extension
    DtwTreePart_hardware_modify(part, DTW_EXECUTE_NOW); // Modify immediately
    DtwTreePart_hardware_commit(part);
    DtwTreePart_free(part);
    return 0;
}
```

### Hardware Write

Writes the content as a new file, ignoring the existence of the old file.

```c
#include "doTheWorldOne.c"

int main() {
    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");
    DtwPath_set_extension(part->path, "md");
    DtwTreePart_hardware_write(part, DTW_EXECUTE_NOW); // Write as new file
    DtwTreePart_hardware_commit(part);
    DtwTreePart_free(part);
    return 0;
}
```

### Hardware Remove

Deletes the file from hardware.

```c
#include "doTheWorldOne.c"

int main() {
    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");
    DtwTreePart_hardware_remove(part, DTW_EXECUTE_NOW); // Remove file
    DtwTreePart_hardware_commit(part);
    DtwTreePart_free(part);
    return 0;
}
```

**Note**: Use `DTW_SET_AS_ACTION` instead of `DTW_EXECUTE_NOW` to stage operations for atomic commits.

## Working with DtwTree

`DtwTree` allows you to handle entire directory structures, perform bulk operations, and manage transactions.

### Loading a Tree from Hardware

Load a directory structure into a `DtwTree` for manipulation.

```c
#include "doTheWorldOne.c"

int main() {
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
        tree,
        "tests/target/",
        (DtwTreeProps){
            .content = DTW_INCLUDE,       // Include file contents
            .hadware_data = DTW_HIDE,     // Hide hardware metadata
            .path_atributes = DTW_INCLUDE // Include path attributes
        }
    );
    DtwTree_represent(tree); // Display tree structure
    DtwTree_free(tree);
    return 0;
}
```

### Iterating Over a Tree

Loop through all `TreeParts` in a `Tree` to perform operations on each.

```c
#include "doTheWorldOne.c"

int main() {
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
        tree,
        "tests/target",
        (DtwTreeProps){
            .content = DTW_INCLUDE,
            .hadware_data = DTW_HIDE,
            .path_atributes = DTW_INCLUDE
        }
    );
    for (int i = 0; i < tree->size; i++) {
        DtwTreePart *current_part = tree->tree_parts[i];
        DtwTreePart_represent(current_part); // Display each part
    }
    DtwTree_free(tree);
    return 0;
}
```

### Finding TreeParts

#### By Name

Search for a `TreePart` by its file name.

```c
#include "doTheWorldOne.c"

int main() {
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
        tree,
        "tests/target",
        (DtwTreeProps){
            .content = DTW_INCLUDE,
            .hadware_data = DTW_HIDE,
            .path_atributes = DTW_INCLUDE
        }
    );
    DtwTreePart *blob = DtwTree_find_tree_part_by_name(tree, "blob.png");
    if (blob) {
        DtwTreePart_represent(blob);
    }
    DtwTree_free(tree);
    return 0;
}
```

#### By Path

Search for a `TreePart` by its full path.

```c
#include "doTheWorldOne.c"

int main() {
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
        tree,
        "tests/target/",
        (DtwTreeProps){
            .content = DTW_INCLUDE,
            .hadware_data = DTW_HIDE,
            .path_atributes = DTW_INCLUDE
        }
    );
    DtwTreePart *element = DtwTree_find_tree_part_by_path(
        tree,
        "tests/target/sub_folder/sub_element.txt"
    );
    if (element) {
        DtwTreePart_represent(element);
    }
    DtwTree_free(tree);
    return 0;
}
```

#### By Custom Function

Search using a custom predicate function.

```c
#include "doTheWorldOne.c"

bool test_if_blob(struct DtwTreePart* part, void *args) {
    char *name = DtwPath_get_full_name(part->path);
    if (!name) return false;
    return strcmp(name, "blob.png") == 0;
}

int main() {
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
        tree,
        "tests/target",
        (DtwTreeProps){
            .content = DTW_INCLUDE,
            .hadware_data = DTW_HIDE,
            .path_atributes = DTW_INCLUDE
        }
    );
    DtwTreePart *blob = DtwTree_find_tree_part_by_function(tree, test_if_blob, NULL);
    if (blob) {
        DtwTreePart_represent(blob);
    }
    DtwTree_free(tree);
    return 0;
}
```

### Tree Transformations

#### Filtering a Tree

Create a new tree containing only `TreeParts` that match a filter condition.

```c
#include "doTheWorldOne.c"

bool filter_txt(struct DtwTreePart *part) {
    char *extension = DtwPath_get_extension(part->path);
    if (!extension) return false;
    return strcmp(extension, "txt") == 0;
}

int main() {
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
        tree,
        "tests/target",
        (DtwTreeProps){
            .content = DTW_INCLUDE,
            .hadware_data = DTW_HIDE,
            .path_atributes = DTW_INCLUDE
        }
    );
    DtwTree *filtered = DtwTree_filter(tree, filter_txt);
    DtwTree_represent(filtered);
    DtwTree_free(filtered);
    DtwTree_free(tree);
    return 0;
}
```

#### Mapping a Tree

Transform each `TreePart` in a tree using a mapping function, returning a new tree.

```c
#include "doTheWorldOne.c"

DtwTreePart *concat_test(struct DtwTreePart *part) {
    if (part->content && !part->is_binary) {
        char *content = DtwTreePart_get_content_string_by_reference(part);
        const char *message = " test";
        char *new_content = (char*)malloc(strlen(content) + strlen(message) + 1);
        strcpy(new_content, content);
        strcat(new_content, message);
        DtwTreePart_set_string_content(part, new_content);
        free(new_content);
    }
    return part;
}

int main() {
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
        tree,
        "tests/target",
        (DtwTreeProps){
            .content = DTW_INCLUDE,
            .hadware_data = DTW_HIDE,
            .path_atributes = DTW_INCLUDE
        }
    );
    DtwTree *mapped = DtwTree_map(tree, concat_test);
    DtwTree_represent(mapped);
    DtwTree_free(mapped);
    DtwTree_free(tree);
    return 0;
}
```

### Committing Tree Changes

Commit all staged changes in a `Tree` atomically to ensure consistency.

```c
#include "doTheWorldOne.c"

int main() {
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
        tree,
        "tests/target",
        (DtwTreeProps){
            .content = DTW_INCLUDE,
            .hadware_data = DTW_HIDE,
            .path_atributes = DTW_INCLUDE
        }
    );
    for (int i = 0; i < tree->size; i++) {
        DtwTreePart *part = tree->tree_parts[i];
        char *extension = DtwPath_get_extension(part->path);
        if (extension && strcmp(extension, "txt") == 0) {
            DtwPath_set_extension(part->path, "md");
            DtwTreePart_hardware_modify(part, DTW_SET_AS_ACTION);
        }
    }
    DtwTree_hardware_commit_tree(tree); // Commit all changes
    DtwTree_free(tree);
    return 0;
}
```

### Transaction Reports

Generate a report of pending changes before committing.

```c
#include "doTheWorldOne.c"

int main() {
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
        tree,
        "tests/target",
        (DtwTreeProps){
            .content = DTW_INCLUDE,
            .hadware_data = DTW_INCLUDE,
            .path_atributes = DTW_INCLUDE
        }
    );
    for (int i = 0; i < tree->size; i++) {
        DtwTreePart *part = tree->tree_parts[i];
        char *extension = DtwPath_get_extension(part->path);
        if (extension && strcmp(extension, "txt") == 0) {
            DtwPath_set_extension(part->path, "md");
            DtwTreePart_hardware_modify(part, DTW_SET_AS_ACTION);
        }
    }
    DtwTreeTransactionReport *report = DtwTree_create_report(tree);
    DtwTreeTransactionReport_represent(report); // Display pending changes
    DtwTreeTransactionReport_free(report);
    DtwTree_free(tree);
    return 0;
}
```

## JSON Serialization of Trees

The library supports saving and loading tree structures as JSON for persistence or transfer.

### Dumping a Tree to a JSON File

Convert a `Tree` to JSON and save it to a file.

```c
#include "doTheWorldOne.c"

int main() {
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
        tree,
        "tests/target/",
        (DtwTreeProps){
            .content = DTW_INCLUDE,
            .hadware_data = DTW_HIDE,
            .path_atributes = DTW_INCLUDE
        }
    );
    DtwTree_dumps_tree_json_to_file(
        tree,
        "tests/target/out.json",
        (DtwTreeProps){
            .minification = DTW_NOT_MIMIFY, // Do not minify JSON
            .ignored_elements = DTW_HIDE,
            .content = DTW_INCLUDE,
            .hadware_data = DTW_HIDE,
            .path_atributes = DTW_INCLUDE
        }
    );
    DtwTree_free(tree);
    return 0;
}
```

### Dumping a Tree to a JSON String

Convert a `Tree` to a JSON string for in-memory use.

```c
#include "doTheWorldOne.c"

int main() {
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
        tree,
        "tests/target/",
        (DtwTreeProps){
            .content = DTW_INCLUDE,
            .hadware_data = DTW_HIDE,
            .path_atributes = DTW_INCLUDE
        }
    );
    char *content = DtwTree_dumps_tree_json(
        tree,
        (DtwTreeProps){
            .minification = DTW_NOT_MIMIFY,
            .ignored_elements = DTW_HIDE,
            .content = DTW_INCLUDE,
            .hadware_data = DTW_HIDE,
            .path_atributes = DTW_INCLUDE
        }
    );
    printf("%s", content);
    free(content);
    DtwTree_free(tree);
    return 0;
}
```

### Loading a Tree from a JSON File

Reconstruct a `Tree` from a saved JSON file.

```c
#include "doTheWorldOne.c"

void dumps_tree() {
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
        tree,
        "tests/target",
        (DtwTreeProps){
            .content = DTW_INCLUDE,
            .hadware_data = DTW_HIDE,
            .path_atributes = DTW_INCLUDE
        }
    );
    DtwTree_dumps_tree_json_to_file(
        tree,
        "tests/target/out.json",
        (DtwTreeProps){
            .minification = DTW_MIMIFY, // Minify JSON
            .ignored_elements = DTW_HIDE,
            .content = DTW_INCLUDE,
            .hadware_data = DTW_HIDE,
            .path_atributes = DTW_INCLUDE
        }
    );
    DtwTree_free(tree);
}

int main() {
    dumps_tree();
    DtwTree *tree = newDtwTree();
    DtwTree_loads_json_tree_from_file(tree, "tests/target/out.json");
    DtwTree_represent(tree);
    DtwTree_free(tree);
    return 0;
}
```

### Loading a Tree from a JSON String

Reconstruct a `Tree` from a JSON string.

```c
#include "doTheWorldOne.c"

char *dumps_tree() {
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
        tree,
        "tests/target",
        (DtwTreeProps){
            .content = DTW_INCLUDE,
            .hadware_data = DTW_INCLUDE,
            .path_atributes = DTW_INCLUDE
        }
    );
    char *content = DtwTree_dumps_tree_json(
        tree,
        (DtwTreeProps){
            .minification = DTW_MIMIFY,
            .ignored_elements = DTW_HIDE,
            .content = DTW_INCLUDE,
            .hadware_data = DTW_HIDE,
            .path_atributes = DTW_INCLUDE
        }
    );
    DtwTree_free(tree);
    return content;
}

int main() {
    char *content = dumps_tree();
    DtwTree *tree = newDtwTree();
    DtwTree_loads_json_tree(tree, content);
    DtwTree_represent(tree);
    DtwTree_free(tree);
    free(content);
    return 0;
}
```

## Key Concepts for Atomic Operations

- **DTW_SET_AS_ACTION**: Stages an operation (write, modify, remove) for later commit, enabling atomic transactions.
- **DTW_EXECUTE_NOW**: Executes the operation immediately, bypassing the transactional system.
- **hardware_commit**: Applies all staged changes to the filesystem, ensuring consistency and safety.

By using these mechanisms, the library ensures that file operations can be performed securely, with the ability to preview changes via transaction reports before finalizing them.
