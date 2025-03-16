
#include "doTheWorld.h"


int main(){
    DtwNamespace  dtw = newDtwNamespace();

    DtwResource *database = dtw.resource.newResource("tests/target/schema_database");

    DtwDatabaseSchema *root_schema  = dtw.resource.newDatabaseSchema(database);
    DtwSchema *users_schema = dtw.database_schema.sub_schema(root_schema,"users");
    dtw.schema.add_primary_key(users_schema,"name");
    dtw.schema.add_primary_key(users_schema,"email");

    DtwResource  *users =dtw.resource.sub_resource(database,"users");

    DtwResource *user = dtw.resource.new_schema_insertion(users);
    dtw.resource.set_string_in_sub_resource(user,"name","mateus");
    dtw.resource.set_string_in_sub_resource(user,"email","mateusmoutinho01@gmail.com");
    dtw.resource.set_string_sha_in_sub_resource(user,"password","12345");
    dtw.resource.set_long_in_sub_resource(user,"age",27);

    if(dtw.resource.error(database)){
        printf("error:%s",dtw.resource.get_error_message(database));
    }

    dtw.resource.commit(database);
    dtw.resource.free(database);
}
