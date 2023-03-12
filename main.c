
#include "code/doTheWorldDevUsage.c"

int main(int argc, char *argv[]){
    struct DtwTreePart *tree_part = dtw_create_tree_part(
        "README.md",true,true    );
        
    dtw_represent_tree_part(tree_part);
}
