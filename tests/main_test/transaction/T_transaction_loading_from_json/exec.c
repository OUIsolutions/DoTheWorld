
#include "../../../../release/doTheWorld.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTransaction *t = dtw.transaction.newTransaction_from_json_file("tests/target/transaction.json");
    if(!t){
        DtwJsonTransactionError *error = dtw_validate_json_transaction_file("tests/target/transaction.json");
        dtw.transaction.json_error.represent(error);
        dtw.transaction.json_error.free(error);
        return 0;
    }

    dtw.transaction.represent(t);
    dtw.transaction.free(t);
}
