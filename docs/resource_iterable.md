## Iterable Resources

with iterable functional system, you can iterate into Resources easly



#### Each
with each, you can pass also a filtrage callback, a start point (defaults its 0),
and the total elements (defaults its all)
```c
#include "doTheWorldOne.c"

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
    DtwResourceForeachProps props = dtw.resource.create_foreach_props(print_user);
    props.filtrage_callback = verify_if_print_user;

    Filtrage f;
    f.age = 18;
    props.args = &f;

    dtw.resource.each(users,props);
    dtw.resource.free(users);
    dtw.randonizer.free(randonizer);
    return 0;
}

```

#### Schema Each
you also can iterate over schemas with schema each

```c
#include "doTheWorldOne.c"


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
    int start  = 0;

    DtwResourceForeachProps props = dtw.resource.create_foreach_props(print_user);
    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

    dtw.resource.schema_each(users,props);
    dtw.resource.free(database);
    dtw.randonizer.free(randonizer);
    return 0;
}

```

#### Map
with map you can construct, objects lists, with what ever you want
you just need to pass the object, the retriver, and some append function
to be called each generated object

```c
#include "doTheWorldOne.c"



DtwNamespace dtw;
DtwRandonizer *randonizer;
typedef struct {
    int age;
}Filtrage;


cJSON * return_user(DtwResource *user, void *filtragem){
    cJSON *created_object =cJSON_CreateObject();
    cJSON_AddStringToObject(
        created_object,
        "name", dtw.resource.get_string_from_sub_resource(user, "name")
    );

    cJSON_AddNumberToObject(
        created_object,
        "age",
        dtw.resource.get_long_from_sub_resource(user,"age")
    );
    return created_object;
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
    randonizer = dtw.randonizer.newRandonizer();

    DtwResource *database = dtw.resource.newResource("database");

    DtwResource *users = dtw.resource.sub_resource(database,"users");

    create_x_users(users,100);
    Filtrage f;
    f.age = 18;
    cJSON *itens = cJSON_CreateArray();
    DtwResourceMapProps props = dtw.resource.create_map_props(
        itens,
        (void (*)(void*,void*))cJSON_AddItemToArray,
        (void* (*)(DtwResource *,void*))return_user
    );

    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

   dtw.resource.map(users,props);

    char *content = cJSON_Print(itens);
    printf("%s",content);
    cJSON_Delete(itens);
    free(content);

    dtw.resource.free(database);
    dtw.randonizer.free(randonizer);

    return 0;
}

```

of course, it also works with schemas

```c

#include "doTheWorldOne.c"

DtwNamespace dtw;
DtwRandonizer *randonizer;
typedef struct {
    int age;
}Filtrage;


cJSON * return_user(DtwResource *user, void *filtragem){
    cJSON *created_object =cJSON_CreateObject();
    cJSON_AddStringToObject(
        created_object,
        "name", dtw.resource.get_string_from_sub_resource(user, "name")
    );

    cJSON_AddNumberToObject(
        created_object,
        "age",
        dtw.resource.get_long_from_sub_resource(user,"age")
    );
    return created_object;
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
    cJSON *itens = cJSON_CreateArray();
    DtwResourceMapProps props = dtw.resource.create_map_props(
        itens,
        (void (*)(void*,void*))cJSON_AddItemToArray,
        (void* (*)(DtwResource *,void*))return_user
    );

    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

   dtw.resource.schema_map(users,props);

    char *content = cJSON_Print(itens);
    printf("%s",content);
    cJSON_Delete(itens);
    free(content);

    dtw.resource.free(database);
    dtw.randonizer.free(randonizer);

    return 0;
}

```

#### CJson Array Map
you also can directly map a cJSON Array

```c
#include "doTheWorldOne.c"


DtwNamespace dtw;
DtwRandonizer *randonizer;
typedef struct {
    int age;
}Filtrage;


cJSON * return_user(DtwResource *user, void *filtragem){
    cJSON *created_object =cJSON_CreateObject();
    cJSON_AddStringToObject(
        created_object,
        "name", dtw.resource.get_string_from_sub_resource(user, "name")
    );

    cJSON_AddNumberToObject(
        created_object,
        "age",
        dtw.resource.get_long_from_sub_resource(user,"age")
    );
    return created_object;
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
    randonizer = dtw.randonizer.newRandonizer();

    DtwResource *database = dtw.resource.newResource("database");
    DtwResource *users = dtw.resource.sub_resource(database,"users");

    create_x_users(users,100);

    Filtrage f;
    f.age = 18;

    DtwResourcecJSONArrayMapProps props = dtw.resource.create_cJSONArrayMapProps(return_user);
    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

    cJSON *itens = dtw.resource.map_cJSONArray(users,props);


    char *content = cJSON_Print(itens);
    printf("%s",content);
    cJSON_Delete(itens);
    free(content);

    dtw.resource.free(database);
    dtw.randonizer.free(randonizer);

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


DtwNamespace dtw;
DtwRandonizer *randonizer;
typedef struct {
    int age;
}Filtrage;


cJSON * return_user(DtwResource *user, void *filtragem){
    cJSON *created_object =cJSON_CreateObject();
    cJSON_AddStringToObject(
        created_object,
        "name", dtw.resource.get_string_from_sub_resource(user, "name")
    );

    cJSON_AddNumberToObject(
        created_object,
        "age",
        dtw.resource.get_long_from_sub_resource(user,"age")
    );
    return created_object;
}
char * get_key(DtwResource *user, void *filtrage){
    return  dtw.resource.get_string_from_sub_resource(user, "name");
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
    randonizer = dtw.randonizer.newRandonizer();

    DtwResource *database = dtw.resource.newResource("database");
    DtwResource *users = dtw.resource.sub_resource(database,"users");

    create_x_users(users,100);

    Filtrage f;
    f.age = 18;

    DtwResourcecJSONObjectMapProps props = dtw.resource.create_cJSONObjectProps(return_user,get_key);

    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

    cJSON *itens = dtw.resource.map_cJSONObject(users,props);


    char *content = cJSON_Print(itens);
    printf("%s",content);
    cJSON_Delete(itens);
    free(content);

    dtw.resource.free(database);
    dtw.randonizer.free(randonizer);

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

    DtwResourceCHashrrayMapProps props = dtw.resource.create_CHashrrayMapProps(return_user);

    props.filtrage_callback = verify_if_print_user;
    props.args = &f;

    CHashArray *itens = dtw.resource.map_CHashArray(users,props);

    char *content = hash.dump_to_json_string(itens);
    printf("%s",content);
    hash.free(itens);
    free(content);

    dtw.resource.free(database);
    dtw.randonizer.free(randonizer);

    return 0;
}

```
