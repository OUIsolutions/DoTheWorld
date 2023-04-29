Do The World

DoTheWorld is a Windows/Linux single file library designed to handle files in C/C++ in a number of ways, providing everything from simple functions for reading/writing files and folders, to complex functions like taking sha256 from files,decoding/enconding base64, checking modification dates. And functionalities of atomic writing of folders/files through transaction systems.

## Reading strings
~~~c
#include "doTheWorld.h"

int main(int argc, char *argv[]){
  //load a string file content
  const char *path = "exemple_folder/a/test.txt";
  char *content = dtw_load_string_file_content(path);
  if(content == NULL){
    printf("error oppening %s\n",path);
    return 1;
  }
  printf("content: %s\n",content);
  free(content);
  return 0;
}
~~~

## Writing strings
~~~c
#include "doTheWorld.h"
int main(int argc, char *argv[]){
  // Write a string to a file the path is auto created
  
  bool result = dtw_write_string_file_content("test/a/test.txt","Hello World!");
  printf("result: %s\n",result ? "true" : "false");
  return 0;
}
~~~

## Listing All Recursively

~~~c

#include "doTheWorld.h"

int main(int argc, char *argv[]){

  struct DtwStringArray *files = dtw_list_all_recursively(
    "exemple_folder",
    DTW_CONCAT_PATH
    );
    
  files->represent(files);
  files->free_string_array(files);
  return 0;
}
~~~
