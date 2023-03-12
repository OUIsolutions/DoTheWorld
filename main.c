#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "code/doTheWorldDevUsage.c"

int main(int argc, char *argv[]){
    
    dtw_write_string_file_content("exemple/a/b/teste.txt","teste",true);
    dtw_write_string_file_content("exemple/a/b/teste2.txt","teste2",true);
    dtw_write_string_file_content("exemple/a/b/teste3.txt","teste3",true);
    dtw_write_string_file_content("exemple/a/b/teste4.txt","teste4",true);
   // dtw_remove_any("exemple");

   //dtw_remove_any("exemple");
    return 0;

}
