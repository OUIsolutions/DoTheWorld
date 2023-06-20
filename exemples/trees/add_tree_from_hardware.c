//
// Created by jurandi on 20-06-2023.
//
#include "../../doTheWorld_test.h"


int main(){

    DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "exemple_folder",
            DTW_LOAD_CONTENT,
            DTW_LOAD_METADATA,
            DTW_PRESERVE_PATH_START
    );
    tree->represent(tree);
    tree->free(tree);
}