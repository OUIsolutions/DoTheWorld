
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.macros.h"
//silver_chain_scope_end

#ifndef PRIVATE_DTW_DATABASE_SCHEMA_MODULE_TYPE_H
#define PRIVATE_DTW_DATABASE_SCHEMA_MODULE_TYPE_H
typedef struct {
    DtwSchema * (*sub_schema)(DtwDatabaseSchema *self,const char *name);
}DtwDatabaseSchemaModule;
#endif
