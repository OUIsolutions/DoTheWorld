
#include "../../../doTheWorld_test.h"

int main(int argc, char *argv[]){

    DtwTree *tree = newDtwTree();
    tree->add_tree_from_hardware(
            tree,
            "tests/target/",
            &(DtwTreeProps){
                    .content = DTW_HIDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
            }
    );
  DtwStringArray *files = tree->list_all(tree,"tests/target/sub_folder",DTW_NOT_CONCAT_PATH);
  files->sort(files);
  files->represent(files);
  files->free(files);
  tree->free(tree);
  return 0;
}