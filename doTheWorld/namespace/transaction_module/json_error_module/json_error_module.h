

typedef struct DtwJsonTransactionErrorModule{
    void (*represent)(struct DtwJsonTransactionError *self);
    void (*prepend_path)(struct DtwJsonTransactionError *self,char *path);
    void (*free)(struct DtwJsonTransactionError *self);

}DtwJsonTransactionErrorModule;

DtwJsonTransactionErrorModule newDtwJsonTransactionErrorModule();