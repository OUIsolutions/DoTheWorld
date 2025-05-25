// Created by jurandi on 20-06-2023.//
#include "doTheWorldOne.c"
int main(){
    DtwTree *tree = newDtwTree();  // Direct call to newDtwTree
    DtwTree_add_tree_from_hardware(  // Direct call to DtwTree_add_tree_from_hardware
            tree,
            "tests/target",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    for(int i = 0; i<tree->size;i++){
        DtwTreePart *current_part = tree->tree_parts[i];
        DtwTreePart_represent(current_part);  // Direct call to DtwTreePart_represent
    }
    DtwTree_free(tree);  // Direct call to DtwTree_free
    return 0;  // Added for completeness, as main should return an int
}