
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.macros.h"
//silver_chain_scope_end


typedef struct  DtwRandonizerModule{
    DtwRandonizer * (*newRandonizer)();
    int (*generate_num)(DtwRandonizer *self,int max);
    char * (*generate_token)(DtwRandonizer*self, int size);
    void (*free)(DtwRandonizer *self);
}DtwRandonizerModule;
