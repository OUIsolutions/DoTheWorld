// Created by jurandi on 20-06-2023.//
#include "doTheWorldOne.c"

bool test_if_blob(struct DtwTreePart*part, void *args){
    char *name = DtwPath_get_full_name(part->path);  // Replaced dtw.path.get_full_name
    if(!name){
        return false;
    }
    if(strcmp(name,"blob.png") == 0){
        return true;
    }
    return false;
};

int main(){
    DtwNamespace dtw = newDtwNamespace();  // Retained, but not used in modified calls

    struct DtwTree *tree = newDtwTree();  // Replaced dtw.tree.newTree
    DtwTree_add_tree_from_hardware(  // Replaced dtw.tree.add_tree_from_hardware
            tree,
            "tests/target",
            (DtwTreeProps){
                .content = DTW_INCLUDE,
                .hadware_data=DTW_HIDE,
                .path_atributes=DTW_INCLUDE
            }
    );

    struct DtwTreePart *blob = DtwTree_find_tree_part_by_function(  // Replaced dtw.tree.find_tree_part_by_function
            tree,
            test_if_blob,
            NULL
    );

    DtwTreePart_represent(blob);  // Replaced dtw.tree.part.represent

    DtwTree_free(tree);  // Replaced dtw.tree.free
}