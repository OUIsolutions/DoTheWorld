

#define DTW_SCHEMA_DEFAULT_VALUES_NAME "value"
#define DTW_SCHEMA_DEFAULT_INDEX_NAME "index"

#define PRIVATE_DTW_SCHEMA_ROOT  1
#define PRIVATE_DTW_SCHEMA_VALUE 2
#define PRIVATE_DTW_SCHEMA_ELEMENT 3
#define PRIVATE_DTW_SCHEMA_ELEMENT_PROP 4
#define PRIVATE_DTW_SCHEMA_INDEX 5
#define PRIVATE_DTW_SCHEMA_PK_FOLDER 6
#define PRIVATE_DTW_SCHEMA_PK_VALUE 7


typedef struct DtwSchema{

    const char *value_name;
    const char *index_name;

    char *name;
    struct DtwSchema **sub_schemas;
    int size;
    DtwStringArray  *primary_keys;
}DtwSchema;

DtwSchema *private_newDtwSchema(const char *name,const char *value_name,const char *index_name);

DtwSchema * privateDtwSchema_get_sub_schema(DtwSchema *self,const char *name);

DtwSchema *DtwSchema_new_sub_schema(DtwSchema *self, const char *name);


void DtwSchema_add_primary_key(DtwSchema *self,const char *name);

void private_newDtwSchema_free(DtwSchema *self);
