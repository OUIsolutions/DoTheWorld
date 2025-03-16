

## Resources
With Resources you can iterate over all types of values ,and modifie than into an single transaction or one by one
### Setting Values

```c

#include "doTheWorld.h"

int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwResource *values = dtw.resource.newResource("tests/target/new_folder");

    DtwResource *string_element = dtw.resource.sub_resource(values,"text.txt");
    dtw.resource.set_string(string_element,"nothing");
    long size;
    unsigned char *blob = dtw_load_binary_content("tests/target/blob.png",&size);

    DtwResource *blob_element = dtw.resource.sub_resource(values,"blob.png");
    dtw.resource.set_binary(blob_element,blob,size);

    free(blob);
    DtwResource *bInt = dtw.resource.sub_resource(values,"b.txt");
    dtw.resource.set_long(bInt,25);

    DtwResource *cDouble = dtw.resource.sub_resource(values,"c.txt");
    dtw.resource.set_double(cDouble,10.5);

    DtwResource *dBool = dtw.resource.sub_resource(values,"b.txt");
    dtw.resource.set_bool(dBool,true);

    DtwResource  *sub_foder = dtw.resource.sub_resource(values,"sub_foder");
    DtwResource *string_element2 = dtw.resource.sub_resource(sub_foder,"a.txt");
    dtw.resource.set_string(string_element2,"nothing");


    dtw.resource.commit(values);
    dtw.resource.free(values);





}

```




### Getting values of Resource
```c
#include "doTheWorld.h"

int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwResource *values = dtw.resource.newResource("tests/target");

    printf("elements:---------------------------------\n");
    DtwStringArray  *sub_elements = dtw.resource.list_names(values);
    DtwStringArray_sort(sub_elements);
    if(!dtw.resource.error(values)){
        dtw.string_array.represent(sub_elements);
        dtw.string_array.free(sub_elements);
    }

    printf("types:--------------------------------------\n");

    DtwResource *string_r = dtw.resource.sub_resource(values, "a.txt");
    char *string_r_value = dtw.resource.get_string(string_r);
    DtwResource  *blob_r = dtw.resource.sub_resource(values,"blob.png");
    long blob_size;
    unsigned  char *blob_r_value = dtw.resource.get_binary(blob_r,&blob_size);

    DtwResource *numerical = dtw.resource.sub_resource(values,"numerical");
    DtwResource  *double_r = dtw.resource.sub_resource(numerical,"double.txt");
    double double_r_value = dtw.resource.get_double(double_r);

    DtwResource  *long_r = dtw.resource.sub_resource(numerical,"integer.txt");
    long long_r_value =dtw.resource.get_long(long_r);
    DtwResource  *bool_r = dtw.resource.sub_resource(numerical,"true_normal.txt");
    bool bool_r_value = dtw.resource.get_bool(bool_r);

    if(!dtw.resource.error(values)){
        printf("value string :%s\n",string_r_value);
        printf("blob size: %ld\n",blob_r->value_size);
        printf("double value %lf\n",double_r_value);
        printf("long value %ld\n",long_r_value);
        printf("bool value %d\n",bool_r_value);
    }

    if(dtw.resource.error(values)){
        char *message = DtwResource_get_error_message(values);
        printf("%s",message);
    }



    dtw.resource.free(values);



}

```





### Schemas

Schema its a way to handle resources into a serializible way, providing foreing key and primary key concepts

### Creating a insertion
in these example we are creating a user using schema concept

```c

#include "doTheWorld.h"


int main(){
    DtwNamespace  dtw = newDtwNamespace();

    DtwResource *database = dtw.resource.newResource("tests/target/schema_database");

    DtwDatabaseSchema *root_schema  = dtw.resource.newDatabaseSchema(database);
    DtwSchema *users_schema = dtw.database_schema.sub_schema(root_schema,"users");
    dtw.schema.add_primary_key(users_schema,"name");
    dtw.schema.add_primary_key(users_schema,"email");

    DtwResource  *users =dtw.resource.sub_resource(database,"users");

    DtwResource *user = dtw.resource.new_schema_insertion(users);
    dtw.resource.set_string_in_sub_resource(user,"name","mateus");
    dtw.resource.set_string_in_sub_resource(user,"email","mateusmoutinho01@gmail.com");
    dtw.resource.set_string_sha_in_sub_resource(user,"password","12345");
    dtw.resource.set_long_in_sub_resource(user,"age",27);

    if(dtw.resource.error(database)){
        printf("error:%s",dtw.resource.get_error_message(database));
    }

    dtw.resource.commit(database);
    dtw.resource.free(database);
}

```



### Removing a insertion
In these example we also can destroy the user , automaticly destroying the index

```c

#include "doTheWorld.h"
DtwNamespace dtw;




void create_users(DtwResource *database,const char *name,const char *email,const char *password, int age){

    DtwResource  *users =dtw.resource.sub_resource(database,"users");
    DtwResource *user = dtw.resource.new_schema_insertion(users);
    dtw.resource.set_string_in_sub_resource(user,"name",name);
    dtw.resource.set_string_in_sub_resource(user,"email",email);
    dtw.resource.set_string_sha_in_sub_resource(user,"password",password);
    dtw.resource.set_long_in_sub_resource(user,"age",age);
}

int main(){

    dtw = newDtwNamespace();
    DtwResource *database = dtw.resource.newResource("tests/target/schema_database");
    DtwDatabaseSchema *root_schema  = dtw.resource.newDatabaseSchema(database);
    DtwSchema *users_schema = dtw.database_schema.sub_schema(root_schema,"users");
    dtw.schema.add_primary_key(users_schema,"name");
    dtw.schema.add_primary_key(users_schema,"email");


    create_users(database,"mateus","mateusmoutinho01@gmail.com","1234",27);
    create_users(database,"user1","user1@gmail.com","1234",27);
    create_users(database,"user2","user2@gmail.com","1234",27);

    DtwResource  *users =dtw.resource.sub_resource(database,"users");
    DtwResource * mateus = dtw.resource.find_by_primary_key_with_string(users,"name","mateus");
    dtw.resource.destroy(mateus);

    if(dtw.resource.error(database)){
        printf("error:%s\n",dtw.resource.get_error_message(database));
        dtw.resource.free(database);
        return 0;
    }

    dtw.resource.commit(database);
    dtw.resource.free(database);


}

```


