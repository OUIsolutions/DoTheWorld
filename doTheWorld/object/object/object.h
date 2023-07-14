

typedef struct DtwObject{

    bool first_object;
    char *path;
    int error;

    DtwRandonizer  *randonizer;
    DtwGarbage  *garbage_array;
    DtwObjectDict  *loaded_elements;

    unsigned char *(*get_binary)(struct DtwObject *self, const char *name, int *size,DtwObjectProps *props);
    void (*set_binary)(struct DtwObject *self, const char *name, unsigned  char *value, int size,DtwObjectProps *props);


    char *(*get_string)(struct DtwObject *self,const char *name,DtwObjectProps *props);
    void (*set_string)(struct DtwObject *self,const char *name,const char *value,DtwObjectProps *props);

    long (*get_long)(struct DtwObject *self, const char *name,DtwObjectProps *props);
    void (*set_long)(struct DtwObject *self,const char *name,long value,DtwObjectProps *props);


    double (*get_double)(struct DtwObject *self, const char *name,DtwObjectProps *props);
    void (*set_double)(struct DtwObject *self,const char *name, double value,DtwObjectProps *props);

    struct DtwObject *(*sub_object)(struct DtwObject *self,const char*name,DtwObjectProps *props);

    int (*type_of)(struct DtwObject *self,const char*name);
    char *(*inspect_type)(struct DtwObject *self,int type);

    DtwStringArray  * (*list_all)(struct DtwObject *self,DtwObjectProps *props);
    void(*destroy)(struct DtwObject *self,const char *name);
    void (*free)(struct DtwObject *self);


}DtwObject;

DtwObject * private_newDtwObject_raw();

DtwObject * newDtwObject(const char *path);

char * private_DtwObject_create_path(struct DtwObject *self,const char *name);


unsigned char * DtwObject_get_binary(struct DtwObject *self, const char *name, int *size,DtwObjectProps *props);
void DtwObject_set_binary(struct DtwObject *self, const char *name, unsigned  char *value, int size,DtwObjectProps *props);


char * DtwObject_get_string(struct DtwObject *self,const char *name,DtwObjectProps *props);
void DtwObject_set_string(struct DtwObject *self,const char *name, const char *value,DtwObjectProps *props);


long DtwObject_get_long(struct DtwObject *self, const char *name,DtwObjectProps *props);
void DtwObject_set_long(struct DtwObject *self,const char *name, long value,DtwObjectProps *props);

double DtwObject_get_double(struct DtwObject *self, const char *name,DtwObjectProps *props);
void DtwObject_set_double(struct DtwObject *self,const char *name, double value,DtwObjectProps *props);


void DtwObject_destroy(struct DtwObject *self,const char *name);
DtwStringArray  * DtwObject_list_all(struct DtwObject *self,DtwObjectProps *props);

DtwObject * DtwObject_sub_object(struct DtwObject *self,const char*name,DtwObjectProps *props);


int DtwObject_type_of(struct DtwObject *self,const char*name);
char *DtwObject_inspect_type(struct DtwObject *self,int type);

void DtwObject_free(struct DtwObject *self);