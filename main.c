
#include "code/doTheWorldSeparated.c"

int main(int argc, char *argv[]){
 
    struct DtwTree *tree = dtw_tree_constructor();
    tree->add_path_from_hardware(tree,"exemples",true,false);
    tree->represent(tree);    
    tree->delete_tree(tree);
    
    


}
