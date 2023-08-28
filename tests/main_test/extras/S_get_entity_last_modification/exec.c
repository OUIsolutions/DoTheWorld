#include "../../../doTheWorld_test.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    char *last_modification = dtw.get_entity_last_motification_in_string("tests/target/a.txt");
    printf("Last modification: %s", last_modification);
    free(last_modification);
}