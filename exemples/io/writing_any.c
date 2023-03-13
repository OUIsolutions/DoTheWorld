
#include "../../doTheWorld.h"

int main(int argc, char *argv[]){
  int size = 12;
  //use these functions for binary files
  bool result = dtw_write_any_content("teste/test.txt","Hello World!",size);
  printf("result: %s\n",result ? "true" : "false");
  return 0;
}
