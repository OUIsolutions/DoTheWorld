
typedef struct {
    DtwResource *master;
    bool owner;
    DtwResource  *values_resource;
    DtwResource  *index_resource;
    DtwStringArray  *primary_keys;
}DtwOldSchema;

bool privateDtwSchema_error(DtwOldSchema *self);

DtwOldSchema * DtwResource_sub_schema(DtwResource *self, const char *format, ...);

DtwOldSchema * newDtwSchema(const char *path);

void DtwSchema_free(DtwOldSchema *self);

void privateDtwSchema_free_self_props(DtwOldSchema *self);


void DtwSchema_add_primary_key(DtwOldSchema *self, const char *primary_key);

void DtwSchema_commit(DtwOldSchema *self);

DtwResource  *DtwSchema_get_find_by_nameID(DtwOldSchema *self, const char *name);

void DtwSchema_dangerours_remove_prop(DtwOldSchema *self, const char *prop);

void DtwSchema_dangerours_rename_prop(DtwOldSchema *self, const char *prop, const char *new_name);


DtwResourceArray * DtwSchema_get_values(DtwOldSchema *self);

DtwResource * DtwSchema_find_by_primary_key_with_binary(DtwOldSchema *self, const char *primary_key, unsigned  char *value, long size);

DtwResource * DtwSchema_find_by_primary_key_with_string(DtwOldSchema *self, const char *key, const char *value);


