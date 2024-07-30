
#include "src/one.c"


DtwNamespace dtw;
DtwRandonizer *randonizer;
typedef struct {
    int age;
}Filtrage;


void print_user(DtwResource *user, void *filtragem){
    printf("age %ld\n",dtw.resource.get_long_from_sub_resource(user,"age"));
    printf("name: %s\n", dtw.resource.get_string_from_sub_resource(user, "name"));
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
        DtwResource *current = dtw.resource.new_schema_insertion(users);

        char formatted_name[20] = {0};
        sprintf(formatted_name,"user%d", i);
        long age = dtw.randonizer.generate_num(randonizer,100);

        dtw.resource.set_string_in_sub_resource(current,"name",formatted_name);
        dtw.resource.set_long_in_sub_resource(current,"age",age);
    }

}
void create_schemas(DtwResource *database){
    DtwDatabaseSchema *schema = dtw.resource.newDatabaseSchema(database);
    DtwSchema *users = dtw.database_schema.sub_schema(schema,"users");
    dtw.schema.add_primary_key(users,"name");
}


int main(){
    dtw = newDtwNamespace();
    randonizer = dtw.randonizer.newRandonizer();

    DtwResource *database = dtw.resource.newResource("database");
    create_schemas(database);

    DtwResource *users = dtw.resource.sub_resource(database,"users");

    create_x_users(users,100);
    Filtrage f;
    f.age = 18;

    DtwResourceForeachProps props = dtw.resource.create_foreach_props(print_user);
    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

    dtw.resource.schema_each(users,props);
    dtw.resource.free(database);
    dtw.randonizer.free(randonizer);
    return 0;
}
