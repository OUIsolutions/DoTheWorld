
#ifndef PRIVATE_DTW_JSON_TRANSACTION_MODULE_TYPE_H
#define PRIVATE_DTW_JSON_TRANSACTION_MODULE_TYPE_H
typedef struct DtwJsonTransactionErrorModule{
    void (*represent)(struct DtwJsonTransactionError *self);
    void (*free)(struct DtwJsonTransactionError *self);

}DtwJsonTransactionErrorModule;
#endif
