#include "src/one.c"

void append(int num){
    int fd = open("lcok.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Travar o arquivo exclusivamente
    if (flock(fd, LOCK_EX) == -1) {
        perror("Erro ao travar o arquivo");
        close(fd);
        exit(EXIT_FAILURE);
    }

    char *content = dtw_load_string_file_content("arquivo.txt");
    char *new_content = malloc(strlen(content) + 20);
    sprintf(new_content,"%s%d\n",content,num);
    dtw_write_string_file_content("arquivo.txt",new_content);
    free(new_content);
    free(content);

    // Destravar o arquivo
    if (flock(fd, LOCK_UN) == -1) {
        perror("Erro ao destravar o arquivo");
    }

    close(fd);

}
int main(){
    int total_process = 30;
    dtw_write_string_file_content("arquivo.txt","");

    for(int i =0; i < total_process; i++){
        if(fork() ==0){
            append(i);
            exit(0);
        }
    }
    // Aguarda o término de todos os processos filhos

    for (int i = 0; i < total_process; i++) {
        int status;
        wait(&status);
    }

}


//mateusmoutinho@localhost DoTheWorld]$ gcc -c src/one.h -o doTheWorld.o 

