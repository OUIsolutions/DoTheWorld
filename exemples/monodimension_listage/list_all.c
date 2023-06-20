


#include "../../doTheWorld_test.h"

int main(int argc, char *argv[]){

  DtwStringArray *all = dtw_list_all("exemple_folder",DTW_CONCAT_PATH);
  all->represent(all);
  return 0;
}