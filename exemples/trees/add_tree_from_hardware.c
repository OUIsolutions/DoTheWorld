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
                    .hadware_data=DTW_INCLUDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    tree->represent(tree);
    tree->free(tree);
}