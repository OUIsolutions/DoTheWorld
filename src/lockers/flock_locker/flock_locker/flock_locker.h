
typedef struct {
   const char *temp_folder;
   privateFlockArray  *locked_files;
}FlockLocker;

FlockLocker * newFlockLocker();

void private_FlockLocker_unlock_by_index(FlockLocker *self, int index);

void FlockLocker_unlock(FlockLocker *self, const char *filename);

int FlockLocker_lock(FlockLocker *self, const char *filename);

void  FlockLocker_free(FlockLocker *self);