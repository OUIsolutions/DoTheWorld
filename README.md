# DoTheWorld
DoTheWorld is a Windows/Linux single file library designed to handle files in C/C++ in a number of ways, providing everything from simple functions for reading/writing files and folders, to complex functions like taking sha256 from files, checking modification dates. And functionalities of atomic writing of folders/files through transaction systems.



## Learning
In These Current Markdown you will see some basic exemples of usage of these library 
but if you want to get an deep knolege see at **exemples** folder, you will find an lot of exemplos of how you can use DoTheWorld

# Installation
The installation of DoTheWorld is made to be as dumb as possible, just  download the file  **doTheWorld.h** :

[Download link](https://github.com/OUIsolutions/DoTheWorld/releases/download/v5.0/doTheWorld.h)

 And include in your project.
if this compiles then the library will work:
~~~c
#include "doTheWorld.h"

int main(int argc, char *argv[]){
    
    
    return 0;
}
~~~

## Full Folder
Alternatively you can download the entire **src** folder and include the **src/one.c** file

~~~c

#include "src/one.c"

int main(int argc, char *argv[]){

    return 0;
}

~~~
## Pre Compiled version
You also can download the pre compiled versions
[Pre Compiled Linux](https://github.com/OUIsolutions/DoTheWorld/releases/download/v5.0/pre_compiled_linux.zip) or
[Pre Compiled Windows](https://github.com/OUIsolutions/DoTheWorld/releases/download/v5.0/pre_compiled_windows.zip) to
optimize compilation time, extract the zip , than you can run with:
~~~c 
#include "doTheWorldDeclaration.h"

int main(){
  return 0;
}
~~~
compile with: 

~~~shel 
gcc main.c cJSON.o doTheWorld.o sha256.o
~~~


# Bulding the Project
if you want to exec all tests, or generate your own amalgamation, 
just run the **./build.out** or **build.exe** located into the root dir of the repo 

~~~shel
./build.out
~~~
# IO Operations

## Reading strings
if you are sure that the content you are going to read is not binary you can call the function **dtw_load_string_file_content**

~~~c

#include "doTheWorld.h"

int main(int argc, char *argv[]){
  //load a string file content
    DtwNamespace dtw = newDtwNamespace();

    const char *path = "tests/target/a.txt";
  char *content = dtw.load_string_file_content(path);
  if(content == NULL){
    printf("error oppening %s\n",path);
    return 1;
  }
  printf("content: %s\n",content);
  free(content);
  return 0;
  
}
~~~

### Reading Any Content


~~~c
#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    const char *path = "tests/target/blob.png";
  long size;
  bool is_binary;
  //load any file, is useful if you don't know if the file is binary or not
  unsigned char *content = dtw.load_any_content(path,&size,&is_binary);
  if(content == NULL){
    printf("error oppening %s\n",path);
    return 1;
  }
  printf("size: %ld\n",size);
  printf("is_binary: %s\n",is_binary ? "true" : "false");

  dtw.write_any_content("tests/target/blob2.png",content,size);
  free(content);
  return 0;
}
~~~

### Reading Double bools and Integers
you also can direclty load all types from an file  with numerical ios 


~~~c

#include "doTheWorld.h"




int main (){

    DtwNamespace dtw = newDtwNamespace();

    double double_txt = dtw.load_double_file_content("tests/target/numerical/double.txt");
    printf("double.txt:%lf\n",double_txt);

    double double_that_not_exist = dtw.load_double_file_content("nothing.txt");
    printf("double that not exist:%lf\n",double_that_not_exist);


    long integer_txt = dtw.load_long_file_content("tests/target/numerical/integer.txt");
    printf("integer.txt:%ld\n",integer_txt);

    
    long integer_that_not_exist = dtw.load_long_file_content("nothing.txt");
    printf("integer that not exist:%ld\n",integer_that_not_exist);

    //false_small.txt = "f"
    bool false_small = dtw.load_bool_file_content("tests/target/numerical/false_small.txt");
    printf("false_small.txt:%d\n",false_small);

    //false_normal.txt = "false"
    bool false_normal = dtw.load_bool_file_content("tests/target/numerical/false_normal.txt");
    printf("false_normal.txt:%d\n",false_normal);

    //true_small.txt = "t"
    bool true_small = dtw.load_bool_file_content("tests/target/numerical/true_small.txt");
    printf("true_small.txt:%d\n",true_small);
    
    //true normal.txt = "true"
    bool true_normal = dtw.load_bool_file_content("tests/target/numerical/true_normal.txt");
    printf("true_normal.txt:%d\n",true_normal);

    bool bool_that_not_exist = dtw.load_bool_file_content("nothing.txt");
    printf("false that not exist:%d\n",bool_that_not_exist);

    return 0;

}
~~~

to write strings in text files is very simple, just call the function **dtw_write_string_file_content**
(Note that the target directory does not need to exist, if it does not exist it will be created automatically)


~~~c
#include "doTheWorld.h"

int main(int argc, char *argv[]){
  // Write a string to a file the path is auto created
    DtwNamespace dtw = newDtwNamespace();

    bool result = dtw.write_string_file_content("tests/target/a.txt","Hello World!");
  printf("result: %s\n",result ? "true" : "false");
  return 0;
}
~~~


### Writing Any
if you want to write anything to a file, it's also very simple, use the **dtw_write_any_content** function, but note that it will be necessary to pass the writing size



~~~c
#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    //load the beer image
  const char *blob_path = "tests/target/blob.png";
  long blob_size;
  unsigned char *content = dtw.load_binary_content(blob_path,&blob_size);
  //use these functions for binary files
  if(content == NULL){
    printf("error oppening %s\n",blob_path);
    return 1;
  }
  printf("size: %ld\n",blob_size);

  bool result = dtw.write_any_content("tests/target/blob2.png",content,blob_size);
  printf("result: %s\n",result ? "true" : "false");
free(content);
  return 0;
}
~~~

### Writing Double , bool and Integers
You also can write any type direclty to an file 


~~~c

#include "doTheWorld.h"




int main (){

    DtwNamespace dtw = newDtwNamespace();

    dtw.write_double_file_content("tests/target/numerical2/double.txt",25.4);
    dtw.write_long_file_content("tests/target/numerical2/long.txt",12);
    dtw.write_bool_file_content("tests/target/numerical2/bool.txt",true);


    return 0;

}
~~~

If you want to create dirs you can call the function **dtw_create_dir_recursively**
passing the folder you want to create,dont wory about if the previews path dont exist 
it will create till reachs the target folder


~~~c
#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    dtw.create_dir_recursively("tests/target/sub_folder/a/b/c");

  return 0;
}
~~~

