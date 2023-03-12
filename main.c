#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "code/doTheWorldDevUsage.c"

int main(int argc, char *argv[]){
    
    char *content = "eai beleza parsa";
    char * result = dtw_replace_string(content,"beleza","vai tomar no cu");
    printf("%s\n",result);
    return 0;

}
