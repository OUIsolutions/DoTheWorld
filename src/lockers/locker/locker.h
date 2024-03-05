
#define DTW_LOCKER_LOCKED 0
#define DTW_LOCKER_IMPOSSIBLE_TO_CREATE_FILE_DESCRIPTOR 5
#define DTW_LOCKER_FLCTL_FAIL 6
#define DTW_LOCKER_WAIT_ERROR 21
typedef struct {

#ifdef _WIN32
    DtwMultiFileLocker  *locker;
#endif

} DtwLocker;


DtwLocker *newDtwLocker();

int DtwLocker_lock(DtwLocker *self, const  char *element);

void DtwLocker_unlock(DtwLocker *self, const  char *element);

void DtwLocker_represemt(DtwLocker *self);

void DtwLocker_free(DtwLocker *self);

