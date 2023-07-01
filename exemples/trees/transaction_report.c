//
// Created by jurandi on 20-06-2023.
//
#include "../../doTheWorld_test.h"

int main(){

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
    for(int i=0; i < tree->size;i++){
        DtwTreePart *part = tree->tree_parts[i];
        DtwPath *path = part->path;
        char *extension = path->get_extension(path);
        if(!extension){
            continue;
        }
        printf("%s\n",extension);
        if(strcmp(extension,"txt") == 0){
            path->set_extension(path,"md");
            part->hardware_modify(part,DTW_SET_AS_ACTION);

        }
        free(extension);
    }
    DtwTransactionReport *report = tree->report(tree);
    report->represent(report);
    report->free(report);
    tree->free(tree);
}