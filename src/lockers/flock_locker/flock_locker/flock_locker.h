

typedef struct {
   const char *temp_folder;
}FlockLocker;

FlockLocker * newFlockLocker();


void  FlockLocker_free(FlockLocker *self);