

typedef struct DtwLockerModule{
    DtwLocker * (*newLocker)(const char *shared_lock_file);
    int (*lock)(struct DtwLocker *self, const  char *element,int time);
    void (*unlock)(struct DtwLocker *self, const  char *element);
    void (*free)(struct DtwLocker *self);

}DtwLockerModule;

DtwLockerModule newDtwLockerModule();