#include "doTheWorldOne.c"

int main(){
    DtwResource *database = new_DtwResource("tests/target/schema_database");

    DtwDatabaseSchema *root_schema = DtwResource_newDatabaseSchema(database);
    DtwSchema *users_schema = DtwDtatabaseSchema_new_subSchema(root_schema, "users");

    DtwSchema_add_primary_key(users_schema, "name");
    DtwSchema_add_primary_key(users_schema, "email");

    DtwResource *users = DtwResource_sub_resource(database, "users");

    DtwResource *user = DtwResource_new_schema_insertion(users);
    DtwResource_set_string_in_sub_resource(user, "name", "mateus");
    DtwResource_set_string_in_sub_resource(user, "email", "mateusmoutinho01@gmail.com");
    DtwResource_set_string_sha_in_sub_resource(user, "password", "12345");
    DtwResource_set_long_in_sub_resource(user, "age", 27);

    if(DtwResource_error(database)){
        printf("error:%s", DtwResource_get_error_message(database));
    }

    DtwResource_commit(database);
    DtwResource_free(database);
}