
#include "doTheWorld/doTheWorldmain.c"

int main(int argc, char *argv[]){
 
    struct DtwTree *tree = dtw_tree_constructor();
    tree->add_path_from_hardware(tree, "doTheWorld",true, true);
    for(int i = 0; i < tree->size; i++){
        struct DtwPath *current_path =  tree->tree_parts[i]->path;
        //add /test 
        current_path->add_start_dir(current_path, "test");
        current_path->add_end_dir(current_path, "final");
    }

    char *json_text = tree->dumps_tree_json(tree,true,true,true, true, false);
    dtw_write_string_file_content("code.json", json_text);
    free(json_text);
}
