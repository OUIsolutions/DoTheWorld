#include "code/doTheWorldDevUsage.c"

int main(int argc, char *argv[]){
  struct DtwTreePart *tree = dtw_create_tree_part("README.md",true);
  dtw_represent_tree_part(tree);
  dtw_free_tree_part(tree);
  
}