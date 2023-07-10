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
                    .hadware_data=DTW_INCLUDE,
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