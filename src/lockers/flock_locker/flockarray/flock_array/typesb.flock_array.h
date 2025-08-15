//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../../../imports/imports.types.h"
//silver_chain_scope_end


#if defined(__linux__) || defined(__APPLE__)

typedef struct {
    privateDtwFlockLockedElement **elements;
    int size;
}privateDtwFlockArray;
#endif
