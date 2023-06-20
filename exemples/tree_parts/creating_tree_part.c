//
// Created by jurandi on 20-06-2023.
//

#include "../../doTheWorld_test.h"


int main(){

    DtwTreePart *part = newDtwTreePart(
            "test.txt",
            DTW_NOT_LOAD_CONTENT,
            DTW_LOAD_METADATA
    );

    part->set_string_content(part,"Hello World");
    part->hardware_write(part,DTW_SET_AS_ACTION);
    part->hardware_commit(part);
    part->free(part);

}