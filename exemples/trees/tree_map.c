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
                    .hadware_data=DTW_INCLUDE,
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