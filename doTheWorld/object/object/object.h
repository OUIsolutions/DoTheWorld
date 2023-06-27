
enum {DTW_OK,DTW_OBJECT_NOT_EXIST,DTW_WRONG_TYPE};
enum {DTW_BY_REFERENCE,DTW_BY_OWNERSHIP,DTW_BY_VALUE};

#define DTW_ALLOW_CACHE true
#define DTW_NOT_CACHE false

#define DTW_RANDOMIC NULL


typedef struct DtwObject{

    bool first_object;
    char *path;
    DtwRandonizer  *randonizer;
    //DtwSubObjectKeyVal  *key_val;

    char *(*get_string)(struct DtwObject *self,const char *name,int mode, int *error);
    void (*set_string)(struct DtwObject *self,const char *name,const char *value);

    long (*get_long)(struct DtwObject *self, const char *name,int  *error);
    void (*set_long)(struct DtwObject *self,const char *name,long value);


    double (*get_double)(struct DtwObject *self, const char *name, int *error);
    void (*set_double)(struct DtwObject *self,const char *name, double value);


    struct DtwObject *(*sub_object)(struct DtwObject *self,const char*name);
    DtwStringArray  * (*list_all)(struct DtwObject *self);
    void(*destroy)(struct DtwObject *self,const char *name);
    void (*free)(struct DtwObject *self);


}DtwObject;

DtwObject * private_newDtwObject_raw();

DtwObject * newDtwObject(const char *path);

char * private_DtwObject_create_path(struct DtwObject *self,const char *name);

char * DtwObject_get_string(struct DtwObject *self,const char *name,int mode, int *error);
void DtwObject_set_string(struct DtwObject *self,const char *name, const char *value);


long DtwObject_get_long(struct DtwObject *self, const char *name,int *error);
void DtwObject_set_long(struct DtwObject *self,const char *name, long value);

double DtwObject_get_double(struct DtwObject *self, const char *name, int *error);
void DtwObject_set_double(struct DtwObject *self,const char *name, double value);

void DtwObject_destroy(struct DtwObject *self,const char *name);

DtwStringArray  * DtwObject_list_all(struct DtwObject *self);

DtwObject * DtwObject_sub_object(struct DtwObject *self,const char *name);
void DtwObject_free(struct DtwObject *self);