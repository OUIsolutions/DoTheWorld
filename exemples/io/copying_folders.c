

#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();
    dtw.copy_any("testargsub_folder","testargsub_folder2",DTW_NOT_MERGE);
  return 0;
}