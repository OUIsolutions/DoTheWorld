
#include "code/doTheWorldSeparated.h"

int main(int argc, char *argv[]){

    struct DtwTreePart *tree = dtw_tree_part_constructor("README.md",true);
    tree->set_string_content(tree,"Salve");
    //tree->free_content(tree);
    tree->represent(tree);
    tree->delete(tree);
}
