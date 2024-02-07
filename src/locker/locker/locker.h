

typedef struct {

   int total_checks;
   int process;
   int max_lock_time;
   DtwStringArray *locked_elements;


}DtwLocker;


DtwLocker *newDtwLocker();

int DtwLocker_lock( DtwLocker *self, const  char *element);

void DtwLocker_unlock( DtwLocker *self, const  char *element);

void DtwLocker_represemt( DtwLocker *self);

void DtwLocker_free( DtwLocker *self);

