
#include "code/doTheWorldSeparated.h"

int main(int argc, char *argv[]){
    //char *path2 = dtw_change_beginning_of_string("/home/teste",5,"/dev");
    //printf("%s\n",path2);
    //free(path2);
    struct DtwTreePart *tree = dtw_tree_part_constructor(
        "testex/.a",false
    );
    tree->set_string_content(tree,"teste");
    tree->represent(tree);
    tree->hardware_write(tree);
    tree->delete_tree_part(tree);
    return 0;
}
