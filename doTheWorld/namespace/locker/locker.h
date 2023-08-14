

typedef struct DtwLockerModule{

    void (*lock)(struct DtwLocker *self, const  char *element);
    void (*free)(struct DtwLocker *self);

}DtwLockerModule;

DtwLockerModule newDtwLockerModule();