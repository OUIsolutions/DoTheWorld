


#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

  DtwStringArray *all = dtw.list_all("tests/target/",DTW_CONCAT_PATH);
  dtw.string_array.sort(all);
  dtw.string_array.represent(all);
  dtw.string_array.free(all);
  return 0;
}
