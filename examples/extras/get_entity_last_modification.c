#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    char *last_modification = dtw_get_entity_last_motification_in_string("tests/target/a.txt");
    printf("Last modification: %s", last_modification);
    free(last_modification);
    return 0;
}