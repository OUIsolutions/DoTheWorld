//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../../imports/imports.fdeclare.h"
//silver_chain_scope_end



DtwTreeTransactionReportModule newDtwTreeTransactionReportModule(){
    DtwTreeTransactionReportModule self = {0};
    self.represent = DtwTreeTransactionReport_represent;
    self.free = DtwTreeTransactionReport_free;
    return self;
}
