#include "doTheWorld.h"


int main(){

     DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");

    //getting the content
    char *content = part->get_content_string_by_reference(part);
    char new_content[100] ={0};
    strcat(new_content,content);
    strcat(new_content," New Mensage");
    part->set_string_content(part,new_content);

    part->hardware_write(part,DTW_SET_AS_ACTION);
    part->hardware_commit(part);
    part->free(part);
}