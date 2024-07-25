#include "../Locker/all.h"
#include "../Randonizer.h"
#include "../Transaction/all.h"

#ifndef PRIVATE_DTW_ROOT_PROPS_RESOURCE_TYPE_H
#define PRIVATE_DTW_ROOT_PROPS_RESOURCE_TYPE_H
typedef struct {
    DtwTransaction  *transaction;
    DtwRandonizer  *randonizer;
    DtwLocker *locker;
    bool is_writing_schema;
    int error_code;
    char *error_path;
    char *error_message;

}privateDtwResourceRootProps;
#endif
