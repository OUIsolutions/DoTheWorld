//
// Created by jurandi on 20-06-2023.
//
#include "../../../doTheWorld_test.h"

bool filter_txt(struct DtwTreePart *part){
    DtwNamespace dtw = newDtwNamespace();

    char *extension = dtw.path.get_extension(part->path);
    if(!extension){
        return false;
    }
    if(strcmp(extension,"txt") == 0){
        free(extension);
        return true;
    }
    free(extension);
    return false;
}

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "tests/target",
            &(DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    DtwTree *filtered = dtw.tree.filter(
            tree,
            filter_txt
    );

    dtw.tree.represent(filtered);
    dtw.tree.free(filtered);
    dtw.tree.free(tree);
}