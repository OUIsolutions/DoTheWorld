#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    dtw_move_any("tests/target/sub_folder","tests/target/sub_folder2",DTW_NOT_MERGE);
    return 0;
}