//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.types.h"
//silver_chain_scope_end


#ifndef PRIVATE_DTW_TRANSACTION_REPORT_TYPE_H
#define PRIVATE_DTW_TRANSACTION_REPORT_TYPE_H
typedef struct DtwTreeTransactionReport{
    DtwStringArray *write;
    DtwStringArray *modify;
    DtwStringArray *remove;

}DtwTreeTransactionReport;
#endif
