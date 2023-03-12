#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "code/structs/path.c"

int main(int argc, char *argv[]){
    
    struct DtwPath *path = dtw_constructor_path("/home/andres/Documentos/teste.c");
    path->set_name(path, "teste123");
    path->set_extension(path, "txt");
    path->represent(path);
    path->delete(path);
}
