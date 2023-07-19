
#include "doTheWorld/doTheWorldMain.h"

int total_process;
int creation_per_process;
int reverifation_delay;
int wait_delay;

void append_once(int num){

    DtwLocker *locker = newDtwLocker(); 
    //locker->reverifcation_delay =  reverifation_delay;
    //locker->wait_delay = wait_delay;
    locker->process= num;
    locker->lock(locker,"a.txt");
    //printf("processo %d bloqueou\n",num);
    char *elelement = dtw_load_string_file_content("a.txt");
    char *formated = (char*) calloc(30000,sizeof(char*));
    strcpy(formated,elelement);
    char current_num[20];
    sprintf(current_num,"%d\n",num);
    
    for(int x = 0; x < creation_per_process; x++){
        strcat(formated,current_num);
    }

    
    dtw_write_string_file_content("a.txt",formated);
   free(elelement);
    free(formated);
    locker->free(locker);
}

int main(int argc, char *argv[]){
   // printf("%ld",(long)(0.1 * 1000000));

    total_process = atoi(argv[1]);
    creation_per_process = atoi(argv[2]);
    //reverifation_delay =  atoi(argv[3]);
    //wait_delay = atoi(argv[4]);
    
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