### Copying Anything
With the function **dtw_copy_any** you can copy either files or folders to one position to anoter position 


~~~c


#include "doTheWorld.h"

int main(int argc, char *argv[]){
  DtwNamespace dtw = newDtwNamespace();
  dtw.copy_any("tests/target/blob.png","tests/target/blob3.png",DTW_NOT_MERGE);
  return 0;
}
~~~

### Moving Any
You can move either folders or files with **dtw_move_any** function


~~~c

#include "doTheWorld.h"

int main(int argc, char *argv[]){

    DtwNamespace dtw = newDtwNamespace();

    dtw.move_any("tests/target/sub_folder","tests/target/sub_folder2",DTW_NOT_MERGE);

    return 0;
}
~~~


With the listage functions you can extract all Strings Arrays of elements in an folder 

## Listing files


~~~c

#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

  DtwStringArray *files = dtw.list_files("tests/target", DTW_CONCAT_PATH);
  dtw.string_array.sort(files);

  for(int i = 0; i < files->size; i++){
    printf("%s\n", files->strings[i]);
  }
  dtw.string_array.free(files);
  return 0;
}
~~~

### Listing Dirs


~~~c


#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

  DtwStringArray *dirs = dtw.list_dirs("tests/target", DTW_NOT_CONCAT_PATH);
  //the represent methold will print the dirs in the console
  dtw.string_array.sort(dirs);
  dtw.string_array.represent(dirs);
  dtw.string_array.free(dirs);
  return 0;
}
~~~

