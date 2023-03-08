#include "doTheWorld.c"
int main(int argc, char *argv[]){
  char *teste;
  strcpy(teste,"exemple");
  struct DtwStringArray  *array = dtw_list_files_recursively(teste);
  dtw_represent_string_array(array);

}