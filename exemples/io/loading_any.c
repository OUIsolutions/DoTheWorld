

#include "../../doTheWorld.h"

int main(int argc, char *argv[]){
 
  const char *path = "exemple_folder/deer.jpg";
  int size;
  bool is_binary;
  //load any file, is useful if you don't know if the file is binary or not
  const char *content = dtw_load_any_content(path,&size,&is_binary);
  if(content == NULL){
    printf("error oppening %s\n",path);
    return 1;
  }
  printf("size: %d\n",size);
  printf("is_binary: %s\n",is_binary ? "true" : "false");
  printf("content: %s\n",content);
  return 0;
}