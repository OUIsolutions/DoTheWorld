

#include "doTheWorld.h"

int main(int argc, char *argv[]){
  DtwNamespace dtw = newDtwNamespace();
  dtw.copy_any("testargblob.png","testargblob3.png",DTW_NOT_MERGE);
  return 0;
}