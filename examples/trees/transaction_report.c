// Created by jurandi on 20-06-2023.//
#include "doTheWorldOne.c"

int main(){
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_INCLUDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    for(int i=0; i < tree->size;i++){
        DtwTreePart *part = tree->tree_parts[i];

        char *extension = DtwPath_get_extension(part->path);
        if(!extension){
            continue;
        }
        printf("%s\n",extension);
        if(strcmp(extension,"txt") == 0){
            DtwPath_set_extension(part->path,"md");
            DtwTreePart_hardware_modify(part,DTW_SET_AS_ACTION);

        }
    }
    DtwTreeTransactionReport *report = DtwTree_create_report(tree);
    DtwTreeTransactionReport_represent(report);
    DtwTreeTransactionReport_free(report);
    DtwTree_free(tree);
}