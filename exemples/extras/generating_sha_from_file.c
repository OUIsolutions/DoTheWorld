
#include "doTheWorld.c"

int main(int argc, char *argv[]){

   char *hash = dtw_generate_sha_from_file("README.md");
   printf("SHA: %s", hash);
   free(hash);
}