
#define DTW_WAIT_ALL -1;
#define DTW_DONT_WAIT -2;
#define DTW_FILE_NOT_CORRECT -1;
#define DTW_INTERNAL_ERROR -2;
typedef struct DtwLocker{

   char *shared_lock_file;
   int process;

}DtwLocker;


DtwLocker *newDtwLocker(const char *shared_lock_file);

void dtw_create_lock_shared_file(const char *location,long max_lock_time);



int DtwLocker_lock(struct DtwLocker *self, const  char *element,int time);

void DtwLocker_unlock(struct DtwLocker *self, const  char *element);

void DtwLocker_represemt(struct DtwLocker *self);

void DtwLocker_free(struct DtwLocker *self);

