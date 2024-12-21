//
// Created by jurandi on 20-06-2023.
//
#include "../../../../release/doTheWorld.h"

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
