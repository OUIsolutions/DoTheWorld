#include "doTheWorld.h"



int main (){
    DtwNamespace dtw = newDtwNamespace();

    for(int i =0 ; i<10; i++){if(fork()==0){
            DtwResource *test = dtw.resource.newResource("testarget");
            DtwResource *a = dtw.resource.sub_resource(test,"numerical.txt");
            dtw.resource.lock(a);
            char *content = NULL;

            if(dtw.resource.type(a) != DTW_NOT_FOUND){
                content = dtw.resource.get_string(a);
            }

            char formated[2000] ={0};
            if(content){
                sprintf(formated,"%s\n%d",content,i);
            }
            else{
                sprintf(formated,"%d",i);
            }

            dtw.resource.set_string(a,formated);
            dtw.resource.commit(test);
            dtw.resource.free(test);
            exit(0);
    }}

}