### Listing All


~~~c



#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

  DtwStringArray *all = dtw.list_all("tests/target/",DTW_CONCAT_PATH);
  dtw.string_array.sort(all);
  dtw.string_array.represent(all);
  dtw.string_array.free(all);
  return 0;
}
~~~

The By Using multi dimension listage functions , you can see all itens listed in all sub folders of the "main" folder 

## Listing Files Recursively


~~~c

#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

  DtwStringArray *files = dtw.list_files_recursively("tests/target/",DTW_CONCAT_PATH);
  dtw.string_array.sort(files);
  dtw.string_array.represent(files);
  dtw.string_array.free(files);
  return 0;
}
~~~

## Listing Dirs Recursively


~~~c

#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

  DtwStringArray *files = dtw.list_dirs_recursively("tests/target/",DTW_CONCAT_PATH);
  dtw.string_array.sort(files);
  dtw.string_array.represent(files);
  dtw.string_array.free(files);
  return 0;
}
~~~

## Listing All Recursively


~~~c

#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

  DtwStringArray *files = dtw.list_all_recursively("tests/target/",DTW_CONCAT_PATH);
  dtw.string_array.sort(files);
  dtw.string_array.represent(files);
  dtw.string_array.free(files);
  return 0;
}
~~~

## Dealing with base64 
You can easly transform an binary file to an base64 string like these


~~~c

#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    const char *deer_path = "tests/target/blob.png";
   char *deerb64  = dtw.convert_binary_file_to_base64(deer_path);
   printf("blob: %s", deerb64);
    free(deerb64);
}
~~~

You also can reconvert an base64 string to binary


~~~c

#include "doTheWorld.h"

int main(int argc, char *argv[]){


    DtwNamespace dtw = newDtwNamespace();

    //creating the b64 file
    const char *blob_path = "tests/target/blob.png";
    char *blob  = dtw.convert_binary_file_to_base64(blob_path);
     long output;
    unsigned char  *result = dtw.base64_decode(blob,&output);

    dtw.write_any_content("tests/target/blob2.png",result,output);

    free(result);
    free(blob);

    return 0;
}
~~~


## Sha256
Generating Sha from file 


~~~c

#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

   char *hash = dtw.generate_sha_from_file("tests/target/blob.png");
   printf("SHA: %s", hash);
   free(hash);
}
~~~

### Unix


~~~c

#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    int last_modification_in_unix = dtw.get_entity_last_motification_in_unix("tests/target/a.txt");
    printf("Last modification: %d\n", last_modification_in_unix);
}
~~~



~~~c
#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();



    char *last_modification = dtw.get_entity_last_motification_in_string("tests/target/a.txt");
    printf("Last modification: %s", last_modification);
    free(last_modification);
}
~~~



## Locker 
With the locker you can Lock files and ensure that even with multprocessment, they will
be executed in an order


~~~c

#include "../doTheWorld_test.h"




void append_text(const char *file,char *text){
    DtwNamespace dtw = newDtwNamespace();


    DtwLocker *locker = newDtwLocker();
    while(dtw.locker.lock(locker,file));
    //printf("process %d get the ownership\n",locker->process);

    char *content = dtw.load_string_file_content(file);

    content = realloc(content,strlen(content) + strlen(text) + 2);
    strcat(content,text);

    dtw.write_string_file_content(file,content);
    free(content);


    dtw.locker.free(locker);

}

int main(int argc, char *argv[]){


    DtwNamespace dtw = newDtwNamespace();
    

    const char *file = "tests/target/append.txt";
    int total_process  = 10;
    // this will reset the file
    dtw.remove_any(file);
    dtw.write_string_file_content(file,"");

    for(int i = 0; i < total_process; i ++){

        if(fork() == 0){
            char formated_content[1000] = {0};
            sprintf(formated_content,"text of: %d process %d \n",i,getpid());
            append_text(file,formated_content);

            exit(0);
        }

    }

    // Hold the end of other process
    for (int i = 0; i < total_process; i++) {
        int status;
        wait(&status);
    }
     


}

