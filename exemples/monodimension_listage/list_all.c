


#include "../../doTheWorld_test.h"

int main(int argc, char *argv[]){

  DtwStringArray *all = dtw_list_all("exemple_folder",DTW_CONCAT_PATH);
  all->represent(all);
  all->free(all);
  return 0;
}