

#include "../../doTheWorld.c"

int main(int argc, char *argv[]){
 
  const char *path = "../exemple_folder/deer.jpg";
  int size;
  //load a binary file content
  unsigned char *content = dtw_load_binary_content(path,&size);
  if(content == NULL){
    printf("error oppening %s\n",path);
    return 1;
  }
  printf("size: %d\n",size);
  printf("content: %s\n",content);
  free(content);
  return 0;
}