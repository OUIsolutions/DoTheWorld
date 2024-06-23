#include "src/one.c"

DtwNamespace dtw;




int main(){
    DtwNamespace  dtw = newDtwNamespace();
    dtw.remove_any("tokens");
    for(int i = 0; i <4; i++){

            //printf("pid =%d\n",i);
            DtwRandonizer *random = dtw.randonizer.newRandonizer();
            char *creation = dtw.randonizer.generate_token(random,20);
            char *path = dtw.concat_path("tokens",creation);
            printf("token %d =%s\n",i,path);
            free(path);
            free(creation);
            dtw.randonizer.free(random);

    }
}


