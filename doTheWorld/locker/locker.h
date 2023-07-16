

typedef struct DtwLocker{
   char *separator;
   char *path;
   int process;
   int max_lock_time;
   DtwStringArray *locked_elements;

   bool (*lock)(struct DtwLocker *self,const  char *element);
   void (*unlock)(struct DtwLocker *self,const  char *element);
   void (*free)(struct DtwLocker *self);

}DtwLocker;


DtwLocker *newDtwLocker(char *path, int process,int max_lock_time);

char *private_DtwLocker_format_element(struct DtwLocker *self,const  char *element);
bool DtwLocker_lock(struct DtwLocker *self,const  char *element);

void DtwLocker_unlock(struct DtwLocker *self,const  char *element);

void DtwLocker_free(struct DtwLocker *self);

