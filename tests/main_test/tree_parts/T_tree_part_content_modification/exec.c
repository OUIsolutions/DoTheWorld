#include "../../../doTheWorld_test.h"


int main(){

     DtwTreePart *part = newDtwTreePartLoading("test.txt");

    //getting the content
    char *content = part->get_content_string_by_reference(part);
    char new_content[100] ="";
    strcat(new_content,content);
    strcat(new_content," New Mensage");
    part->set_string_content(part,new_content);

    part->hardware_write(part,DTW_SET_AS_ACTION);
    part->hardware_commit(part);
    part->free(part);
}