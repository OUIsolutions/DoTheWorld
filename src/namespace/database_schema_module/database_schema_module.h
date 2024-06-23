
typedef struct {
    DtwSchema * (*sub_schema)(DtwDtatabaseSchema *self,const char *name);
}DtwDatabaseSchemaModule;

DtwDatabaseSchemaModule newDtwDatabaseSchemaModule();