
#include "doTheWorld.h"


void append_text(char *file,char *text){

  
    DtwLocker *locker = newDtwLocker();
    locker->lock(locker,file);
    printf("process %d get the ownership\n",locker->process);

    char *content = dtw_load_string_file_content(file);

    content = realloc(content,strlen(content) + 20);
    strcat(content,text);
        
    dtw_write_string_file_content(file,content);
    free(content);


    locker->free(locker);
    
}

int main(int argc, char *argv[]){

    char *file = "tests/target/append.txt";
    int total_process  = 20;

    dtw_remove_any(file);
    dtw_write_string_file_content(file,"");

    for(int i = 0; i < total_process; i ++){

        if(fork() == 0){
            char formated_content[100] = {0};
            sprintf(formated_content,"text of: %d\n",i);
            append_text(file,formated_content);
            
            exit(0);
        }

    }

    // Hold the end of other process

    for (int i = 0; i < total_process; i++) {
        int status;
        wait(&status);
    }



}