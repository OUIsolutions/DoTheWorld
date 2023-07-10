
#include "../../../doTheWorld_test.h"

int main(int argc, char *argv[]){
   int last_modification_in_unix = dtw_get_file_last_motification_in_unix("README.md");
    printf("Last modification: %d\n", last_modification_in_unix);
}