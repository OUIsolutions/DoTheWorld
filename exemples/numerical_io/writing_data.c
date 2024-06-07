
#include "doTheWorld.h"




int main (){

    DtwNamespace dtw = newDtwNamespace();

    dtw.write_double_file_content("tests/target/numerical2/double.txt",25.4);
    dtw.write_long_file_content("tests/target/numerical2/long.txt",12);
    dtw.write_bool_file_content("tests/target/numerical2/bool.txt",true);


    return 0;

}