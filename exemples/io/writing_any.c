
#include "../../doTheWorld.h"

int main(int argc, char *argv[]){

  //load the beer image
  int deer_size;
  char *deer_content = dtw_load_binary_content("../exemple_folder/deer.jpg",&deer_size);
  //use these functions for binary files
  printf("size: %d\n",deer_size);

  bool result = dtw_write_any_content("exemple/deer.jpg",deer_content,deer_size);
  printf("result: %s\n",result ? "true" : "false");
  return 0;
}
