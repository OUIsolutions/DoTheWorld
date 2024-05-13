
typedef struct {

    DtwSchema * (*newSchema)(const char *path);
    void (*free)(DtwSchema *self);
    DtwResource * (*new_insertion)(DtwSchema *schema);
    DtwResourceArray * (*get_values)(DtwSchema *schema);
    void (*add_primary_key)(DtwSchema *self,const char *primary_key);
    void (*commit)(DtwSchema *self);
    DtwResource  *(*find_by_nameID)(DtwSchema *self,const char *name);
    void (*dangerous_remove_prop)(DtwSchema *self, const char *prop);
    void (*dangerous_rename_prop)(DtwSchema *self, const char *prop, const char *new_name);

    DtwResource * (*find_by_primary_key_with_binary)(DtwSchema *schema, const char *key, unsigned  char *value, long size);
    DtwResource * (*find_by_primary_key_with_string)(DtwSchema *schema,const char *key,const char *value);
}DtwSchemaModule;

DtwSchemaModule newDtwSchemaModule();