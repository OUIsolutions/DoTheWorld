
#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

   char *hash = dtw.generate_sha_from_file("testargblob.png");
   printf("SHA: %s", hash);
   free(hash);
}