#include "doTheWorldOne.c"

void create_users(DtwResource *database, const char *name, const char *email, const char *password, int age) {
    DtwResource *users = DtwResource_sub_resource(database, "users");
    DtwResource *user = DtwResource_new_schema_insertion(users);
    DtwResource_set_string_in_sub_resource(user, "name", name);
    DtwResource_set_string_in_sub_resource(user, "email", email);
    DtwResource_set_string_sha_in_sub_resource(user, "password", password);
    DtwResource_set_long_in_sub_resource(user, "age", age);
}

int main() {
    DtwResource *database = new_DtwResource("tests/target/schema_database");
    DtwDatabaseSchema *root_schema = DtwResource_newDatabaseSchema(database);
    DtwSchema *users_schema = DtwDtatabaseSchema_new_subSchema(root_schema, "users");
    DtwSchema_add_primary_key(users_schema, "name");
    DtwSchema_add_primary_key(users_schema, "email");

    create_users(database, "mateus", "mateusmoutinho01@gmail.com", "1234", 27);
    create_users(database, "user1", "user1@gmail.com", "1234", 27);
    create_users(database, "user2", "user2@gmail.com", "1234", 27);
    
    DtwResource *users = DtwResource_sub_resource(database, "users");
    DtwResource *mateus = DtwResource_find_by_primary_key_with_string(users, "name", "mateus");
    char *name = DtwResource_get_string_from_sub_resource(mateus, "name");
    char *email = DtwResource_get_string_from_sub_resource(mateus, "email");
    long age = DtwResource_get_long_from_sub_resource(mateus, "age");

    if (!DtwResource_error(database)) {
        printf("name: %s\n", name);
        printf("email: %s\n", email);
        printf("age: %ld\n", age);
    }

    if (DtwResource_error(database)) {
        printf("error: %s\n", DtwResource_get_error_message(database));
        DtwResource_free(database);
        return 0;
    }

    DtwResource_commit(database);
    DtwResource_free(database);
    return 0;
}