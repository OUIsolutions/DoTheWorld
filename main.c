
#include "doTheWorld/doTheWorldmain.c"

int main(int argc, char *argv[]){
 
    struct DtwTree *tree = dtw_tree_constructor();
    char *code = dtw_load_string_file_content("code.json");
    tree->loads_json_tree(tree, code);

}
