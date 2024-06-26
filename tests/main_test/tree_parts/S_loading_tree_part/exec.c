

#include "../../../doTheWorld_test.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTreePart *part = dtw.tree.part.newPartLoading("tests/target/a.txt");
    dtw.tree.part.represent(part);
    dtw.tree.part.free(part);
}