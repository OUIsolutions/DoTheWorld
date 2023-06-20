
#include "../../doTheWorld_test.h"

int main(int argc, char *argv[]){

  struct DtwStringArray *files = dtw_list_files("exemple_folder", DTW_CONCAT_PATH);
  for(int i = 0; i < files->size; i++){
    printf("%s\n", files->strings[i]);
  }
  files->free(files);
  return 0;
}