typedef struct Filtragem{
    int idade;
} Filtragem;

#include <stdio.h>
#define DTW_DEBUG_TIME
#include "src/one.c"
DtwNamespace dtw;
DtwRandonizer *randonizer;


cJSON * Retorna_json_formatado(DtwResource *user, void *filtragem){
    cJSON *obj_criado = cJSON_CreateObject();

    cJSON_AddStringToObject(obj_criado, "nome", dtw.resource.get_string_from_sub_resource(user, "nome"));
    cJSON_AddNumberToObject(obj_criado, "idade", dtw.resource.get_long_from_sub_resource(user, "idade"));
    return obj_criado;
}

int ordena_por_idade(DtwResource *user1,DtwResource *user2,void *args) {
    printf("aaaaa\n");
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

    DtwResource *usuarios = dtw.resource.newResource("usuarios");

    Filtragem f;
    f.idade = 18;

    cJSON *itens = DtwResource_map_cJSON(
        usuarios,
        verifica_se_e_adiciona,
        ordena_por_idade,
        Retorna_json_formatado,
        (void*)&f,
        0,
        5
        );

    char *texto = cJSON_Print(itens);
    dtw.write_string_file_content("saida.json", texto);
    cJSON_Delete(itens);
    free(texto);
    dtw.randonizer.free(randonizer);
    dtw.resource.free(usuarios);
    return 0;
}
