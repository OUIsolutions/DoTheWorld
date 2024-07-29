#include "../../../doTheWorld_test.h"

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

    long idade = dtw.resource.get_long_from_sub_resource(user, "age");

    if(idade < f->age){

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

    DtwResource *users = dtw.resource.newResource("users");
    create_x_users(users,100);
    Filtrage f;
    f.age = 18;
    int start  = 0;
    dtw.resource.each(users, verify_if_print_user, print_user, &f, start, DTW_RESOURCE_ALL);
    dtw.resource.free(users);
    dtw.randonizer.free(randonizer);
    return 0;
}
