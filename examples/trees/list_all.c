#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    DtwTree *tree = newDtwTree();
    DtwTree_add_tree_from_hardware(
            tree,
            "tests/target/",
            (DtwTreeProps){
                    .content = DTW_HIDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    DtwStringArray *files = DtwTree_list_all(tree, "tests/target/sub_folder", DTW_NOT_CONCAT_PATH);
    DtwStringArray_sort(files);
    DtwStringArray_represent(files);
    DtwStringArray_free(files);
    DtwTree_free(tree);
    return 0;
}