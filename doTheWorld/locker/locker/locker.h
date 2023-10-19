
#define DTW_WAIT_ALL -1
#define DTW_DONT_WAIT -2
#define DTW_FILE_NOT_CORRECT -1
#define DTW_INTERNAL_ERROR -2
typedef struct DtwLocker{
   int expiration;
   char *shared_lock_file;
   int process;

}DtwLocker;


DtwLocker *newDtwLocker(const char *shared_lock_file);

void DtwLocker_create_shared_file(const char *location);


int DtwLocker_lock(struct DtwLocker *self, const  char *element,int max_time);

void DtwLocker_unlock(struct DtwLocker *self, const  char *element);


void DtwLocker_free(struct DtwLocker *self);

