
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.typesg.h"
//silver_chain_scope_end

typedef struct {
    void (*add_primary_key)(DtwSchema *self, const char *primary_key);
    DtwSchema * (*sub_schema)(DtwSchema *self,const char *name);
}DtwSchemaModule;
