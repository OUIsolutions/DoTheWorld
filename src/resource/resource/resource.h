

typedef struct DtwResource{

    bool allow_transaction;
    bool use_locker_on_unique_values;
    void *schema;
    privateDtwResourceRootProps *root_props;
    struct DtwResource *mother;
    char *name;
    char *path;

    bool loaded;
    bool is_binary;
    unsigned char *value_any;
    long value_size;
   
    //cache implementation
    bool cache_sub_resources;
    void *sub_resources;

}DtwResource;




DtwResource *new_DtwResource(const char *path);

bool DtwResource_error(DtwResource *self);

#define DtwResource_protected(self)  if(!DtwResource_error(self))
#define DtwResource_catch(self)  if(DtwResource_error(self))

int DtwResource_get_error_code(DtwResource *self);

char * DtwResource_get_error_message(DtwResource *self);

void  private_DtwResource_raise_error(DtwResource *self, int error_code, const char *error_message);

void  DtwResource_clear_errors(DtwResource *self);

DtwResource * DtwResource_sub_resource(DtwResource *self,const  char *format, ...);

DtwResource * DtwResource_sub_resource_ensuring_not_exist(DtwResource *self,const  char *format, ...);

DtwResource * DtwResource_sub_resource_next(DtwResource *self, const char *end_path);

DtwResource * DtwResource_sub_resource_now(DtwResource *self, const char *end_path);

DtwResource * DtwResource_sub_resource_now_in_unix(DtwResource *self, const char *end_path);

DtwResource * DtwResource_sub_resource_random(DtwResource *self, const char *end_path);


void DtwResource_unload(DtwResource *self);

void DtwResource_load(DtwResource *self);

void DtwResource_load_if_not_loaded(DtwResource *self);

int DtwResource_lock(DtwResource *self);

void DtwResource_unlock(DtwResource *self);


void DtwResource_rename(DtwResource *self,const  char *new_name);

//getters

unsigned char *DtwResource_get_any(DtwResource *self, long *size, bool *is_binary);
unsigned char *DtwResource_get_any_from_sub_resource(DtwResource *self, long *size, bool *is_binary,const char *format,...);


void DtwResource_set_binary_sha(DtwResource *self, unsigned  char *value, long size);
void DtwResource_set_string_sha(DtwResource *self,const char *value);

void DtwResource_set_binary_sha_in_sub_resource(DtwResource *self, const char *key, unsigned  char *value, long size);
void DtwResource_set_string_sha_in_sub_resource(DtwResource *self, const char *key, const char *value);


unsigned char *DtwResource_get_binary(DtwResource *self, long *size);


unsigned char *DtwResource_get_binary_from_sub_resource(DtwResource *self, long *size,const char *format,...);


char *DtwResource_get_string(DtwResource *self);
char *DtwResource_get_string_from_sub_resource(DtwResource *self,const char *format,...);

long DtwResource_get_long(DtwResource *self);

long DtwResource_get_long_from_sub_resource(DtwResource *self,const char *format,...);

double DtwResource_get_double(DtwResource *self);
double DtwResource_get_double_from_sub_resource(DtwResource *self,const char *format,...);


bool DtwResource_get_bool(DtwResource *self);

bool DtwResource_get_bool_from_sub_resource(DtwResource *self,const char *format,...);


void DtwResource_set_binary(DtwResource *self, unsigned char *element, long size);

void DtwResource_set_binary_in_sub_resource(DtwResource *self,const char *key, unsigned char *element, long size);



void DtwResource_set_string(DtwResource *self,const  char *element);

void DtwResource_set_string_in_sub_resource(DtwResource *self, const char *key, const  char *element);

void DtwResource_set_long(DtwResource *self,long element);

void DtwResource_set_long_in_sub_resource(DtwResource *self, const char *key, long element);


void DtwResource_set_double(DtwResource *self,double element);

void DtwResource_set_double_in_sub_resource(DtwResource *self, const char *key, double element);

void DtwResource_set_bool( DtwResource *self,bool element);

void DtwResource_set_bool_in_sub_resource(DtwResource *self,const char *key, bool element);

void private_DtwResurce_destroy_primary_key(DtwResource *self,void *schema,const char *current_pk);

void private_DtwResource_destroy_all_primary_keys(DtwResource *self,void *vschema);

void DtwResource_destroy(DtwResource *self);

long DtwResource_size(DtwResource *self);

DtwStringArray *DtwResource_list_names(DtwResource *self);

int DtwResource_type(DtwResource *self);

bool DtwResource_is_file(DtwResource *self);


const char * DtwResource_type_in_str(DtwResource *self);

void DtwResource_commit(DtwResource *self);

void DtwResource_represent(DtwResource *self);

void DtwResource_free(struct DtwResource *self);