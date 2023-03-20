# DoTheWorld
DoTheWorld is a single file library designed to handle files in C in a number of ways, providing everything from simple functions for reading/writing files and folders, to complex functions like taking sha256 from files, checking modification dates. And functionalities of atomic writing of folders/files through transaction systems.
### Installation

The installation of DoTheWorld is made to be as dumb as possible, just  download the file   **doTheWorld.c**  and include in your project.
if this compiles then the library will work:
~~~cpp
#include "doTheWorld.c"

int main(int argc, char *argv[]){
    
    
    return 0;
}
~~~
Alternatively you can download the entire **doTheWorld** folder and include the **doTheWorld/doTheWorldMain.c** file

~~~cpp

#include "doTheWorld/doTheWorldMain.c"

int main(int argc, char *argv[]){

    return 0;
}

~~~
### IO Operations

#### Reading data
##### Reading string
if you are sure that the content you are going to read is not binary you can call the function **dtw_load_string_file_content**
~~~cpp


#include "doTheWorld.c"

int main(int argc, char *argv[]){
  //load a string file content
  const char *path = "../exemple_folder/a/test.txt";
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
