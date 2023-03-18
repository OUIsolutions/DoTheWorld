
#include "doTheWorld/doTheWorldmain.c"
void load_and_dump_file(){
    struct DtwTree *tree = dtw_tree_constructor();
    char *code = dtw_load_string_file_content("exemples.json");
    
    tree->loads_json_tree(tree, code);
    
    for (int i = 0; i < tree->size; i++){
        struct DtwTreePart *part = tree->tree_parts[i];
        struct DtwPath *path = part->path;
        path->add_start_dir(path,"exemples2");
        part->hardware_write(part,DTW_SET_AS_ACTION);
        
    }
    tree->hardware_commit_tree(tree);
    tree->free_tree(tree);
    free(code);
    
}

void load_hardware_and_dump_string(){
    struct DtwTree *tree = dtw_tree_constructor();
    tree->add_path_from_hardware(tree,"exemples",DTW_LOAD_CONTENT,DTW_PRESERVE_CONTENT);
    char *generated =tree->dumps_json_tree(
        tree,
        DTW_PRESERVE_CONTENT,
        DTW_PRESERVE_PATH_ATRIBUTES,
        DTW_PRESERVE_HARDWARE_DATA,
        DTW_PRESERVE_CONTENT_DATA,
        DTW_NOT_MINIFY
        );
    dtw_write_string_file_content("exemples.json",generated);
    free(generated);
    tree->free_tree(tree);
}


int main(int argc, char *argv[]){
    
    char *current_dir = dtw_get_current_dir();
    printf("current dir : %s",current_dir);
    free(current_dir);
    return 0;
}
