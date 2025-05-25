#include "doTheWorldOne.c"

int main(){
    DtwTransaction *t = newDtwTransaction_from_json_file("tests/target/wrong_transaction.json");
    if(!t){
        DtwJsonTransactionError *error = dtw_validate_json_transaction_file("tests/target/wrong_transaction.json");
        DtwJsonTransactionError_represent(error);
        DtwJsonTransactionError_free(error);
        return 0;
    }

    DtwTransaction_represent(t);
    DtwTransaction_free(t);
}