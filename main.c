
#include "code/doTheWorldSeparated.c"

int main(int argc, char *argv[]){
 
    struct DtwTreePart *tree_part = dtw_tree_part_constructor(
        "README.md",
        false,
        true
    );
    //tree_part->set_string_content(tree_part,"aaaa");
    bool result = tree_part->hardware_write(tree_part);
    printf("result: %d\n",result);
    tree_part->represent(tree_part);
    tree_part->delete_tree_part(tree_part);

    


}
