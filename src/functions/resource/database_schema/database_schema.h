


#include "../unique.declaration_requirements.h"


DtwDatabaseSchema *private_newDtwDtatabaseSchema();

DtwSchema * privateDtwDtatabaseSchema_get_sub_schema(DtwDatabaseSchema *self,const char *name);

DtwSchema * DtwDtatabaseSchema_new_subSchema(DtwDatabaseSchema *self,const char *name);

void private_new_DtwDtatabaseSchema_free(DtwDatabaseSchema *self);
