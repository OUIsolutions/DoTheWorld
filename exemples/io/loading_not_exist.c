
#include "doTheWorld.h"

int main(int argc, char *argv[]){
/load a string file content
    DtwNamespace dtw = newDtwNamespace();

    const char *path = "testargaaaaa";
  char *content = dtw.load_string_file_content(path);
  if(content == NULL){
    printf("error oppening %s\n",path);
    return 0;
  }
  printf("content: %s\n",content);
  free(content);
  return 0;
  
}