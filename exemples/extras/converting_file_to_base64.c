
#include "doTheWorld.c"

int main(int argc, char *argv[]){
   const char *deer_path = "exemple_folder/deer.jpg";
   char *deerb64  = dtw_convert_binary_file_to_base64(deer_path);
   printf("deer: %s", deerb64);
    free(deerb64);
}