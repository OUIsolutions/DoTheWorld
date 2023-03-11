#include "code/doTheWorldDevUsage.c"

int main(int argc, char *argv[])
{

    int size;
    bool is_binary;
    char *teste = dtw_load_string_file_content("README.md");
    printf("content: %s", teste);
    dtw_write_string_file_content("teste/vvv/xxx/xx/x/teste.txt", teste, true);
    free(teste);
}