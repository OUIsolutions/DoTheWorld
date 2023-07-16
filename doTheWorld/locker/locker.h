

typedef struct DtwLocker{

   char *path;
   int process;
   int max_lock_time;
   DtwStringArray *locked_entitys;

   bool (*lock)(struct DtwLocker *self,const  char *element);
   void (*unlock)(struct DtwLocker *self,const  char *element);
   void (*free)(struct DtwLocker *self);

}DtwLocker;



DtwLocker *newDtwLocker(char *path, int process,int max_lock_time);

bool DtwLocker_lock(struct DtwLocker *self,const  char *element);

void DtwLocker_unlock(struct DtwLocker *self,const  char *element);

void DtwLocker_free(struct DtwLocker *self);

