
#include "doTheWorld/doTheWorldMain.h"

int total_process;
int creation_per_process;


void append_once(int num){

    DtwLocker *locker = newDtwLocker("aaaa");
    
    locker->lock(locker,"a.txt",-1);
    char *elelement = dtw_load_string_file_content("a.txt");
    char formated[2000] = {0};
    strcpy(formated,elelement);
    char current_num[20];
    sprintf(current_num,"%d\n",num);
    for(int x = 0; x < creation_per_process; x++){
        strcat(formated,current_num);
    }

    dtw_write_string_file_content("a.txt",formated);
   free(elelement);

    locker->free(locker);
}

int main(int argc, char *argv[]){
   // printf("%ld",(long)(0.1 * 1000000));

    total_process = atoi(argv[1]);
    creation_per_process = atoi(argv[2]);

    dtw_remove_any("a.txt");
    dtw_write_string_file_content("a.txt","");

    for(int i = 0; i < total_process; i ++){
        if(fork() == 0){
           // printf("created process %d\n",i);
            append_once(i);
            exit(0);
        }
    }

    

    // Aguarda o término de todos os processos filhos

    for (int i = 0; i < total_process; i++) {
        int status;
        wait(&status);
    }



}