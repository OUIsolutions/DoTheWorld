

#include "doTheWorld.c"

int main(int argc, char *argv[]){

   char *b64 = dtw_convert_binary_file_to_base64("LICENSE");
   printf("%s", b64);
   return 0;
}