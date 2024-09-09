#ifndef PRIVATE_DTW_JSON_TRANSACTION_ERROR_TYPE_H
#define PRIVATE_DTW_JSON_TRANSACTION_ERROR_TYPE_H
typedef struct DtwJsonTransactionError{
    int code;
    char *mensage;
    char *path;


}DtwJsonTransactionError;
#endif
