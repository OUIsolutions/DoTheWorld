
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.globals.h"
//silver_chain_scope_end



DtwResource *new_DtwResource(const char *path);

DtwResource * DtwResource_sub_resource(DtwResource *self,const  char *format, ...);

DtwResource * DtwResource_sub_resource_ensuring_not_exist(DtwResource *self,const  char *format, ...);

void DtwResource_free(DtwResource *self);