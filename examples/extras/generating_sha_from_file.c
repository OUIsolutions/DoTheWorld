#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
   char *hash = dtw_generate_sha_from_file("tests/target/blob.png");
   printf("SHA: %s", hash);
   free(hash);
}