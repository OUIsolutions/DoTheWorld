# DoTheWorld
DoTheWorld is a Windows/Linux single file library designed to handle files in C/C++ in a number of ways, providing everything from simple functions for reading/writing files and folders, to complex functions like taking sha256 from files, checking modification dates. And functionalities of atomic writing of folders/files through transaction systems.



## Learning
In These Current Markdown you will see some basic exemples of usage of these library 
but if you want to get an deep knolege see at **exemples** folder, you will find an lot of exemplos of how you can use DoTheWorld

# Installation
The installation of DoTheWorld is made to be as dumb as possible, just  download the file  amalgamation **doTheWorld.h**  and include in your project.
if this compiles then the library will work:
~~~c
#include "doTheWorld.h"

int main(int argc, char *argv[]){
    
    
    return 0;
}
~~~

## Full Folder
Alternatively you can download the entire **doTheWorld** folder and include the **doTheWorld/doTheWorldMain.h** file

~~~c

#include "doTheWorld/doTheWorldMain.h"

int main(int argc, char *argv[]){

    return 0;
}

~~~
# IO Operations

## Reading strings
if you are sure that the content you are going to read is not binary you can call the function **dtw_load_string_file_content**
<!--codeof:exemples/io/loading_string.c-->
~~~c

#include "doTheWorld.h"

