

typedef struct DtwDataBase{

    DtwTransaction *cursor;
    DtwLocker *locker;
    char *path;
    bool save_backup;
    bool use_unix_as_backup;

    void (*reconstruct)();
    void (*commit)();

}DtwDataBase;