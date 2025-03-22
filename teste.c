#include "doTheWorldOne.c"
DtwNamespace dtw ;
int main(){
    dtw = newDtwNamespace();


    DtwTransaction *t = newDtwTransaction();
    dtw.transaction.write_string(t,"b.txt","aaaaa");
    dtw.transaction.write_string(t,"c.txt","bbbbb");
    dtw.transaction.commit(t,"tests/");
    dtw.transaction.free(t);

}