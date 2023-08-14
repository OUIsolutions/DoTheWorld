
typedef struct DtwResourceModule{

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

    void (*rename)(struct DtwResource *self, char *new_name);

    void (*free)(struct DtwResource *self);

}DtwResourceModule;

DtwResourceModule newDtwResourceModule();