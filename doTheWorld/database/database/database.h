

typedef struct DtwDataBase{

    DtwTransaction *cursor;
    DtwLocker *locker;
    char *path;
    char *data_path;
    int max_lock_time;
    bool save_backup;
    bool use_unix_time;

    DtwJsonTransactionError *(*reconstruct)(struct DtwDataBase *self);
    DtwJsonTransactionError *(*commit)(struct DtwDataBase *self);
    void (*free)(struct DtwDataBase *self);
}DtwDataBase;

DtwDataBase * newDtwDataBase(const char *path);

DtwJsonTransactionError *DtwDataBase_reconstruct(struct DtwDataBase *self);
DtwJsonTransactionError *DtwDataBase_commit(struct DtwDataBase *self);
void DtwDataBase_free(struct DtwDataBase *self);

