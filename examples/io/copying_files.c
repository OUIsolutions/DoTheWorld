#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
  dtw_copy_any("tests/target/blob.png","tests/target/blob3.png",DTW_NOT_MERGE);
  return 0;
}