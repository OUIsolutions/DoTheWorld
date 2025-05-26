### Trees and TreeParts
with tree concepts, you can manipulate files as trees, and implement IO modifications with atomic concepts

### Loading An TreePart

```c
#include "doTheWorldOne.c"

int main(){
    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");
    DtwTreePart_represent(part);
    DtwTreePart_free(part);
}
```

### Creating an empty tree Part

```c
#include "doTheWorldOne.c"

int main(){
    DtwTreePart *part = newDtwTreePartEmpty("tests/target/b.txt");
    DtwTreePart_set_string_content(part, "my mensage");
    DtwTreePart_hardware_write(part, DTW_SET_AS_ACTION);
    DtwTreePart_hardware_commit(part);
    DtwTreePart_free(part);
}
```
### Modifying an tree part
```c
#include "doTheWorldOne.c"

int main(){
    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");

    //getting the content
    char *content = DtwTreePart_get_content_string_by_reference(part);
    char new_content[100] = {0};
    strcat(new_content, content);
    strcat(new_content, " New Mensage");
    DtwTreePart_set_string_content(part, new_content);

    DtwTreePart_hardware_write(part, DTW_SET_AS_ACTION);
    DtwTreePart_hardware_commit(part);
    DtwTreePart_free(part);
}
```
### Removing an tree part

```c
### Retrieving Paths Params

#include "doTheWorldOne.c"

int main(){
    DtwPath *path = newDtwPath("a/b/c/d.txt");
    char *name = DtwPath_get_full_name(path);
    char *extension = DtwPath_get_extension(path);
    char *dir = DtwPath_get_dir(path);
    char *full_path = DtwPath_get_path(path);
    printf("name : %s\n", name);
    printf("extension : %s\n", extension);
    printf("dir : %s\n", dir);
    printf("full_path : %s\n", full_path);
    DtwPath_free(path);
}
```
### Changing path Attributes at once

```c
#include "doTheWorldOne.c"

int main(){
    DtwPath *path = newDtwPath("a/b/c/d.txt");
    DtwPath_set_name(path, "test");
    DtwPath_set_extension(path, "md");
    DtwPath_represent(path);
    DtwPath_free(path);
}
```

With the **hardware_modify**, **hardware_write**, **hardware_remove**
Functions, you can generate modifications without implementing them, in this
way, you can create massive atomic transactions, and execute all at once

### hardware_modify
Will modify the original content, for example, if you change the extension of a file, it will modify the original content

```c
#include "doTheWorldOne.c"

int main(){
    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");

    DtwPath_set_extension(part->path, "md");

    DtwTreePart_hardware_modify(part, DTW_EXECUTE_NOW);
    DtwTreePart_hardware_commit(part);
    DtwTreePart_free(part);
}

Will write the file as a "new" file, ignoring the existence of the
old file

#include "doTheWorldOne.c"

int main(){
    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");
    DtwPath_set_extension(part->path, "md");
    DtwTreePart_hardware_write(part, DTW_EXECUTE_NOW);
    DtwTreePart_hardware_commit(part);
    DtwTreePart_free(part);
}

```
Will delete the current content

```c
#include "doTheWorldOne.c"

int main(){
    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");

    DtwTreePart_hardware_remove(part, DTW_EXECUTE_NOW);
    DtwTreePart_hardware_commit(part);
    DtwTreePart_free(part);
}

```
With Trees you can make massive folder and file modifications with
easy steps
### Loading Tree From Hardware

```c
#include "doTheWorldOne.c"

int main(){
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
            tree,
            "tests/target/",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    DtwTree_represent(tree);
    DtwTree_free(tree);
}

```
### Iterating over An Tree

#include "doTheWorldOne.c"
int main(){
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    for(int i = 0; i < tree->size; i++){
        DtwTreePart *current_part = tree->tree_parts[i];
        DtwTreePart_represent(current_part);
    }
    DtwTree_free(tree);
}

### Finding An Tree by name

#include "doTheWorldOne.c"

int main(){
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    DtwTreePart *blob = DtwTree_find_tree_part_by_name(tree, "blob.png");
    if(blob){
        DtwTreePart_represent(blob);
    }
    DtwTree_free(tree);
}

### Finding An Tree by Path

#include "doTheWorldOne.c"

int main(){
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
            tree,
            "tests/target/",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    DtwTreePart *element = DtwTree_find_tree_part_by_path(
            tree,
            "tests/target/sub_folder/sub_element.txt"
    );
    if(element){
        DtwTreePart_represent(element);
    }
    DtwTree_free(tree);
}

### Finding An Tree by Function

#include "doTheWorldOne.c"

bool test_if_blob(struct DtwTreePart* part, void *args){
    char *name = DtwPath_get_full_name(part->path);
    if(!name){
        return false;
    }

    if(strcmp(name, "blob.png") == 0){
        return true;
    }
    return false;
};

