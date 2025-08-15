//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.typesm.h"
//silver_chain_scope_end




DtwResourceArray * newDtwResourceArray();

void DtwResourceArray_append(DtwResourceArray *self, DtwResource *element);


DtwResource * DtwResourceArray_get_by_name(DtwResourceArray *self, const char *name);




void DtwResourceArray_represent(DtwResourceArray *self);

void DtwResourceArray_free(DtwResourceArray *self);
