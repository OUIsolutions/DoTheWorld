
## Dealing with base64
You can easly transform an binary file to an base64 string like these

```c

#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    const char *deer_path = "tests/target/blob.png";
   char *deerb64  = dtw.convert_binary_file_to_base64(deer_path);
   printf("blob: %s", deerb64);
    free(deerb64);
}

```

You also can reconvert an base64 string to binary

```c

#include "doTheWorldOne.c"

int main(int argc, char *argv[]){


    DtwNamespace dtw = newDtwNamespace();

    //creating the b64 file
    const char *blob_path = "tests/target/blob.png";
    char *blob  = dtw.convert_binary_file_to_base64(blob_path);
     long output;
    unsigned char  *result = dtw.base64_decode(blob,&output);

    dtw.write_any_content("tests/target/blob2.png",result,output);

    free(result);
    free(blob);

    return 0;
}

```

