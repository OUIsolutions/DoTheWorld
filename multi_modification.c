
#include "doTheWorld/doTheWorldMain.h"

int total_process;
int creation_per_process;
double reverifation_delay;
double wait_delay;
char *target = "a.txt";

void append_x_times(int num,int times){

  
    
    char result[30] ={0};
    sprintf(result,"%d\n",num);

    for(int i = 0; i < times; i++){
        DtwLocker *locker = newDtwLocker();
        locker->reverifcation_delay =  reverifation_delay;
        locker->wait_delay = wait_delay;
        locker->process= num;
        locker->lock(locker,target);
        printf("process %d get the ownership\n",num);
        //printf("aaaaaaaaaaa %d\n",times);

        char *content = dtw_load_string_file_content(target);

        content = realloc(content,strlen(content) + 20);
        strcat(content,result);
        
        dtw_write_string_file_content(target,content);
        free(content);


        locker->free(locker);
        sleep(1);

    }
    


}

int main(int argc, char *argv[]){

    total_process  = 20;
    creation_per_process = 10;
    reverifation_delay = 0.1;
    wait_delay = 0.5;


    dtw_remove_any(target);
    dtw_write_string_file_content(target,"");

    for(int i = 0; i < total_process; i ++){

        if(fork() == 0){
            // printf("created process %d\n",i);
            append_x_times(i,creation_per_process);
            exit(0);
        }

    }



    // Aguarda o término de todos os processos filhos

    for (int i = 0; i < total_process; i++) {
        int status;
        wait(&status);
    }



}