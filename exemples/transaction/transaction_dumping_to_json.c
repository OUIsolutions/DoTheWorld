
#include "doTheWorld.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTransaction *t = newDtwTransaction();
    dtw.transaction.write_string(t,"b.txt","aaaaa");
    dtw.transaction.move_any(t,"a.txt","c.txt");
    dtw.transaction.delete_any(t,"blob.png");
    dtw.transaction.copy_any(t,"sub_folder","sub_folder2");
    dtw.transaction.represent(t);
    dtw.transaction.dumps_transaction_to_json_file(t,"testargtransaction.json");
    dtw.transaction.free(t);
}