

typedef struct DtwLockerModule{
    DtwLocker * (*newLocker)(const char *shared_lock_file);
    void (*create_shared_file)(const char *location);

    int (*lock)(struct DtwLocker *self, const  char *element,int max_time);
    int (*unlock)(struct DtwLocker *self, const  char *element);
    void (*free)(struct DtwLocker *self);

}DtwLockerModule;

DtwLockerModule newDtwLockerModule();