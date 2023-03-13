#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "code/doTheWorldSeparated.c"

int main(int argc, char *argv[]){

  struct DtwTreePart *tree_part = dtw_tree_part_constructor("deer.jpgaa",true);
  tree_part->represent(tree_part);

}
