
#include "../../../doTheWorld_test.h"

int main(int argc, char *argv[]){

  DtwStringArray *files = dtw_list_files("tests/target", DTW_CONCAT_PATH);
  files->sort(files);

  for(int i = 0; i < files->size; i++){
    printf("%s\n", files->strings[i]);
  }
  files->free(files);
  return 0;
}