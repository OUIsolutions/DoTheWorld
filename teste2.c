#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void imprimistring(long teste){
    char convertido = (char)teste;
    printf("\n\tchar do long: %s\n\n", convertido);

}

int main(){
    char *qualque = (char *)malloc(30);
    sprintf(qualque, "slaslasla");
    printf("\n\t%ld\n", (long)qualque);
    qualque  = qualque +2;
    printf("\n\t%ld\n", (long)qualque);
    printf("\n\t%s\n", qualque);
    return 0;
}