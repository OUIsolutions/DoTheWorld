// Created by mateusmoutinho on 23/
#include "doTheWorld.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTransaction *t = dtw.transaction.newTransaction_from_json_file("testargwrong_transaction.json");
    if(!t){
        DtwJsonTransactionError *error = dtw.transaction.validate_json_transaction_file("testargwrong_transaction.json");
        dtw.transaction.json_error.represent(error);
        dtw.transaction.json_error.free(error);
        return 0;
    }
    
    dtw.transaction.represent(t);
    dtw.transaction.free(t);
}