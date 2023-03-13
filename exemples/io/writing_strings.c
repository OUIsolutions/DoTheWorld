
#include "../../doTheWorld.h"

int main(int argc, char *argv[]){
  // Write a string to a file the path is auto created
  
  bool result = dtw_write_string_file_content("../exemple_folder/test.txt","Hello World!");
  printf("result: %s\n",result ? "true" : "false");
  return 0;
}
