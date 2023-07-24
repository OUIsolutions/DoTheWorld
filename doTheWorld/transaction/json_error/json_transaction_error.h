
typedef struct DtwJsonTransactionError{
    int code;
    char *mensage;
    char *path;
    void (*represent)(struct DtwJsonTransactionError *self);
    void (*free)(struct DtwJsonTransactionError *self);

}DtwJsonTransactionError;

DtwJsonTransactionError * private_new_DtwJsonTransactionError( int code,const char *mensage,const  char *path);

void DtwJsonTransactionError_represent(struct DtwJsonTransactionError *self);

void DtwJsonTransactionError_free(struct DtwJsonTransactionError *self);
