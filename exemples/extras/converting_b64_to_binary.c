#include "doTheWorld.c"

int main(int argc, char *argv[]){
   //creating the b64 file
   const char *deer_path = "exemple_folder/deer.jpg";
   char *deerb64  = dtw_convert_binary_file_to_base64(deer_path);
   dtw_write_string_file_content("deer.txt", deerb64);
   free(deerb64);

   // loading and reconverting to binary 
    char *string_deer64 = dtw_load_string_file_content("deer.txt");
    int string_deer64_size = strlen(string_deer64);
    size_t out_size = 0;
    unsigned char *deer = dtw_base64_decode(string_deer64, string_deer64_size, &out_size);
    dtw_write_any_content("deer2.jpg", deer, out_size);
}