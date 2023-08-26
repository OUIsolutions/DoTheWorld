

typedef struct DtwLocker{
   double reverifcation_delay;
   double wait_delay;
   int process;
   int max_lock_time;
   DtwStringArray *locked_elements;


}DtwLocker;


DtwLocker *newDtwLocker();



void DtwLocker_lock(struct DtwLocker *self, const  char *element);

void DtwLocker_unlock(struct DtwLocker *self, const  char *element);

void DtwLocker_free(struct DtwLocker *self);

