
#include "doTheWorld/doTheWorldMain.h"

int main(int argc, char *argv[]){
 
  DtwPath *path = newDtwPath("teste.txt");
  path->add_start_dir(path,"test");
  path->represent(path);
  path->free(path);
  return 0;
}