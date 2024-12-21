
#include "doTheWorld.h"

int main(int argc, char *argv[]){


    DtwNamespace dtw = newDtwNamespace();

  /creating the b64 file
    const char *blob_path = "testargblob.png";
    char *blob  = dtw.convert_binary_file_to_base64(blob_path);
     long output;
    unsigned char  *result = dtw.base64_decode(blob,&output);

    dtw.write_any_content("testargblob2.png",result,output);

    free(result);
    free(blob);

    return 0;
}