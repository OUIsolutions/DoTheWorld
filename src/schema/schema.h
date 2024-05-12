
#define DTW_SCHEMA_VALUES_NAME "value"
#define DTW_SCHEMA_INDEX_NAME "index"

typedef struct {
    DtwResource *master;
    bool owner;
    DtwResource  *values_resource;
    DtwResource  *index_resource;
    DtwStringArray  *primary_keys;
}DtwSchema;

DtwSchema * DtwResource_sub_schema(DtwResource *self, const char *format,...);

DtwSchema * newDtwSchema(const char *path);

void DtwSchema_free(DtwSchema *self);

void privateDtwSchema_free_self_props(DtwSchema *self);

DtwResource * DtwSchema_new_insertion(DtwSchema *schema);

void DtwSchema_add_primary_key(DtwSchema *self,const char *primary_key);


DtwResourceArray * DtwSchema_get_values(DtwSchema *schema);

DtwResource * DtwSchema_find_by_primary_key_with_any(DtwSchema *schema,const char *key,unsigned  char *value,long size);

DtwResource * DtwSchema_find_by_primary_key_with_string(DtwSchema *schema,const char *key,const char *value);


