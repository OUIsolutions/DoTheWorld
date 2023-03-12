#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "code/doTheWorldSeparated.c"

int main(int argc, char *argv[]){

    struct DtwStringArray * path = dtw_list_all_recursively("code",true);
    printf("%i",path->size);
}
