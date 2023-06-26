
typedef enum {DTW_OK,DTW_OBJECT_NOT_EXIST,DTW_WRONG_TYPE} DtwObjectError;

typedef struct DtwObject{

    bool first_object;
    char *path;
    DtwRandonizer  *randonizer;


    char *(*get_string)(struct DtwObject *self,const char *name,DtwObjectError *error);
    void (*set_string)(struct DtwObject *self,const char *name,const char *value);


    long (*get_long)(struct DtwObject *self, const char *name,DtwObjectError *error);
    void (*set_long)(struct DtwObject *self,const char *name,long value);


    double (*get_double)(struct DtwObject *self, const char *name, DtwObjectError *error);
    void (*set_double)(struct DtwObject *self,const char *name, double value);

    struct DtwObject *(*sub_object)(struct DtwObject *self,const char*name);
    struct DtwObject *(*unique_random_sub_object)(struct DtwObject *self);


    void (*free)(struct DtwObject *self);


}DtwObject;
DtwObject * private_newDtwObject_raw();

DtwObject * newDtwObject(const char *path);
char * private_DtwObject_create_path(struct DtwObject *self,const char *name);

char * DtwObject_get_string(struct DtwObject *self,const char *name,DtwObjectError *error);
void DtwObject_set_string(struct DtwObject *self,const char *name, const char *value);


long DtwObject_get_long(struct DtwObject *self, const char *name,DtwObjectError *error);
void DtwObject_set_long(struct DtwObject *self,const char *name, long value);

double DtwObject_get_double(struct DtwObject *self, const char *name, DtwObjectError *error);
void DtwObject_set_double(struct DtwObject *self,const char *name, double value);


DtwObject * DtwObject_unique_random_sub_object(DtwObject *self);
DtwObject * DtwObject_sub_object(DtwObject *self,const char *name);
DtwObject * DtwObject_free(DtwObject *self);