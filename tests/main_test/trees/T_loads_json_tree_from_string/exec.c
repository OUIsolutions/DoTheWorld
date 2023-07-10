//
// Created by jurandi on 20-06-2023.
//
#include "../../../doTheWorld_test.h"

char *dumps_tree(){

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
    char *content = tree->dumps_json_tree(
            tree,
            &(DtwTreeProps){
                    .minification = DTW_MIMIFY,
                    .ignored_elements=DTW_HIDE,
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_INCLUDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    tree->free(tree);
    return content;
}
int main(){
    char * content = dumps_tree();
    DtwTree *tree = newDtwTree();
    tree->loads_json_tree(tree,content);
    tree->represent(tree);
    tree->free(tree);
    free(content);
}