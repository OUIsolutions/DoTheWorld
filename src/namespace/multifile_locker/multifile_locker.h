

typedef struct DtwMultiFileLockerModule{
    DtwMultiFileLocker * (*newLocker)();
    int (*lock)(DtwMultiFileLocker *self, const  char *element);
    void (*unlock)(DtwMultiFileLocker *self, const  char *element);
    void (*represemt)(DtwMultiFileLocker *self);
    void (*free)(DtwMultiFileLocker *self);

}DtwMultiFileLockerModule;

DtwMultiFileLockerModule newDtwLockerModule();