// Created by jurandi on 20-06-2023.//
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
    DtwTree_loads_json_tree_from_file(tree,"tests/target/out.json");
    DtwTree_represent(tree);
    DtwTree_free(tree);
}