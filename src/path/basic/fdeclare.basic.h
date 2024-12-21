
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end



DtwPath * newDtwPath(const char *path);

bool DtwPath_changed(struct DtwPath *self);




void DtwPath_represent(struct DtwPath *self);



void DtwPath_free(struct DtwPath *self);
