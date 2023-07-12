
#include "../../../doTheWorld_test.h"

int main(){

    DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "tests/target/",
            &(DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );

    char *content = tree->dumps_json_tree(
            tree,
            &(DtwTreeProps){
                    .minification = DTW_NOT_MIMIFY,
                    .ignored_elements=DTW_HIDE,
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
    printf("%s",content);
    free(content);
    tree->free(tree);
}