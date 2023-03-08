#include "functions/monodimension_listage.c"

int main(int argc, char *argv[]){
    
    struct DtwStringArray *array = dtw_list_basic("/home/jurandi","all",true);
    dtw_represent_string_array(array);

}