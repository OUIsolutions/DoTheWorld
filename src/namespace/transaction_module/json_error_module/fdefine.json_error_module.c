
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.fdeclare.h"
//silver_chain_scope_end


DtwJsonTransactionErrorModule newDtwJsonTransactionErrorModule(){
    DtwJsonTransactionErrorModule self = {0};
    self.represent = DtwJsonTransactionError_represent;
    self.free = DtwJsonTransactionError_free;
    return self;
}
