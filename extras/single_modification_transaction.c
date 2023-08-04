#include "doTheWorld/doTheWorldMain.h"
#include <sys/wait.h>

int main (){
    
    dtw_write_string_file_content("a.txt","");

    for(int i = 0; i < 30; i++){ // Alterado para i < 30 para criar 30 processos

        if(fork() == 0){
            DtwResource  *a = new_DtwResource("a.txt");
            a->auto_lock = true;

            char *result = a->get_string(a);
          
            char *formated = calloc(1, strlen(result) + 10);
            sprintf(formated, "%s\n%d", result, i);
            a->set_string(a, formated);

            a->commit(a);
            a->free(a);
            exit(0);
        }
    }

    // Aguardar os processos filhos terminarem
    for (int i = 0; i < 30; i++) {
        int status;
        wait(NULL);
    }

    return 0;
}





