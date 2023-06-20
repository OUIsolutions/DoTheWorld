//
// Created by jurandi on 20-06-2023.
//
#include "../../doTheWorld_test.h"
int main(){

    struct DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "exemple_folder",
            DTW_LOAD_CONTENT,
            DTW_LOAD_METADATA,
            DTW_PRESERVE_PATH_START
    );
    for(int i = 0; i<tree->size;i++){
        struct DtwTreePart *current_part = tree->tree_parts[i];
        current_part->represent(current_part);
    }
    tree->free(tree);
}