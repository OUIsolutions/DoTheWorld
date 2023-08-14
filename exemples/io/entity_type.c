

#include "doTheWorld.h"


void print_entity(const char *name , int type){

 if(type == DTW_FOLDER_TYPE){
      printf("%s is an folder\n",name);
    }
    if(type == DTW_FILE_TYPE){
      printf("%s is an file\n",name);
    }
    if(type == DTW_NOT_FOUND){
      printf("%s not exist\n",name);
    }

}

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    //| entity_type return the type of the entity
    //| it can be:
    //| dtw.FILE = 1
    //| dtw.FOLDER = 2
    //| dtw.NOT_FOUND = -1
    short type;
    const char *not_exist = "asasasas";
    type = dtw.entity_type(not_exist);
    print_entity(not_exist,type);

    const char *folder = "tests/target/";
    type = dtw.entity_type(folder);
    print_entity(folder,type);


    const char *file = "tests/target/a.txt";
    type = dtw.entity_type(file);
    print_entity(file,type);
    

    
  return 0;
}