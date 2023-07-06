
#include "../../doTheWorld_test.h"

int main(int argc, char *argv[]){
 
  const char *path = "exemple_folder/deer.jpg";
  long size;
  //load a binary file content
  unsigned char *content = dtw_load_binary_content(path,&size);
  if(content == NULL){
    printf("error oppening %s\n",path);
    return 1;
  }
  printf("size: %ld\n",size);
  free(content);
  return 0;
}