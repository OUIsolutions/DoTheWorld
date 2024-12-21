//
// Created by jurandi on 20-06-2023.
//
#include "../../../../release/doTheWorld.h"

DtwTreePart * concat_test(struct DtwTreePart *part){
    DtwNamespace dtw = newDtwNamespace();

    if(part->content && part->is_binary == false){
        char *content = dtw.tree.part.get_content_string_by_reference(part);
        const char *mensage = " test";
        char *new_content = (char*)malloc(strlen(content) + strlen(mensage)+ 2);
        strcpy(new_content,content);
        strcat(new_content,mensage);
        dtw.tree.part.set_string_content(part,new_content);
        free(new_content);
    }
    return part;
}

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    DtwTree *concated = dtw.tree.map(
            tree,
            concat_test
    );

    dtw.tree.represent(concated);
    dtw.tree.free(concated);
    dtw.tree.free(tree);
}
