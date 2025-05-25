#include "doTheWorldOne.c"

typedef struct {
    int age;
} Filtrage;

void print_user(DtwResource *user, void *filtragem) {
    printf("age %ld\n", DtwResource_get_long_from_sub_resource(user, "age"));
    printf("name: %s\n", DtwResource_get_string_from_sub_resource(user, "name"));
}

bool verify_if_print_user(DtwResource *user, void *filtragem) {
    Filtrage *f = (Filtrage *)filtragem;
    long idade = DtwResource_get_long_from_sub_resource(user, "age");
    if (idade < f->age) {
        return true;
    }
    return false;
}

void create_x_users(DtwResource *users, long quantity, DtwRandonizer *randonizer) {
    for (int i = 0; i < quantity; i++) {
        DtwResource *current = DtwResource_sub_resource_random(users, NULL);
        char formatted_name[20] = {0};
        sprintf(formatted_name, "user%d", i);
        long age = DtwRandonizer_generate_num(randonizer, 100);
        DtwResource_set_string_in_sub_resource(current, "name", formatted_name);
        DtwResource_set_long_in_sub_resource(current, "age", age);
    }
}

int main() {
    DtwRandonizer *randonizer = newDtwRandonizer();
    DtwResource *users = new_DtwResource("users");
    create_x_users(users, 100, randonizer);
    DtwResourceForeachProps props = DtwResource_create_foreach_props(print_user);
    props.filtrage_callback = verify_if_print_user;
    Filtrage f;
    f.age = 18;
    props.args = &f;
    DtwResource_foreach(users, props);
    DtwResource_free(users);
    DtwRandonizer_free(randonizer);
    return 0;
}