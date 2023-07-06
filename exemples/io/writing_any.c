#include "../../doTheWorld_test.h"

int main(int argc, char *argv[]){
  //load the beer image
  const char *deer_path = "exemple_folder/deer.jpg";
  long deer_size;
  unsigned char *content = dtw_load_binary_content(deer_path,&deer_size);
  //use these functions for binary files
  if(content == NULL){
    printf("error oppening %s\n",deer_path);
    return 1;
  }
  printf("size: %ld\n",deer_size);

  bool result = dtw_write_any_content("output_folder/deer.jpg",content,deer_size);
  printf("result: %s\n",result ? "true" : "false");
  free(content);
  return 0;
}