
#include "doTheWorld.h"

int main(int argc, char *argv[]){

  DtwStringArray *files = dtw_list_dirs_recursively("tests/target/",DTW_CONCAT_PATH);
  files->represent(files);
  files->free(files);
  return 0;
}