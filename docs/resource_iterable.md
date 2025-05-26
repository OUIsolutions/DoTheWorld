# Iterable Resources

The iterable functional system in the `doTheWorld` library allows you to easily iterate over `DtwResource` objects, apply filters, and map data into various formats. This documentation covers the different iteration and mapping methods available for resources and schemas, including examples for each method.

## Table of Contents
- [Each](#each)
- [Schema Each](#schema-each)
- [Map](#map)
- [Schema Map](#schema-map)
- [cJSON Array Map](#cjson-array-map)
- [cJSON Object Map](#cjson-object-map)
- [CHash Array Map](#chash-array-map)

## Each

The `DtwResource_foreach` function allows you to iterate over all sub-resources of a `DtwResource`. You can customize the iteration with a callback function to process each resource, a filtration callback to include or exclude resources, a start index (defaults to 0), and a total number of elements to process (defaults to all).

### Example: Iterating Over Resources with Filtration

```c
#include "doTheWorldOne.c"

DtwRandonizer *randomizer;

typedef struct {
    int age;
} Filtrage;

void print_user(DtwResource *user, void *filtrage) {
    printf("Age: %ld\n", DtwResource_get_long_from_sub_resource(user, "age"));
    printf("Name: %s\n", DtwResource_get_string_from_sub_resource(user, "name"));
}

bool verify_if_print_user(DtwResource *user, void *filtrage) {
    Filtrage *f = (Filtrage *)filtrage;
    long age = DtwResource_get_long_from_sub_resource(user, "age");
    return age < f->age;
}

void create_x_users(DtwResource *users, long quantity) {
    for (int i = 0; i < quantity; i++) {
        DtwResource *current = DtwResource_sub_resource_random(users, NULL);
        char formatted_name[20] = {0};
        sprintf(formatted_name, "user%d", i);
        long age = DtwRandonizer_generate_num(randomizer, 100);
        DtwResource_set_string_in_sub_resource(current, "name", formatted_name);
        DtwResource_set_long_in_sub_resource(current, "age", age);
    }
}

int main() {
    randomizer = newDtwRandonizer();
    DtwResource *users = new_DtwResource("users");
    create_x_users(users, 100);
    
    DtwResourceForeachProps props = DtwResource_create_foreach_props(print_user);
    Filtrage f;
    f.age = 18;
    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

    DtwResource_foreach(users, props);
    
    DtwResource_free(users);
    DtwRandonizer_free(randomizer);
    return 0;
}
```

### Explanation
- **Initialization**: A `DtwResource` named `users` is created, and 100 user sub-resources are added with random ages and formatted names.
- **Filtration**: The `verify_if_print_user` function filters users under 18 years old.
- **Iteration**: The `print_user` callback prints the name and age of each filtered user.
- **Props Configuration**: The `DtwResourceForeachProps` struct allows customization of the iteration behavior, including the filtration callback and arguments.

## Schema Each

The `DtwResource_schema_foreach` function enables iteration over resources within a schema. This is useful when working with structured data defined by a `DtwDatabaseSchema`.

### Example: Iterating Over Schema Resources

```c
#include "doTheWorldOne.c"

DtwRandonizer *randomizer;

typedef struct {
    int age;
} Filtrage;

void print_user(DtwResource *user, void *filtrage) {
    printf("Age: %ld\n", DtwResource_get_long_from_sub_resource(user, "age"));
    printf("Name: %s\n", DtwResource_get_string_from_sub_resource(user, "name"));
}

bool verify_if_print_user(DtwResource *user, void *filtrage) {
    Filtrage *f = (Filtrage *)filtrage;
    long age = DtwResource_get_long_from_sub_resource(user, "age");
    return age < f->age;
}

void create_x_users(DtwResource *users, long quantity) {
    for (int i = 0; i < quantity; i++) {
        DtwResource *current = DtwResource_new_schema_insertion(users);
        char formatted_name[20] = {0};
        sprintf(formatted_name, "user%d", i);
        long age = DtwRandonizer_generate_num(randomizer, 100);
        DtwResource_set_string_in_sub_resource(current, "name", formatted_name);
        DtwResource_set_long_in_sub_resource(current, "age", age);
    }
}

void create_schemas(DtwResource *database) {
    DtwDatabaseSchema *schema = DtwResource_newDatabaseSchema(database);
    DtwSchema *users = DtwDatabaseSchema_new_subSchema(schema, "users");
    DtwSchema_add_primary_key(users, "name");
}

int main() {
    randomizer = newDtwRandonizer();
    DtwResource *database = new_DtwResource("database");
    create_schemas(database);
    DtwResource *users = DtwResource_sub_resource(database, "users");
    create_x_users(users, 100);
    
    Filtrage f;
    f.age = 18;
    DtwResourceForeachProps props = DtwResource_create_foreach_props(print_user);
    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

    DtwResource_schema_foreach(users, props);
    
    DtwResource_free(database);
    DtwRandonizer_free(randomizer);
    return 0;
}
```

### Explanation
- **Schema Creation**: A database schema is defined with a `users` subschema and a primary key on `name`.
- **Data Insertion**: Users are added using `DtwResource_new_schema_insertion` to adhere to the schema structure.
- **Iteration**: The `DtwResource_schema_foreach` function iterates over the schema resources, applying the same filtration and printing logic as in the `Each` example.

## Map

The `DtwResource_map` function allows you to transform resources into a custom data structure. You provide an object to store results, a retrieval function to create transformed data, and an append function to add transformed data to your object.

### Example: Mapping Resources to a cJSON Array

```c
#include "doTheWorldOne.c"

DtwRandonizer *randomizer;

typedef struct {
    int age;
} Filtrage;

cJSON *return_user(DtwResource *user, void *filtrage) {
    cJSON *created_object = cJSON_CreateObject();
    cJSON_AddStringToObject(created_object, "name", DtwResource_get_string_from_sub_resource(user, "name"));
    cJSON_AddNumberToObject(created_object, "age", DtwResource_get_long_from_sub_resource(user, "age"));
    return created_object;
}

bool verify_if_print_user(DtwResource *user, void *filtrage) {
    Filtrage *f = (Filtrage *)filtrage;
    long age = DtwResource_get_long_from_sub_resource(user, "age");
    return age < f->age;
}

void create_x_users(DtwResource *users, long quantity) {
    for (int i = 0; i < quantity; i++) {
        DtwResource *current = DtwResource_sub_resource_random(users, NULL);
        char formatted_name[20] = {0};
        sprintf(formatted_name, "user%d", i);
        long age = DtwRandonizer_generate_num(randomizer, 100);
        DtwResource_set_string_in_sub_resource(current, "name", formatted_name);
        DtwResource_set_long_in_sub_resource(current, "age", age);
    }
}

int main() {
    randomizer = newDtwRandonizer();
    DtwResource *database = new_DtwResource("database");
    DtwResource *users = DtwResource_sub_resource(database, "users");
    create_x_users(users, 100);
    
    Filtrage f;
    f.age = 18;
    cJSON *items = cJSON_CreateArray();
    DtwResourceMapProps props = DtwResource_create_map_props(
        items,
        (void (*)(void*, void*))cJSON_AddItemToArray,
        (void* (*)(DtwResource *, void*))return_user
    );
    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

    DtwResource_map(users, props);
    
    char *content = cJSON_Print(items);
    printf("%s\n", content);
    cJSON_Delete(items);
    free(content);
    DtwResource_free(database);
    DtwRandonizer_free(randomizer);
    return 0;
}
```

### Explanation
- **Transformation**: The `return_user` function converts each `DtwResource` into a `cJSON` object with `name` and `age` fields.
- **Filtration**: Only users under 18 are included in the mapping.
- **Result Storage**: The transformed data is appended to a `cJSON` array using `cJSON_AddItemToArray`.

## Schema Map

The `DtwResource_schema_map` function works similarly to `DtwResource_map` but operates on schema-based resources.

### Example: Mapping Schema Resources to a cJSON Array

```c
#include "doTheWorldOne.c"

DtwRandonizer *randomizer;

typedef struct {
    int age;
} Filtrage;

cJSON *return_user(DtwResource *user, void *filtrage) {
    cJSON *created_object = cJSON_CreateObject();
    cJSON_AddStringToObject(created_object, "name", DtwResource_get_string_from_sub_resource(user, "name"));
    cJSON_AddNumberToObject(created_object, "age", DtwResource_get_long_from_sub_resource(user, "age"));
    return created_object;
}

bool verify_if_print_user(DtwResource *user, void *filtrage) {
    Filtrage *f = (Filtrage *)filtrage;
    long age = DtwResource_get_long_from_sub_resource(user, "age");
    return age < f->age;
}

void create_x_users(DtwResource *users, long quantity) {
    for (int i = 0; i < quantity; i++) {
        DtwResource *current = DtwResource_new_schema_insertion(users);
        char formatted_name[20] = {0};
        sprintf(formatted_name, "user%d", i);
        long age = DtwRandonizer_generate_num(randomizer, 100);
        DtwResource_set_string_in_sub_resource(current, "name", formatted_name);
        DtwResource_set_long_in_sub_resource(current, "age", age);
    }
}

void create_schemas(DtwResource *database) {
    DtwDatabaseSchema *schema = DtwResource_newDatabaseSchema(database);
    DtwSchema *users = DtwDatabaseSchema_new_subSchema(schema, "users");
    DtwSchema_add_primary_key(users, "name");
}

int main() {
    randomizer = newDtwRandonizer();
    DtwResource *database = new_DtwResource("database");
    create_schemas(database);
    DtwResource *users = DtwResource_sub_resource(database, "users");
    create_x_users(users, 100);
    
    Filtrage f;
    f.age = 18;
    cJSON *items = cJSON_CreateArray();
    DtwResourceMapProps props = DtwResource_create_map_props(
        items,
        (void (*)(void*, void*))cJSON_AddItemToArray,
        (void* (*)(DtwResource *, void*))return_user
    );
    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

    DtwResource_schema_map(users, props);
    
    char *content = cJSON_Print(items);
    printf("%s\n", content);
    cJSON_Delete(items);
    free(content);
    DtwResource_free(database);
    DtwRandonizer_free(randomizer);
    return 0;
}
```

### Explanation
- **Schema Context**: Similar to the `Map` example, but data is inserted using schema-specific functions.
- **Mapping**: The `DtwResource_schema_map` function processes schema resources, applying the same transformation and filtration logic.

## cJSON Array Map

The `DtwResource_map_cJSONArray` function provides a convenient way to directly map resources into a `cJSON` array without manually defining append functions.

### Example: Direct Mapping to cJSON Array

```c
#include "doTheWorldOne.c"

DtwRandonizer *randomizer;

typedef struct {
    int age;
} Filtrage;

cJSON *return_user(DtwResource *user, void *filtrage) {
    cJSON *created_object = cJSON_CreateObject();
    cJSON_AddStringToObject(created_object, "name", DtwResource_get_string_from_sub_resource(user, "name"));
    cJSON_AddNumberToObject(created_object, "age", DtwResource_get_long_from_sub_resource(user, "age"));
    return created_object;
}

bool verify_if_print_user(DtwResource *user, void *filtrage) {
    Filtrage *f = (Filtrage *)filtrage;
    long age = DtwResource_get_long_from_sub_resource(user, "age");
    return age < f->age;
}

void create_x_users(DtwResource *users, long quantity) {
    for (int i = 0; i < quantity; i++) {
        DtwResource *current = DtwResource_sub_resource_random(users, NULL);
        char formatted_name[20] = {0};
        sprintf(formatted_name, "user%d", i);
        long age = DtwRandonizer_generate_num(randomizer, 100);
        DtwResource_set_string_in_sub_resource(current, "name", formatted_name);
        DtwResource_set_long_in_sub_resource(current, "age", age);
    }
}

int main() {
    randomizer = newDtwRandonizer();
    DtwResource *database = new_DtwResource("database");
    DtwResource *users = DtwResource_sub_resource(database, "users");
    create_x_users(users, 100);
    
    Filtrage f;
    f.age = 18;
    DtwResourcecJSONArrayMapProps props = DtwResource_create_cJSONArrayMapProps(return_user);
    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

    cJSON *items = DtwResource_map_cJSONArray(users, props);
    
    char *content = cJSON_Print(items);
    printf("%s\n", content);
    cJSON_Delete(items);
    free(content);
    DtwResource_free(database);
    DtwRandonizer_free(randomizer);
    return 0;
}
```

### Explanation
- **Simplified Mapping**: The `DtwResource_map_cJSONArray` function handles the creation and population of a `cJSON` array internally, simplifying the process compared to the generic `DtwResource_map`.

## cJSON Object Map

The `DtwResource_map_cJSONObject` function maps resources into a `cJSON` object, where each resource is associated with a unique key provided by a `key_provider` function.

### Example: Mapping to cJSON Object with Keys

```c
#include "doTheWorldOne.c"

DtwRandonizer *randomizer;

typedef struct {
    int age;
} Filtrage;

cJSON *return_user(DtwResource *user, void *filtrage) {
    cJSON *created_object = cJSON_CreateObject();
    cJSON_AddStringToObject(created_object, "name", DtwResource_get_string_from_sub_resource(user, "name"));
    cJSON_AddNumberToObject(created_object, "age", DtwResource_get_long_from_sub_resource(user, "age"));
    return created_object;
}

char *get_key(DtwResource *user, void *filtrage) {
    return DtwResource_get_string_from_sub_resource(user, "name");
}

bool verify_if_print_user(DtwResource *user, void *filtrage) {
    Filtrage *f = (Filtrage *)filtrage;
    long age = DtwResource_get_long_from_sub_resource(user, "age");
    return age < f->age;
}

void create_x_users(DtwResource *users, long quantity) {
    for (int i = 0; i < quantity; i++) {
        DtwResource *current = DtwResource_sub_resource_random(users, NULL);
        char formatted_name[20] = {0};
        sprintf(formatted_name, "user%d", i);
        long age = DtwRandonizer_generate_num(randomizer, 100);
        DtwResource_set_string_in_sub_resource(current, "name", formatted_name);
        DtwResource_set_long_in_sub_resource(current, "age", age);
    }
}

int main() {
    randomizer = newDtwRandonizer();
    DtwResource *database = new_DtwResource("database");
    DtwResource *users = DtwResource_sub_resource(database, "users");
    create_x_users(users, 100);
    
    Filtrage f;
    f.age = 18;
    DtwResourcecJSONObjectMapProps props = DtwResource_create_cJSONObjectProps(return_user, get_key);
    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

    cJSON *items = DtwResource_map_cJSONObject(users, props);
    
    char *content = cJSON_Print(items);
    printf("%s\n", content);
    cJSON_Delete(items);
    free(content);
    DtwResource_free(database);
    DtwRandonizer_free(randomizer);
    return 0;
}
```

### Explanation
- **Key Provision**: The `get_key` function provides a unique key (the user's name) for each `cJSON` object entry.
- **Object Mapping**: The resulting `cJSON` object uses these keys to organize the transformed user data.

## CHash Array Map

The `DtwResource_map_CHashArray` function maps resources into a `CHashArray` from the [CHashManipulator](https://github.com/OUIsolutions/CHashManipulator) library. This requires defining `DTW_ALLOW_CHASH` and including the appropriate header.

### Example: Mapping to CHash Array

```c
#define DTW_CHASH_PATH "CHashManipulator.h"
#define DTW_ALLOW_CHASH
#include "doTheWorldOne.c"

CHashNamespace hash;
DtwRandonizer *randomizer;

typedef struct {
    int age;
} Filtrage;

CHashObject *return_user(DtwResource *user, void *filtrage) {
    return newCHashObject(
        "name", hash.newString(DtwResource_get_string_from_sub_resource(user, "name")),
        "age", hash.newNumber(DtwResource_get_long_from_sub_resource(user, "age"))
    );
}

bool verify_if_print_user(DtwResource *user, void *filtrage) {
    Filtrage *f = (Filtrage *)filtrage;
    long age = DtwResource_get_long_from_sub_resource(user, "age");
    return age < f->age;
}

void create_x_users(DtwResource *users, long quantity) {
    for (int i = 0; i < quantity; i++) {
        DtwResource *current = DtwResource_sub_resource_random(users, NULL);
        char formatted_name[20] = {0};
        sprintf(formatted_name, "user%d", i);
        long age = DtwRandonizer_generate_num(randomizer, 100);
        DtwResource_set_string_in_sub_resource(current, "name", formatted_name);
        DtwResource_set_long_in_sub_resource(current, "age", age);
    }
}

int main() {
    hash = newCHashNamespace();
    randomizer = newDtwRandonizer();
    DtwResource *database = new_DtwResource("database");
    DtwResource *users = DtwResource_sub_resource(database, "users");
    create_x_users(users, 100);
    
    Filtrage f;
    f.age = 18;
    DtwResourceCHashArrayMapProps props = DtwResource_create_CHashArrayMapProps(return_user);
    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

    CHashArray *items = DtwResource_map_CHashArray(users, props);
    
    char *content = hash.dump_to_json_string(items);
    printf("%s\n", content);
    hash.free(items);
    free(content);
    DtwResource_free(database);
    DtwRandonizer_free(randomizer);
    return 0;
}
```

### Explanation
- **CHash Integration**: The `CHashManipulator` library is used to create a `CHashArray` of user objects.
- **Configuration**: The `DTW_ALLOW_CHASH` macro must be defined to enable this feature, as it is not included in the default amalgamation.