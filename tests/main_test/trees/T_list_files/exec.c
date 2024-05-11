
#include "../../../doTheWorld_test.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(
            tree,
            "tests/target/",
            (DtwTreeProps){
                    .content = DTW_HIDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
  DtwStringArray *files = dtw.tree.list_files(tree,"tests/target/sub_folder",DTW_NOT_CONCAT_PATH);
  dtw.string_array.sort(files);
  dtw.string_array.represent(files);
  dtw.string_array.free(files);
  dtw.tree.free(tree);
  return 0;
}