

typedef struct DtwResource{

    bool allow_transaction;
    bool use_locker_on_unique_values;
    bool locked;

    DtwTransaction  *transaction;
    DtwRandonizer  *randonizer;

    DtwLocker *locker;


    char *mothers_path;
    char *name;
    char *path;
    bool child;

    bool loaded;
    bool is_binary;
    unsigned char *value_any;
    long value_size;
   
    //cache implementation
    bool cache_sub_resources;
    void *sub_resources;

}DtwResource;




DtwResource *new_DtwResource(const char *path);

DtwResource * DtwResource_sub_resource(DtwResource *self,const  char *format, ...);

DtwResource * DtwResource_sub_resource_ensuring_not_exist(DtwResource *self,const  char *format, ...);

DtwResource * DtwResource_sub_resource_next(DtwResource *self, const char *end_path);

DtwResource * DtwResource_sub_resource_now(DtwResource *self, const char *end_path);

DtwResource * DtwResource_sub_resource_now_in_unix(DtwResource *self, const char *end_path);

DtwResource * DtwResource_sub_resource_random(DtwResource *self, const char *end_path);


void DtwResource_unload(DtwResource *self);

void DtwResource_load(DtwResource *self);

void DtwResource_load_if_not_loaded(DtwResource *self);

void DtwResource_lock(DtwResource *self);

void DtwResource_unlock(DtwResource *self);


void DtwResource_rename(DtwResource *self, char *new_name);

//getters

unsigned char *DtwResource_get_any(DtwResource *self, long *size, bool *is_binary);
unsigned char *DtwResource_get_any_from_sub_resource(DtwResource *self, long *size, bool *is_binary,char *format,...);


unsigned char *DtwResource_get_binary(DtwResource *self, long *size);

unsigned char *DtwResource_get_binary_from_sub_resource(DtwResource *self, long *size,char *format,...);


char *DtwResource_get_string(DtwResource *self);
char *DtwResource_get_string_from_sub_resource(DtwResource *self,char *format,...);

long DtwResource_get_long(DtwResource *self);

long DtwResource_get_long_from_sub_resource(DtwResource *self,char *format,...);

double DtwResource_get_double(DtwResource *self);
double DtwResource_get_double_from_sub_resource(DtwResource *self,char *format,...);


bool DtwResource_get_bool(DtwResource *self);

bool DtwResource_get_bool_from_sub_resource(DtwResource *self,char *format,...);



void DtwResource_set_binary(DtwResource *self, unsigned char *element, long size);


void DtwResource_set_string(DtwResource *self,const  char *element);

void DtwResource_set_string_in_sub_resource(DtwResource *self,const  char *element,char *format,...);

void DtwResource_set_long(DtwResource *self,long element);

void DtwResource_set_double(DtwResource *self,double element);

void DtwResource_set_bool( DtwResource *self,bool element);

void DtwResource_destroy(DtwResource *self);

long DtwResource_size(DtwResource *self);

DtwStringArray *DtwResource_list_names(DtwResource *self);

int DtwResource_type(DtwResource *self);


const char * DtwResource_type_in_str(DtwResource *self);

void DtwResource_commit(DtwResource *self);

void DtwResource_represent(DtwResource *self);

void DtwResource_free(struct DtwResource *self);