~~~

## Resources 
With Resources you can iterate over all types of values ,and modifie than into an single transaction or one by one 
### Setting Values 


~~~c

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






~~~




### Getting values of Resource

~~~c
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






~~~


### Generating transaction
with transactions you can make all modifications and executed or denny it one time,avoid nod
wanted side effects


~~~c

#include "doTheWorld.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTransaction *t = newDtwTransaction();
    dtw.transaction.write_string(t,"b.txt","aaaaa");
    dtw.transaction.move_any(t,"a.txt","c.txt");
    dtw.transaction.delete_any(t,"blob.png");
    dtw.transaction.copy_any(t,"sub_folder","sub_folder2");
    dtw.transaction.commit(t,"tests/target");
    dtw.transaction.free(t);

}
~~~


You also can dump the transaction to an json file to store it 


~~~c

#include "doTheWorld.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTransaction *t = newDtwTransaction();
    dtw.transaction.write_string(t,"b.txt","aaaaa");
    dtw.transaction.move_any(t,"a.txt","c.txt");
    dtw.transaction.delete_any(t,"blob.png");
    dtw.transaction.copy_any(t,"sub_folder","sub_folder2");
    dtw.transaction.represent(t);
    dtw.transaction.dumps_transaction_to_json_file(t,"tests/target/transaction.json");
    dtw.transaction.free(t);
}
~~~


~~~c

#include "doTheWorld.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTransaction *t = dtw.transaction.newTransaction_from_json_file("tests/target/transaction.json");
    if(!t){
        DtwJsonTransactionError *error = dtw_validate_json_transaction_file("tests/target/transaction.json");
        dtw.transaction.json_error.represent(error);
        dtw.transaction.json_error.free(error);
        return 0;
    }
    
    dtw.transaction.represent(t);
    dtw.transaction.free(t);
}
~~~



### Schemas

Schema its a way to handle resources into a serializible way, providing foreing key and primary key concepts

### Creating a insertion
in these example we are creating a user using schema concept  


~~~c

#include "doTheWorld.h"


int main(){
    DtwNamespace  dtw = newDtwNamespace();

    DtwResource *database = dtw.resource.newResource("tests/target/schema_database");
    DtwSchema *schema  = dtw.resource.newSchema(database);
    DtwSchema *users_schema = dtw.schema.sub_schema(schema,"users");
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





~~~



### Removing a insertion
In these example we also can destroy the user , automaticly destroying the index


~~~c

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
    DtwSchema *schema  = dtw.resource.newSchema(database);
    DtwSchema *users_schema = dtw.schema.sub_schema(schema,"users");
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



~~~


### Finding a insertion
With  primary keys you can find values without loop iteration increasing readability and speed, 


~~~c

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
    DtwSchema *schema  = dtw.resource.newSchema(database);
    DtwSchema *users_schema = dtw.schema.sub_schema(schema,"users");
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



~~~


### Iterating over insertions
you also can iterate over insertions 


~~~c

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
    DtwSchema *schema  = dtw.resource.newSchema(database);
    DtwSchema *users_schema = dtw.schema.sub_schema(schema,"users");
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


~~~


### Trees and TreeParts 
with tree concepts, you can manipulate files as trees, and implement IO modifications with atomic concepts

### Loading An TreePart 


~~~c


#include "doTheWorld.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTreePart *part = dtw.tree.part.newPartLoading("tests/target/a.txt");
    part->last_modification_time = 0;
    
    dtw.tree.part.represent(part);
    dtw.tree.part.free(part);
}
~~~


### Creating an empty tree Part


~~~c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTreePart *part = dtw.tree.part.newPartEmpty("tests/target/b.txt");
    dtw.tree.part.set_string_content(part,"my mensage");
    dtw.tree.part.hardware_write(part,DTW_SET_AS_ACTION);
    dtw.tree.part.hardware_commit(part);
    dtw.tree.part.free(part);
}
~~~

### Modifying an tree part


