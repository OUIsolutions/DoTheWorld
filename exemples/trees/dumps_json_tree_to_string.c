
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

    char *content = tree->dumps_json_tree(
            tree,
            DTW_NOT_MINIFY,
            DTW_LOAD_METADATA,
            DTW_PRESERVE_PATH_ATRIBUTES,
            DTW_PRESERVE_HARDWARE_DATA,
            DTW_PRESERVE_CONTENT_DATA,
            DTW_CONSIDER_IGNORE
    );
    printf("%s",content);
    tree->free(tree);
}