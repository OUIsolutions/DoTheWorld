
#include "FlockLocker/all.h"
#include "MultiFileLocker.h"

#ifndef PRIVATE_DTW_LOCKER_TYPE_H
#define PRIVATE_DTW_LOCKER_TYPE_H
typedef struct {
#ifdef __linux__
    DtwFlockLocker *locker;
#endif
#ifdef _WIN32
    DtwMultiFileLocker  *locker;
#endif

} DtwLocker;
#endif
