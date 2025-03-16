# Copy and Move Files and Folders

If you want to create dirs you can call the function **dtw_create_dir_recursively**
passing the folder you want to create,dont wory about if the previews path dont exist
it will create till reachs the target folder

```c
#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    dtw.create_dir_recursively("tests/target/sub_folder/a/b/c");

  return 0;
}

```

### Copying Anything
With the function **dtw_copy_any** you can copy either files or folders to one position to anoter position

```c


#include "doTheWorld.h"

int main(int argc, char *argv[]){
  DtwNamespace dtw = newDtwNamespace();
  dtw.copy_any("tests/target/blob.png","tests/target/blob3.png",DTW_NOT_MERGE);
  return 0;
}

```

### Moving Any
You can move either folders or files with **dtw_move_any** function

```c

#include "doTheWorld.h"

int main(int argc, char *argv[]){

    DtwNamespace dtw = newDtwNamespace();

    dtw.move_any("tests/target/sub_folder","tests/target/sub_folder2",DTW_NOT_MERGE);

    return 0;
}

```
