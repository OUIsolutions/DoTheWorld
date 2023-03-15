
#include "code/doTheWorldSeparated.c"

int main(int argc, char *argv[]){
 
    struct DtwTreePart *tree_part = dtw_tree_part_constructor(
        "README.md",
        true,
        true
    );
    tree_part->set_string_content(tree_part,"");
    tree_part->path->set_name(tree_part->path, "teste");
    tree_part->hardware_modify(tree_part);
    tree_part->delete_tree_part(tree_part);

    


}
