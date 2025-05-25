#include "doTheWorldOne.c"

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

    DtwTreePart *blob = DtwTree_find_tree_part_by_name(tree, "blob.png");
    
    if(blob){
        DtwTreePart_represent(blob);
    }
    
    DtwTree_free(tree);
    
    return 0;
}