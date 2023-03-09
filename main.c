#include "code/doTheWorldDevUsage.c"

int main(int argc, char *argv[]){
  
    dtw_write_file_recursively("teste.txt","teste",0);
   
   int size;
   bool is_binary;
   char *teste = dtw_load_file_content("teste.txt",&size,&is_binary);
   printf("%s",teste);
}