
#include "../doTheWorld/doTheWorldMain.c"
#include "io_testing.c"
#include "monodimension_listage_testing.c"


int main(int argc, char *argv[]){
    
    bool io = test_io_operations();
    if(io){
        puts("All io tests passed");
    }else{
        puts("Some io tests failed");
        return 1;
    }
    bool monodimension_listage = test_monodimension_listage();
    if(monodimension_listage){
        puts("All monodimension listage tests passed");
    }else{
        puts("Some monodimension listage tests failed");
        return 1;
    }
    return 0;
}
