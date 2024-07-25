
#include "FlockArray.h"
#ifndef PRIVATE_DTW_FLOCK_LOCKER_TYPE_H
#define PRIVATE_DTW_FLOCK_LOCKER_TYPE_H
typedef struct {
    const char *temp_folder;
    privateDtwFlockArray  *locked_files;
}DtwFlockLocker;
#endif
