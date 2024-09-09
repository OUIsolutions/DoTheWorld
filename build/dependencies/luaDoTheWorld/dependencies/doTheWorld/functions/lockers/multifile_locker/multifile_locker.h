#include "../unique.declaration_requirements.h"


DtwMultiFileLocker *newDtwMultiFileLocker();

int DtwMultiFIleLocker_lock(DtwMultiFileLocker *self, const  char *element);

void DtwMultifileLocker_unlock(DtwMultiFileLocker *self, const  char *element);

void DtwMultiFileLocker_represemt(DtwMultiFileLocker *self);

void DtwMultiFileLocker_free(DtwMultiFileLocker *self);
