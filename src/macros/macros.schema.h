
//silver_chain_scope_start
//mannaged by silver chain
#include "../imports/imports.consts.h"
//silver_chain_scope_end

#define DtwSchemaRebase self->root_props->schema_unsafe =old;
#define privateDtwSchemaUnsafe(scope){\
    bool old = self->root_props->schema_unsafe;\
    self->root_props->schema_unsafe = true;\
    scope;\
    DtwSchemaRebase\
}
