

#include "../../doTheWorld_test.h"

int main(){

    DtwTreePart *part = newDtwTreePart(
            "exemple_folder/a.txt",
            DTW_LOAD_CONTENT,
            DTW_LOAD_METADATA
    );

    part->represent(part);
    part->free(part);
}