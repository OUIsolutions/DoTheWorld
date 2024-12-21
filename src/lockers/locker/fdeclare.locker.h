
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end



DtwLocker *newDtwLocker();

int DtwLocker_lock(DtwLocker *self, const  char *element);

void DtwLocker_unlock(DtwLocker *self, const  char *element);

void DtwLocker_represemt(DtwLocker *self);

void DtwLocker_free(DtwLocker *self);
