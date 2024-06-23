#include "src/one.c"

DtwNamespace dtw;




int main(){
    DtwNamespace  dtw = newDtwNamespace();

    for(int i = 0 ;  i <4 ; i++){if(fork()==0) {
        DtwRandonizer *random = dtw.randonizer.newRandonizer();
        char *creation = dtw.randonizer.generate_token(random,20);
        printf("%s\n",creation);

    }}
}


