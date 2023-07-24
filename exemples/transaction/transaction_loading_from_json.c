
#include "doTheWorld.h"

int main(){
    DtwTransaction *t = newDtwTransaction_from_json_file("tests/target/transaction.json");
    if(!t){
        DtwJsonTransactionError *error = dtw_validate_json_transaction_file("tests/target/transaction.json");
        error->represent(error);
        error->free(error);
        return 0;
    }
    
    t->represent(t);
    t->free(t);
}