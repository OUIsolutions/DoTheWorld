
#include "CHashManipulator.h"
#define DTW_ALLOW_CHASH
#include "doTheWorld.h"


CHashNamespace hash;
DtwNamespace dtw;
DtwRandonizer *randonizer;
typedef struct {
    int age;
}Filtrage;


CHashObject * return_user(DtwResource *user, void *filtragem){
    return newCHashObject(
        "name",hash.newString(dtw.resource.get_string_from_sub_resource(user, "name")),
        "age", hash.newNumber(dtw.resource.get_long_from_sub_resource(user,"age"))
    );
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
    hash = newCHashNamespace();
    randonizer = dtw.randonizer.newRandonizer();

    DtwResource *database = dtw.resource.newResource("database");
    DtwResource *users = dtw.resource.sub_resource(database,"users");

    create_x_users(users,100);

    Filtrage f;
    f.age = 18;

    DtwResourceCHashObjectMapProps props = dtw.resource.createCHashObjectMapProps(
        return_user,get_key
    );
    props.free_key = true;
    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

    CHashArray *itens = dtw.resource.map_CHashObject(users,props);

    char *content = hash.dump_to_json_string(itens);
    printf("%s",content);
    hash.free(itens);
    free(content);

    dtw.resource.free(database);
    dtw.randonizer.free(randonizer);

    return 0;
}
