//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.types.h"
//silver_chain_scope_end


#ifndef PRIVATE_DT_TRANSACTION_TYPE_H
#define PRIVATE_DT_TRANSACTION_TYPE_H

typedef struct DtwTransaction{
    DtwEncriptionInterface *encryption;
    short encryption_mode;
    DtwActionTransaction  **actions;
    bool encryption_owner;
    long size;

}DtwTransaction;
#endif
