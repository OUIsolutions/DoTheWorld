
#include "doTheWorld.h"
DtwNamespace dtw;




void create_users(DtwResource *database,const char *name,const char *email,const char *password, int age){

    DtwSchema  *users =dtw.resource.sub_schema(database,"users");
    DtwResource *user = dtw.schema.new_insertion(users);
    dtw.resource.set_string_in_sub_resource(user,"name",name);
    dtw.resource.set_string_in_sub_resource(user,"email",email);
    dtw.resource.set_string_sha_in_sub_resource(user,"password",password);
    dtw.resource.set_long_in_sub_resource(user,"age",age);
}

int main(){

    dtw = newDtwNamespace();
    DtwResource *database = dtw.resource.newResource("tests/target/schema_database");
    DtwSchema  *users =dtw.resource.sub_schema(database,"users");
    dtw.schema.add_primary_key(users,"name");
    dtw.schema.add_primary_key(users,"email");

    create_users(database,"mateus","mateusmoutinho01@gmail.com","1234",27);
    create_users(database,"user1","user1@gmail.com","1234",27);
    create_users(database,"user2","user2@gmail.com","1234",27);

    DtwResourceArray *all_users = dtw.schema.get_values(users);
    for(int i = 0; i < all_users->size;i++){

        DtwResource * current = all_users->resources[i];
        char *name = dtw.resource.get_string_from_sub_resource(current,"name");
        char *email  = dtw.resource.get_string_from_sub_resource(current,"email");
        long age = dtw.resource.get_long_from_sub_resource(current,"age");

        if(!dtw.resource.error(database)){
            printf("name: %s\n",name);
            printf("email: %s\n",email);
            printf("age: %ld\n",age);
        }

    }


    if(dtw.resource.error(database)){
        printf("error:%s\n",dtw.resource.get_error_message(database));
        dtw.resource.free(database);
        return 0;
    }

    dtw.resource.commit(database);
    dtw.resource.free(database);


}

