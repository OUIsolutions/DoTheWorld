
#include <stdio.h>
#define DTW_DEBUG_TIME
#include "src/declaration.h"
DtwNamespace dtw;
DtwRandonizer *randonizer;

typedef struct {
    int idade;
}Filtragem;

int sla = 0;

void imprime_user(DtwResource *user, void *filtragem){
    sla++;
    printf("nome: %s\n", dtw.resource.get_string_from_sub_resource(user, "nome"));
}


bool verifica_imprime_user(DtwResource *user, void *filtragem){

     Filtragem *f = (Filtragem *)filtragem;

    long idade = dtw.resource.get_long_from_sub_resource(user, "idade");

    if(idade < f->idade){

        return true;
    }

    return false;
}

int main(){
    dtw = newDtwNamespace();
    randonizer = dtw.randonizer.newRandonizer();

    DtwResource *usuarios = dtw.resource.newResource("usuarios");

    Filtragem f;
    f.idade = 18;

    DtwResource_foreach(usuarios, verifica_imprime_user, imprime_user, &f, 0, -1);

    return 0;
}
