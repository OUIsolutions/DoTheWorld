//
// Created by jurandi on 20-06-2023.
//


#include "doTheWorld.h"


#include "../../doTheWorld_test.h"

int main(){

    DtwTreePart *part = newDtwTreePart(
            "main.c",
            DTW_LOAD_CONTENT,
            DTW_LOAD_METADATA
    );

    part->represent(part);
    part->free(part);
}