//
// Created by jurandi on 20-06-2023.
//
#include "../../doTheWorld_test.h"

void dumps_tree(){

    DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "exemple_folder",
            DTW_LOAD_CONTENT,
            DTW_LOAD_METADATA,
            DTW_PRESERVE_PATH_START
    );

    tree->dumps_json_tree_to_file(
            tree,
            "test.json",
            DTW_NOT_MINIFY,
            DTW_LOAD_METADATA,
            DTW_PRESERVE_PATH_ATRIBUTES,
            DTW_PRESERVE_HARDWARE_DATA,
            DTW_PRESERVE_CONTENT_DATA,
            DTW_CONSIDER_IGNORE
    );

    tree->free(tree);
}
int main(){
    dumps_tree();
    DtwTree *tree = newDtwTree();
    tree->loads_json_tree_from_file(tree,"test.json");
    tree->represent(tree);
    tree->free(tree);
}