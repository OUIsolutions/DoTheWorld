#include "../../../../release/doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    //load the beer image
  const char *blob_path = "tests/target/blob.png";
  long blob_size;
  unsigned char *content = dtw.load_binary_content(blob_path,&blob_size);
  //use these functions for binary files
  if(content == NULL){
    printf("error oppening %s\n",blob_path);
    return 1;
  }
  printf("size: %ld\n",blob_size);

  bool result = dtw.write_any_content("tests/target/blob2.png",content,blob_size);
  printf("result: %s\n",result ? "true" : "false");
free(content);
  return 0;
}
