

#include "../../doTheWorld.h"

int main(int argc, char *argv[]){
  //| if you set merge to true,
  //| the content of the folder will be merged 
  //| with the content of the destination folder
  bool merge = false;
  dtw_copy_any("exemple_folder","exemple_folder_copy",merge);
  return 0;
}