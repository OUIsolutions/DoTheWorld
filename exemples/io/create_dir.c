

#include "../../doTheWorld.c"

int main(int argc, char *argv[]){

  //| it will create dirs recursively
  dtw_create_dir("exemple/a/b");
  dtw_create_dir("exemple/a/b/c");
  dtw_create_dir("exemple/a/c/");
  return 0;
}