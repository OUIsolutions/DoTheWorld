

#include "doTheWorld/doTheWorldMain.c"

int main(int argc, char *argv[]){

    struct DtwTree *tree = dtw_tree_constructor();
    tree->add_tree_from_hardware(tree,"exemples",true,true);
    char *json = tree->dumps_json_tree(tree,false,true,true,true,true,true);
    dtw_write_string_file_content("teste.json",json);
   return 0;
}