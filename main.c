
#include "code/doTheWorldSeparated.c"

int main(int argc, char *argv[]){
    //char *path2 = dtw_change_beginning_of_string("/home/teste",5,"/dev");
    //printf("%s\n",path2);
    //free(path2);
    //struct DtwTreePart *tree_part = dtw_tree_part_constructor("README.md",true,true);
    //tree_part->path->represent(tree_part->path);
    
    
    
    /*
    struct DtwTreePart *part = dtw_tree_part_constructor("README.md",true,true);
    part->represent(part);
    part->delete_tree_part(part);
    return 0;
    */
    
    struct DtwTree *tree = dtw_tree_constructor();
    tree->add_path_from_hardware(tree,"code",true,false);
    tree->add_path_from_hardware(tree,"exemples",true,false);
    tree->represent(tree);    
    tree->delete_tree(tree);

    
    /*
    struct DtwPath *path = dtw_constructor_path("/home/teste.c");
    path->represent(path);
    path->delete_path(path);
    */

}
