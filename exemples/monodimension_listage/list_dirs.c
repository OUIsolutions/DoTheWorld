

#include "../../doTheWorld_test.h"

int main(int argc, char *argv[]){

  struct DtwStringArray *dirs = dtw_list_dirs("exemple_folder", DTW_NOT_CONCAT_PATH);
  //the represent methold will print the dirs in the console
  dirs->represent(dirs);
  return 0;
}