

#include "doTheWorld.h"

int main(int argc, char *argv[]){

  DtwStringArray *dirs = dtw_list_dirs("tests/target", DTW_NOT_CONCAT_PATH);
  //the represent methold will print the dirs in the console
  dirs->represent(dirs);
  dirs->free(dirs);
  return 0;
}