
#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    const char *deer_path = "testargblob.png";
   char *deerb64  = dtw.convert_binary_file_to_base64(deer_path);
   printf("blob: %s", deerb64);
    free(deerb64);
}