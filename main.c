
#include "doTheWorld/doTheWorldmain.c"
void load_and_dump_string(){

    struct DtwTree *tree = dtw_tree_constructor();
    char *code = dtw_load_string_file_content("code.json");
    tree->loads_json_tree(tree, code);
    char *generated =tree->dumps_json_tree(tree,true,true,true,true,false);
    dtw_write_string_file_content("generated.json",generated);
    free(generated);
    free(code);
}


int main(int argc, char *argv[]){
    

    DtwStringArray 

    //char *content_json = tree->dumps_json_tree(tree,true,true,true,true,false);
    //dtw_write_string_file_content("code.json",content_json);
    
}
