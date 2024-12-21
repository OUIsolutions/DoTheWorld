
#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    int last_modification_in_unix = dtw.get_entity_last_motification_in_unix("testarga.txt");
    printf("Last modification: %d\n", last_modification_in_unix);
}