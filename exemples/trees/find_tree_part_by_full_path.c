//
// Created by jurandi on 20-06-2023.
//
#include "../../doTheWorld_test.h"

int main(){

    DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "exemple_folder",
            DTW_LOAD_CONTENT,
            DTW_LOAD_METADATA,
            DTW_PRESERVE_PATH_START
    );

    DtwTreePart *deer = tree->find_part_by_path(
            tree,
            "exemple_folder/deer.jpg"
    );
    if(deer){
        deer->represent(deer);
    }
    tree->free(tree);
}
~~~