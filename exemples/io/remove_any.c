

#include "../../doTheWorld.h"

int main(int argc, char *argv[]){
  //| remove any will delete anything you passs to it

  //| if you pass a file, it will delete it
  dtw_remove_any("../exemple_folder/deer.jpg");

  //| if you pass a folder, it will delete it
  dtw_remove_any("../exemple_folder/a");
  return 0;
}