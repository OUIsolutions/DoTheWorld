
#include "doTheWorld/doTheWorldmain.c"

int main(int argc, char *argv[]){
 
    struct DtwTree *tree = dtw_tree_constructor();

    char *json_text = tree->dumps_tree_json(tree,true,true,false, false, false);
    dtw_write_string_file_content("exemples.json", json_text);
    free(json_text);
}
