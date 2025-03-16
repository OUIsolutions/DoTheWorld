
#include "src/one.c"


int main(){

    int type = dtw_entity_type("teste.c");
   if(type == DTW_FILE_TYPE){
       printf("file\n");
   }
    if(type == DTW_FOLDER_TYPE){
         printf("folder\n");
    }
    if(type == DTW_NOT_FOUND){
         printf("null\n");
    }
}