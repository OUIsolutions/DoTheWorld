
#include "doTheWorld.h"

int main(int argc, char *argv[]){
   const char *test = "Hello World!";
   char *hash = dtw_generate_sha_from_string(test);
   printf("SHA: %s", hash);
   free(hash);
   
}