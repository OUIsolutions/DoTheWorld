
#include "../../doTheWorld_test.h"

int main(int argc, char *argv[]){

  struct DtwStringArray *files = dtw_list_dirs_recursively("exemple_folder");
  files->represent(files);
  return 0;
}