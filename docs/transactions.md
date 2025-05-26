### Generating transaction
with transactions you can make all modifications and execute or deny it one time, avoid unwanted side effects

```c
#include "doTheWorldOne.c"

int main(){
    DtwTransaction *t = newDtwTransaction();
    dtw_write_string_file_content("b.txt", "aaaaa");
    dtw_move_any("a.txt", "c.txt", false);
    dtw_remove_any("blob.png");
    dtw_copy_any("sub_folder", "sub_folder2", false);
    DtwTransaction_commit(t, "tests/target");
    DtwTransaction_free(t);
}
```

You also can dump the transaction to a JSON file to store it

```c
#include "doTheWorldOne.c"

int main(){
    DtwTransaction *t = newDtwTransaction();
    dtw_write_string_file_content("b.txt", "aaaaa");
    dtw_move_any("a.txt", "c.txt", false);
    dtw_remove_any("blob.png");
    dtw_copy_any("sub_folder", "sub_folder2", false);
    DtwTransaction_represent(t);
    DtwTransaction_dumps_to_json_file(t, "tests/target/transaction.json");
    DtwTransaction_free(t);
}
```

```c
#include "doTheWorldOne.c"

int main(){
    DtwTransaction *t = newDtwTransaction_from_json_file("tests/target/transaction.json");
    if(!t){
        DtwJsonTransactionError *error = dtw_validate_json_transaction_file("tests/target/transaction.json");
        DtwJsonTransactionError_represent(error);
        DtwJsonTransactionError_free(error);
        return 0;
    }

    DtwTransaction_represent(t);
    DtwTransaction_free(t);
}
```
