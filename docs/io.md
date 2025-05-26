# IO Operations

### Reading strings
if you are sure that the content you are going to read is not binary you can call the function **dtw_load_string_file_content**
```c

#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
  //load a string file content
    const char *path = "tests/target/a.txt";
  char *content = dtw_load_string_file_content(path);
  if(content == NULL){
    printf("error oppening %s\n",path);
    return 1;
  }
  printf("content: %s\n",content);
  free(content);
  return 0;

}

```

### Reading Any Content

```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    const char *path = "tests/target/blob.png";
  long size;
  bool is_binary;
  //load any file, is useful if you don't know if the file is binary or not
  unsigned char *content = dtw_load_any_content(path,&size,&is_binary);
  if(content == NULL){
    printf("error oppening %s\n",path);
    return 1;
  }
  printf("size: %ld\n",size);
  printf("is_binary: %s\n",is_binary ? "true" : "false");

  dtw_write_any_content("tests/target/blob2.png",content,size);
  free(content);
  return 0;

}

```




### Reading Double bools and Integers
you also can direclty load all types from an file  with numerical ios

```c

#include "doTheWorldOne.c"




int main (){

    double double_txt = dtw_load_double_file_content("tests/target/numerical/double.txt");
    printf("double.txt:%lf\n",double_txt);

    double double_that_not_exist = dtw_load_double_file_content("nothing.txt");
    printf("double that not exist:%lf\n",double_that_not_exist);


    long integer_txt = dtw_load_long_file_content("tests/target/numerical/integer.txt");
    printf("integer.txt:%ld\n",integer_txt);


    long integer_that_not_exist = dtw_load_long_file_content("nothing.txt");
    printf("integer that not exist:%ld\n",integer_that_not_exist);

    //false_small.txt = "f"
    bool false_small = dtw_load_bool_file_content("tests/target/numerical/false_small.txt");
    printf("false_small.txt:%d\n",false_small);

    //false_normal.txt = "false"
    bool false_normal = dtw_load_bool_file_content("tests/target/numerical/false_normal.txt");
    printf("false_normal.txt:%d\n",false_normal);

    //true_small.txt = "t"
    bool true_small = dtw_load_bool_file_content("tests/target/numerical/true_small.txt");
    printf("true_small.txt:%d\n",true_small);

    //true normal.txt = "true"
    bool true_normal = dtw_load_bool_file_content("tests/target/numerical/true_normal.txt");
    printf("true_normal.txt:%d\n",true_normal);

    bool bool_that_not_exist = dtw_load_bool_file_content("nothing.txt");
    printf("false that not exist:%d\n",bool_that_not_exist);

    return 0;

}

```

to write strings in text files is very simple, just call the function **dtw_write_string_file_content**
(Note that the target directory does not need to exist, if it does not exist it will be created automatically)

```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
  // Write a string to a file the path is auto created
    bool result = dtw_write_string_file_content("tests/target/a.txt","Hello World!");
  printf("result: %s\n",result ? "true" : "false");
  return 0;

}

```


### Writing Any
if you want to write anything to a file, it's also very simple, use the **dtw_write_any_content** function, but note that it will be necessary to pass the writing size


```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    //load the beer image
  const char *blob_path = "tests/target/blob.png";
  long blob_size;
  unsigned char *content = dtw_load_binary_content(blob_path,&blob_size);
  //use these functions for binary files
  if(content == NULL){
    printf("error oppening %s\n",blob_path);
    return 1;
  }
  printf("size: %ld\n",blob_size);

  bool result = dtw_write_any_content("tests/target/blob2.png",content,blob_size);
  printf("result: %s\n",result ? "true" : "false");
free(content);
  return 0;

}

```

### Writing Double , bool and Integers
You also can write any type direclty to an file

```c

#include "doTheWorldOne.c"




int main (){

    dtw_write_double_file_content("tests/target/numerical2/double.txt",25.4);
    dtw_write_long_file_content("tests/target/numerical2/long.txt",12);
    dtw_write_bool_file_content("tests/target/numerical2/bool.txt",true);


    return 0;

}

```