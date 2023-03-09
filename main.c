#include "code/doTheWorldDevUsage.c"

int main(int argc, char *argv[]){
  unsigned char *content = dtw_load_file_content("build.py");
  printf("%s",content);
  dtw_create_file_recursively("deer2",content);
  free(content);
  
}