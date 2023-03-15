
#include "doTheWorld.c"


int main() {
    // Exemplo de JSON para ser analisado
    // Criar um novo objeto JSON
    cJSON *new_json = cJSON_CreateObject();
    cJSON_AddStringToObject(new_json, "name", "Maria");
    cJSON_AddNumberToObject(new_json, "age", 25);

    // Criar um novo array JSON
    cJSON *new_array = cJSON_CreateArray();
    cJSON_AddItemToArray(new_array, cJSON_CreateString("blue"));
    cJSON_AddItemToArray(new_array, cJSON_CreateString("red"));
    cJSON_AddItemToArray(new_array, cJSON_CreateString("green"));

    // Adicionar o array ao objeto JSON
    cJSON_AddItemToObject(new_json, "colors", new_array);

    // Gerar JSON a partir do objeto
    char *new_json_str = cJSON_Print(new_json);


    // Imprimir o novo JSON gerado
    printf("New JSON: %s\n", new_json_str);

    // Liberar memória alocada

    cJSON_Delete(new_json);
    free(new_json_str);

    return 0;
}