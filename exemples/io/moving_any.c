

#include "../../doTheWorld.c"

int main(int argc, char *argv[]){
  //| if you set merge to true,
  //| the content of the folder will be merged 
  //| with the content of the destination folder
  bool merge = false;
  dtw_move_any("../exemple_folder","exemple_folder_copy",merge);
  
  //| you can use move_any to move a file
  dtw_move_any("exemple_folder_copy/deer.jpg","deer.jpg",false);

  return 0;
}