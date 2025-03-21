//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../../imports/imports.fdeclare.h"
//silver_chain_scope_end



DtwJsonTransactionErrorModule newDtwJsonTransactionErrorModule(){
    DtwJsonTransactionErrorModule self = {0};
    self.represent = DtwJsonTransactionError_represent;
    self.free = DtwJsonTransactionError_free;
    return self;
}
