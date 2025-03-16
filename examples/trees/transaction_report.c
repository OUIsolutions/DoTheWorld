//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorldOne.c"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
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

        char *extension = dtw.path.get_extension(part->path);
        if(!extension){
            continue;
        }
        printf("%s\n",extension);
        if(strcmp(extension,"txt") == 0){
            dtw.path.set_extension(part->path,"md");
            dtw.tree.part.hardware_modify(part,DTW_SET_AS_ACTION);

        }
    }
    DtwTreeTransactionReport *report = dtw.tree.create_report(tree);
    dtw.tree.transaction_report.represent(report);
    dtw.tree.transaction_report.free(report);
    dtw.tree.free(tree);
}
