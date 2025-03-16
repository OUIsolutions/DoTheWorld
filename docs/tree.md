

### Trees and TreeParts
with tree concepts, you can manipulate files as trees, and implement IO modifications with atomic concepts

### Loading An TreePart

```c


#include "doTheWorldOne.c"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTreePart *part = dtw.tree.part.newPartLoading("tests/target/a.txt");
    dtw.tree.part.represent(part);
    dtw.tree.part.free(part);
}

```


### Creating an empty tree Part

```c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorldOne.c"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTreePart *part = dtw.tree.part.newPartEmpty("tests/target/b.txt");
    dtw.tree.part.set_string_content(part,"my mensage");
    dtw.tree.part.hardware_write(part,DTW_SET_AS_ACTION);
    dtw.tree.part.hardware_commit(part);
    dtw.tree.part.free(part);
}

```

### Modifying an tree part

```c
#include "doTheWorldOne.c"


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

```


### Retriing Paths Paramns

```c

#include "doTheWorldOne.c"


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

```

### Changing path Atributes at once


```c

#include "doTheWorldOne.c"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwPath * path = dtw.path.newPath("a/b/c/d.txt");
    dtw.path.set_name(path,"test");
    dtw.path.set_extension(path,"md");
    dtw.path.represent(path);
    dtw.path.free(path);


}

```

With the **hardware_modify** , **hardware_write**, **hardware_remove**
Functions , you can generate modifications, without implement it, in these
way , you can create massive atomic transactions, and execute all at once


### hardware_modify
Will Modificate the original content, for exemple, if you change the extension of an file, it will modificate the original content


```c
#include "doTheWorldOne.c"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTreePart *part = dtw.tree.part.newPartLoading("tests/target/a.txt");

    dtw.path.set_extension(part->path,"md");

    dtw.tree.part.hardware_modify(part,DTW_EXECUTE_NOW);
    dtw.tree.part.hardware_commit(part);
    dtw.tree.part.free(part);

}

```

Will write the file as an "new" file, ignoring the existence of the
old file

```c

#include "doTheWorldOne.c"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTreePart *part = dtw.tree.part.newPartLoading("tests/target/a.txt");
    dtw.path.set_extension(part->path,"md");
    dtw.tree.part.hardware_write(part,DTW_EXECUTE_NOW);
    dtw.tree.part.hardware_commit(part);
    dtw.tree.part.free(part);

}

```


Will Delete the current Content


```c


#include "doTheWorldOne.c"



int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTreePart *part = dtw.tree.part.newPartLoading("tests/target/a.txt");

    dtw.tree.part.hardware_remove(part,DTW_EXECUTE_NOW);
    dtw.tree.part.hardware_commit(part);
    dtw.tree.part.free(part);

}

```

With Trees you can make massive folders and files modifications with
easy steps
### Loading Tree From Hardware

```c
#include "doTheWorldOne.c"


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

```

### Iterating over An Tree

```c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorldOne.c"
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

```

### Finding An Tree by name

```c
//
// Created by jurandi on 20-06-2023.
//


#include "doTheWorldOne.c"

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

```


### Finding An Tree by Path

```c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorldOne.c"

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

```

### Finding An Tree by Function

```c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorldOne.c"


bool test_if_blob(struct DtwTreePart*part,void *args){
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
            test_if_blob,
            NULL
    );

    dtw.tree.part.represent(blob);

    dtw.tree.free(tree);

}

```

Trees suports even Maps or filters, it returns an new tree of the of the current lambda procediment
### Filter
with filter you can filter the contents you want in an tree with an bool lambda

```c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorldOne.c"

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

```

### Map

```c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorldOne.c"

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

```

With **hardware_commit_tree** you can commit all modifications at Once
turning system ultra securty


```c
//
// Created by jurandi on 20-06-2023.
//

#include "doTheWorldOne.c"

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

```


With transactin Reports , you can see what will be modified

```c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorldOne.c"

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

```

With Json Trees Operations you can save or load trees, from hardware or strings in an super easy mode

### Dumping Tree Json To File
It will transform the tree in an json document

```c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorldOne.c"


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

```


```c

#include "doTheWorldOne.c"

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

```

If you want to recuperate the file you saved in the json file
you can load it

```c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorldOne.c"

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

```


```c
//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorldOne.c"

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

```
