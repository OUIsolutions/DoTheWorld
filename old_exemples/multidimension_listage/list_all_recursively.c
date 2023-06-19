
#include "doTheWorld.c"

int main(int argc, char *argv[]){

  struct DtwStringArray *files = dtw_list_all_recursively("exemple_folder");
  files->represent(files);
  return 0;
}