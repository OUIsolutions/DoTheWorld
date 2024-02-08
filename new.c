
#include "src/one.h"

int total_process;
int creation_per_process;
long total_checks;
char *target = "a.txt";

void append_once(int num){

    DtwLocker *locker = newDtwLocker();

    locker->process= num;
    locker->total_checks = total_checks;
    DtwLocker_lock(locker,target);
    printf("processo %d bloqueou\n",num);
    char *elelement = dtw_load_string_file_content(target);
    char *formated = (char*) calloc(30000,sizeof(char*));
    strcpy(formated,elelement);
    char current_num[20];
    sprintf(current_num,"%d\n",num);

    for(int x = 0; x < creation_per_process; x++){
        strcat(formated,current_num);
    }


    dtw_write_string_file_content(target,formated);
    free(elelement);
    free(formated);
    DtwLocker_free(locker);
}

int main(int argc, char *argv[]){

    total_process  = atoi(argv[1]);
    creation_per_process = atoi(argv[2]);
    total_checks = atoi(argv[3]);



    dtw_remove_any(target);
    dtw_write_string_file_content(target,"");

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