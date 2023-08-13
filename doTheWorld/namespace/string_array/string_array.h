
typedef struct DtwStringArrayModule{
    void (*set_value)(struct DtwStringArray *self,int index,const char *value);
    void (*append)(struct DtwStringArray *self,const char *string);
    void (*merge_string_array)(struct DtwStringArray *self, struct DtwStringArray *other);
    void (*represent)(struct DtwStringArray *self);
    void (*free)(struct DtwStringArray *self);
    int (*find_position)(struct DtwStringArray *self,const char *string);
    void (*sort)(struct DtwStringArray *self);

}DtwStringArrayModule;

DtwStringArrayModule newDtwStringArrayModule();