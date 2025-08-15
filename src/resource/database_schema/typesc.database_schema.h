//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.typesb.h"
//silver_chain_scope_end



#ifndef  PRIVATE_DTW_DATABASE_SCHEMA_TYPE_H
#define PRIVATE_DTW_DATABASE_SCHEMA_TYPE_H
typedef struct DtwDatabaseSchema{

    const char *value_name;
    const char *index_name;
    struct DtwSchema **sub_schemas;
    int size;
}DtwDatabaseSchema;
#endif
