#include "../../../../release/doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    const char *path = "tests/target/blob.png";
  long size;
  bool is_binary;
  //load any file, is useful if you don't know if the file is binary or not
  unsigned char *content = dtw.load_any_content(path,&size,&is_binary);
  if(content == NULL){
    printf("error oppening %s\n",path);
    return 1;
  }
  printf("size: %ld\n",size);
  printf("is_binary: %s\n",is_binary ? "true" : "false");

  dtw.write_any_content("tests/target/blob2.png",content,size);
  free(content);
  return 0;
}
