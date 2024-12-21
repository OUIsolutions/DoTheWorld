
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../../imports/imports.globals.h"
//silver_chain_scope_end


DtwResourceForeachProps DtwResource_create_foreach_props( void(*callback)(DtwResource *item, void *args));

void DtwResource_foreach(DtwResource *self,DtwResourceForeachProps props);

void DtwResource_schema_foreach(DtwResource *self,DtwResourceForeachProps props);
