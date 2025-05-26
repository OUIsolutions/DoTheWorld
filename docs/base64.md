## Dealing with base64
You can easily transform a binary file to a base64 string like this:

```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    const char *deer_path = "tests/target/blob.png";
    char *deerb64 = dtw_convert_binary_file_to_base64(deer_path);
    printf("blob: %s", deerb64);
    free(deerb64);
}
```

You can also reconvert a base64 string to binary:

```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    // Creating the b64 file
    const char *blob_path = "tests/target/blob.png";
    char *blob = dtw_convert_binary_file_to_base64(blob_path);
    long output;
    unsigned char *result = dtw_base64_decode(blob, &output);

    dtw_write_any_content("tests/target/blob2.png", result, output);

    free(result);
    free(blob);

    return 0;
}
```