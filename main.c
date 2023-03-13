
#include "code/doTheWorldSeparated.h"

int main(int argc, char *argv[]){

    struct DtwTreePart *tree = dtw_tree_part_constructor("README.md",false);
    tree->set_string_content(tree,"Hello World!");
    tree->represent(tree);

}
