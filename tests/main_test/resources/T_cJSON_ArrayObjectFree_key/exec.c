#include "../../../../release/doTheWorld.h"


DtwNamespace dtw;
DtwRandonizer *randonizer;
typedef struct {
    int age;
}Filtrage;


cJSON * return_user(DtwResource *user, void *filtragem){
    cJSON *created_object =cJSON_CreateObject();
    cJSON_AddStringToObject(
        created_object,
        "name", dtw.resource.get_string_from_sub_resource(user, "name")
    );

    cJSON_AddNumberToObject(
        created_object,
        "age",
        dtw.resource.get_long_from_sub_resource(user,"age")
    );
    return created_object;
}
char * get_key(DtwResource *user, void *filtrage){
    return strdup(dtw.resource.get_string_from_sub_resource(user, "name"));
}


bool verify_if_print_user(DtwResource *user, void *filtragem){
     Filtrage *f = (Filtrage *)filtragem;
    long age = dtw.resource.get_long_from_sub_resource(user, "age");

    if(age < f->age){

        return true;
    }

    return false;
}
void create_x_users(DtwResource *users,long quantity){
    for(int i =0; i < quantity; i++){
        DtwResource *current = dtw.resource.sub_resource_random(users,NULL);

        char formatted_name[20] = {0};
        sprintf(formatted_name,"user%d", i);
        long age = dtw.randonizer.generate_num(randonizer,100);

        dtw.resource.set_string_in_sub_resource(current,"name",formatted_name);
        dtw.resource.set_long_in_sub_resource(current,"age",age);
    }

}





int main(){
    dtw = newDtwNamespace();
    randonizer = dtw.randonizer.newRandonizer();

    DtwResource *database = dtw.resource.newResource("database");
    DtwResource *users = dtw.resource.sub_resource(database,"users");

    create_x_users(users,100);

    Filtrage f;
    f.age = 18;

    DtwResourcecJSONObjectMapProps props = dtw.resource.create_cJSONObjectProps(return_user,get_key);

    props.filtrage_callback = verify_if_print_user;
    props.args = &f;
    props.free_key = true;

    cJSON *itens = dtw.resource.map_cJSONObject(users,props);


    char *content = cJSON_Print(itens);
    printf("%s",content);
    cJSON_Delete(itens);
    free(content);

    dtw.resource.free(database);
    dtw.randonizer.free(randonizer);

    return 0;
}
