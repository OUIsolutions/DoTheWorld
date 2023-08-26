#include "doTheWorld/doTheWorldMain.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    DtwResource *t = dtw.resource.newResource("a");
    DtwResource *t1 = dtw.resource.sub_resource(t,"a1");
    dtw.resource.lock(t1);
    dtw.resource.set_string(t1,"ta functionando porra3333");
    
    dtw.resource.commit(t);
    dtw.resource.free(t);
}