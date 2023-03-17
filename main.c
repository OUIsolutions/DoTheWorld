
#include "doTheWorld/doTheWorldmain.c"
void load_and_dump_string(){
    struct DtwTree *tree = dtw_tree_constructor();
    char *code = dtw_load_string_file_content("exemples.json");
    tree->loads_json_tree(tree, code);
    for (int i = 0; i < tree->size; i++){
        struct DtwTreePart *part = tree->tree_parts[i];
        struct DtwPath *path = part->path;
        path->add_start_dir(path,"exemples2");
        part->hardware_write(part);
    }
    
    tree->delete_tree(tree);
    free(code);
}

void load_hardware_and_dump_string(){
    struct DtwTree *tree = dtw_tree_constructor();
    tree->add_path_from_hardware(tree,"exemples",true,true);
    char *generated =tree->dumps_json_tree(tree,true,true,true,true,false);
    dtw_write_string_file_content("exemples.json",generated);
    free(generated);
    tree->delete_tree(tree);
}

int main(int argc, char *argv[]){
    
    load_and_dump_string();
    return 0;
}
