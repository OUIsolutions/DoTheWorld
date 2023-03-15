
#include "code/doTheWorldSeparated.c"

int main(int argc, char *argv[]){
    //char *path2 = dtw_change_beginning_of_string("/home/teste",5,"/dev");
    //printf("%s\n",path2);
    //free(path2);
    //struct DtwTreePart *tree_part = dtw_tree_part_constructor("README.md",true,true);
    //tree_part->path->represent(tree_part->path);
    
    struct DtwTreePart *tree_part = dtw_tree_part_constructor("README.md");
    return 0;
   
}
