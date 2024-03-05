#define DTW_MULTIFILE_LOCKER_TOTAL_CHECK 500
#define DTW_MULTIFILE_LOCKER_MAX_TIMEOUT 10
#define DTW_MULFILE_LOCKER_MAX_WAIT 10
#define DTW_MULFILE_LOCKER_LOCKED 0
#define DTW_MULTIFILE_LOCKER_FAIL_INTERVAL_MAX 50
#define DTW_MULTIFILE_LOCKER_WAIT_ERROR 1


typedef struct {

   int total_checks;
   int process;
   int max_wait;
   int max_lock_time;
   DtwStringArray *locked_elements;


}DtwMultiFileLocker;


DtwMultiFileLocker *newDtwMultiFileLocker();

int DtwMultiFIleLocker_lock(DtwMultiFileLocker *self, const  char *element);

void DtwMultifileLocker_unlock(DtwMultiFileLocker *self, const  char *element);

void DtwMultiFileLocker_represemt(DtwMultiFileLocker *self);

void DtwMultiFileLocker_free(DtwMultiFileLocker *self);

