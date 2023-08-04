

typedef struct DtwResource{

    bool allow_transaction;
    bool auto_lock;
    bool locked;
    DtwTransaction  *transaction;
#ifdef  __linux__
    DtwLocker  *locker;
#endif
    char *name;
    char *path;
    bool child;
    /*
    struct DtwResourceArray{
        long size;
        struct DtwResource **resources;
    }childs;
    */

    struct DtwResource * (*sub_resource)(struct DtwResource *self,const  char *path);

    void (*lock)(struct DtwResource *self);

    void (*destroy)(struct DtwResource *self);

    void (*set_binary)(struct DtwResource *self, unsigned char *element, long size);
    void (*set_string)(struct DtwResource *self,const  char *element);
    void (*set_long)(struct DtwResource *self,long element);
    void (*set_double)(struct DtwResource *self,double element);
    void (*set_bool)(struct DtwResource *self,bool element);

    unsigned char *(*get_any)(struct DtwResource *self, long *size, bool *is_binary);
    unsigned char *(*get_binary)(struct DtwResource *self, long *size);
    char *(*get_string)(struct DtwResource *self);
    long (*get_long)(struct DtwResource *self);
    double (*get_double)(struct DtwResource *self);
    bool (*get_bool)(struct DtwResource *self);

    DtwStringArray *(*list)(struct DtwResource *self);

    int (*type)(struct DtwResource *self);
    const char *(*type_in_str)(struct DtwResource *self);

    void (*commit)(struct DtwResource *self);

    void (*represent)(struct DtwResource *self);

    void (*free)(struct DtwResource *self);

}DtwResource;


DtwResource *private_new_DtwResource_raw();

DtwResource *new_DtwResource(const char *path);

DtwResource * DtwResource_sub_resource(DtwResource *self,const  char *path);

void DtwResource_lock(DtwResource *self);

void private_DtwResource_lock_if_auto_lock(DtwResource *self);

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