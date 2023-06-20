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
    for(int i=0; i < tree->size;i++){
        struct DtwTreePart *part = tree->tree_parts[i];
        struct DtwPath *path = part->path;
        char *extension = path->get_extension(path);
        if(!extension){
            continue;
        }
        if(strcmp(extension,"txt") == 0){
            path->set_extension(path,"md");
            part->hardware_modify(part,DTW_SET_AS_ACTION);

        }
        free(extension);
    }

    tree->hardware_commit_tree(tree);
    tree->free(tree);
}