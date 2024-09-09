#include "../StringArray.h"

#ifndef PRIVATE_DTW_TRANSACTION_REPORT_TYPE_H
#define PRIVATE_DTW_TRANSACTION_REPORT_TYPE_H
typedef struct DtwTreeTransactionReport{
    DtwStringArray *write;
    DtwStringArray *modify;
    DtwStringArray *remove;

}DtwTreeTransactionReport;
#endif
