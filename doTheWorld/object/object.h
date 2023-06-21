
typedef enum {DTO_OK,DTW_OBJECT_NOT_EXIST,DTW_WRONG_TYPE} DtwObjectError;

typedef struct DtwObject{

    char *path;
    char *(*get_string)(struct DtwObject *self,const char *name,DtwObjectError *error);
    long (*get_long)(struct DtwObject *self, const char *name,DtwObjectError *error);
    double (*get_double)(struct DtwObject *self, const char *name, DtwObjectError *error);
    struct DtwObject *(*sub_object)(struct DtwObject *self,const char*name);
    struct DtwObject *(*unique_random_sub_object)(struct DtwObject *self);


    void (*set_long)(struct DtwObject *self,long value);
    void (*set_double)(struct DtwObject *self, double value);
    void (*set_string)(struct DtwObject *self,const char *value);
    void (*free)(struct DtwObject *self);


}DtwObject;
DtwObject * private_newDtwObject_raw();

DtwObject * newDtwObject(const char *path);

char * DtwObject_get_string(struct DtwObject *self,const char *name,DtwObjectError *error);
void DtwObject_set_string(struct DtwObject *self,const char *name, const char *value);

long DtwObject_get_long(struct DtwObject *self, const char *name,DtwObjectError *error);
void DtwObject_set_long(struct DtwObject *self,const char *name, long value);

double DtwObject_get_double(struct DtwObject *self, const char *name, DtwObjectError *error);
void DtwObject_set_double(struct DtwObject *self,const char *name, double value);


DtwObject * DtwObject_unique_random_sub_object(DtwObject *self);
DtwObject * DtwObject_sub_object(DtwObject *self,const char *name);
DtwObject * DtwObject_free(DtwObject *self);