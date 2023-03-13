

#include "../../doTheWorld.h"

int main(int argc, char *argv[]){
 
  const char *path = "writing_any.c";
  int size;
  //load a binary file content
  const char *content = dtw_load_binary_content(path,&size);
  if(content == NULL){
    printf("error oppening %s\n",path);
    return 1;
  }
  printf("size: %d\n",size);
  printf("content: %s\n",content);
}