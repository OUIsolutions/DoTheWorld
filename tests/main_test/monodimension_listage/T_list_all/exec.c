


#include "../../../doTheWorld_test.h"

int main(int argc, char *argv[]){

  DtwStringArray *all = dtw_list_all("tests/target/",DTW_CONCAT_PATH);
  all->sort(all);
  all->represent(all);
  all->free(all);
  return 0;
}