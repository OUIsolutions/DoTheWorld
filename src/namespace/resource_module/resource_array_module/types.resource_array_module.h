
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.macros.h"
//silver_chain_scope_end


typedef struct DtwResourceArrayModule{

    void (*append)(DtwResourceArray *self, DtwResource *element);
    DtwResource * (*get_by_name)(DtwResourceArray *self, const char *name);
    void (*represent)(DtwResourceArray *self);
    void (*free)(DtwResourceArray *self);

}DtwResourceArrayModule;
