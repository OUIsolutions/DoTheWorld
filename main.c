
#include "code/doTheWorldDevUsage.c"

int main(int argc, char *argv[]){
   struct DtwTreePart *tree = dtw_create_tree_part("README.md",true);
   dtw_set_tree_part_string_content(tree, "Hello World!sss", 0);
   dtw_implement_tree_part(tree);
   dtw_represent_tree_part(tree);
}
