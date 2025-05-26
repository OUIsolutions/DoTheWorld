### Unix
// Get the last modification of a file in Unix timestamp format.
#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    int last_modification_in_unix = dtw_get_entity_last_motification_in_unix("tests/target/a.txt");
    printf("Last modification: %d\n", last_modification_in_unix);
}

// Get the last modification of a file in string format.
#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    char *last_modification = dtw_get_entity_last_motification_in_string("tests/target/a.txt");
    printf("Last modification: %s", last_modification);
    free(last_modification);
}
