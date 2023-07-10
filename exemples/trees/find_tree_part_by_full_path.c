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
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    DtwTreePart *element = tree->find_part_by_path(
            tree,
            "tests/target/sub_folder/sub_element.txt"
    );
    if(element){
        element->represent(element);
    }
    tree->free(tree);
}
