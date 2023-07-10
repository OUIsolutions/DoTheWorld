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
                    .hadware_data=DTW_INCLUDE,
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
                    .hadware_data=DTW_INCLUDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    tree->free(tree);
}