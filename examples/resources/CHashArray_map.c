#define DTW_CHASH_PATH  "CHashManipulator.h"
#define DTW_ALLOW_CHASH
#include "doTheWorldOne.c"

typedef struct {
    int age;
} Filtrage;

CHashObject *return_user(DtwResource *user, void *filtragem) {
    return newCHashObject(
        "name", newCHashString(DtwResource_get_string_from_sub_resource(user, "name")),
        "age", newCHashNumber(DtwResource_get_long_from_sub_resource(user, "age"))
    );
}

bool verify_if_print_user(DtwResource *user, void *filtragem) {
    Filtrage *f = (Filtrage *)filtragem;
    long age = DtwResource_get_long_from_sub_resource(user, "age");

    if (age < f->age) {
        return true;
    }
    return false;
}

void create_x_users(DtwResource *users, long quantity) {
    for (int i = 0; i < quantity; i++) {
        DtwResource *current = DtwResource_sub_resource_random(users, NULL);

        char formatted_name[20] = {0};
        sprintf(formatted_name, "user%d", i);
        long age = DtwRandonizer_generate_num(DtwRandonizer_newRandonizer(), 100);

        DtwResource_set_string_in_sub_resource(current, "name", formatted_name);
        DtwResource_set_long_in_sub_resource(current, "age", age);
    }
}

int main() {
    DtwResource *database = DtwResource_newResource("database");
    DtwResource *users = DtwResource_sub_resource(database, "users");

    create_x_users(users, 100);

    Filtrage f;
    f.age = 18;

    DtwResourceCHashrrayMapProps props = DtwResource_create_CHashrrayMapProps(return_user);
    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

    CHashArray *itens = DtwResource_map_CHashArray(users, props);

    char *content = CHash_dump_to_json_string(itens);
    printf("%s", content);
    CHash_free(itens);
    free(content);

    DtwResource_free(database);
    return 0;
}