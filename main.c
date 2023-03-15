
#include "code/doTheWorldSeparated.c"

int main(int argc, char *argv[]){
 
    struct DtwTree *tree = dtw_tree_constructor();
    tree->add_path_from_hardware(tree,"code",true,false);
    const char *data = tree->dumps_tree_json(tree,true,true,true,true);
    dtw_write_string_file_content("code.json",data);
    tree->delete_tree(tree);

    


}
