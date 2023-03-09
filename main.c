#include "doTheWorldDevUsage.c"
int main(int argc, char *argv[]){
  //struct DtwTree *tree = dtw_create_tree("README.md",true);
  //dtw_represent_tree(tree);
  //dtw_free_tree(tree);

  char *teste = dtw_load_file_content("build.py");
  printf("%s",teste);
  free(teste);
}