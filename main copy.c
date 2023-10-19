
#include "doTheWorld/doTheWorldMain.h"


int main() {
    // Criar um file descriptor virtual na memória
    DtwLocker_create_shared_file("lock");

    dtw_write_string_file_content("a.txt","");


    for(int i =0; i < 20; i++){if(fork()==0){
            DtwLocker *t = newDtwLocker("lock");
            t->expiration = 20;
            for(int j =0 ;j <10;j++){
                DtwLocker_lock(t,"a.txt",DTW_WAIT_ALL);
                //printf("liberou para o %ld\n",i);
                char *conteudo = dtw_load_string_file_content("a.txt");
                char formated[10000] ={0};
                sprintf(formated,"%s%d:%d\n",conteudo,i,j);
                dtw_write_string_file_content("a.txt",formated);
                if(i ==10 && j==5){
                    printf("esperando\n");
                    sleep(10);
                    printf("saiu\n");

                }
                free(conteudo);
                DtwLocker_unlock(t,"a.txt");
            }

            DtwLocker_free(t);

            exit(0);
        }}


    return 0;
}





