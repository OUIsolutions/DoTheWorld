
#include <stdio.h>
#define DTW_DEBUG_TIME
#include "src/one.c"
DtwNamespace dtw;
DtwRandonizer *randonizer;

typedef struct {
    int idade;
} Filtragem;

cJSON * Retorna_json_formatado(DtwResource *user, void *filtragem){
    cJSON *obj_criado = cJSON_CreateObject();
    cJSON_AddStringToObject(obj_criado, "nome", dtw.resource.get_string_from_sub_resource(user, "nome"));
    cJSON_AddNumberToObject(obj_criado, "idade", dtw.resource.get_long_from_sub_resource(user, "idade"));
    return obj_criado;
}


bool verifica_se_e_um_json(DtwResource *user, void *filtragem){
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

    cJSON *itens = DtwResource_map_cJSON(
        usuarios,
        verifica_se_e_um_json,
        Retorna_json_formatado,
        &f,
        0,
        -1
        );
   
    char *texto = cJSON_Print(itens);
    dtw.write_string_file_content("saida.json", texto);

    return 0;
}




