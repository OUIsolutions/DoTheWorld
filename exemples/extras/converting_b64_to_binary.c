
#include "doTheWorld.h"

int main(int argc, char *argv[]){



    //creating the b64 file
    const char *blob_path = "tests/target/blob.png";
    char *blob  = dtw_convert_binary_file_to_base64(blob_path);
    unsigned long output;
    unsigned char  *result = dtw_base64_decode(blob,&output);

    dtw_write_any_content("tests/target/blob2.png",result,output);

    free(result);
    free(blob);

    return 0;
}