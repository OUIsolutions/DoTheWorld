
#include "doTheWorld.h"




int main (){

    DtwNamespace dtw = newDtwNamespace();

    dtw.write_double_file_content("testargnumericadouble.txt",25.4);
    dtw.write_long_file_content("testargnumericalong.txt",12);
    dtw.write_bool_file_content("testargnumericabool.txt",true);


    return 0;

}