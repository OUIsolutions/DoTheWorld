
#include "../../../doTheWorld_test.h"
DtwNamespace dtw;




char *create_users(const char *name,const char *email,const char *password, int age){

    DtwResource *database = dtw.resource.newResource("tests/target/schema_database");
    DtwSchema  *users =dtw.resource.sub_schema(database,"users");
    dtw.schema.add_primary_key(users,"name");
    dtw.schema.add_primary_key(users,"email");
    DtwResource *user = dtw.schema.new_insertion(users);
    dtw.resource.set_string_in_sub_resource(user,"name",name);
    dtw.resource.set_string_in_sub_resource(user,"email",email);
    dtw.resource.set_string_sha_in_sub_resource(user,"password",password);
    dtw.resource.set_long_in_sub_resource(user,"age",age);
    dtw.resource.commit(database);
    if(dtw.resource.error(database)){
        char *error = dtw.resource.get_error_message(database);
        char *copy = strdup(error);
        dtw.resource.free(database);
        return copy;
    }
    dtw.resource.free(database);
    return NULL;
}

int main(){
    dtw = newDtwNamespace();

    char *error = create_users("mateus","mateusmoutinho01@gmail.com","1234",27);
    if(error){
        printf("error:%s\n",error);
        free(error);
        return 0;
    }


}


