
#include "../../doTheWorld_test.h"

int main(int argc, char *argv[]){



    //creating the b64 file
    const char *deer_path = "exemple_folder/deer.jpg";
    char *deerb64  = dtw_convert_binary_file_to_base64(deer_path);
    long output;
    unsigned char  *result = dtw_base64_decode(deerb64,&output);

    dtw_write_any_content("deer.jpg",result,output);

    free(result);
    free(deerb64);

    return 0;
}