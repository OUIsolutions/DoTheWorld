
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../../../imports/imports.globals.h"
//silver_chain_scope_end


int  private_dtwResource_compare(const void *item1,const void*item2);

DtwResourceMapProps DtwResource_create_map_props(
    void *main_array,
    void(*append)(void *main_array_arg, void *item),
    void *(*callback)(DtwResource *item, void *args)
);

void DtwResource_map(DtwResource *self,DtwResourceMapProps props);

void DtwResource_schema_map(DtwResource *self,DtwResourceMapProps props);
