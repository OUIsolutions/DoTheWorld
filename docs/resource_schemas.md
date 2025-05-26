# Resource Schemas

## Overview
Schemas in the DoTheWorld library provide a structured way to manage resources in a serializable format. They introduce concepts like primary keys and foreign keys, enabling efficient data organization, retrieval, and manipulation. This allows for database-like operations on resources with improved readability and performance.

This document focuses on how to use schemas to create, remove, find, and iterate over resource insertions. Each operation is accompanied by detailed examples to demonstrate practical usage.

## Key Concepts
- **Schema**: A blueprint for organizing resources with defined rules, such as primary keys.
- **Primary Key**: A unique identifier for a resource insertion, used for quick lookups.
- **Insertion**: A single record or entry created under a schema.
- **Resource**: A fundamental entity in DoTheWorld that can represent files, directories, or data structures.

---

## Creating an Insertion
You can create a new resource insertion within a schema. This example demonstrates how to define a schema for users and insert a new user record with fields like name, email, password, and age.

### Example: Creating a User Insertion
```c
#include "doTheWorldOne.c"

int main() {
    // Initialize a new resource database
    DtwResource *database = new_DtwResource("tests/target/schema_database");

    // Create a root schema for the database
    DtwDatabaseSchema *root_schema = DtwResource_newDatabaseSchema(database);
    
    // Define a sub-schema for users
    DtwSchema *users_schema = DtwDatabaseSchema_new_subSchema(root_schema, "users");
    
    // Set primary keys for unique identification
    DtwSchema_add_primary_key(users_schema, "name");
    DtwSchema_add_primary_key(users_schema, "email");

    // Access the users resource
    DtwResource *users = DtwResource_sub_resource(database, "users");

    // Create a new user insertion
    DtwResource *user = DtwResource_new_schema_insertion(users);
    DtwResource_set_string_in_sub_resource(user, "name", "mateus");
    DtwResource_set_string_in_sub_resource(user, "email", "mateusmoutinho01@gmail.com");
    DtwResource_set_string_sha_in_sub_resource(user, "password", "12345");
    DtwResource_set_long_in_sub_resource(user, "age", 27);

    // Check for errors
    if (DtwResource_error(database)) {
        printf("Error: %s\n", DtwResource_get_error_message(database));
    }

    // Commit changes to persist them
    DtwResource_commit(database);
    // Free resources to prevent memory leaks
    DtwResource_free(database);
    return 0;
}
```

### Explanation
- **Database Initialization**: A resource database is created at the specified path.
- **Schema Definition**: A root schema is established, with a sub-schema for "users".
- **Primary Keys**: The fields "name" and "email" are set as primary keys to ensure uniqueness.
- **Insertion**: A new user is created with fields set using type-specific setters (e.g., `set_string`, `set_long`, `set_string_sha` for hashed values).
- **Error Handling**: Any errors during the process are captured and displayed.
- **Commit and Cleanup**: Changes are saved with `commit`, and memory is freed.

---

## Removing an Insertion
You can remove a specific insertion from a schema. This operation also automatically handles the removal of associated indices tied to primary keys.

### Example: Removing a User Insertion
```c
#include "doTheWorldOne.c"

// Helper function to create user insertions
void create_users(DtwResource *database, const char *name, const char *email, const char *password, int age) {
    DtwResource *users = DtwResource_sub_resource(database, "users");
    DtwResource *user = DtwResource_new_schema_insertion(users);
    DtwResource_set_string_in_sub_resource(user, "name", name);
    DtwResource_set_string_in_sub_resource(user, "email", email);
    DtwResource_set_string_sha_in_sub_resource(user, "password", password);
    DtwResource_set_long_in_sub_resource(user, "age", age);
}

int main() {
    // Initialize database and schema
    DtwResource *database = new_DtwResource("tests/target/schema_database");
    DtwDatabaseSchema *root_schema = DtwResource_newDatabaseSchema(database);
    DtwSchema *users_schema = DtwDatabaseSchema_new_subSchema(root_schema, "users");
    DtwSchema_add_primary_key(users_schema, "name");
    DtwSchema_add_primary_key(users_schema, "email");

    // Create multiple users
    create_users(database, "mateus", "mateusmoutinho01@gmail.com", "1234", 27);
    create_users(database, "user1", "user1@gmail.com", "1234", 27);
    create_users(database, "user2", "user2@gmail.com", "1234", 27);

    // Access users resource
    DtwResource *users = DtwResource_sub_resource(database, "users");
    // Find and remove a specific user by primary key
    DtwResource *mateus = DtwResource_find_by_primary_key_with_string(users, "name", "mateus");
    DtwResource_destroy(mateus);

    // Error handling
    if (DtwResource_error(database)) {
        printf("Error: %s\n", DtwResource_get_error_message(database));
        DtwResource_free(database);
        return 0;
    }

    // Commit changes and cleanup
    DtwResource_commit(database);
    DtwResource_free(database);
    return 0;
}
```

### Explanation
- **Helper Function**: `create_users` simplifies the process of adding multiple users.
- **Removal**: The `DtwResource_destroy` function removes the specified user insertion and associated indices.
- **Primary Key Search**: The user is located using a primary key search before removal.

---

## Finding an Insertion
Using primary keys, you can quickly find a specific insertion without iterating over all records, improving both readability and performance.

