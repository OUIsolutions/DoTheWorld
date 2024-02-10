#define DTW_LOCKER_TOTAL_CHECK 500

#define DTW_LOCKER_MAX_TIMEOUT 10
#define DTW_LOCKER_MAX_WAIT 10
#define DTW_LOCKER_LOCKED 0
#define  DTW_FAIL_LOCKER_DELAY 100
#define DTW_LOCKER_WAIT_ERROR 1



typedef struct {

   int total_checks;
   int process;
   double delay;
   int max_wait;
   int max_lock_time;
   DtwStringArray *locked_elements;


}DtwLocker;


DtwLocker *newDtwLocker();

int DtwLocker_lock( DtwLocker *self, const  char *element);

void DtwLocker_unlock( DtwLocker *self, const  char *element);

void DtwLocker_represemt( DtwLocker *self);

void DtwLocker_free( DtwLocker *self);

