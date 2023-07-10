//
// Created by jurandi on 20-06-2023.
//
#include "../../../doTheWorld_test.h"

void dumps_tree(){

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

    tree->dumps_json_tree_to_file(
            tree,
            "tests/target/out.json",
            &(DtwTreeProps){
                    .minification = DTW_MIMIFY,
                    .ignored_elements=DTW_HIDE,
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_INCLUDE,
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