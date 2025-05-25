#include "doTheWorldOne.c"

int main(){
    DtwTransaction *t = newDtwTransaction();
    DtwTransaction_write_string(t, "b.txt", "aaaaa");
    DtwTransaction_move_any(t, "a.txt", "c.txt");
    DtwTransaction_delete_any(t, "blob.png");
    DtwTransaction_copy_any(t, "sub_folder", "sub_folder2");
    DtwTransaction_commit(t, "tests/target");
    DtwTransaction_free(t);
    return 0;
}