#define DTW_CACHE_UNUSED 0 
#define DTW_CACHE_LOADED_ONLY_TYPE 1 
#define DTW_CACHE_LOADED 2
#define DTW_LOAD_RESOURCE true
#define DTW_NOT_LOAD_RESOURCE false

typedef struct DtwResource{

        bool allow_transaction;
        bool auto_lock;
        bool locked;
        DtwTransaction  *transaction;
    #ifdef  __linux__
        DtwLocker  *locker;
    #endif
        char *mothers_path;
        char *name;
        char *path;
        bool child;

    bool loaded;
    bool is_binary;
    unsigned char *value_any;
    long value_size;
   
    //cache implementation

    void *sub_resources;



}DtwResource;




DtwResource *new_DtwResource(const char *path);

DtwResource * DtwResource_sub_resource(DtwResource *self,const  char *name,bool load_content);

DtwResource * DtwResource_sub_resource_loading(DtwResource *self,const  char *name);

DtwResource * DtwResource_sub_resource_not_loading(DtwResource *self,const  char *name);


void DtwResource_unload(DtwResource *self);

void DtwResource_load(DtwResource *self);

void DtwResource_load_if_not_loaded(DtwResource *self);

void DtwResource_lock(DtwResource *self);

void private_DtwResource_lock_if_auto_lock(DtwResource *self);

void DtwResource_rename(DtwResource *self, char *new_name);

//getters
unsigned char *DtwResource_get_binary(DtwResource *self, long *size);

char *DtwResource_get_string(DtwResource *self);

long DtwResource_get_long(DtwResource *self);

double DtwResource_get_double(DtwResource *self);

bool DtwResource_get_bool(DtwResource *self);

void DtwResource_set_binary(DtwResource *self, unsigned char *element, long size);

void DtwResource_set_string(DtwResource *self,const  char *element);

void DtwResource_set_long(DtwResource *self,long element);

void DtwResource_set_double(DtwResource *self,double element);

void DtwResource_set_bool( DtwResource *self,bool element);

void DtwResource_destroy(DtwResource *self);


DtwStringArray *DtwResource_list(DtwResource *self);

int DtwResource_type(DtwResource *self);


const char * DtwResource_type_in_str(DtwResource *self);

void DtwResource_commit(DtwResource *self);

void DtwResource_represent(DtwResource *self);

void DtwResource_free(struct DtwResource *self);