
typedef struct {

    DtwSchema * (*newSchema)(const char *path);
    void (*free)(DtwSchema *self);
    DtwResource * (*new_insertion)(DtwSchema *schema);
    DtwResourceArray * (*get_values)(DtwSchema *schema);
    void (*add_primary_key)(DtwSchema *self,const char *primary_key);

    DtwResource * (*find_by_primary_key_with_binary)(DtwSchema *schema, const char *key, unsigned  char *value, long size);
    DtwResource * (*find_by_primary_key_with_string)(DtwSchema *schema,const char *key,const char *value);
}DtwSchemaModule;

DtwSchemaModule newDtwSchemaModule();