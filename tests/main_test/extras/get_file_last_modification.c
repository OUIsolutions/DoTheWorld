#include "../../doTheWorld_test.h"

int main(int argc, char *argv[]){
    char *last_modification = dtw_get_file_last_motification_in_string("tests/target/a.txt");
    printf("Last modification: %s", last_modification);
    free(last_modification);
}