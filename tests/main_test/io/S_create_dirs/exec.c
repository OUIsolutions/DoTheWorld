#include "../../../../release/doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    dtw.create_dir_recursively("tests/target/sub_folder/a/b/c");

  return 0;
}
