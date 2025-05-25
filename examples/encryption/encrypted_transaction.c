#include "doTheWorldOne.c"

int main(){
    DtwTransaction *t = newDtwTransaction();
    DtwEncriptionInterface *enc = newDtwAES_Custom_CBC_v1_interface("my encryption key");
    DtwTransaction_set_encryption(t, enc, DTW_HEX_MODE);
    DtwTransaction_write_string(t, "b.txt", "content of b");
    DtwTransaction_write_string(t, "c.txt", "content of c");
    DtwTransaction_commit(t, "tests/");
    DtwTransaction_free(t);
    DtwEncriptionInterface_free(enc);
}