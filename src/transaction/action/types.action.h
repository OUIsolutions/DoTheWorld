
#ifndef PRIVATE_DTW_ACTION_TRANSACTION_TYPE_H
#define PRIVATE_DTW_ACTION_TRANSACTION_TYPE_H
typedef struct DtwActionTransaction{
    short action_type;
    unsigned  char *content;
    long size;
    bool is_binary;
    DtwEncriptionInterface *encryption;
    short encryption_mode;

    char *dest;
    char *source;

}DtwActionTransaction;
#endif
