With the listage functions you can extract all Strings Arrays of elements in a folder

## Listing files

#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
  DtwStringArray *files = dtw_list_files("tests/target", DTW_CONCAT_PATH);
  DtwStringArray_sort(files);

  for(int i = 0; i < files->size; i++){
    printf("%s\n", files->strings[i]);
  }
  DtwStringArray_free(files);
  return 0;
}

### Listing Dirs

#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
  DtwStringArray *dirs = dtw_list_dirs("tests/target", DTW_NOT_CONCAT_PATH);
  //the represent method will print the dirs in the console
  DtwStringArray_sort(dirs);
  DtwStringArray_represent(dirs);
  DtwStringArray_free(dirs);
  return 0;
}

### Listing All

#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
  DtwStringArray *all = dtw_list_all("tests/target/", DTW_CONCAT_PATH);
  DtwStringArray_sort(all);
  DtwStringArray_represent(all);
  DtwStringArray_free(all);
  return 0;
}

The By Using multi dimension listage functions, you can see all items listed in all sub folders of the "main" folder

### Listing Files Recursively

#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
  DtwStringArray *files = dtw_list_files_recursively("tests/target/", DTW_CONCAT_PATH);
  DtwStringArray_sort(files);
  DtwStringArray_represent(files);
  DtwStringArray_free(files);
  return 0;
}

### Listing Dirs Recursively

#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
  DtwStringArray *files = dtw_list_dirs_recursively("tests/target/", DTW_CONCAT_PATH);
  DtwStringArray_sort(files);
  DtwStringArray_represent(files);
  DtwStringArray_free(files);
  return 0;
}

### Listing All Recursively

#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
  DtwStringArray *files = dtw_list_all_recursively("tests/target/", DTW_CONCAT_PATH);
  DtwStringArray_sort(files);
  DtwStringArray_represent(files);
  DtwStringArray_free(files);
  return 0;
}