~~~c
#include "doTheWorld.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();

     DtwTreePart *part = dtw.tree.part.newPartLoading("tests/target/a.txt");

    //getting the content
    char *content = dtw.tree.part.get_content_string_by_reference(part);
    char new_content[100] ={0};
    strcat(new_content,content);
    strcat(new_content," New Mensage");
    dtw.tree.part.set_string_content(part,new_content);

    dtw.tree.part.hardware_write(part,DTW_SET_AS_ACTION);
    dtw.tree.part.hardware_commit(part);
    dtw.tree.part.free(part);
}
~~~


### Retriing Paths Paramns


~~~c

#include "doTheWorld.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();
    DtwPath *path = dtw.path.newPath("a/b/c/d.txt");
    char *name = dtw.path.get_full_name(path);
    char *extension = dtw.path.get_extension(path);
    char *dir = dtw.path.get_dir(path);
    char *full_path = dtw.path.get_path(path);
    printf("name : %s\n",name);
    printf("extension : %s\n",extension);
    printf("dir : %s\n",dir);
    printf("full_path : %s\n",full_path);
    dtw.path.free(path);


}
~~~

### Changing path Atributes at once 



~~~c

#include "doTheWorld.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwPath * path = dtw.path.newPath("a/b/c/d.txt");
    dtw.path.set_name(path,"test");
    dtw.path.set_extension(path,"md");
    dtw.path.represent(path);
    dtw.path.free(path);


}
~~~

With the **hardware_modify** , **hardware_write**, **hardware_remove** 
Functions , you can generate modifications, without implement it, in these 
way , you can create massive atomic transactions, and execute all at once 


### hardware_modify
Will Modificate the original content, for exemple, if you change the extension of an file, it will modificate the original content 



~~~c
#include "doTheWorld.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTreePart *part = dtw.tree.part.newPartLoading("tests/target/a.txt");

    dtw.path.set_extension(part->path,"md");

    dtw.tree.part.hardware_modify(part,DTW_EXECUTE_NOW);
    dtw.tree.part.hardware_commit(part);
    dtw.tree.part.free(part);

}
~~~

Will write the file as an "new" file, ignoring the existence of the 
old file 


~~~c

#include "doTheWorld.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTreePart *part = dtw.tree.part.newPartLoading("tests/target/a.txt");
    dtw.path.set_extension(part->path,"md");
    dtw.tree.part.hardware_write(part,DTW_EXECUTE_NOW);
    dtw.tree.part.hardware_commit(part);
    dtw.tree.part.free(part);

}
~~~


Will Delete the current Content 



~~~c


#include "doTheWorld.h"



int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTreePart *part = dtw.tree.part.newPartLoading("tests/target/a.txt");

    dtw.tree.part.hardware_remove(part,DTW_EXECUTE_NOW);
    dtw.tree.part.hardware_commit(part);
    dtw.tree.part.free(part);

}
~~~

With Trees you can make massive folders and files modifications with 
easy steps 
### Loading Tree From Hardware


~~~c
#include "doTheWorld.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "tests/target/",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    dtw.tree.represent(tree);
    dtw.tree.free(tree);
}
~~~

### Iterating over An Tree


~~~c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"
int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    for(int i = 0; i<tree->size;i++){
        DtwTreePart *current_part = tree->tree_parts[i];
        dtw.tree.part.represent(current_part);
    }
    dtw.tree.free(tree);
}
~~~

### Finding An Tree by name


~~~c
//
// Created by jurandi on 20-06-2023.
//


#include "doTheWorld.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    DtwTreePart *blob = dtw.tree.find_tree_part_by_name(tree,"blob.png");
    if(blob){
        dtw.tree.part.represent(blob);
    }
    dtw.tree.free(tree);

}
~~~


### Finding An Tree by Path


~~~c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "tests/target/",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    DtwTreePart *element = dtw.tree.find_tree_part_by_path(
            tree,
            "tests/target/sub_folder/sub_element.txt"
    );
    if(element){
        dtw.tree.part.represent(element);
    }
    dtw.tree.free(tree);
}

~~~

