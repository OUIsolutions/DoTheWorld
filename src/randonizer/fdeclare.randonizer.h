
//silver_chain_scope_start
//mannaged by silver chain
#include "../imports/imports.globals.h"
//silver_chain_scope_end






DtwRandonizer * newDtwRandonizer();

int DtwRandonizer_generate_num(DtwRandonizer *self,int max);

char * DtwRandonizer_generate_token(struct DtwRandonizer*self, int size);
void DtwRandonizer_free(struct DtwRandonizer *self);