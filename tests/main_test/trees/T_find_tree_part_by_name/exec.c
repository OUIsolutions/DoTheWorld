//
// Created by jurandi on 20-06-2023.
//


#include "../../../doTheWorld_test.h"

int main(){

    DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "exemple_folder",
            &(DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_INCLUDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    DtwTreePart *deer = tree->find_part_by_name(tree,"deer.jpg");
    if(deer){
        deer->represent(deer);
    }
    tree->free(tree);

}