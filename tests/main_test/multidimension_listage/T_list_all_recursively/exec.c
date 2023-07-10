
#include "../../../doTheWorld_test.h"

int main(int argc, char *argv[]){

  DtwStringArray *files = dtw_list_all_recursively("exemple_folder",DTW_CONCAT_PATH);
  files->represent(files);
  files->free(files);
  return 0;
}