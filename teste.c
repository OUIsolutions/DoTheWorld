#include <stdio.h>
#include <time.h>

int main() {
    clock_t inicio, fim;
    double tempo_decorrido;

    inicio = clock(); // Marca o início da medição
    // Coloque o trecho de código que deseja medir aqui

    fim = clock(); // Marca o fim da medição

    tempo_decorrido = ((double) (fim - inicio)) / CLOCKS_PER_SEC;

    printf("Tempo decorrido: %f segundos\n", tempo_decorrido);

    return 0;
}