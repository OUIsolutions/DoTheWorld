# Copy and Move Files and Folders

If you want to create dirs you can call the function **dtw_create_dir_recursively**
passing the folder you want to create, don't worry about if the previous path doesn't exist
it will create until it reaches the target folder

```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    dtw_create_dir_recursively("tests/target/sub_folder/a/b/c");

    return 0;
}
```

### Copying Anything
With the function **dtw_copy_any** you can copy either files or folders from one position to another position

```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    dtw_copy_any("tests/target/blob.png", "tests/target/blob3.png", DTW_NOT_MERGE);
    return 0;
}
```

### Moving Any
You can move either folders or files with **dtw_move_any** function

```c
#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    dtw_move_any("tests/target/sub_folder", "tests/target/sub_folder2", DTW_NOT_MERGE);
    return 0;
}
```
