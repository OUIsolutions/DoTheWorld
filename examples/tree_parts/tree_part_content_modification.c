#include "doTheWorldOne.c"

int main(){
    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");

    char *content = DtwTreePart_get_content_string_by_reference(part);
    char new_content[100] = {0};
    strcat(new_content, content);
    strcat(new_content, " New Mensage");
    DtwTreePart_set_string_content(part, new_content);

    DtwTreePart_hardware_write(part, DTW_SET_AS_ACTION);
    DtwTreePart_hardware_commit(part);
    DtwTreePart_free(part);
}