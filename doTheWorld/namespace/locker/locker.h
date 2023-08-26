

typedef struct DtwLockerModule{
    DtwLocker * (*newLocker)();
    void (*lock)(struct DtwLocker *self, const  char *element);
    void (*unlock)(struct DtwLocker *self, const  char *element);
    void (*represemt)(struct DtwLocker *self);
    void (*free)(struct DtwLocker *self);

}DtwLockerModule;

DtwLockerModule newDtwLockerModule();