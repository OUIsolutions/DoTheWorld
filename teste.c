

#include "pre_compiled_linux/doTheWorldDeclaration.h"

int main() {
    char *lua  =dtw_load_string_file_content("teste.lua");
    printf("%s\n",lua);
    free(lua);
}