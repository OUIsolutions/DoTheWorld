

#include "../../../doTheWorld_test.h"


int main(int argc, char *argv[]){

  DtwStringArray *listage = dtw_list_files("tests/target",DTW_CONCAT_PATH);
  listage->represent(listage);
  listage->free(listage);
  return 0;
}