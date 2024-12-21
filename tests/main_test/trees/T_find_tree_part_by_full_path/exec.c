//
// Created by jurandi on 20-06-2023.
//
#include "../../../../release/doTheWorld.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "tests/target/",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    DtwTreePart *element = dtw.tree.find_tree_part_by_path(
            tree,
            "tests/target/sub_folder/sub_element.txt"
    );
    if(element){
        dtw.tree.part.represent(element);
    }
    dtw.tree.free(tree);
}
