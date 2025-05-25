#include "doTheWorldOne.c"

// Removed global variable: DtwNamespace dtw;

void create_users(DtwResource *database, const char *name, const char *email, const char *password, int age) {
    DtwResource *users = DtwResource_sub_resource(database, "users");  // Replaced dtw.resource.sub_resource
    DtwResource *user = DtwResource_new_schema_insertion(users);  // Replaced dtw.resource.new_schema_insertion
    DtwResource_set_string_in_sub_resource(user, "name", name);  // Replaced dtw.resource.set_string_in_sub_resource
    DtwResource_set_string_in_sub_resource(user, "email", email);  // Replaced dtw.resource.set_string_in_sub_resource
    DtwResource_set_string_sha_in_sub_resource(user, "password", password);  // Replaced dtw.resource.set_string_sha_in_sub_resource
    DtwResource_set_long_in_sub_resource(user, "age", age);  // Replaced dtw.resource.set_long_in_sub_resource
}

int main() {
    // Removed: dtw = newDtwNamespace();
    
    DtwResource *database = new_DtwResource("tests/target/schema_database");  // Replaced dtw.resource.newResource
    DtwDatabaseSchema *root_schema = DtwResource_newDatabaseSchema(database);  // Replaced dtw.resource.newDatabaseSchema
    DtwSchema *users_schema = DtwDatabaseSchema_new_subSchema(root_schema, "users");  // Replaced dtw.database_schema.sub_schema
    DtwSchema_add_primary_key(users_schema, "name");  // Replaced dtw.schema.add_primary_key
    DtwSchema_add_primary_key(users_schema, "email");  // Replaced dtw.schema.add_primary_key
    
    create_users(database, "mateus", "mateusmoutinho01@gmail.com", "1234", 27);
    
    DtwResource *users = DtwResource_sub_resource(database, "users");  // Replaced dtw.resource.sub_resource
    DtwResource *mateus = DtwResource_find_by_primary_key_with_string(users, "name", "mateus");  // Replaced dtw.resource.find_by_primary_key_with_string
    DtwResource_rename_sub_resource(mateus, "name", "new name created");  // Replaced dtw.resource.rename_sub_resource
    
    if (DtwResource_error(database)) {  // Replaced dtw.resource.error
        printf("error:%s\n", DtwResource_get_error_message(database));  // Replaced dtw.resource.get_error_message
        DtwResource_free(database);  // Replaced dtw.resource.free
        return 0;
    }
    
    DtwResource_commit(database);  // Replaced dtw.resource.commit
    DtwResource_free(database);  // Replaced dtw.resource.free
    
    return 0;
}