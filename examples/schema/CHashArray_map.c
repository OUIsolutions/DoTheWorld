#include "CHashManipulator.h"
#define DTW_ALLOW_CHASH
#include "doTheWorldOne.c"

typedef struct {
    int age;
}Filtrage;

CHashObject * return_user(DtwResource *user, void *filtragem){
    return newCHashObject(
        "name",newString(DtwResource_get_string_from_sub_resource(user, "name")),
        "age", newNumber(DtwResource_get_long_from_sub_resource(user,"age"))
    );
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
        DtwResource *current = new_schema_insertion(users);

        char formatted_name[20] = {0};
        sprintf(formatted_name,"user%d", i);
        long age = DtwRandonizer_generate_num(randonizer,100);

        DtwResource_set_string_in_sub_resource(current,"name",formatted_name);
        DtwResource_set_long_in_sub_resource(current,"age",age);
    }

}
void create_schemas(DtwResource *database){
    DtwDatabaseSchema *schema = newDatabaseSchema(database);
    DtwSchema *users = DtwDatabaseSchema_sub_schema(schema,"users");
    DtwSchema_add_primary_key(users,"name");
}


int main(){
    // dtw = newDtwNamespace();  // Removed global, so this line is commented out or removed
    // hash = newCHashNamespace();  // Removed
    // randonizer = DtwRandonizer_newRandonizer();  // Removed global, replaced with direct call if possible

    DtwResource *database = newResource("database");
    create_schemas(database);

    DtwResource *users = DtwResource_sub_resource(database,"users");

    create_x_users(users,100);

    Filtrage f;
    f.age = 18;

    DtwResourceCHashrrayMapProps props = create_CHashrrayMapProps(return_user);

    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

    CHashArray *itens = DtwResource_schema_map_CHashArray(users,props);

    char *content = dump_to_json_string(itens);
    printf("%s",content);
    free(itens);
    free(content);

    DtwResource_free(database);
    // dtw.randonizer.free(randonizer);  // Removed

    return 0;
}