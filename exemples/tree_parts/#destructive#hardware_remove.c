//
// Created by jurandi on 20-06-2023.
//

#include "../../doTheWorld_test.h"



int main(){

    struct DtwTreePart *part = newDtwTreePart(
            "exemple_folder/a.txt",
            DTW_LOAD_CONTENT,
            DTW_LOAD_METADATA
    );


    part->hardware_remove(part,DTW_EXECUTE_NOW);
    part->hardware_commit(part);
    part->free(part);

}