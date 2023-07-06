
#include "../../../doTheWorld_test.h"

int main(int argc, char *argv[]){
  //load a string file content
  const char *path = "tests/target/a.txt";
  char *content = dtw_load_string_file_content(path);
  if(content == NULL){
    printf("error oppening %s\n",path);
    return 1;
  }
  printf("content: %s\n",content);
  free(content);
  return 0;
  
}