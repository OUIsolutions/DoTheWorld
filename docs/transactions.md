# Transactions in DoTheWorld

Transactions provide a mechanism to group multiple file and directory operations together, allowing you to execute or rollback all changes at once. This helps avoid unwanted side effects by ensuring that operations are applied as a single unit. This document explains how to create, manage, and store transactions using the DoTheWorld library.

## Table of Contents
- [Overview of Transactions](#overview-of-transactions)
- [Creating and Committing a Transaction](#creating-and-committing-a-transaction)
- [Storing a Transaction to JSON](#storing-a-transaction-to-json)
- [Loading a Transaction from JSON](#loading-a-transaction-from-json)

## Overview of Transactions

A transaction in the DoTheWorld library is a collection of file and directory operations (e.g., writing, moving, copying, or removing) that can be executed or discarded as a single unit. This approach ensures consistency and prevents partial application of changes, which could lead to unintended side effects. Transactions can also be serialized to JSON for storage and later retrieval.

Key features of transactions:
- **Atomic Execution**: All operations in a transaction are applied together when committed.
- **Rollback Capability**: If not committed, operations can be discarded without affecting the filesystem.
- **Serialization**: Transactions can be saved to and loaded from JSON files for persistence or transfer.

## Creating and Committing a Transaction

You can create a new transaction using `newDtwTransaction()` and add operations to it. Once all operations are defined, use `DtwTransaction_commit()` to apply the changes to the specified directory.

### Example: Creating and Committing a Transaction

The following example demonstrates how to create a transaction, add operations, and commit the changes to a target directory.

```c
#include "doTheWorldOne.c"

int main() {
    // Create a new transaction
    DtwTransaction *t = newDtwTransaction();
    
    // Add file and directory operations to the transaction
    dtw_write_string_file_content("b.txt", "aaaaa");          // Write content to a file
    dtw_move_any("a.txt", "c.txt", false);                   // Move a file
    dtw_remove_any("blob.png");                              // Remove a file
    dtw_copy_any("sub_folder", "sub_folder2", false);        // Copy a directory
    
    // Commit the transaction to the target directory
    DtwTransaction_commit(t, "tests/target");
    
    // Free the transaction resources
    DtwTransaction_free(t);
    return 0;
}
```

### Explanation of Operations
- `dtw_write_string_file_content`: Writes a string as the content of a specified file.
- `dtw_move_any`: Moves a file or directory from one path to another. The boolean parameter indicates whether to overwrite if the destination exists.
- `dtw_remove_any`: Deletes a specified file or directory.
- `dtw_copy_any`: Copies a file or directory to a new location. The boolean parameter indicates whether to overwrite if the destination exists.
- `DtwTransaction_commit`: Applies all operations in the transaction to the specified base directory.

## Storing a Transaction to JSON

Transactions can be serialized to a JSON file for storage or transfer. This is useful for saving a set of operations to be executed later or on a different system.

### Example: Dumping a Transaction to JSON

The following example shows how to create a transaction, add operations, and save it to a JSON file.

```c
#include "doTheWorldOne.c"

int main() {
    // Create a new transaction
    DtwTransaction *t = newDtwTransaction();
    
    // Add file and directory operations to the transaction
    dtw_write_string_file_content("b.txt", "aaaaa");
    dtw_move_any("a.txt", "c.txt", false);
    dtw_remove_any("blob.png");
    dtw_copy_any("sub_folder", "sub_folder2", false);
    
    // Display the transaction details (optional, for debugging)
    DtwTransaction_represent(t);
    
    // Save the transaction to a JSON file
    DtwTransaction_dumps_to_json_file(t, "tests/target/transaction.json");
    
    // Free the transaction resources
    DtwTransaction_free(t);
    return 0;
}
```

### Explanation of Functions
- `DtwTransaction_represent`: Prints a human-readable representation of the transaction (useful for debugging or logging).
- `DtwTransaction_dumps_to_json_file`: Serializes the transaction to a JSON file at the specified path.

## Loading a Transaction from JSON

You can load a previously saved transaction from a JSON file and inspect or execute it. The library also provides error handling to validate the JSON file before loading.

### Example: Loading a Transaction from JSON

The following example demonstrates how to load a transaction from a JSON file and handle potential errors.

```c
#include "doTheWorldOne.c"

int main() {
    // Load a transaction from a JSON file
    DtwTransaction *t = newDtwTransaction_from_json_file("tests/target/transaction.json");
    
    // Check if the transaction was loaded successfully
    if (!t) {
        // If loading fails, validate the JSON file and display errors
        DtwJsonTransactionError *error = dtw_validate_json_transaction_file("tests/target/transaction.json");
        DtwJsonTransactionError_represent(error); // Display error details
        DtwJsonTransactionError_free(error);      // Free error resources
        return 0;
    }
    
    // Display the loaded transaction details (optional, for debugging)
    DtwTransaction_represent(t);
    
    // Free the transaction resources
    DtwTransaction_free(t);
    return 0;
}
```

### Explanation of Functions
- `newDtwTransaction_from_json_file`: Attempts to load a transaction from the specified JSON file. Returns `NULL` if the file is invalid or cannot be read.
- `dtw_validate_json_transaction_file`: Validates the JSON file and returns an error object with details if the file is invalid.
- `DtwJsonTransactionError_represent`: Prints a human-readable representation of the validation errors.
- `DtwJsonTransactionError_free`: Frees the resources associated with the error object.

## Notes
- Always free transaction resources using `DtwTransaction_free()` to prevent memory leaks.
- Ensure the target directory specified in `DtwTransaction_commit()` exists and is writable.
- JSON files used for transactions should not be manually edited, as invalid formats may cause loading errors.