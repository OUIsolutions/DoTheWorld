//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../../imports/imports.typesm.h"
//silver_chain_scope_end



#ifdef __linux__


DtwFlockLocker * newFlockLocker();

void private_FlockLocker_unlock_by_index(DtwFlockLocker *self, int index);

void DtwFlockLocker_unlock(DtwFlockLocker *self, const char *filename);

int DtwFlockLocker_lock(DtwFlockLocker *self, const char *filename);

void  DtwFlockLocker_represent(DtwFlockLocker *self);

void  DtwFlockLocker_free(DtwFlockLocker *self);
#endif
