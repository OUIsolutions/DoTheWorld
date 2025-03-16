

With the listage functions you can extract all Strings Arrays of elements in an folder

## Listing files

```c

#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

  DtwStringArray *files = dtw.list_files("tests/target", DTW_CONCAT_PATH);
  dtw.string_array.sort(files);

  for(int i = 0; i < files->size; i++){
    printf("%s\n", files->strings[i]);
  }
  dtw.string_array.free(files);
  return 0;
}

```

### Listing Dirs

```c


#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

  DtwStringArray *dirs = dtw.list_dirs("tests/target", DTW_NOT_CONCAT_PATH);
  //the represent methold will print the dirs in the console
  dtw.string_array.sort(dirs);
  dtw.string_array.represent(dirs);
  dtw.string_array.free(dirs);
  return 0;
}

```

### Listing All

```c



#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

  DtwStringArray *all = dtw.list_all("tests/target/",DTW_CONCAT_PATH);
  dtw.string_array.sort(all);
  dtw.string_array.represent(all);
  dtw.string_array.free(all);
  return 0;
}

```

The By Using multi dimension listage functions , you can see all itens listed in all sub folders of the "main" folder

### Listing Files Recursively

```c

#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

  DtwStringArray *files = dtw.list_files_recursively("tests/target/",DTW_CONCAT_PATH);
  dtw.string_array.sort(files);
  dtw.string_array.represent(files);
  dtw.string_array.free(files);
  return 0;
}

```

### Listing Dirs Recursively

```c

#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

  DtwStringArray *files = dtw.list_dirs_recursively("tests/target/",DTW_CONCAT_PATH);
  dtw.string_array.sort(files);
  dtw.string_array.represent(files);
  dtw.string_array.free(files);
  return 0;
}

```

### Listing All Recursively

```c

#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

  DtwStringArray *files = dtw.list_all_recursively("tests/target/",DTW_CONCAT_PATH);
  dtw.string_array.sort(files);
  dtw.string_array.represent(files);
  dtw.string_array.free(files);
  return 0;
}

```
