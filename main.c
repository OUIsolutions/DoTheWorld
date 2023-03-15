
#include "doTheWorld.c"

int main(int argc, char *argv[]){
    //char *path2 = dtw_change_beginning_of_string("/home/teste",5,"/dev");
    //printf("%s\n",path2);
    //free(path2);
    /*
    struct DtwTreePart *tree = dtw_tree_part_constructor("teste.txt",false);
    tree->set_string_content(tree,"teste");

    struct DtwTreePart *tree2 = dtw_tree_part_constructor("teste2.txt",true);
    tree2->set_string_content(tree2,"teste");


    struct DtwTree *full = dtw_tree_constructor();

    full->add_tree_part_by_referene(full,tree);
    full->add_tree_part_by_referene(full,tree2);
    
    //tree->delete_tree_part(tree);
    //tree2->delete_tree_part(tree2);

    full->represent(full);
    return 0;
    */
    struct DtwStringArray *dirs = dtw_list_all_recursively("code",false);
    dirs->represent(dirs);
    dirs->delete_string_array(dirs);
}
