//
// Created by mateusmoutinho on 24/07/23.
//
#include "../../../doTheWorld_test.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTransaction *t = dtw.transaction.newTransaction_from_json_file("tests/target/wrong_transaction.json");
    if(!t){
        DtwJsonTransactionError *error = dtw.transaction.validate_json_transaction_file("tests/target/wrong_transaction.json");
        dtw.transaction.json_error.represent(error);
        dtw.transaction.json_error.free(error);
        return 0;
    }
    
    dtw.transaction.represent(t);
    dtw.transaction.free(t);
}