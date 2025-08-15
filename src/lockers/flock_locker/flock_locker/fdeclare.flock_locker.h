//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../../imports/imports.typesm.h"
//silver_chain_scope_end



#if defined(__linux__) || defined(__APPLE__)


DtwFlockLocker * newFlockLocker();

void private_FlockLocker_unlock_by_index(DtwFlockLocker *self, int index);

void DtwFlockLocker_unlock(DtwFlockLocker *self, const char *filename);

int DtwFlockLocker_lock(DtwFlockLocker *self, const char *filename);

void  DtwFlockLocker_represent(DtwFlockLocker *self);

void  DtwFlockLocker_free(DtwFlockLocker *self);
#endif
