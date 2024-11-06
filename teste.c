#include "src/one.c"


int main(){

    char *teste = dtw_get_absolute_path("src");
    if(teste){
        printf("%s\n",teste);
        free(teste);
    }
    else{
        printf("path não existe\n");
    }
    return 0;
}
