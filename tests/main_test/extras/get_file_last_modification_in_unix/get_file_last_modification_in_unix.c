
#include "../../../doTheWorld_test.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    int last_modification_in_unix = dtw.get_file_last_motification_in_unix("tests/target/a.txt");
    printf("Last modification: %d\n", last_modification_in_unix);
}