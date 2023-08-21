
typedef struct DtwResourceModule{

    DtwResource *(*newResource)(const char *path);
    struct DtwResource * (*sub_resource)(struct DtwResource *self,const  char *path,bool load_content);

    void (*load)(DtwResource *self);
    void (*unload)(DtwResource *self);

    void (*lock)(DtwResource *self);

    void (*destroy)(DtwResource *self);

    void (*set_binary)(DtwResource *self, unsigned char *element, long size);

    void (*set_string)(DtwResource *self,const  char *element);

    void (*set_long)(DtwResource *self,long element);

    void (*set_double)(DtwResource *self,double element);

    void (*set_bool)(DtwResource *self,bool element);



    DtwStringArray *(*list)(DtwResource *self);


    const char *(*type_in_str)(DtwResource *self);
    void (*commit)(DtwResource *self);

    void (*represent)(DtwResource *self);

    void (*rename)(DtwResource *self, char *new_name);

    void (*free)(DtwResource *self);

}DtwResourceModule;

DtwResourceModule newDtwResourceModule();