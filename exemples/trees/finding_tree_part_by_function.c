//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"

bool test_if_blob(struct DtwTreePart*part){
    DtwNamespace dtw = newDtwNamespace();

    char *name = dtw.path.get_full_name(part->path);
    if(!name){
        return false;
    }
    if(strcmp(name,"blob.png") == 0){
        free(name);
        return true;
    }
    free(name);
    return false;
};


int main(){
    DtwNamespace dtw = newDtwNamespace();

    struct DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "exemple_folder",
            &(DtwTreeProps){
                .content = DTW_INCLUDE,
                .hadware_data=DTW_HIDE,
                .path_atributes=DTW_INCLUDE
            }
    );


    struct DtwTreePart *blob = dtw.tree.find_tree_part_by_function(
            tree,
            test_if_blob
    );

    if(blob){
        dtw.tree.part.represent(blob);
    }
    dtw.tree.free(tree);

}