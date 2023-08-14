
#include "../../../doTheWorld_test.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

   char *hash = dtw.generate_sha_from_file("tests/target/blob.png");
   printf("SHA: %s", hash);
   free(hash);
}