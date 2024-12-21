
#include "../../../../release/doTheWorld.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTransaction *t = newDtwTransaction();
    dtw.transaction.write_string(t,"b.txt","aaaaa");
    dtw.transaction.move_any(t,"a.txt","c.txt");
    dtw.transaction.delete_any(t,"blob.png");
    dtw.transaction.copy_any(t,"sub_folder","sub_folder2");
    dtw.transaction.represent(t);
    dtw.transaction.free(t);
}
