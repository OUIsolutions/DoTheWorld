
#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "testarg",
            (DtwTreeProps){
                    .content = DTW_HIDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
  DtwStringArray *files = dtw.tree.list_files(tree,"testargsub_folder",DTW_NOT_CONCAT_PATH);
  dtw.string_array.sort(files);
  dtw.string_array.represent(files);
  dtw.string_array.free(files);
  dtw.tree.free(tree);
  return 0;
}