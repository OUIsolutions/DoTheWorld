## Iterable Resources

with iterable functional system, you can iterate into Resources easly



#### Each
with each, you can pass also a filtrage callback, a start point (defaults its 0),
and the total elements (defaults its all)
```c
#include "doTheWorldOne.c"

DtwRandonizer *randonizer;
typedef struct {
    int age;
}Filtrage;


void print_user(DtwResource *user, void *filtragem){
    printf("age %ld\n",DtwResource_get_long_from_sub_resource(user,"age"));
    printf("name: %s\n", DtwResource_get_string_from_sub_resource(user, "name"));
}

bool verify_if_print_user(DtwResource *user, void *filtragem){

     Filtrage *f = (Filtrage *)filtragem;

    long idade = DtwResource_get_long_from_sub_resource(user, "age");

    if(idade < f->age){

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
    randonizer = newDtwRandonizer();

    DtwResource *users = new_DtwResource("users");
    create_x_users(users,100);
    DtwResourceForeachProps props = DtwResource_create_foreach_props(print_user);
    props.filtrage_callback = verify_if_print_user;

    Filtrage f;
    f.age = 18;
    props.args = &f;

    DtwResource_foreach(users,props);
    DtwResource_free(users);
    DtwRandonizer_free(randonizer);
    return 0;
}

```

#### Schema Each
you also can iterate over schemas with schema each

```c
#include "doTheWorldOne.c"


DtwRandonizer *randonizer;
typedef struct {
    int age;
}Filtrage;


void print_user(DtwResource *user, void *filtragem){
    printf("age %ld\n",DtwResource_get_long_from_sub_resource(user,"age"));
    printf("name: %s\n", DtwResource_get_string_from_sub_resource(user, "name"));
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
        DtwResource *current = DtwResource_new_schema_insertion(users);

        char formatted_name[20] = {0};
        sprintf(formatted_name,"user%d", i);
        long age = DtwRandonizer_generate_num(randonizer,100);

        DtwResource_set_string_in_sub_resource(current,"name",formatted_name);
        DtwResource_set_long_in_sub_resource(current,"age",age);
    }

}
void create_schemas(DtwResource *database){
    DtwDatabaseSchema *schema = DtwResource_newDatabaseSchema(database);
    DtwSchema *users = DtwDtatabaseSchema_new_subSchema(schema,"users");
    DtwSchema_add_primary_key(users,"name");
}


int main(){
    randonizer = newDtwRandonizer();

    DtwResource *database = new_DtwResource("database");
    create_schemas(database);

    DtwResource *users = DtwResource_sub_resource(database,"users");

    create_x_users(users,100);
    Filtrage f;
    f.age = 18;
    int start  = 0;

    DtwResourceForeachProps props = DtwResource_create_foreach_props(print_user);
    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

    DtwResource_schema_foreach(users,props);
    DtwResource_free(database);
    DtwRandonizer_free(randonizer);
    return 0;
}

```

#### Map
with map you can construct, objects lists, with what ever you want
you just need to pass the object, the retriver, and some append function
to be called each generated object

```c
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
    randonizer = newDtwRandonizer();

    DtwResource *database = new_DtwResource("database");

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

   DtwResource_map(users,props);

    char *content = cJSON_Print(itens);
    printf("%s",content);
    cJSON_Delete(itens);
    free(content);

    DtwResource_free(database);
    DtwRandonizer_free(randonizer);

    return 0;
}

```

of course, it also works with schemas

```c

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
        DtwResource *current = DtwResource_new_schema_insertion(users);

        char formatted_name[20] = {0};
        sprintf(formatted_name,"user%d", i);
        long age = DtwRandonizer_generate_num(randonizer,100);

        DtwResource_set_string_in_sub_resource(current,"name",formatted_name);
        DtwResource_set_long_in_sub_resource(current,"age",age);
    }

}
void create_schemas(DtwResource *database){
    DtwDatabaseSchema *schema = DtwResource_newDatabaseSchema(database);
    DtwSchema *users = DtwDtatabaseSchema_new_subSchema(schema,"users");
    DtwSchema_add_primary_key(users,"name");
}




int main(){
    randonizer = newDtwRandonizer();

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

```

#### CJson Array Map
you also can directly map a cJSON Array

```c
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
    randonizer = newDtwRandonizer();

    DtwResource *database = new_DtwResource("database");
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

```

### CJSON Object Map
you also can generate a cJSON object, but you need to
provide a "keey_provider" function ,to determine the key of each
object generation (note that these key can bee released(free) after, you pass the),
free_key prop into the props object

```c
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
    randonizer = newDtwRandonizer();

    DtwResource *database = new_DtwResource("database");
    DtwResource *users = DtwResource_sub_resource(database,"users");

    create_x_users(users,100);

    Filtrage f;
    f.age = 18;

    DtwResourcecJSONObjectMapProps props = DtwResource_create_cJSONObjectProps(return_user,get_key);

    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

    cJSON *itens = DtwResource_map_cJSONObject(users,props);


    char *content = cJSON_Print(itens);
    printf("%s",content);
    cJSON_Delete(itens);
    free(content);

    DtwResource_free(database);
    DtwRandonizer_free(randonizer);

    return 0;
}

```

### CCHash
you can use [CHash](https://github.com/OUIsolutions/CHashManipulator) objects too
but in these case , you need to use define  DTW_ALLOW_CHASH , and include the lib
into the project since CHashManipulator, its not included into the amalgamation
```c

#define DTW_CHASH_PATH  "CHashManipulator.h"
#define DTW_ALLOW_CHASH
#include "doTheWorldOne.c"


CHashNamespace hash;
DtwRandonizer *randonizer;
typedef struct {
    int age;
}Filtrage;


CHashObject * return_user(DtwResource *user, void *filtragem){
    return newCHashObject(
        "name",hash.newString(DtwResource_get_string_from_sub_resource(user, "name")),
        "age", hash.newNumber(DtwResource_get_long_from_sub_resource(user,"age"))
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
        DtwResource *current = DtwResource_sub_resource_random(users,NULL);

        char formatted_name[20] = {0};
        sprintf(formatted_name,"user%d", i);
        long age = DtwRandonizer_generate_num(randonizer,100);

        DtwResource_set_string_in_sub_resource(current,"name",formatted_name);
        DtwResource_set_long_in_sub_resource(current,"age",age);
    }

}





int main(){
    hash = newCHashNamespace();
    randonizer = newDtwRandonizer();

    DtwResource *database = new_DtwResource("database");
    DtwResource *users = DtwResource_sub_resource(database,"users");

    create_x_users(users,100);

    Filtrage f;
    f.age = 18;

    DtwResourceCHashrrayMapProps props = DtwResource_create_CHashrrayMapProps(return_user);

    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

    CHashArray *itens = DtwResource_map_CHashArray(users,props);

    char *content = hash.dump_to_json_string(itens);
    printf("%s",content);
    hash.free(itens);
    free(content);

    DtwResource_free(database);
    DtwRandonizer_free(randonizer);

    return 0;
}

```
