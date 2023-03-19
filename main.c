
#include "doTheWorld.c"


int main(int argc, char *argv[]){
    
    struct DtwTree *tree = dtw_tree_constructor();
    
    tree->add_tree_from_hardware(tree,"exemples",DTW_LOAD_CONTENT,DTW_PRESERVE_CONTENT);
    
    tree->represent(tree);
    char *json_string = tree->dumps_json_tree(
        tree,
        DTW_PRESERVE_CONTENT,
        DTW_PRESERVE_PATH_ATRIBUTES,
        DTW_PRESERVE_HARDWARE_DATA,
        DTW_PRESERVE_CONTENT_DATA,
        DTW_NOT_MINIFY,
        DTW_CONSIDER_IGNORE
    );

    dtw_write_string_file_content("exemples.json",json_string);
    

    
    
    tree->free_tree(tree);
    return 0;
}
