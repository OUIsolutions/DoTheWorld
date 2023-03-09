#include "doTheWorldDevUsage.c"
int main(int argc, char *argv[]){

    struct DtwStringArray * teste = dtw_list_dirs_recursively(
      "C:\\Users\\USER\\OneDrive\\Documentos\\GitHub\\DoTheWorld"
    );
    dtw_represent_string_array(teste);
    printf("\n");
}