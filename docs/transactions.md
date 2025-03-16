### Generating transaction
with transactions you can make all modifications and executed or denny it one time,avoid nod
wanted side effects

```c

#include "doTheWorldOne.c"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTransaction *t = newDtwTransaction();
    dtw.transaction.write_string(t,"b.txt","aaaaa");
    dtw.transaction.move_any(t,"a.txt","c.txt");
    dtw.transaction.delete_any(t,"blob.png");
    dtw.transaction.copy_any(t,"sub_folder","sub_folder2");
    dtw.transaction.commit(t,"tests/target");
    dtw.transaction.free(t);

}

```


You also can dump the transaction to an json file to store it

```c

#include "doTheWorldOne.c"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTransaction *t = newDtwTransaction();
    dtw.transaction.write_string(t,"b.txt","aaaaa");
    dtw.transaction.move_any(t,"a.txt","c.txt");
    dtw.transaction.delete_any(t,"blob.png");
    dtw.transaction.copy_any(t,"sub_folder","sub_folder2");
    dtw.transaction.represent(t);
    dtw.transaction.dumps_transaction_to_json_file(t,"tests/target/transaction.json");
    dtw.transaction.free(t);
}

```

```c

#include "doTheWorldOne.c"

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

```
