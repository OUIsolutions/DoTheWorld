//
// Created by jurandi on 20-06-2023.
//
#include "../../../doTheWorld_test.h"
int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "tests/target",
            &(DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    for(int i = 0; i<tree->size;i++){
        DtwTreePart *current_part = tree->tree_parts[i];
        dtw.tree.part.represent(current_part);
    }
    dtw.tree.free(tree);
}