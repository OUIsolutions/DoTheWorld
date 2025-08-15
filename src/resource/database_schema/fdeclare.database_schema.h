//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.typesm.h"
//silver_chain_scope_end







DtwDatabaseSchema *private_newDtwDtatabaseSchema();

DtwSchema * privateDtwDtatabaseSchema_get_sub_schema(DtwDatabaseSchema *self,const char *name);

DtwSchema * DtwDtatabaseSchema_new_subSchema(DtwDatabaseSchema *self,const char *name);

void private_new_DtwDtatabaseSchema_free(DtwDatabaseSchema *self);
