
#include "../../doTheWorld.h"

int main(int argc, char *argv[]){
  int size = 12;
  const char *content = "Hello World!";
  //use these functions for binary files
  bool result = dtw_write_any_content("teste/test.txt",content,size);
  printf("result: %s\n",result ? "true" : "false");
}
