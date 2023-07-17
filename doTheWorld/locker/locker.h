
enum {
    PRIVATE_DTW_ABLE_TO_LOCK,
    PRIVATE_DTW_ALREADY_LOCKED_BY_SELF,
    PRIVADE_DTW_LOCKED
};
typedef struct DtwLocker{
   char *separator;
   char *path;
   long reverifcation_delay;
   long min_interval_delay;
   long max_interval_delay;
   int process;
   int max_lock_time;
   DtwStringArray *locked_elements;

   int (*status)(struct DtwLocker *self, const  char *element);
   void (*lock)(struct DtwLocker *self, const  char *element);
   void (*unlock)(struct DtwLocker *self,const  char *element);
   void (*free)(struct DtwLocker *self);

}DtwLocker;


DtwLocker *newDtwLocker(char *path);

void private_DtwLocker_format_element(char *result,struct DtwLocker *self,const  char *element);

int DtwLocker_element_status(struct DtwLocker *self, const  char *element);


void DtwLocker_lock(struct DtwLocker *self, const  char *element);

void DtwLocker_unlock(struct DtwLocker *self,const  char *element);

void DtwLocker_free(struct DtwLocker *self);