int main(){
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                .content = DTW_INCLUDE,
                .hadware_data=DTW_HIDE,
                .path_atributes=DTW_INCLUDE
            }
    );

    DtwTreePart *blob = DtwTree_find_tree_part_by_function(
            tree,
            test_if_blob,
            NULL
    );

    DtwTreePart_represent(blob);

    DtwTree_free(tree);
}

Trees support even Maps or filters, it returns a new tree of the current lambda procedure
### Filter
with filter you can filter the contents you want in a tree with a bool lambda

#include "doTheWorldOne.c"

bool filter_txt(struct DtwTreePart *part){
    char *extension = DtwPath_get_extension(part->path);
    if(!extension){
        return false;
    }
    if(strcmp(extension, "txt") == 0){
        return true;
    }
    return false;
}

int main(){
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    DtwTree *filtered = DtwTree_filter(
            tree,
            filter_txt
    );

    DtwTree_represent(filtered);
    DtwTree_free(filtered);
    DtwTree_free(tree);
}

### Map

#include "doTheWorldOne.c"

DtwTreePart * concat_test(struct DtwTreePart *part){
    if(part->content && part->is_binary == false){
        char *content = DtwTreePart_get_content_string_by_reference(part);
        const char *mensage = " test";
        char *new_content = (char*)malloc(strlen(content) + strlen(mensage) + 2);
        strcpy(new_content, content);
        strcat(new_content, mensage);
        DtwTreePart_set_string_content(part, new_content);
        free(new_content);
    }
    return part;
}

int main(){
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    DtwTree *concated = DtwTree_map(
            tree,
            concat_test
    );

    DtwTree_represent(concated);
    DtwTree_free(concated);
    DtwTree_free(tree);
}

With **hardware_commit_tree** you can commit all modifications at once
turning system ultra secure

#include "doTheWorldOne.c"

int main(){
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                .content = DTW_INCLUDE,
                .hadware_data=DTW_HIDE,
                .path_atributes=DTW_INCLUDE
            }
    );

    for(int i=0; i < tree->size; i++){
        struct DtwTreePart *part = tree->tree_parts[i];

        char *extension = DtwPath_get_extension(part->path);
        if(!extension){
            continue;
        }
        if(strcmp(extension, "txt") == 0){
            DtwPath_set_extension(part->path, "md");
            DtwTreePart_hardware_modify(part, DTW_SET_AS_ACTION);
        }
    }

    DtwTree_hardware_commit_tree(tree);
    DtwTree_free(tree);
}

With transaction Reports, you can see what will be modified

#include "doTheWorldOne.c"

int main(){
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_INCLUDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    for(int i=0; i < tree->size; i++){
        DtwTreePart *part = tree->tree_parts[i];

        char *extension = DtwPath_get_extension(part->path);
        if(!extension){
            continue;
        }
        printf("%s\n", extension);
        if(strcmp(extension, "txt") == 0){
            DtwPath_set_extension(part->path, "md");
            DtwTreePart_hardware_modify(part, DTW_SET_AS_ACTION);
        }
    }
    DtwTreeTransactionReport *report = DtwTree_create_report(tree);
    DtwTreeTransactionReport_represent(report);
    DtwTreeTransactionReport_free(report);
    DtwTree_free(tree);
}

With Json Trees Operations you can save or load trees, from hardware or strings in a super easy mode

### Dumping Tree Json To File
It will transform the tree into a json document

#include "doTheWorldOne.c"

int main(){
    struct DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
            tree,
            "tests/target/",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    DtwTree_dumps_tree_json_to_file(
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

    DtwTree_free(tree);
}

#include "doTheWorldOne.c"

int main(){
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
            tree,
            "tests/target/",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    char *content = DtwTree_dumps_tree_json(
            tree,
            (DtwTreeProps){
                    .minification = DTW_NOT_MIMIFY,
                    .ignored_elements=DTW_HIDE,
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    printf("%s", content);
    free(content);
    DtwTree_free(tree);
}

If you want to recuperate the file you saved in the json file
you can load it

#include "doTheWorldOne.c"

void dumps_tree(){
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    DtwTree_dumps_tree_json_to_file(
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

    DtwTree_free(tree);
}
int main(){
    dumps_tree();
    DtwTree *tree = newDtwTree();
    DtwTree_loads_json_tree_from_file(tree, "tests/target/out.json");
    DtwTree_represent(tree);
    DtwTree_free(tree);
}

#include "doTheWorldOne.c"

char *dumps_tree(){
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_INCLUDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    char *content = DtwTree_dumps_tree_json(
            tree,
            (DtwTreeProps){
                    .minification = DTW_MIMIFY,
                    .ignored_elements=DTW_HIDE,
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    DtwTree_free(tree);
    return content;
}
int main(){
    char *content = dumps_tree();
    DtwTree *tree = newDtwTree();
    DtwTree_loads_json_tree(tree, content);
    DtwTree_represent(tree);
    DtwTree_free(tree);
    free(content);
}
