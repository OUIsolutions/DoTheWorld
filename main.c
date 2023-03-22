

#include "doTheWorld/doTheWorldMain.c"

int main(int argc, char *argv[]){

    struct DtwTree *tree = dtw_tree_constructor();
    tree->add_tree_from_hardware(tree,"exemples",true,true);
    tree->dumps_json_tree_to_file(tree,"teste.json",false,true,true,true,true,true);
   
   return 0;
}