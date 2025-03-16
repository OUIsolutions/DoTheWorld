
### Locker
With the locker you can Lock files and ensure that even with multprocessment, they will
be executed in an order

```c

#include "doTheWorld.h"




void append_text(const char *file,char *text){
    DtwNamespace dtw = newDtwNamespace();


    DtwLocker *locker = newDtwLocker();
    while(dtw.locker.lock(locker,file));
    //printf("process %d get the ownership\n",locker->process);

    char *content = dtw.load_string_file_content(file);

    content = realloc(content,strlen(content) + strlen(text) + 2);
    strcat(content,text);

    dtw.write_string_file_content(file,content);
    free(content);


    dtw.locker.free(locker);

}

int main(int argc, char *argv[]){


    DtwNamespace dtw = newDtwNamespace();


    const char *file = "tests/target/append.txt";
    int total_process  = 10;
    // this will reset the file
    dtw.remove_any(file);
    dtw.write_string_file_content(file,"");

    for(int i = 0; i < total_process; i ++){

        if(fork() == 0){
            char formated_content[1000] = {0};
            sprintf(formated_content,"text of: %d process %d \n",i,getpid());
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

```
