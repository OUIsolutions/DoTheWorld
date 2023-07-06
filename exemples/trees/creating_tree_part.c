//
// Created by jurandi on 20-06-2023.
//
#include "../../doTheWorld_test.h"


int main(){

    DtwTreePart *part = newDtwTreePartEmpty("test.txt");
    part->set_string_content(part,"my mensage");
    part->hardware_write(part,DTW_SET_AS_ACTION);
    part->hardware_commit(part);
    part->free(part);
}