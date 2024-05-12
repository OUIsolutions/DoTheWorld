
#include "../../../doTheWorld_test.h"
DtwNamespace dtw;

void  create_users(DtwSchema *schema,const char *name,const char *email,const char *password, int age){
    DtwResource *user = dtw.schema.new_insertion(schema);
    dtw.resource.set_string_in_sub_resource(user,"name",name);
    dtw.resource.set_string_in_sub_resource(user,"email",email);
    dtw.resource.set_string_sha_in_sub_resource(user,"password",password);
    dtw.resource.set_long_in_sub_resource(user,"age",age);
}

int main(){
    dtw = newDtwNamespace();

    DtwResource *database = dtw.resource.newResource("schema_database");
    DtwSchema  *users =dtw.resource.sub_schema(database,"users");
    dtw.schema.add_primary_key(users,"name");
    dtw.schema.add_primary_key(users,"email");

    create_users(users,"mateus","mateusmoutinho01@gmail.com","1234",27);

    if(dtw.resource.error(database)){
        printf("error:%s",dtw.resource.get_error_message(database));
    }

    dtw.resource.commit(database);
    dtw.resource.free(database);
}




