#include "doTheWorldOne.c"


typedef struct {
    int age;
} Filtrage;


cJSON * return_user(DtwResource *user, void *filtragem){
    cJSON *created_object = cJSON_CreateObject();
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
    DtwRandonizer *randonizer = newDtwRandonizer();
    for(int i =0; i < quantity; i++){
        DtwResource *current = DtwResource_new_schema_insertion(users);

        char formatted_name[20] = {0};
        sprintf(formatted_name,"user%d", i);
        long age = DtwRandonizer_generate_num(randonizer,100);

        DtwResource_set_string_in_sub_resource(current,"name",formatted_name);
        DtwResource_set_long_in_sub_resource(current,"age",age);
    }
    DtwRandonizer_free(randonizer);

}
void create_schemas(DtwResource *database){
    DtwDatabaseSchema *schema = DtwResource_newDatabaseSchema(database);
    DtwSchema *users = DtwDtatabaseSchema_new_subSchema(schema,"users");
    DtwSchema_add_primary_key(users,"name");
}



int main(){
    DtwRandonizer *randonizer = newDtwRandonizer();

    DtwResource *database = new_DtwResource("database");
    create_schemas(database);
    DtwResource *users = DtwResource_sub_resource(database,"users");

    create_x_users(users,100);

    Filtrage f;
    f.age = 18;
    cJSON *itens = cJSON_CreateArray();
    DtwResourceMapProps props = DtwResource_create_map_props(
        itens,
        (void (*)(void*,void*))cJSON_AddItemToArray,
        (void* (*)(DtwResource *,void*))return_user
    );

    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

   DtwResource_schema_map(users,props);

    char *content = cJSON_Print(itens);
    printf("%s",content);
    cJSON_Delete(itens);
    free(content);

    DtwResource_free(database);
    DtwRandonizer_free(randonizer);

    return 0;
}