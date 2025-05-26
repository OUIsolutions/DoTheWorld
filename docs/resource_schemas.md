## Schemas

Schema its a way to handle resources into a serializible way, providing foreing key and primary key concepts

### Creating a insertion
in these example we are creating a user using schema concept

```c
#include "doTheWorldOne.c"


int main(){
    DtwResource *database = new_DtwResource("tests/target/schema_database");

    DtwDatabaseSchema *root_schema  = DtwResource_newDatabaseSchema(database);
    DtwSchema *users_schema = DtwDtatabaseSchema_new_subSchema(root_schema,"users");
    DtwSchema_add_primary_key(users_schema,"name");
    DtwSchema_add_primary_key(users_schema,"email");

    DtwResource  *users = DtwResource_sub_resource(database,"users");

    DtwResource *user = DtwResource_new_schema_insertion(users);
    DtwResource_set_string_in_sub_resource(user,"name","mateus");
    DtwResource_set_string_in_sub_resource(user,"email","mateusmoutinho01@gmail.com");
    DtwResource_set_string_sha_in_sub_resource(user,"password","12345");
    DtwResource_set_long_in_sub_resource(user,"age",27);

    if(DtwResource_error(database)){
        printf("error:%s",DtwResource_get_error_message(database));
    }

    DtwResource_commit(database);
    DtwResource_free(database);
}
```


### Removing a insertion
In these example we also can destroy the user , automaticly destroying the index

```c
#include "doTheWorldOne.c"


void create_users(DtwResource *database,const char *name,const char *email,const char *password, int age){

    DtwResource  *users = DtwResource_sub_resource(database,"users");
    DtwResource *user = DtwResource_new_schema_insertion(users);
    DtwResource_set_string_in_sub_resource(user,"name",name);
    DtwResource_set_string_in_sub_resource(user,"email",email);
    DtwResource_set_string_sha_in_sub_resource(user,"password",password);
    DtwResource_set_long_in_sub_resource(user,"age",age);
}

int main(){

    DtwResource *database = new_DtwResource("tests/target/schema_database");
    DtwDatabaseSchema *root_schema  = DtwResource_newDatabaseSchema(database);
    DtwSchema *users_schema = DtwDtatabaseSchema_new_subSchema(root_schema,"users");
    DtwSchema_add_primary_key(users_schema,"name");
    DtwSchema_add_primary_key(users_schema,"email");


    create_users(database,"mateus","mateusmoutinho01@gmail.com","1234",27);
    create_users(database,"user1","user1@gmail.com","1234",27);
    create_users(database,"user2","user2@gmail.com","1234",27);

    DtwResource  *users = DtwResource_sub_resource(database,"users");
    DtwResource * mateus = DtwResource_find_by_primary_key_with_string(users,"name","mateus");
    DtwResource_destroy(mateus);

    if(DtwResource_error(database)){
        printf("error:%s\n",DtwResource_get_error_message(database));
        DtwResource_free(database);
        return 0;
    }

    DtwResource_commit(database);
    DtwResource_free(database);
}
```


### Finding a insertion
With primary keys you can find values without loop iteration increasing readability and speed,

```c
#include "doTheWorldOne.c"



void create_users(DtwResource *database,const char *name,const char *email,const char *password, int age){
    DtwResource  *users = DtwResource_sub_resource(database,"users");
    DtwResource *user = DtwResource_new_schema_insertion(users);
    DtwResource_set_string_in_sub_resource(user,"name",name);
    DtwResource_set_string_in_sub_resource(user,"email",email);
    DtwResource_set_string_sha_in_sub_resource(user,"password",password);
    DtwResource_set_long_in_sub_resource(user,"age",age);
}

int main(){

    DtwResource *database = new_DtwResource("tests/target/schema_database");
    DtwDatabaseSchema *root_schema  = DtwResource_newDatabaseSchema(database);
    DtwSchema *users_schema = DtwDtatabaseSchema_new_subSchema(root_schema,"users");
    DtwSchema_add_primary_key(users_schema,"name");
    DtwSchema_add_primary_key(users_schema,"email");

    create_users(database,"mateus","mateusmoutinho01@gmail.com","1234",27);
    create_users(database,"user1","user1@gmail.com","1234",27);
    create_users(database,"user2","user2@gmail.com","1234",27);
    DtwResource  *users = DtwResource_sub_resource(database,"users");
    DtwResource * mateus = DtwResource_find_by_primary_key_with_string(users,"name","mateus");
    char *name = DtwResource_get_string_from_sub_resource(mateus,"name");
    char *email  = DtwResource_get_string_from_sub_resource(mateus,"email");
    long age = DtwResource_get_long_from_sub_resource(mateus,"age");



    if(!DtwResource_error(database)){
        printf("name: %s\n",name);
        printf("email: %s\n",email);
        printf("age: %ld\n",age);
    }


    if(DtwResource_error(database)){
        printf("error:%s\n",DtwResource_get_error_message(database));
        DtwResource_free(database);
        return 0;
    }

    DtwResource_commit(database);
    DtwResource_free(database);
}
```

### Iterating over insertions
you also can iterate over insertions

```c
#include "doTheWorldOne.c"



void create_users(DtwResource *database,const char *name,const char *email,const char *password, int age){
    DtwResource  *users = DtwResource_sub_resource(database,"users");
    DtwResource *user = DtwResource_new_schema_insertion(users);
    DtwResource_set_string_in_sub_resource(user,"name",name);
    DtwResource_set_string_in_sub_resource(user,"email",email);
    DtwResource_set_string_sha_in_sub_resource(user,"password",password);
    DtwResource_set_long_in_sub_resource(user,"age",age);
}

int main(){

    DtwResource *database = new_DtwResource("tests/target/schema_database");
    DtwDatabaseSchema *root_schema  = DtwResource_newDatabaseSchema(database);
    DtwSchema *users_schema = DtwDtatabaseSchema_new_subSchema(root_schema,"users");
    DtwSchema_add_primary_key(users_schema,"name");
    DtwSchema_add_primary_key(users_schema,"email");

    create_users(database,"mateus","mateusmoutinho01@gmail.com","1234",27);
    create_users(database,"user1","user1@gmail.com","1234",27);
    create_users(database,"user2","user2@gmail.com","1234",27);

    DtwResource  *users = DtwResource_sub_resource(database,"users");
    DtwResourceArray *all_users = DtwResource_get_schema_values(users);
    for(int i = 0; i < all_users->size;i++){

        DtwResource * current = all_users->resources[i];
        char *name = DtwResource_get_string_from_sub_resource(current,"name");
        char *email  = DtwResource_get_string_from_sub_resource(current,"email");
        long age = DtwResource_get_long_from_sub_resource(current,"age");

        if(!DtwResource_error(database)){
            printf("name: %s\n",name);
            printf("email: %s\n",email);
            printf("age: %ld\n",age);
        }

    }


    if(DtwResource_error(database)){
        printf("error:%s\n",DtwResource_get_error_message(database));
        DtwResource_free(database);
        return 0;
    }

    DtwResource_commit(database);
    DtwResource_free(database);
}
```
