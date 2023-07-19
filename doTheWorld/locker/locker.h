

typedef struct DtwLocker{
   char *separator;
   double reverifcation_delay;

   int process;
   int max_lock_time;
   DtwStringArray *locked_elements;

   int (*status)(struct DtwLocker *self, const  char *element);
   void (*lock)(struct DtwLocker *self, const  char *element);
   void (*free)(struct DtwLocker *self);

}DtwLocker;


DtwLocker *newDtwLocker();



void DtwLocker_lock(struct DtwLocker *self, const  char *element);


void DtwLocker_free(struct DtwLocker *self);

