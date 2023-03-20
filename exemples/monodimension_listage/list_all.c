


#include "doTheWorld.c"

int main(int argc, char *argv[]){

  struct DtwStringArray *all = dtw_list_all("exemple_folder",DTW_CONCAT_PATH);
  all->represent(all);
  return 0;
}