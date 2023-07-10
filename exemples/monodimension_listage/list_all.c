


#include "doTheWorld.h"

int main(int argc, char *argv[]){

  DtwStringArray *all = dtw_list_all("tests/target/",DTW_CONCAT_PATH);
  all->represent(all);
  all->free(all);
  return 0;
}