### Finding a insertion
With  primary keys you can find values without loop iteration increasing readability and speed,

```c

#include "doTheWorld.h"
DtwNamespace dtw;




void create_users(DtwResource *database,const char *name,const char *email,const char *password, int age){
    DtwResource  *users =dtw.resource.sub_resource(database,"users");
    DtwResource *user = dtw.resource.new_schema_insertion(users);
    dtw.resource.set_string_in_sub_resource(user,"name",name);
    dtw.resource.set_string_in_sub_resource(user,"email",email);
    dtw.resource.set_string_sha_in_sub_resource(user,"password",password);
    dtw.resource.set_long_in_sub_resource(user,"age",age);
}

int main(){

    dtw = newDtwNamespace();
    DtwResource *database = dtw.resource.newResource("tests/target/schema_database");
    DtwDatabaseSchema *root_schema  = dtw.resource.newDatabaseSchema(database);
    DtwSchema *users_schema = dtw.database_schema.sub_schema(root_schema,"users");
    dtw.schema.add_primary_key(users_schema,"name");
    dtw.schema.add_primary_key(users_schema,"email");

    create_users(database,"mateus","mateusmoutinho01@gmail.com","1234",27);
    create_users(database,"user1","user1@gmail.com","1234",27);
    create_users(database,"user2","user2@gmail.com","1234",27);
    DtwResource  *users =dtw.resource.sub_resource(database,"users");
    DtwResource * mateus = dtw.resource.find_by_primary_key_with_string(users,"name","mateus");
    char *name = dtw.resource.get_string_from_sub_resource(mateus,"name");
    char *email  = dtw.resource.get_string_from_sub_resource(mateus,"email");
    long age = dtw.resource.get_long_from_sub_resource(mateus,"age");



    if(!dtw.resource.error(database)){
        printf("name: %s\n",name);
        printf("email: %s\n",email);
        printf("age: %ld\n",age);
    }


    if(dtw.resource.error(database)){
        printf("error:%s\n",dtw.resource.get_error_message(database));
        dtw.resource.free(database);
        return 0;
    }

    dtw.resource.commit(database);
    dtw.resource.free(database);


}

```

### Iterating over insertions
you also can iterate over insertions

```c

#include "doTheWorld.h"
DtwNamespace dtw;




void create_users(DtwResource *database,const char *name,const char *email,const char *password, int age){
    DtwResource  *users =dtw.resource.sub_resource(database,"users");
    DtwResource *user = dtw.resource.new_schema_insertion(users);
    dtw.resource.set_string_in_sub_resource(user,"name",name);
    dtw.resource.set_string_in_sub_resource(user,"email",email);
    dtw.resource.set_string_sha_in_sub_resource(user,"password",password);
    dtw.resource.set_long_in_sub_resource(user,"age",age);
}

int main(){

    dtw = newDtwNamespace();
    DtwResource *database = dtw.resource.newResource("tests/target/schema_database");
    DtwDatabaseSchema *root_schema  = dtw.resource.newDatabaseSchema(database);
    DtwSchema *users_schema = dtw.database_schema.sub_schema(root_schema,"users");
    dtw.schema.add_primary_key(users_schema,"name");
    dtw.schema.add_primary_key(users_schema,"email");

    create_users(database,"mateus","mateusmoutinho01@gmail.com","1234",27);
    create_users(database,"user1","user1@gmail.com","1234",27);
    create_users(database,"user2","user2@gmail.com","1234",27);

    DtwResource  *users =dtw.resource.sub_resource(database,"users");
    DtwResourceArray *all_users = dtw.resource.get_schema_values(users);
    for(int i = 0; i < all_users->size;i++){

        DtwResource * current = all_users->resources[i];
        char *name = dtw.resource.get_string_from_sub_resource(current,"name");
        char *email  = dtw.resource.get_string_from_sub_resource(current,"email");
        long age = dtw.resource.get_long_from_sub_resource(current,"age");

        if(!dtw.resource.error(database)){
            printf("name: %s\n",name);
            printf("email: %s\n",email);
            printf("age: %ld\n",age);
        }

    }


    if(dtw.resource.error(database)){
        printf("error:%s\n",dtw.resource.get_error_message(database));
        dtw.resource.free(database);
        return 0;
    }

    dtw.resource.commit(database);
    dtw.resource.free(database);


}

```

### Iterable Resources

with iterable functional system , you can iterate into Resources easly



#### Each
with each, you can pass  also a filtrage callback, a start point (defaults its 0),
and the total elements (defaults its all)
```c
#include "doTheWorld.h"

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
#include "doTheWorld.h"


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
#include "doTheWorld.h"



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

#include "doTheWorld.h"

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
#include "doTheWorld.h"


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
#include "doTheWorld.h"


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

#include "../../../../dependencies/CHashManipulator.h"
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
