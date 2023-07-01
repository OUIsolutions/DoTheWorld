
#include "../../doTheWorld_test.h"

int main(){

    DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "exemple_folder",
           NULL
    );

    char *content = tree->dumps_json_tree(
            tree,
            NULL
    );
    printf("%s",content);
    free(content);
    tree->free(tree);
}