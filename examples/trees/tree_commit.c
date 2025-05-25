#include "doTheWorldOne.c"

int main(){
    DtwNamespace dtw = newDtwNamespace();  // Retain as it's the initializer

    DtwTree *tree = newDtwTree();  // Replace dtw.tree.newTree() with global function
    DtwTree_add_tree_from_hardware(  // Replace dtw.tree.add_tree_from_hardware
            tree,
            "tests/target",
            (DtwTreeProps){
                .content = DTW_INCLUDE,
                .hadware_data=DTW_HIDE,
                .path_atributes=DTW_INCLUDE
            }
    );

    for(int i=0; i < tree->size;i++){
        struct DtwTreePart *part = tree->tree_parts[i];

        char *extension = DtwPath_get_extension(part->path);  // Replace dtw.path.get_extension
        if(!extension){
            continue;
        }
        if(strcmp(extension,"txt") == 0){
            DtwPath_set_extension(part->path,"md");  // Replace dtw.path.set_extension
            DtwTreePart_hardware_modify(part,DTW_SET_AS_ACTION);  // Replace dtw.tree.part.hardware_modify
        }
    }

    DtwTree_hardware_commit_tree(tree);  // Replace dtw.tree.hardware_commit_tree
    DtwTree_free(tree);  // Replace dtw.tree.free
}