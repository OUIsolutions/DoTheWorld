
enum {
    PRIVATE_DTW_ABLE_TO_LOCK,
    PRIVATE_DTW_ALREADY_LOCKED_BY_SELF,
    PRIVADTE_DTW_LOCKED
};
typedef struct DtwLocker{
   char *separator;
   char *path;
   int process;
   int max_lock_time;
   DtwStringArray *locked_elements;

   void (*wait_til_lock)(struct DtwLocker *self, const  char *element);
   void (*unlock)(struct DtwLocker *self,const  char *element);
   void (*free)(struct DtwLocker *self);

}DtwLocker;


DtwLocker *newDtwLocker(char *path, int process,int max_lock_time);

char *private_DtwLocker_format_element(struct DtwLocker *self,const  char *element);

int private_DtwLocker_element_status(struct DtwLocker *self,const  char *element);


void DtwLocker_wait_lock(struct DtwLocker *self, const  char *element);

void DtwLocker_unlock(struct DtwLocker *self,const  char *element);

void DtwLocker_free(struct DtwLocker *self);

