//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.typesm.h"
//silver_chain_scope_end




DtwSchema *private_newDtwSchema(const char *name);

DtwSchema * privateDtwSchema_get_sub_schema(DtwSchema *self,const char *name);


DtwSchema * (DtwSchema_new_subSchema)(DtwSchema *self,const char *name);

void DtwSchema_add_primary_key(DtwSchema *self,const char *name);

void private_newDtwSchema_free(DtwSchema *self);
