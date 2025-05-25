#define DTW_CHASH_PATH  "CHashManipulator.h"
#define DTW_ALLOW_CHASH
#include "doTheWorldOne.c"

typedef struct {
    int age;
} Filtrage;

CHashObject * return_user(DtwResource *user, void *filtragem){
    return newCHashObject(
        "name", newCHashString(DtwResource_get_string_from_sub_resource(user, "name")),
        "age", newCHashNumber(DtwResource_get_long_from_sub_resource(user, "age"))
    );
}

char * get_key(DtwResource *user, void *filtrage){
    return strdup(DtwResource_get_string_from_sub_resource(user, "name"));
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
        long age = DtwRandonizer_generate_num(newDtwRandonizer(),100);

        DtwResource_set_string_in_sub_resource(current,"name",formatted_name);
        DtwResource_set_long_in_sub_resource(current,"age",age);
    }

}



int main(){
    DtwRandonizer *randonizer = newDtwRandonizer();
    DtwResource *database = new_DtwResource("database");
    DtwResource *users = DtwResource_sub_resource(database,"users");

    create_x_users(users,100);

    Filtrage f;
    f.age = 18;

    DtwResourceCHashObjectMapProps props = DtwResource_createCHashObjectMapProps(
        return_user,get_key
    );
    props.free_key = true;
    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

    CHashArray *itens = DtwResource_map_CHashObject(users,props);

    char *content = newCHashStringDumpToJson(itens);
    printf("%s",content);
    newCHashFree(itens);
    free(content);

    DtwResource_free(database);
    DtwRandonizer_free(randonizer);

    return 0;
}