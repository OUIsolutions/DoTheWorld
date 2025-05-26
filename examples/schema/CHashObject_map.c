#include "CHashManipulator.h"
#define DTW_ALLOW_CHASH
#include "doTheWorldOne.c"

typedef struct {
    int age;
}Filtrage;

CHashObject * return_user(DtwResource *user, void *filtragem){
    return newCHashObject(
        "name",newCHashString(DtwResource_get_string_from_sub_resource(user, "name")),
        "age", newCHashNumber(DtwResource_get_long_from_sub_resource(user,"age"))
    );
}
char * get_key(DtwResource *user, void *filtrage){
    return  DtwResource_get_string_from_sub_resource(user, "name");
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
    DtwResource *database = new_DtwResource("database");
    create_schemas(database);

    DtwResource *users = DtwResource_sub_resource(database,"users");

    create_x_users(users,100);

    Filtrage f;
    f.age = 18;

    DtwResourceCHashObjectMapProps props = DtwResource_createCHashObjectMapProps(
        return_user,get_key
    );

    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

    CHashArray *itens = DtwResource_schema_map_CHashObject(users,props);

    char *content = CHash_dump_to_json_string(itens);
    printf("%s",content);
    CHash_free(itens);
    free(content);

    DtwResource_free(database);

    return 0;
}