//
// Created by jurandi on 20-06-2023.
//
#include "../../doTheWorld_test.h"

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
            "exemple_folder",
            DTW_LOAD_CONTENT,
            DTW_LOAD_METADATA,
            DTW_PRESERVE_PATH_START
    );
    DtwTree *filtered = tree->filter(
            tree,
            filter_txt
    );

    filtered->represent(filtered);
    filtered->free(filtered);
    tree->free(tree);
}