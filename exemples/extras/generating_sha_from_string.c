
#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    const char *test = "Hello World!";
   char *hash = dtw.generate_sha_from_string(test);
   printf("SHA: %s", hash);
   free(hash);
   
}