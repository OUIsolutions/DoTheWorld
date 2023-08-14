//
// Created by jurandi on 20-06-2023.
//
#include "doTheWorld.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTreePart *part = dtw.tree.part.newPartEmpty("tests/target/b.txt");
    dtw.tree.part.set_string_content(part,"my mensage");
    dtw.tree.part.hardware_write(part,DTW_SET_AS_ACTION);
    dtw.tree.part.hardware_commit(part);
    dtw.tree.part.free(part);
}