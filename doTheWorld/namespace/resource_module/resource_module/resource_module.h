
typedef struct DtwResourceModule{

    DtwResource *(*newResource)(const char *path);
    struct DtwResource * (*sub_resource)(struct DtwResource *self,const  char *format,...);
    DtwResource * (*sub_resource_ensuring_not_exist)(DtwResource *self,const  char *format, ...);
    DtwResource * (*sub_resource_next)(DtwResource *self, const char *end_path);
    void (*load)(DtwResource *self);

    void (*unload)(DtwResource *self);

    void (*lock)(DtwResource *self);

    void (*destroy)(DtwResource *self);

    unsigned char *(*get_any)(struct DtwResource *self, long *size, bool *is_binary);

    unsigned char *(*get_binary)(struct DtwResource *self, long *size);

    char *(*get_string)(struct DtwResource *self);

    long (*get_long)(struct DtwResource *self);

    double (*get_double)(struct DtwResource *self);

    bool (*get_bool)(struct DtwResource *self);

    void (*set_binary)(DtwResource *self, unsigned char *element, long size);

    void (*set_string)(DtwResource *self,const  char *element);

    void (*set_long)(DtwResource *self,long element);

    void (*set_double)(DtwResource *self,double element);

    void (*set_bool)(DtwResource *self,bool element);



    DtwStringArray *(*list_names)(DtwResource *self);

    int (*type)(DtwResource *self);

    const char *(*type_in_str)(DtwResource *self);
    void (*commit)(DtwResource *self);

    void (*represent)(DtwResource *self);

    void (*rename)(DtwResource *self, char *new_name);

    void (*free)(DtwResource *self);
    DtwResourceArray * (*sub_resources)(DtwResource *self);
    DtwResourceArrayModule array;


}DtwResourceModule;

DtwResourceModule newDtwResourceModule();