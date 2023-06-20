//
// Created by jurandi on 20-06-2023.
//
#include "../../doTheWorld_test.h"

bool test_if_deer(struct DtwTreePart*part){

    char *name = part->path->get_full_name(part->path);
    if(!name){
        return false;
    }
    if(strcmp(name,"deer.jpg") == 0){
        free(name);
        return true;
    }
    free(name);
    return false;
};


int main(){

    struct DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "exemple_folder",
            DTW_LOAD_CONTENT,
            DTW_LOAD_METADATA,
            DTW_PRESERVE_PATH_START
    );


    struct DtwTreePart *deer = tree->find_part_by_function(
            tree,
            test_if_deer
    );

    if(deer){
        deer->represent(deer);
    }
    tree->free(tree);

}