
#define DTW_WAIT_ALL -1
#define DTW_DONT_WAIT -2
#define DTW_FILE_NOT_CORRECT -1
#define DTW_INTERNAL_ERROR -2
#define DTW_TIMEOUT_ERROR -3
typedef struct DtwLocker{
   int expiration;
   char *shared_lock_file;
   int process;

}DtwLocker;


DtwLocker *newDtwLocker(const char *shared_lock_file);

void DtwLocker_create_shared_file(const char *location);


int privateDtwLocker_json_enssure_correct(struct DtwLocker *self, cJSON *elements);

void  privateDtwLocker_remove_expireds(struct DtwLocker *self,cJSON *elements);

int  privateDtwLocker_get_locked_position_from_json(struct DtwLocker *self,cJSON *elements,const char *element);



int DtwLocker_lock(DtwLocker *self, const  char *element,int max_time);

void DtwLocker_unlock(DtwLocker *self, const  char *element);


void DtwLocker_free(DtwLocker *self);

