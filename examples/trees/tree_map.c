// Created by jurandi on 20-06-2023.//
#include "doTheWorldOne.c"

DtwTreePart * concat_test(struct DtwTreePart *part){
    if(part->content && part->is_binary == false){
        char *content = DtwTreePart_get_content_string_by_reference(part);
        const char *mensage = " test";
        char *new_content = (char*)malloc(strlen(content) + strlen(mensage)+ 2);
        strcpy(new_content,content);
        strcat(new_content,mensage);
        DtwTreePart_set_string_content(part,new_content);
        free(new_content);
    }
    return part;
}

int main(){
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
            tree,
            "tests/target",
            (DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    DtwTree *concated = DtwTree_map(
            tree,
            concat_test
    );

    DtwTree_represent(concated);
    DtwTree_free(concated);
    DtwTree_free(tree);
}