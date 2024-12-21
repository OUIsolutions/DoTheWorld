// Created by jurandi on 20-06-2023/
#include "doTheWorld.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "testarg",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    DtwTreePart *element = dtw.tree.find_tree_part_by_path(
            tree,
            "testargsub_foldsub_element.txt"
    );
    if(element){
        dtw.tree.part.represent(element);
    }
    dtw.tree.free(tree);
}
