#include "code/doTheWorldDevUsage.c"

int main(int argc, char *argv[])
{

    int size;
    bool is_binary;
    char *teste = dtw_load_any_content("deer.jpg", &size, &is_binary);
    printf("size: %i\n", size);
    printf("is_binary: %i\n", is_binary);
    // dtw_write_binary_recursively("teste.txt","teste",0);
}