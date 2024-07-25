#ifndef PRIVATE_DTW_TRANSACTION_REPORT_MODULE_TYPE_H
#define PRIVATE_DTW_TRANSACTION_REPORT_MODULE_TYPE_H
typedef struct  DtwTreeTransactionReportModule{

    void (*represent)(struct DtwTreeTransactionReport *report);
    void (*free)(struct DtwTreeTransactionReport *report);

}DtwTreeTransactionReportModule;
#endif
