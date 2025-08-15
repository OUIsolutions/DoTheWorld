//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../../imports/imports.dep_define.h"
//silver_chain_scope_end



DtwTreeTransactionReportModule newDtwTreeTransactionReportModule(){
    DtwTreeTransactionReportModule self = {0};
    self.represent = DtwTreeTransactionReport_represent;
    self.free = DtwTreeTransactionReport_free;
    return self;
}
