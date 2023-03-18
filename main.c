
#include "doTheWorld/doTheWorldmain.c"
void load_and_dump_file(){
    struct DtwTree *tree = dtw_tree_constructor();
    char *code = dtw_load_string_file_content("exemples.json");
    struct DtWJsonError *json_error = dtw_validate_json_tree(code);
    if(json_error->code != DTW_JSON_ERROR_CODE_OK){
        printf("Error: %s at position %d\n",json_error->message,json_error->position);
        json_error->free_json_error(json_error);
        return;
    }
    json_error->free_json_error(json_error);
    tree->loads_json_tree(tree, code);
    tree->hardware_write_tree(tree);
    tree->represent(tree);
    tree->free_tree(tree);
    free(code);
    
}

void load_hardware_and_dump_string(){
    struct DtwTree *tree = dtw_tree_constructor();
    tree->add_tree_from_hardware(tree,"exemples",DTW_LOAD_CONTENT,DTW_PRESERVE_CONTENT);
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
    
    struct DtwTree *tree = dtw_tree_constructor();
    tree->add_tree_from_hardware(tree,"exemples",DTW_LOAD_CONTENT,DTW_PRESERVE_CONTENT);
    for(int i = 0; i < tree->size; i++){
        tree->tree_parts[i]->hardware_write(tree->tree_parts[i],DTW_SET_AS_ACTION);
    }
    tree->represent(tree);
    tree->free_tree(tree);
    return 0;
}
