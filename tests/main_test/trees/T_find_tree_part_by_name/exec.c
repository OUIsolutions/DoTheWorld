//
// Created by jurandi on 20-06-2023.
//


#include "../../../doTheWorld_test.h"

int main(){

    DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "tests/target",
            &(DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    DtwTreePart *blob = tree->find_part_by_name(tree,"blob.png");
    if(blob){
        blob->represent(blob);
    }
    tree->free(tree);

}