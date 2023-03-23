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
#### Lite Version
You alson can download the **doTheWorldLite.c** file and use it, these version does not  
have suport to json trees, witch means, all json functions wont work here 

~~~cpp


#include "doTheWorldLite.c"

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
### Used Dependencies And Atributions
DoTheWorld includes all self dependecies in the single file, so you dont need to care about it, but if you will use one of these librarys, dont include it in your code to avoid circular imports:




#### CJson<br><br>
**cJson**: from https://github.com/DaveGamble/cJSON <br>
Copyright (c) 2009-2017 Dave Gamble and cJSON contributors

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#### sha-256 <br>
**sha-256**: from https://github.com/amosnier/sha-2 <br>
### IO Operations
Zero Clause BSD License
© 2021 Alain Mosnier

Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

##### Reading strings
if you are sure that the content you are going to read is not binary you can call the function **dtw_load_string_file_content**
~~~cpp


#include "doTheWorld.c"

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
##### Reading Any
if you are not sure what data type a file is you can call the function **dtw_load_any_content**

~~~cpp
#include "doTheWorld.c"

int main(int argc, char *argv[]){
 
  const char *path = "exemple_folder/deer.jpg";
  int size;
  bool is_binary;
  //load any file, is useful if you don't know if the file is binary or not
  unsigned char *content = dtw_load_any_content(path,&size,&is_binary);
  if(content == NULL){
    printf("error oppening %s\n",path);
    return 1;
  }
  printf("size: %d\n",size);
  printf("is_binary: %s\n",is_binary ? "true" : "false");
  printf("content: %s\n",content);
  free(content);
  return 0;
}
~~~
##### Reading Binary
if you are sure the file is a binary , call the function **dtw_load_binary_content**
~~~cpp


#include "doTheWorld.c"

int main(int argc, char *argv[]){
 
  const char *path = "exemple_folder/deer.jpg";
  int size;
  //load a binary file content
  unsigned char *content = dtw_load_binary_content(path,&size);
  if(content == NULL){
    printf("error oppening %s\n",path);
    return 1;
  }
  printf("size: %d\n",size);
  printf("content: %s\n",content);
  free(content);
  return 0;
}

~~~

##### Writing strings

to write strings in text files is very simple, just call the function **dtw_write_string_file_content**
(Note that the target directory does not need to exist, if it does not exist it will be created automatically)

~~~cpp
#include "doTheWorld.c"
int main(int argc, char *argv[]){
  // Write a string to a file the path is auto created
  
  bool result = dtw_write_string_file_content("test/a/test.txt","Hello World!");
  printf("result: %s\n",result ? "true" : "false");
  return 0;
}
~~~

##### Writing Any

if you want to write anything to a file, it's also very simple, use the **dtw_load_binary_content** function, but note that it will be necessary to pass the writing size

~~~cpp

#include "doTheWorld.c"

int main(int argc, char *argv[]){
  //load the beer image
  const char *deer_path = "test/exemple_folder/deer.jpg";
  int deer_size;
  unsigned char *content = dtw_load_binary_content(deer_path,&deer_size);
  //use these functions for binary files
  if(content == NULL){
    printf("error oppening %s\n",deer_path);
    return 1;
  }
  printf("size: %d\n",deer_size);

  bool result = dtw_write_any_content("test/deer.jpg",content,deer_size);
  printf("result: %s\n",result ? "true" : "false");
  return 0;
}
~~~
##### Creating Dirs
If you want to create dirs you can call the function **dtw_create_dir_recursively**
passing the folder you want to create,dont wory about if the previews path dont exist 
it will create till reachs the target folder
~~~cpp
#include "doTheWorld.c"

int main(int argc, char *argv[]){
 
  dtw_create_dir_recursively("a/b/c/");
  return 0;
}
~~~
#####  Copying Things 
With the function **dtw_copy_any** you can copy either files or folders to one position to anoter position 
##### Copying files
~~~cpp


#include "doTheWorld.c"

int main(int argc, char *argv[]){

  dtw_copy_any("exemple_folder/deer.jpg","deer.jpg",DTW_NOT_MERGE);
  return 0;
}
~~~
##### Copying folders
~~~cpp

#include "doTheWorld.c"

int main(int argc, char *argv[]){

  dtw_copy_any("exemple_folder","exemple_folder2",DTW_NOT_MERGE);
  return 0;
}
~~~
also you can use the **dtw_copy_any** function  to merge the content in the target  folder with the target
~~~cpp

#include "doTheWorld.c"

int main(int argc, char *argv[]){
  dtw_write_string_file_content("exemple_folder2/x.txt","hello world");
  dtw_copy_any("exemple_folder","exemple_folder2",DTW_MERGE);
  return 0;
}
~~~

##### Moving Things

You can move either folders or files with **dtw_move_any** function 

##### Moving Files
~~~cpp

#include "doTheWorld.c"

int main(int argc, char *argv[]){


  dtw_move_any("exemple_folder/deer.jpg","deer.jpg",DTW_NOT_MERGE);

  return 0;
}
~~~

##### Moving Folders
~~~cpp


#include "doTheWorld.c"

int main(int argc, char *argv[]){


  dtw_move_any("exemple_folder","exemple_folder2",DTW_NOT_MERGE);

  return 0;
}
~~~

as the same as copying files , you alson can merge 
~~~cpp

#include "doTheWorld.c"

int main(int argc, char *argv[]){

  dtw_write_string_file_content("exemple_folder2/exemple_file.txt","Hello World !");
  dtw_move_any("exemple_folder","exemple_folder2",DTW_MERGE);

  return 0;
}
~~~

### Monodimension Listage

With the listage functions you can extract all Strings Arrays of elements in an folder 

##### Listing files
with the **dtw_list_files** you can list all files in the folder you pass as argument 

~~~cpp

#include "doTheWorld.c"

int main(int argc, char *argv[]){

  struct DtwStringArray *files = dtw_list_files("exemple_folder", DTW_CONCAT_PATH);
  for(int i = 0; i < files->size; i++){
    printf("%s\n", files->strings[i]);
  }
  return 0;
}
~~~
if you pass concat path to false in all the listage functions, it will not show the previews path

~~~cpp
#include "doTheWorld.c"

int main(int argc, char *argv[]){

  struct DtwStringArray *files = dtw_list_files("exemple_folder", DTW_NOT_CONCAT_PATH);
  for(int i = 0; i < files->size; i++){
    printf("%s\n", files->strings[i]);
  }
  return 0;
}
~~~

##### Listing dirs 
~~~cpp

#include "doTheWorld.c"

int main(int argc, char *argv[]){

  struct DtwStringArray *files = dtw_list_dirs("exemple_folder", DTW_NOT_CONCAT_PATH);
  files->represent(files);
  return 0;
}
~~~

##### Listing All 
will list everything in the current folder 
~~~cpp
#include "doTheWorld.c"

int main(int argc, char *argv[]){

  struct DtwStringArray *all = dtw_list_all("exemple_folder",DTW_CONCAT_PATH);
  all->represent(all);
  return 0;
}
~~~