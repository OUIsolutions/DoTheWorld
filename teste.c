
#include "src/one.c"
DtwNamespace dtw;
int main (){
    dtw = newDtwNamespace();

    DtwResource *t = dtw.resource.newResource("data");
    DtwResource *ar = dtw.resource.sub_resource(t,"a.txt");

    bool is_binary;
    long size;
    unsigned char *a = dtw.load_any_content("a.txt",&size,&is_binary);
    dtw.resource.set_any(ar,a,size,is_binary);
    printf("a %s\n",dtw.resource.get_string(ar));
    dtw.resource.free(ar);
    dtw.resource.commit(t);
    free(a);
}


