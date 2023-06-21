//
typedef struct DtwObject{

    char *path;

    long (*get_long)(struct DtwObject *self, const char *name);
    float (*get_float)(struct DtwObject *self, const char *name);
    char *(*get_string)(struct DtwObject *self,const char *name);
    struct DtwObject *(*sub_object)(struct DtwObject *self,const char*name);
    struct DtwObject *(*unique_random_sub_object)(struct DtwObject *self);


    void (*set_long)(struct DtwObject *self,long value);
    void (*set_float)(struct DtwObject *self,float value);
    void (*set_string)(struct DtwObject *self,const char *value);


}DtwObject;
DtwObject * private_newDtwObject_raw();

DtwObject * newDtwObject(const char *path);

long DtwObject_get_long(struct DtwObject *self, const char *name);
float DtwObject_get_float(struct DtwObject *self, const char *name);
char * DtwObject_get_string(struct DtwObject *self,const char *name);


void DtwObject_set_long(struct DtwObject *self, long value);
void DtwObject_set_float(struct DtwObject *self, float value);
void DtwObject_set_string(struct DtwObject *self, const char *value);

DtwObject * DtwObject_unique_random_sub_object(DtwObject *self);
DtwObject * DtwObject_sub_object(DtwObject *self,const char *name);
