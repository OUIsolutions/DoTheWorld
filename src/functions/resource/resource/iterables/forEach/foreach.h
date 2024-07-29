#include "../unique.declaration_requirements.h"

DtwResourceForeachProps DtwResource_create_foreach_props( void(*callback)(DtwResource *item, void *args));

void DtwResource_foreach(DtwResource *self,DtwResourceForeachProps props);

void DtwResource_schema_foreach(DtwResource *self,DtwResourceForeachProps props);
