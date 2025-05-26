## Schemas

Schema its a way to handle resources into a serializible way, providing foreing key and primary key concepts

### Creating a insertion
in these example we are creating a user using schema concept

```c
#include "doTheWorldOne.c"


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
#include "doTheWorldOne.c"
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
With primary keys you can find values without loop iteration increasing readability and speed,

```c
#include "doTheWorldOne.c"
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
#include "doTheWorldOne.c"
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
