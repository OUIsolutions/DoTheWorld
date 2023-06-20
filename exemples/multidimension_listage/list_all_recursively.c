
#include "../../doTheWorld_test.h"

int main(int argc, char *argv[]){

  struct DtwStringArray *files = dtw_list_all_recursively("exemple_folder");
  files->represent(files);
  files->free(files);
  return 0;
}