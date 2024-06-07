

#include "../../../doTheWorld_test.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();
    dtw.copy_any("tests/target/sub_folder","tests/target/sub_folde42",DTW_NOT_MERGE);
  return 0;
}