### Finding An Tree by Function


~~~c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"

bool test_if_blob(struct DtwTreePart*part){
    DtwNamespace dtw = newDtwNamespace();

    char *name = dtw.path.get_full_name(part->path);
    if(!name){
        return false;
    }

    if(strcmp(name,"blob.png") == 0){
        return true;
    }
    return false;
};


int main(){
    DtwNamespace dtw = newDtwNamespace();

    struct DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                .content = DTW_INCLUDE,
                .hadware_data=DTW_HIDE,
                .path_atributes=DTW_INCLUDE
            }
    );


    struct DtwTreePart *blob = dtw.tree.find_tree_part_by_function(
            tree,
            test_if_blob
    );

    dtw.tree.part.represent(blob);
    
    dtw.tree.free(tree);

}
~~~

Trees suports even Maps or filters, it returns an new tree of the of the current lambda procediment 
#### Filter 
with filter you can filter the contents you want in an tree with an bool lambda


~~~c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"

bool filter_txt(struct DtwTreePart *part){
    DtwNamespace dtw = newDtwNamespace();

    char *extension = dtw.path.get_extension(part->path);
    if(!extension){
        return false;
    }
    if(strcmp(extension,"txt") == 0){
        return true;
    }
    return false;
}

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    DtwTree *filtered = dtw.tree.filter(
            tree,
            filter_txt
    );

    dtw.tree.represent(filtered);
    dtw.tree.free(filtered);
    dtw.tree.free(tree);
}
~~~

### Map 


~~~c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"

DtwTreePart * concat_test(struct DtwTreePart *part){
    DtwNamespace dtw = newDtwNamespace();

    if(part->content && part->is_binary == false){
        char *content = dtw.tree.part.get_content_string_by_reference(part);
        const char *mensage = " test";
        char *new_content = (char*)malloc(strlen(content) + strlen(mensage)+ 2);
        strcpy(new_content,content);
        strcat(new_content,mensage);
        dtw.tree.part.set_string_content(part,new_content);
        free(new_content);
    }
    return part;
}

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    DtwTree *concated = dtw.tree.map(
            tree,
            concat_test
    );

    dtw.tree.represent(concated);
    dtw.tree.free(concated);
    dtw.tree.free(tree);
}
~~~

With **hardware_commit_tree** you can commit all modifications at Once 
turning system ultra securty



~~~c
//
// Created by jurandi on 20-06-2023.
//

#include "doTheWorld.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                .content = DTW_INCLUDE,
                .hadware_data=DTW_HIDE,
                .path_atributes=DTW_INCLUDE
            }
    );

    for(int i=0; i < tree->size;i++){
        struct DtwTreePart *part = tree->tree_parts[i];

        char *extension = dtw.path.get_extension( part->path);
        if(!extension){
            continue;
        }
        if(strcmp(extension,"txt") == 0){
            dtw.path.set_extension( part->path,"md");
            dtw.tree.part.hardware_modify(part,DTW_SET_AS_ACTION);

        }
    }

    dtw.tree.hardware_commit_tree(tree);
    dtw.tree.free(tree);
}
~~~


With transactin Reports , you can see what will be modified


~~~c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_INCLUDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    for(int i=0; i < tree->size;i++){
        DtwTreePart *part = tree->tree_parts[i];

        char *extension = dtw.path.get_extension(part->path);
        if(!extension){
            continue;
        }
        printf("%s\n",extension);
        if(strcmp(extension,"txt") == 0){
            dtw.path.set_extension(part->path,"md");
            dtw.tree.part.hardware_modify(part,DTW_SET_AS_ACTION);

        }
    }
    DtwTreeTransactionReport *report = dtw.tree.create_report(tree);
    dtw.tree.transaction_report.represent(report);
    dtw.tree.transaction_report.free(report);
    dtw.tree.free(tree);
}
~~~

With Json Trees Operations you can save or load trees, from hardware or strings in an super easy mode 

#### Dumping Tree Json To File 
It will transform the tree in an json document


