//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.typesg.h"
//silver_chain_scope_end


#ifndef PRIVATE_DTW_DATABASE_SCHEMA_MODULE_TYPE_H
#define PRIVATE_DTW_DATABASE_SCHEMA_MODULE_TYPE_H
typedef struct {
    DtwSchema * (*sub_schema)(DtwDatabaseSchema *self,const char *name);
}DtwDatabaseSchemaModule;
#endif
