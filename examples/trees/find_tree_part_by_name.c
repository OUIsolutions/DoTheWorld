//
// Created by jurandi on 20-06-2023.
//


#include "doTheWorld.h"

int main(){
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

    DtwTreePart *blob = dtw.tree.find_tree_part_by_name(tree,"blob.png");
    if(blob){
        dtw.tree.part.represent(blob);
    }
    dtw.tree.free(tree);

}