### Example: Finding a User by Primary Key
```c
#include "doTheWorldOne.c"

// Helper function to create user insertions
void create_users(DtwResource *database, const char *name, const char *email, const char *password, int age) {
    DtwResource *users = DtwResource_sub_resource(database, "users");
    DtwResource *user = DtwResource_new_schema_insertion(users);
    DtwResource_set_string_in_sub_resource(user, "name", name);
    DtwResource_set_string_in_sub_resource(user, "email", email);
    DtwResource_set_string_sha_in_sub_resource(user, "password", password);
    DtwResource_set_long_in_sub_resource(user, "age", age);
}

int main() {
    // Initialize database and schema
    DtwResource *database = new_DtwResource("tests/target/schema_database");
    DtwDatabaseSchema *root_schema = DtwResource_newDatabaseSchema(database);
    DtwSchema *users_schema = DtwDatabaseSchema_new_subSchema(root_schema, "users");
    DtwSchema_add_primary_key(users_schema, "name");
    DtwSchema_add_primary_key(users_schema, "email");

    // Create multiple users
    create_users(database, "mateus", "mateusmoutinho01@gmail.com", "1234", 27);
    create_users(database, "user1", "user1@gmail.com", "1234", 27);
    create_users(database, "user2", "user2@gmail.com", "1234", 27);

    // Access users resource
    DtwResource *users = DtwResource_sub_resource(database, "users");
    // Find a user by primary key
    DtwResource *mateus = DtwResource_find_by_primary_key_with_string(users, "name", "mateus");
    // Retrieve field values
    char *name = DtwResource_get_string_from_sub_resource(mateus, "name");
    char *email = DtwResource_get_string_from_sub_resource(mateus, "email");
    long age = DtwResource_get_long_from_sub_resource(mateus, "age");

    // Display retrieved data if no errors
    if (!DtwResource_error(database)) {
        printf("Name: %s\n", name);
        printf("Email: %s\n", email);
        printf("Age: %ld\n", age);
    }

    // Error handling
    if (DtwResource_error(database)) {
        printf("Error: %s\n", DtwResource_get_error_message(database));
        DtwResource_free(database);
        return 0;
    }

    // Commit changes and cleanup
    DtwResource_commit(database);
    DtwResource_free(database);
    return 0;
}
```

### Explanation
- **Efficient Lookup**: The `DtwResource_find_by_primary_key_with_string` function allows direct access to a record using a primary key.
- **Data Retrieval**: Field values are retrieved using type-specific getters (e.g., `get_string`, `get_long`).

---

## Iterating Over Insertions
You can iterate over all insertions in a schema to process or display records. This is useful for generating reports or performing batch operations.

### Example: Iterating Over User Insertions
```c
#include "doTheWorldOne.c"

// Helper function to create user insertions
void create_users(DtwResource *database, const char *name, const char *email, const char *password, int age) {
    DtwResource *users = DtwResource_sub_resource(database, "users");
    DtwResource *user = DtwResource_new_schema_insertion(users);
    DtwResource_set_string_in_sub_resource(user, "name", name);
    DtwResource_set_string_in_sub_resource(user, "email", email);
    DtwResource_set_string_sha_in_sub_resource(user, "password", password);
    DtwResource_set_long_in_sub_resource(user, "age", age);
}

int main() {
    // Initialize database and schema
    DtwResource *database = new_DtwResource("tests/target/schema_database");
    DtwDatabaseSchema *root_schema = DtwResource_newDatabaseSchema(database);
    DtwSchema *users_schema = DtwDatabaseSchema_new_subSchema(root_schema, "users");
    DtwSchema_add_primary_key(users_schema, "name");
    DtwSchema_add_primary_key(users_schema, "email");

    // Create multiple users
    create_users(database, "mateus", "mateusmoutinho01@gmail.com", "1234", 27);
    create_users(database, "user1", "user1@gmail.com", "1234", 27);
    create_users(database, "user2", "user2@gmail.com", "1234", 27);

    // Access users resource
    DtwResource *users = DtwResource_sub_resource(database, "users");
    // Get all user insertions as an array
    DtwResourceArray *all_users = DtwResource_get_schema_values(users);
    // Iterate over each user
    for (int i = 0; i < all_users->size; i++) {
        DtwResource *current = all_users->resources[i];
        char *name = DtwResource_get_string_from_sub_resource(current, "name");
        char *email = DtwResource_get_string_from_sub_resource(current, "email");
        long age = DtwResource_get_long_from_sub_resource(current, "age");

        if (!DtwResource_error(database)) {
            printf("Name: %s\n", name);
            printf("Email: %s\n", email);
            printf("Age: %ld\n", age);
        }
    }

    // Error handling
    if (DtwResource_error(database)) {
        printf("Error: %s\n", DtwResource_get_error_message(database));
        DtwResource_free(database);
        return 0;
    }

    // Commit changes and cleanup
    DtwResource_commit(database);
    DtwResource_free(database);
    return 0;
}
```

### Explanation
- **Array Retrieval**: `DtwResource_get_schema_values` returns an array of all insertions in the schema.
- **Iteration**: A loop processes each insertion, extracting and displaying field values.

---

## Best Practices
1. **Always Handle Errors**: Use `DtwResource_error` and `DtwResource_get_error_message` to catch and handle errors gracefully.
2. **Commit Changes**: Ensure `DtwResource_commit` is called to persist changes to the underlying storage.
3. **Free Resources**: Use `DtwResource_free` to prevent memory leaks after operations are complete.
4. **Use Primary Keys**: Define primary keys for efficient lookups and to enforce uniqueness.

---

## Notes
- This documentation focuses on schema-specific operations. For broader library usage, refer to the main documentation.
- The examples assume the `doTheWorldOne.c` header provides necessary function definitions and dependencies.
