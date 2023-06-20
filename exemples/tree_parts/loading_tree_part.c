//
// Created by jurandi on 20-06-2023.
//



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