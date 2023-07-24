
#include "../../../doTheWorld_test.h"

int main(){
    DtwTransaction *t = newDtwTransaction();
    t->write_string(t,"b.txt","aaaaa");
    t->move_any(t,"a.txt","c.txt");
    t->delete_any(t,"blob.png");
    t->copy_any(t,"sub_folder","sub_folder2");
    t->represent(t);
    t->dumps_transaction_to_json_file(t,"tests/target/transaction.json");
    t->free(t);
}