//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"
int main(){

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
    for(int i = 0; i<tree->size;i++){
        DtwTreePart *current_part = tree->tree_parts[i];
        current_part->represent(current_part);
    }
    tree->free(tree);
}