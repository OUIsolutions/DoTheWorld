
#include "../../../doTheWorld_test.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    const char *path = "tests/target/blob.png";
  long size;
  //load a binary file content
  unsigned char *content = dtw.load_binary_content(path,&size);
  if(content == NULL){
    printf("error oppening %s\n",path);
    return 1;
  }
  printf("size: %ld\n",size);
  dtw.write_any_content("tests/target/blob2.png",content,size);
  free(content);
  return 0;
}