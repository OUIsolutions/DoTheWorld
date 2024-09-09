
#include "../unique.declaration_requirements.h"

DtwLocker *newDtwLocker();

int DtwLocker_lock(DtwLocker *self, const  char *element);

void DtwLocker_unlock(DtwLocker *self, const  char *element);

void DtwLocker_represemt(DtwLocker *self);

void DtwLocker_free(DtwLocker *self);
