#include "doTheWorldOne.c"

void create_users(DtwResource  *database,const char *name,const char *email,const char *password, int age){
    DtwResource  *users = DtwResource_sub_resource(database,"users");
    DtwResource *user = DtwResource_new_schema_insertion(users);
    DtwResource_set_string_in_sub_resource(user,"name",name);
    DtwResource_set_string_in_sub_resource(user,"email",email);
    DtwResource_set_string_sha_in_sub_resource(user,"password",password);
    DtwResource_set_long_in_sub_resource(user,"age",age);
    DtwResource_commit(database);
}

int main(){


    DtwResource *database = new_DtwResource("tests/target/schema_database");
    DtwDatabaseSchema *root_schema  = DtwResource_newDatabaseSchema(database);
    DtwSchema *users_schema = DtwDatabaseSchema_new_subSchema(root_schema,"users");
    DtwSchema_add_primary_key(users_schema,"name");
    DtwSchema_add_primary_key(users_schema,"email");

    create_users(database,"mateus","mateusmoutinho01@gmail.com","1234",27);
    if(DtwResource_error(database)){
        printf("error 1:%s\n",DtwResource_get_error_message(database));
    }

    create_users(database,"mateus","mateusmoutinho01@gmail.com","1234",27);
    if(DtwResource_error(database)){
        printf("error 2:%s\n",DtwResource_get_error_message(database));
    }

    DtwResource_free(database);
}