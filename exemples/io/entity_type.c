

#include "../../doTheWorld.h"

int main(int argc, char *argv[]){
  
  //| entity_type return the type of the entity
  //| it can be:
  //| DTW_FILE = 1
  //| DTW_FOLDER = 2
  //| DTW_NOT_FOUND = -1
  const char *not_exist = "not_exist";
  short type = dtw_entity_type(not_exist);
  printf("%s is a %i\n",not_exist,type);

  const char *file = "../exemple_folder/deer.jpg";
  type = dtw_entity_type(file);
  printf("%s is a %i\n",file,type);

  const char *folder = "../exemple_folder";
  type = dtw_entity_type(folder);
  printf("%s is a %i\n",folder,type);

  

  return 0;
}