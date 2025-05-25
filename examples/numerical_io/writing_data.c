#include "doTheWorldOne.c"

int main (){
    dtw_write_double_file_content("tests/target/numerical2/double.txt", 25.4);
    dtw_write_long_file_content("tests/target/numerical2/long.txt", 12);
    dtw_write_bool_file_content("tests/target/numerical2/bool.txt", true);
    return 0;
}