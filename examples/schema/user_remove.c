#include "doTheWorldOne.c"

void create_users(DtwResourceModule resource, DtwResource *database, const char *name, const char *email, const char *password, int age){
    DtwResource *users = resource.sub_resource(database, "users");
    DtwResource *user = resource.new_schema_insertion(users);
    resource.set_string_in_sub_resource(user, "name", name);
    resource.set_string_in_sub_resource(user, "email", email);
    resource.set_string_sha_in_sub_resource(user, "password", password);
    resource.set_long_in_sub_resource(user, "age", age);
}

int main(){
    DtwResourceModule resource = newDtwResourceModule();
    DtwSchemaModule schema = newDtwSchemaModule();
    DtwDatabaseSchemaModule database_schema_mod = newDtwDatabaseSchemaModule();

    DtwResource *database = resource.newResource("tests/target/schema_database");
    DtwDatabaseSchema *root_schema = resource.newDatabaseSchema(database);
    DtwSchema *users_schema = database_schema_mod.sub_schema(root_schema, "users");
    schema.add_primary_key(users_schema, "name");
    schema.add_primary_key(users_schema, "email");

    create_users(resource, database, "mateus", "mateusmoutinho01@gmail.com", "1234", 27);
    create_users(resource, database, "user1", "user1@gmail.com", "1234", 27);
    create_users(resource, database, "user2", "user2@gmail.com", "1234", 27);

    DtwResource *users = resource.sub_resource(database, "users");
    DtwResource *mateus = resource.find_by_primary_key_with_string(users, "name", "mateus");
    resource.destroy(mateus);

    if(resource.error(database)){
        printf("error:%s\n", resource.get_error_message(database));
        resource.free(database);
        return 0;
    }

    resource.commit(database);
    resource.free(database);
}