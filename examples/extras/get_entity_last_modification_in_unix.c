#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    int last_modification_in_unix = dtw_get_entity_last_motification_in_unix("tests/target/a.txt");
    printf("Last modification: %d\n", last_modification_in_unix);
}