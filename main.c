#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "code/doTheWorldDevUsage.c"

int main(int argc, char *argv[]){
    
    const char *frase = "eai beleza , ta tudo certo? beleza";
    char * nova = dtw_replace_string(frase, "beleza", "legal");
    printf("%s", nova);

}
