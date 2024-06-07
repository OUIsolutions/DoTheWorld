

#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

  DtwStringArray *dirs = dtw.list_dirs("tests/target", DTW_NOT_CONCAT_PATH);
  //the represent methold will print the dirs in the console
  dtw.string_array.sort(dirs);
  dtw.string_array.represent(dirs);
  dtw.string_array.free(dirs);
  return 0;
}