~~~c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    struct DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "tests/target/",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    dtw.tree.dumps_json_tree_to_file(
            tree,
            "tests/target/out.json",
            (DtwTreeProps){
                    .minification = DTW_NOT_MIMIFY,
                    .ignored_elements=DTW_HIDE,
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    dtw.tree.free(tree);
}
~~~



~~~c

#include "doTheWorld.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "tests/target/",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    char *content = dtw.tree.dumps_json_tree(
            tree,
            (DtwTreeProps){
                    .minification = DTW_NOT_MIMIFY,
                    .ignored_elements=DTW_HIDE,
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    printf("%s",content);
    free(content);
    dtw.tree.free(tree);
}
~~~

If you want to recuperate the file you saved in the json file
you can load it 


~~~c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"

void dumps_tree(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    dtw.tree.dumps_json_tree_to_file(
            tree,
            "tests/target/out.json",
            (DtwTreeProps){
                    .minification = DTW_MIMIFY,
                    .ignored_elements=DTW_HIDE,
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    dtw.tree.free(tree);
}
int main(){
    DtwNamespace dtw = newDtwNamespace();
    dumps_tree();
    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.loads_json_tree_from_file(tree,"tests/target/out.json");
    dtw.tree.represent(tree);
    dtw.tree.free(tree);
}
~~~



~~~c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"

char *dumps_tree(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_INCLUDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    char *content = dtw.tree.dumps_json_tree(
            tree,
            (DtwTreeProps){
                    .minification = DTW_MIMIFY,
                    .ignored_elements=DTW_HIDE,
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    dtw.tree.free(tree);
    return content;
}
int main(){
    DtwNamespace dtw = newDtwNamespace();

    char * content = dumps_tree();
    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.loads_json_tree(tree,content);
    dtw.tree.represent(tree);
    dtw.tree.free(tree);
    free(content);
}
~~~


## Hash

By using hash Object you can digest values,( its very usefull in dynamic programing)
or to avoid recomputation in compilers or bundlers

### Simple Hashing


~~~c
#include "doTheWorld.h"





int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwHash *my_hash = dtw.hash.newHash();

    dtw.hash.digest_string(my_hash,"my string");
    printf("value after digest string %s\n",my_hash->hash);

    dtw.hash.digest_long(my_hash,10);
    printf("value after long: %s\n",my_hash->hash);

    dtw.hash.digest_double(my_hash,15.6);
    printf("value after double: %s\n",my_hash->hash);

    dtw.hash.digest_bool(my_hash,true);
    printf("value after digest bool %s\n",my_hash->hash);

    DtwStringArray *test = dtw.string_array.newStringArray();
    dtw.string_array.append(test,"b");
    dtw.string_array.append(test,"a");

    dtw.hash.digest_string_array(my_hash,test);
    printf("value after string array %s\n",my_hash->hash);
    dtw.string_array.free(test);

    dtw.hash.free(my_hash);
}
~~~


~~~c
#include "doTheWorld.h"





int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwHash *my_hash = dtw.hash.newHash();

    dtw.hash.digest_file(my_hash,"tests/target/a.txt");

    printf("after a file :%s\n",my_hash->hash);

    dtw.hash.digest_folder_by_content(my_hash,"tests/target");
    printf("after a folder %s\n",my_hash->hash);

    dtw.hash.free(my_hash);
}
~~~


~~~c
#include "doTheWorld.h"





int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwHash *my_hash = dtw.hash.newHash();

    dtw.hash.digest_entity_last_modification(my_hash,"tests/target/a.txt");

    printf("after a file :%s\n",my_hash->hash);

    dtw.hash.digest_folder_by_last_modification(my_hash,"tests/target");
    printf("after a folder %s\n",my_hash->hash);
    
    dtw.hash.free(my_hash);
}
~~~

## CJson<br><br>
**CJson**: from https://github.com/DaveGamble/cJSON <br>
Copyright (c) 2009-2017 Dave Gamble and cJSON contributors

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## sha-256 <br>
**sha-256**: from https://github.com/amosnier/sha-2 <br>

Zero Clause BSD License
© 2021 Alain Mosnier

Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
