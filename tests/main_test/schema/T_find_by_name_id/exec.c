
#include "../../../../release/doTheWorld.h"
DtwNamespace dtw;




char * create_users(DtwResource *database,const char *name,const char *email,const char *password, int age){

    DtwResource  *users =dtw.resource.sub_resource(database,"users");
    DtwResource *user = dtw.resource.new_schema_insertion(users);
    dtw.resource.set_string_in_sub_resource(user,"name",name);
    dtw.resource.set_string_in_sub_resource(user,"email",email);
    dtw.resource.set_string_sha_in_sub_resource(user,"password",password);
    dtw.resource.set_long_in_sub_resource(user,"age",age);
    return user->name;
}

int main(){

    dtw = newDtwNamespace();
    DtwResource *database = dtw.resource.newResource("tests/target/schema_database");
    DtwDatabaseSchema *root_schema  = dtw.resource.newDatabaseSchema(database);
    DtwSchema *users = dtw.database_schema.sub_schema(root_schema,"users");
    dtw.schema.add_primary_key(users,"name");
    dtw.schema.add_primary_key(users,"email");

     char *name_id =  create_users(database,"mateus","mateusmoutinho01@gmail.com","1234",27);

    if(dtw.resource.error(database)){
        printf("error:%s\n",dtw.resource.get_error_message(database));
        dtw.resource.free(database);
        return 0;
    }
    printf("name id: %s\n",name_id);

    dtw.resource.commit(database);
    dtw.resource.free(database);


}
