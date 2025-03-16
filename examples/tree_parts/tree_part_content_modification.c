#include "doTheWorldOne.c"


int main(){
    DtwNamespace dtw = newDtwNamespace();

     DtwTreePart *part = dtw.tree.part.newPartLoading("tests/target/a.txt");

    //getting the content
    char *content = dtw.tree.part.get_content_string_by_reference(part);
    char new_content[100] ={0};
    strcat(new_content,content);
    strcat(new_content," New Mensage");
    dtw.tree.part.set_string_content(part,new_content);

    dtw.tree.part.hardware_write(part,DTW_SET_AS_ACTION);
    dtw.tree.part.hardware_commit(part);
    dtw.tree.part.free(part);
}
