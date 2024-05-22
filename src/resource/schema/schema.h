

typedef struct DtwSchema{
    char *name;
    struct DtwSchema **sub_schemas;
    int size;
    DtwStringArray  *primary_keys;
}DtwSchema;

DtwSchema *private_newDtwSchema(const char *name);

DtwSchema * privateDtwSchema_get_sub_schema(DtwSchema *self,const char *name);

DtwSchema *DtwSchema_new_sub_schema(DtwSchema *self, const char *name);


void DtwSchema_add_primary_key(DtwSchema *self,const char *name);

void private_newDtwSchema_free(DtwSchema *self);
