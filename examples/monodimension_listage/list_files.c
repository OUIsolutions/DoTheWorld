
#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

  DtwStringArray *files = dtw.list_files("tests/target", DTW_CONCAT_PATH);
  dtw.string_array.sort(files);

  for(int i = 0; i < files->size; i++){
    printf("%s\n", files->strings[i]);
  }
  dtw.string_array.free(files);
  return 0;
}
