#include "../../doTheWorld_test.h"

int main(int argc, char *argv[]){
   //creating the b64 file
   const char *deer_path = "exemple_folder/deer.jpg";
   char *deerb64  = dtw_convert_binary_file_to_base64(deer_path);
   dtw_write_string_file_content("deer.txt", deerb64);
   free(deerb64);

}