// Created by jurandi on 20-06-2023.//
#include "doTheWorldOne.c"

int main(){
    DtwTree *tree = newDtwTree();
    add_tree_from_hardware(
            tree,
            "tests/target/",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    DtwTreePart *element = find_tree_part_by_path(
            tree,
            "tests/target/sub_folder/sub_element.txt"
    );
    if(element){
        represent(element);
    }
    DtwTree_free(tree);
}