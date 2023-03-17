
#include "doTheWorld/doTheWorldmain.c"

int main(int argc, char *argv[]){
 
    struct DtwTree *tree = dtw_tree_constructor();
    /*
    tree->add_path_from_hardware(tree,"doTheWorld",true,true);
    char *code = tree->dumps_json_tree(tree,true,true,true,true,false);
    dtw_write_string_file_content("code.json",code);
    */
    
    char *code = dtw_load_string_file_content("code.json");
    tree->loads_json_tree(tree, code);
    char *generated =tree->dumps_json_tree(tree,true,true,true,true,false);
    dtw_write_string_file_content("generated.json",generated);
    
    /*
    for (int i = 0; i < tree->size; i++){
        struct DtwTreePart *part = tree->tree_parts[i];
        char *dir = part->path->get_dir(part->path);
        char *new_dir = dtw_replace_string(dir,"doTheWorld","doTheWorld2");
        part->path->set_dir(part->path,new_dir);
        free(new_dir);
        free(dir);
    }
    */
    
}
