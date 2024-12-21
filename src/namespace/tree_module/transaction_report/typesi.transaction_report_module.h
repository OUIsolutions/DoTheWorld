
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.typesg.h"
//silver_chain_scope_end

typedef struct  DtwTreeTransactionReportModule{

    void (*represent)(struct DtwTreeTransactionReport *report);
    void (*free)(struct DtwTreeTransactionReport *report);

}DtwTreeTransactionReportModule;
