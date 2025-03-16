//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorldOne.c"


bool test_if_blob(struct DtwTreePart*part,void *args){
    DtwNamespace dtw = newDtwNamespace();

    char *name = dtw.path.get_full_name(part->path);
    if(!name){
        return false;
    }

    if(strcmp(name,"blob.png") == 0){
        return true;
    }
    return false;
};


int main(){
    DtwNamespace dtw = newDtwNamespace();

    struct DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                .content = DTW_INCLUDE,
                .hadware_data=DTW_HIDE,
                .path_atributes=DTW_INCLUDE
            }
    );


    struct DtwTreePart *blob = dtw.tree.find_tree_part_by_function(
            tree,
            test_if_blob,
            NULL
    );

    dtw.tree.part.represent(blob);

    dtw.tree.free(tree);

}
