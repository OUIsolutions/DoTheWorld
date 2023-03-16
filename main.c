
#include "doTheWorld/doTheWorldmain.c"

int main(int argc, char *argv[]){
 
    struct DtwTree *tree = dtw_tree_constructor();
    tree->add_path_from_hardware(tree, "exemples", true, true);

    char *json_text = tree->dumps_tree_json(tree, true, true, true, true,false);
    dtw_write_string_file_content("exemples.json", json_text);
    free(json_text);
}
