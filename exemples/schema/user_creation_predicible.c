
#include "doTheWorld.h"


int main(){
    dtw_debug_time = true;
    DtwNamespace  dtw = newDtwNamespace();

    DtwResource *database = dtw.resource.newResource("tests/target/schema_database");
    DtwSchema  *users =dtw.resource.sub_schema(database,"users");
    dtw.schema.add_primary_key(users,"name");
    dtw.schema.add_primary_key(users,"email");

    DtwResource *user = dtw.schema.new_insertion(users);
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




