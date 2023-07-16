

typedef struct DtwObject{

    bool first_object;
    char *path;
    int error;

    DtwRandonizer  *randonizer;
    DtwGarbage  *garbage_array;

    unsigned char *(*get_binary)(struct DtwObject *self, const char *name, long *size,DtwObjectProps *props);
    void (*set_binary)(struct DtwObject *self, const char *name, unsigned  char *value, long size);


    char *(*get_string)(struct DtwObject *self,const char *name,DtwObjectProps *props);
    void (*set_string)(struct DtwObject *self,const char *name,const char *value);
    void (*append_string)(struct DtwObject *self,const char *value);


    long (*get_long)(struct DtwObject *self, const char *name);
    void (*set_long)(struct DtwObject *self,const char *name,long value);


    double (*get_double)(struct DtwObject *self, const char *name);
    void (*set_double)(struct DtwObject *self,const char *name, double value);

    struct DtwObject *(*sub_object)(struct DtwObject *self,const char*name,DtwObjectProps *props);

    int (*type_of)(struct DtwObject *self,const char*name);
    char *(*inspect_type)(struct DtwObject *self,int type);


    DtwStringArray  * (*list_all)(struct DtwObject *self,DtwObjectProps *props);
    long (*size)(struct DtwObject *self);

    void(*destroy)(struct DtwObject *self,const char *name);
    void (*free)(struct DtwObject *self);


}DtwObject;

DtwObject * private_newDtwObject_raw();

DtwObject * newDtwObject(const char *path);

char * private_DtwObject_create_path(struct DtwObject *self,const char *name);


unsigned char * DtwObject_get_binary(struct DtwObject *self, const char *name, long *size,DtwObjectProps *props);
void DtwObject_set_binary(struct DtwObject *self, const char *name, unsigned  char *value, long size);



char * DtwObject_get_string(struct DtwObject *self,const char *name,DtwObjectProps *props);
void DtwObject_set_string(struct DtwObject *self,const char *name, const char *value);
void DtwObject_append_string(struct DtwObject *self, const char *value);



long DtwObject_get_long(struct DtwObject *self, const char *name);
void DtwObject_set_long(struct DtwObject *self,const char *name, long value);

double DtwObject_get_double(struct DtwObject *self, const char *name);
void DtwObject_set_double(struct DtwObject *self,const char *name, double value);


void DtwObject_destroy(struct DtwObject *self,const char *name);
DtwStringArray  * DtwObject_list_all(struct DtwObject *self,DtwObjectProps *props);

DtwObject * DtwObject_sub_object(struct DtwObject *self,const char*name,DtwObjectProps *props);

long DtwObject_size(struct DtwObject *self);

int DtwObject_type_of(struct DtwObject *self,const char*name);
char *DtwObject_inspect_type(struct DtwObject *self,int type);

void DtwObject_free(struct DtwObject *self);