int main(int argc, char *argv[]){
  //load a string file content
  const char *path = "tests/target/a.txt";
  char *content = dtw_load_string_file_content(path);
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
<!--codeof:exemples/io/loading_any.c-->
~~~c
#include "doTheWorld.h"

int main(int argc, char *argv[]){
 
  const char *path = "tests/target/blob.png";
  long size;
  bool is_binary;
  //load any file, is useful if you don't know if the file is binary or not
  unsigned char *content = dtw_load_any_content(path,&size,&is_binary);
  if(content == NULL){
    printf("error oppening %s\n",path);
    return 1;
  }
  printf("size: %ld\n",size);
  printf("is_binary: %s\n",is_binary ? "true" : "false");

  dtw_write_any_content("tests/target/blob2.png",content,size);
  free(content);
  return 0;
}
~~~
### Writing Strings
to write strings in text files is very simple, just call the function **dtw_write_string_file_content**
(Note that the target directory does not need to exist, if it does not exist it will be created automatically)

<!--codeof:exemples/io/writing_strings.c-->
~~~c
#include "doTheWorld.h"

int main(int argc, char *argv[]){
  // Write a string to a file the path is auto created
  
  bool result = dtw_write_string_file_content("tests/target/a.txt","Hello World!");
  printf("result: %s\n",result ? "true" : "false");
  return 0;
}
~~~
### Writing Any
if you want to write anything to a file, it's also very simple, use the **dtw_write_any_content** function, but note that it will be necessary to pass the writing size

<!--codeof:exemples/io/write_any.c-->
~~~c
#include "doTheWorld.h"

int main(int argc, char *argv[]){
  //load the beer image
  const char *blob_path = "tests/target/blob.png";
  long blob_size;
  unsigned char *content = dtw_load_binary_content(blob_path,&blob_size);
  //use these functions for binary files
  if(content == NULL){
    printf("error oppening %s\n",blob_path);
    return 1;
  }
  printf("size: %ld\n",blob_size);

  bool result = dtw_write_any_content("tests/target/blob2.png",content,blob_size);
  printf("result: %s\n",result ? "true" : "false");
free(content);
  return 0;
}
~~~
### Creating Dirs
If you want to create dirs you can call the function **dtw_create_dir_recursively**
passing the folder you want to create,dont wory about if the previews path dont exist 
it will create till reachs the target folder

<!--codeof:exemples/io/create_dirs.c-->
~~~c
#include "doTheWorld.h"

int main(int argc, char *argv[]){
 
  dtw_create_dir_recursively("tests/target/sub_folder/a/b/c");

  return 0;
}
~~~
### Copying Anything
With the function **dtw_copy_any** you can copy either files or folders to one position to anoter position 

<!--codeof:exemples/io/copying_files.c-->
~~~c


#include "doTheWorld.h"

int main(int argc, char *argv[]){

  dtw_copy_any("tests/target/blob.png","tests/target/blob3.png",DTW_NOT_MERGE);
  return 0;
}
~~~
### Moving Any
You can move either folders or files with **dtw_move_any** function
<!--codeof:exemples/io/move_any.c-->
~~~c

#include "doTheWorld.h"

int main(int argc, char *argv[]){


    dtw_move_any("tests/target/sub_folder","tests/target/sub_folder2",DTW_NOT_MERGE);

    return 0;
}
~~~

With the listage functions you can extract all Strings Arrays of elements in an folder 

## Listing files
<!--codeof:exemples/monodimension_listage/list_files.c-->
~~~c

#include "doTheWorld.h"

int main(int argc, char *argv[]){

  DtwStringArray *files = dtw_list_files("tests/target", DTW_CONCAT_PATH);
  files->sort(files);

  for(int i = 0; i < files->size; i++){
    printf("%s\n", files->strings[i]);
  }
  files->free(files);
  return 0;
}
~~~
### Listing Dirs
<!--codeof:exemples/monodimension_listage/list_dirs.c-->
~~~c


#include "doTheWorld.h"

int main(int argc, char *argv[]){

  DtwStringArray *dirs = dtw_list_dirs("tests/target", DTW_NOT_CONCAT_PATH);
  //the represent methold will print the dirs in the console
  dirs->sort(dirs);
  dirs->represent(dirs);
  dirs->free(dirs);
  return 0;
}
~~~
### Listing All
<!--codeof:exemples/monodimension_listage/list_all.c-->
~~~c



#include "doTheWorld.h"

int main(int argc, char *argv[]){

  DtwStringArray *all = dtw_list_all("tests/target/",DTW_CONCAT_PATH);
  all->sort(all);
  all->represent(all);
  all->free(all);
  return 0;
}
~~~
The By Using multi dimension listage functions , you can see all itens listed in all sub folders of the "main" folder 

## Listing Files Recursively
<!--codeof:exemples/multidimension_listage/list_files_recursively.c-->
~~~c

#include "doTheWorld.h"

int main(int argc, char *argv[]){

  DtwStringArray *files = dtw_list_files_recursively("tests/target/",DTW_CONCAT_PATH);
  files->sort(files);
  files->represent(files);
  files->free(files);
  return 0;
}
~~~
## Listing Dirs Recursively

<!--codeof:exemples/multidimension_listage/list_dirs_recursively.c-->
~~~c

#include "doTheWorld.h"

int main(int argc, char *argv[]){

  DtwStringArray *files = dtw_list_dirs_recursively("tests/target/",DTW_CONCAT_PATH);
  files->sort(files);
  files->represent(files);
  files->free(files);
  return 0;
}
~~~

## Listing All Recursively
<!--codeof:exemples/multidimension_listage/list_all_recursively.c-->
~~~c

#include "doTheWorld.h"

int main(int argc, char *argv[]){

  DtwStringArray *files = dtw_list_all_recursively("tests/target/",DTW_CONCAT_PATH);
  files->sort(files);
  files->represent(files);
  files->free(files);
  return 0;
}
~~~

## Dealing with base64 
You can easly transform an binary file to an base64 string like these
<!--codeof:exemples/extras/converting_file_to_base64.c-->
~~~c

#include "doTheWorld.h"

int main(int argc, char *argv[]){
   const char *deer_path = "tests/target/blob.png";
   char *deerb64  = dtw_convert_binary_file_to_base64(deer_path);
   printf("blob: %s", deerb64);
    free(deerb64);
}
~~~
You also can reconvert an base64 string to binary
<!--codeof:exemples/extras/converting_b64_to_binary.c-->
~~~c

#include "doTheWorld.h"

int main(int argc, char *argv[]){



    //creating the b64 file
    const char *blob_path = "tests/target/blob.png";
    char *blob  = dtw_convert_binary_file_to_base64(blob_path);
    unsigned long output;
    unsigned char  *result = dtw_base64_decode(blob,&output);

    dtw_write_any_content("tests/target/blob2.png",result,output);

    free(result);
    free(blob);

    return 0;
}
~~~



Generating Sha from file 
<!--codeof:exemples/extras/generating_sha_from_file.c-->
~~~c

#include "doTheWorld.h"

int main(int argc, char *argv[]){

   char *hash = dtw_generate_sha_from_file("tests/target/blob.png");
   printf("SHA: %s", hash);
   free(hash);
}
~~~
### Unix

<!--codeof:exemples/extras/get_file_last_modification_in_unix.c-->
~~~c

#include "doTheWorld.h"

int main(int argc, char *argv[]){
   int last_modification_in_unix = dtw_get_file_last_motification_in_unix("tests/target/a.txt");
    printf("Last modification: %d\n", last_modification_in_unix);
}
~~~
<!--codeof:exemples/extras/get_file_last_modification.c-->
~~~c
#include "doTheWorld.h"

int main(int argc, char *argv[]){
    char *last_modification = dtw_get_file_last_motification_in_string("tests/target/a.txt");
    printf("Last modification: %s", last_modification);
    free(last_modification);
}
~~~

with tree concepts, you can manipulate files as trees, and implement IO modifications with atomic concepts 

## Locker 
With the locker you can Lock files and ensure that even with multprocessment, they will
be executed in an order
<!--codeof:exemples/locker/locker_test.c-->
~~~c

#include "doTheWorld.h"


void append_text(char *file,char *text){

  
    DtwLocker *locker = newDtwLocker();
    locker->lock(locker,file);
    printf("process %d get the ownership\n",locker->process);

    char *content = dtw_load_string_file_content(file);

    content = realloc(content,strlen(content) + 20);
    strcat(content,text);
        
    dtw_write_string_file_content(file,content);
    free(content);


    locker->free(locker);
    
}

int main(int argc, char *argv[]){

    char *file = "tests/target/append.txt";
    int total_process  = 20;

    dtw_remove_any(file);
    dtw_write_string_file_content(file,"");

    for(int i = 0; i < total_process; i ++){

        if(fork() == 0){
            char formated_content[100] = {0};
            sprintf(formated_content,"text of: %d\n",i);
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

### Loading An TreePart 
<!--codeof:exemples/tree_parts/loading_tree_part.c-->
~~~c


#include "doTheWorld.h"

int main(){

    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");
    part->last_modification_time = 0;
    
    part->represent(part);
    part->free(part);
}
~~~
### Creating an empty tree Part
<!--codeof:exemples/trees/creating_tree_part.c-->
~~~c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"


int main(){

    DtwTreePart *part = newDtwTreePartEmpty("tests/target/b.txt");
    part->set_string_content(part,"my mensage");
    part->hardware_write(part,DTW_SET_AS_ACTION);
    part->hardware_commit(part);
    part->free(part);
}
~~~

### Modifying an tree part
<!--codeof:exemples/tree_parts/tree_part_content_modification.c-->
~~~c
#include "doTheWorld.h"


int main(){

     DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");

    //getting the content
    char *content = part->get_content_string_by_reference(part);
    char new_content[100] ={0};
    strcat(new_content,content);
    strcat(new_content," New Mensage");
    part->set_string_content(part,new_content);

    part->hardware_write(part,DTW_SET_AS_ACTION);
    part->hardware_commit(part);
    part->free(part);
}
~~~

### Retriing Paths Paramns
<!--codeof:exemples/path/getting_path_paramns.c-->
~~~c

#include "doTheWorld.h"


int main(){

    DtwTreePart *part = newDtwTreePartLoading( "tests/target/a.txt");

    DtwPath *path = part->path;

    char *name = path->get_full_name(path);
    char *extension = path->get_extension(path);
    char *dir = path->get_dir(path);
    char *full_path = path->get_path(path);
    printf("name : %s\n",name);
    printf("extension : %s\n",extension);
    printf("dir : %s\n",dir);
    printf("full_path : %s\n",full_path);


    free(name);
    free(extension);
    free(dir);
    free(full_path);
    part->free(part);
}
~~~


### Changing path Atributes at once 

<!--codeof:exemples/path/change_path_attributes.c-->
~~~c

#include "doTheWorld.h"


int main(){

    DtwTreePart *part = newDtwTreePartLoading("tests/target/sub_folder/a.txt");

    DtwPath *path = part->path;

    path->set_dir(path,"a/b");
    path->set_name(path,"test2");
    path->set_extension(path,"md");
    path->represent(path);
    part->hardware_modify(part,DTW_SET_AS_ACTION);
    part->hardware_commit(part);
    part->free(part);

}
~~~
With the **hardware_modify** , **hardware_write**, **hardware_remove** 
Functions , you can generate modifications, without implement it, in these 
way , you can create massive atomic transactions, and execute all at once 


### hardware_modify
Will Modificate the original content, for exemple, if you change the extension of an file, it will modificate the original content 

<!--codeof:exemples/tree_parts/hardware_modify.c-->
~~~c
#include "doTheWorld.h"


int main(){

    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");

    DtwPath *path = part->path;

    path->set_extension(path,"md");

    part->hardware_modify(part,DTW_EXECUTE_NOW);
    part->hardware_commit(part);
    part->free(part);

}
~~~
Will write the file as an "new" file, ignoring the existence of the 
old file 

<!--codeof:exemples/tree_parts/hardware_write.c-->
~~~c

#include "doTheWorld.h"


int main(){

    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");

    DtwPath *path = part->path;

    path->set_extension(path,"md");

    part->hardware_write(part,DTW_EXECUTE_NOW);
    part->hardware_commit(part);
    part->free(part);

}
~~~

Will Delete the current Content 

<!--codeof:exemples/tree_parts/hardware_remove.c-->
~~~c


#include "doTheWorld.h"



int main(){

    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");

    part->hardware_remove(part,DTW_EXECUTE_NOW);
    part->hardware_commit(part);
    part->free(part);

}
~~~
With Trees you can make massive folders and files modifications with 
easy steps 
### Loading Tree From Hardware

<!--codeof:exemples/trees/add_tree_from_hardware.c-->
~~~c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"


int main(){

    DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "tests/target/",
            &(DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    tree->represent(tree);
    tree->free(tree);
}
~~~

### Iterating over An Tree
<!--codeof:exemples/trees/tree_iteration.c-->
~~~c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"
int main(){

    DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "tests/target",
            &(DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    for(int i = 0; i<tree->size;i++){
        DtwTreePart *current_part = tree->tree_parts[i];
        current_part->represent(current_part);
    }
    tree->free(tree);
}
~~~

### Finding An Tree by name
<!--codeof:exemples/trees/find_tree_part_by_name.c-->
~~~c
//
// Created by jurandi on 20-06-2023.
//


#include "doTheWorld.h"

int main(){

    DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "tests/target",
            &(DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    DtwTreePart *blob = tree->find_part_by_name(tree,"blob.png");
    if(blob){
        blob->represent(blob);
    }
    tree->free(tree);

}
~~~

### Finding An Tree by Path
<!--codeof:exemples/trees/find_tree_part_by_full_path.c-->
~~~c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"

int main(){

    DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "tests/target/",
            &(DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    DtwTreePart *element = tree->find_part_by_path(
            tree,
            "tests/target/sub_folder/sub_element.txt"
    );
    if(element){
        element->represent(element);
    }
    tree->free(tree);
}

~~~
### Finding An Tree by Function
<!--codeof:exemples/trees/finding_tree_part_by_function.c-->
~~~c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"

bool test_if_blob(struct DtwTreePart*part){

    char *name = part->path->get_full_name(part->path);
    if(!name){
        return false;
    }
    if(strcmp(name,"blob.png") == 0){
        free(name);
        return true;
    }
    free(name);
    return false;
};


int main(){

    struct DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "exemple_folder",
            &(DtwTreeProps){
                .content = DTW_INCLUDE,
                .hadware_data=DTW_HIDE,
                .path_atributes=DTW_INCLUDE
            }
    );


    struct DtwTreePart *blob = tree->find_part_by_function(
            tree,
            test_if_blob
    );

    if(blob){
        blob->represent(blob);
    }
    tree->free(tree);

}
~~~
Trees suports even Maps or filters, it returns an new tree of the of the current lambda procediment 
#### Filter 
with filter you can filter the contents you want in an tree with an bool lambda

<!--codeof:exemples/trees/tree_filter.c-->
~~~c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"

bool filter_txt(struct DtwTreePart *part){
    char *extension = part->path->get_extension(part->path);
    if(!extension){
        return false;
    }
    if(strcmp(extension,"txt") == 0){
        free(extension);
        return true;
    }
    free(extension);
    return false;
}

int main(){

    DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "tests/target",
            &(DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    DtwTree *filtered = tree->filter(
            tree,
            filter_txt
    );

    filtered->represent(filtered);
    filtered->free(filtered);
    tree->free(tree);
}
~~~

### Map 
<!--codeof:exemples/trees/tree_map.c-->
~~~c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"

DtwTreePart * concat_test(struct DtwTreePart *part){
    if(part->content_exist_in_memory && part->is_binary == false){
        char *content = part->get_content_string_by_reference(part);
        const char *mensage = " test";
        char *new_content = (char*)malloc(strlen(content) + strlen(mensage)+ 2);
        strcpy(new_content,content);
        strcat(new_content,mensage);
        part->set_string_content(part,new_content);
        free(new_content);
    }
    return part;
}

int main(){

    DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "tests/target",
            &(DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    DtwTree *concated = tree->map(
            tree,
            concat_test
    );

    concated->represent(concated);
    concated->free(concated);
    tree->free(tree);
}
~~~
With **hardware_commit_tree** you can commit all modifications at Once 
turning system ultra securty

<!--codeof:exemples/trees/tree_commit.c-->
~~~c
//
// Created by jurandi on 20-06-2023.
//

#include "doTheWorld.h"

int main(){

    DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "tests/target",
            &(DtwTreeProps){
                .content = DTW_INCLUDE,
                .hadware_data=DTW_HIDE,
                .path_atributes=DTW_INCLUDE
            }
    );

    for(int i=0; i < tree->size;i++){
        struct DtwTreePart *part = tree->tree_parts[i];
        struct DtwPath *path = part->path;
        char *extension = path->get_extension(path);
        if(!extension){
            continue;
        }
        if(strcmp(extension,"txt") == 0){
            path->set_extension(path,"md");
            part->hardware_modify(part,DTW_SET_AS_ACTION);

        }
        free(extension);
    }

    tree->hardware_commit_tree(tree);
    tree->free(tree);
}
~~~

With transactin Reports , you can see what will be modified
<!--codeof:exemples/trees/transaction_report.c-->
~~~c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"

int main(){

    DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "tests/target",
            &(DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_INCLUDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    for(int i=0; i < tree->size;i++){
        DtwTreePart *part = tree->tree_parts[i];
        DtwPath *path = part->path;
        char *extension = path->get_extension(path);
        if(!extension){
            continue;
        }
        printf("%s\n",extension);
        if(strcmp(extension,"txt") == 0){
            path->set_extension(path,"md");
            part->hardware_modify(part,DTW_SET_AS_ACTION);

        }
        free(extension);
    }
    DtwTreeTransactionReport *report = tree->report(tree);
    report->represent(report);
    report->free(report);
    tree->free(tree);
}
~~~
With Json Trees Operations you can save or load trees, from hardware or strings in an super easy mode 

#### Dumping Tree Json To File 
It will transform the tree in an json document
<!--codeof:exemples/trees/dumps_json_tree_to_file.c-->
~~~c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"


int main(){

    struct DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "tests/target/",
            &(DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    tree->dumps_json_tree_to_file(
            tree,
            "tests/target/out.json",
            &(DtwTreeProps){
                    .minification = DTW_NOT_MIMIFY,
                    .ignored_elements=DTW_HIDE,
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    tree->free(tree);
}
~~~
<!--codeof:exemples/trees/dumps_json_tree_to_string.c-->
~~~c

#include "doTheWorld.h"

int main(){

    DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "tests/target/",
            &(DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    char *content = tree->dumps_json_tree(
            tree,
            &(DtwTreeProps){
                    .minification = DTW_NOT_MIMIFY,
                    .ignored_elements=DTW_HIDE,
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    printf("%s",content);
    free(content);
    tree->free(tree);
}
~~~
If you want to recuperate the file you saved in the json file
you can load it 

<!--codeof:exemples/trees/loads_json_tree_from_file.c-->
~~~c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"

void dumps_tree(){

    DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "tests/target",
            &(DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    tree->dumps_json_tree_to_file(
            tree,
            "tests/target/out.json",
            &(DtwTreeProps){
                    .minification = DTW_MIMIFY,
                    .ignored_elements=DTW_HIDE,
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    tree->free(tree);
}
int main(){
    dumps_tree();
    DtwTree *tree = newDtwTree();
    tree->loads_json_tree_from_file(tree,"tests/target/out.json");
    tree->represent(tree);
    tree->free(tree);
}
~~~



<!--codeof:exemples/trees/loads_json_tree_from_string.c-->
~~~c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"

char *dumps_tree(){

    DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "tests/target",
            &(DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_INCLUDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    char *content = tree->dumps_json_tree(
            tree,
            &(DtwTreeProps){
                    .minification = DTW_MIMIFY,
                    .ignored_elements=DTW_HIDE,
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    tree->free(tree);
    return content;
}
int main(){
    char * content = dumps_tree();
    DtwTree *tree = newDtwTree();
    tree->loads_json_tree(tree,content);
    tree->represent(tree);
    tree->free(tree);
    free(content);
}
~~~



DoTheWorld includes all self dependecies in the single file, so you dont need to care about it, but if you will use one of these librarys, dont include it in your code to avoid circular imports

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

