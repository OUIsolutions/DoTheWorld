//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"

char *dumps_tree(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_INCLUDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    char *content = dtw.tree.dumps_json_tree(
            tree,
            (DtwTreeProps){
                    .minification = DTW_MIMIFY,
                    .ignored_elements=DTW_HIDE,
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    dtw.tree.free(tree);
    return content;
}
int main(){
    DtwNamespace dtw = newDtwNamespace();

    char * content = dumps_tree();
    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.loads_json_tree(tree,content);
    dtw.tree.represent(tree);
    dtw.tree.free(tree);
    free(content);
}
