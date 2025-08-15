//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../../imports/imports.typesm.h"
//silver_chain_scope_end



void private_DtwResurce_destroy_primary_key(DtwResource *self);


void private_DtwResource_destroy_all_primary_keys(DtwResource *self);

void DtwResource_destroy(DtwResource *self);


void DtwResource_destroy_sub_resource(DtwResource *self, const char *key);
