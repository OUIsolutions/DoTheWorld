#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "code/doTheWorldSeparated.c"

int main(int argc, char *argv[]){

   struct DtwPath *path = dtw_constructor_path("/home/andres/DoTheWorld.c");
   path->represent(path);

}
