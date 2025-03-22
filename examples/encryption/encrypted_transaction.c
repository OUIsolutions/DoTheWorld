#include "doTheWorldOne.c"
DtwNamespace dtw ;
int main(){
    dtw = newDtwNamespace();

    DtwTransaction *t = newDtwTransaction();
    DtwEncriptionInterface *enc = dtw.encryption.newAES_Custom_CBC_v1_interface("my encryption key");
    dtw.transaction.set_encryption(t,enc,DTW_HEX_MODE);
    dtw.transaction.write_string(t,"b.txt","content of b");
    dtw.transaction.write_string(t,"c.txt","content of c");
    dtw.transaction.commit(t,"tests/");
    dtw.transaction.free(t);
    dtw.encryption.free(enc);

}