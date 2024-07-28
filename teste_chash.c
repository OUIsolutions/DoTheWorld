#define DTW_ALLOW_CHASH
#include "extras/CHashManipulator.h"


#include "src/one.c"
DtwNamespace dtw;
DtwRandonizer *randonizer;
CHashNamespace hash;

typedef struct Filtragem{
    int idade;
} Filtragem;


CHash * Retorna_json_formatado(DtwResource *user, void *filtragem){
    return  newCHashObject(
      "nome",hash.newString(dtw.resource.get_string_from_sub_resource(user, "nome")),
      "idade",hash.newNumber(dtw.resource.get_long_from_sub_resource(user, "idade"))
    );
}

int ordena_por_idade(DtwResource *user1,DtwResource *user2,void *args) {
    long idade1 = dtw.resource.get_long_from_sub_resource(user1, "idade");
    long idade2 = dtw.resource.get_long_from_sub_resource(user2, "idade");
    return  idade1 - idade2;
}

bool verifica_se_e_adiciona(DtwResource *user, void *filtragem){
    Filtragem *f = (Filtragem*)filtragem;
    long idade = dtw.resource.get_long_from_sub_resource(user, "idade");
    if(idade < f->idade){
        return true;
    }

    return false;
}

int main(){
    dtw = newDtwNamespace();
    randonizer = dtw.randonizer.newRandonizer();
    hash = newCHashNamespace();
    DtwResource *usuarios = dtw.resource.newResource("usuarios2");

    Filtragem f;
    f.idade = 18;

    CHash *itens = dtw.resource.map_CHashArray(
        usuarios,
        verifica_se_e_adiciona,
        ordena_por_idade,
        Retorna_json_formatado,
        (void*)&f,
        0,
        5
        );
    char *texto = hash.dump_to_json_string(itens);
    dtw.write_string_file_content("saida2.json", texto);
    hash.free(itens);
    free(texto);
    dtw.randonizer.free(randonizer);
    dtw.resource.free(usuarios);
    return 0;
}
