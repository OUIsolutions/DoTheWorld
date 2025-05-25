#include "doTheWorldOne.c"


int main (){
    DtwNamespace dtw = newDtwNamespace();

    for(int i =0 ; i<10; i++){if(fork()==0){
            DtwResource *test = new_DtwResource("tests/target");
            DtwResource *a = DtwResource_sub_resource(test,"numerical.txt");
            DtwResource_lock(a);
            char *content = NULL;

            if(DtwResource_type(a) != DTW_NOT_FOUND){
                content = DtwResource_get_string(a);
            }

            char formated[2000] ={0};
            if(content){
                sprintf(formated,"%s\n%d",content,i);
            }
            else{
                sprintf(formated,"%d",i);
            }

            DtwResource_set_string(a,formated);
            DtwResource_commit(test);
            DtwResource_free(test);
            exit(0);
    }}

}
