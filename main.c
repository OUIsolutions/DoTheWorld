#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "code/doTheWorldDevUsage.c"

int main(int argc, char *argv[]){
    
    char *content = "eai beleza parsa";
    char * result = dtw_change_beginning_of_string(content,strlen("eai"),"oi");
    printf("%s",result);
}
