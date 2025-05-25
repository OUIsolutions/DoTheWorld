#include "doTheWorldOne.c"

DtwRandonizer *randonizer;
typedef struct {
    int age;
}Filtrage;

cJSON * return_user(DtwResource *user, void *filtragem){
    cJSON *created_object =cJSON_CreateObject();
    cJSON_AddStringToObject(
        created_object,
        "name", DtwResource_get_string_from_sub_resource(user, "name")
    );

    cJSON_AddNumberToObject(
        created_object,
        "age",
        DtwResource_get_long_from_sub_resource(user,"age")
    );
    return created_object;
}

bool verify_if_print_user(DtwResource *user, void *filtragem){
     Filtrage *f = (Filtrage *)filtragem;
    long age = DtwResource_get_long_from_sub_resource(user, "age");

    if(age < f->age){

        return true;
    }

    return false;
}
void create_x_users(DtwResource *users,long quantity){
    for(int i =0; i < quantity; i++){
        DtwResource *current = DtwResource_sub_resource_random(users,NULL);

        char formatted_name[20] = {0};
        sprintf(formatted_name,"user%d", i);
        long age = DtwRandonizer_generate_num(randonizer,100);

        DtwResource_set_string_in_sub_resource(current,"name",formatted_name);
        DtwResource_set_long_in_sub_resource(current,"age",age);
    }

}


int main(){
    randonizer = DtwRandonizer_newRandonizer();

    DtwResource *database = DtwResource_newResource("database");
    DtwResource *users = DtwResource_sub_resource(database,"users");

    create_x_users(users,100);

    Filtrage f;
    f.age = 18;

    DtwResourcecJSONArrayMapProps props = DtwResource_create_cJSONArrayMapProps(return_user);
    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

    cJSON *itens = DtwResource_map_cJSONArray(users,props);


    char *content = cJSON_Print(itens);
    printf("%s",content);
    cJSON_Delete(itens);
    free(content);

    DtwResource_free(database);
    DtwRandonizer_free(randonizer);

    return 0;
}