

typedef struct DtwResource{

        bool allow_transaction;
        bool auto_lock;
        bool locked;
        DtwTransaction  *transaction;
    #ifdef  __linux__
        DtwLocker  *locker;
    #endif
        char *mothhers_path;
        char *name;
        char *path;

        bool child;

    //cache implementation
    bool resset_cache;

    bool cache_used;
    int cache_type;

    int cache_size;
    unsigned char *cache_any;
    double cache_number;



}DtwResource;




DtwResource *new_DtwResource(const char *path);

DtwResource * DtwResource_sub_resource(DtwResource *self,const  char *name);

void DtwResource_lock(DtwResource *self);

void private_DtwResource_lock_if_auto_lock(DtwResource *self);

void DtwResource_clear_cache(DtwResource *self);



void DtwResource_rename(DtwResource *self, char *new_name);

void DtwResource_set_binary(DtwResource *self, unsigned char *element, long size);

void DtwResource_set_string(DtwResource *self,const  char *element);

void DtwResource_set_long(DtwResource *self,long element);

void DtwResource_set_double(DtwResource *self,double element);

void DtwResource_set_bool( DtwResource *self,bool element);

unsigned char *DtwResource_get_any(DtwResource *self, long *size, bool *is_binary);

void DtwResource_destroy(DtwResource *self);

DtwStringArray *DtwResource_list(DtwResource *self);

unsigned char *DtwResource_get_binary(DtwResource *self, long *size);

char *DtwResource_get_string(DtwResource *self);

long DtwResource_get_long(DtwResource *self);

double DtwResource_get_double(DtwResource *self);

int DtwResource_type(DtwResource *self);

const char * DtwResource_type_in_str(DtwResource *self);

bool DtwResource_get_bool(DtwResource *self);

void DtwResource_commit(DtwResource *self);

void DtwResource_represent(DtwResource *self);

void DtwResource_free(struct DtwResource *self);