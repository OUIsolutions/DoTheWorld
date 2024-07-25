#include "../unique.all_types_less_dependencies.h"
#ifndef PRIVATE_DTW_RESOURCE_ARRAY_MODULE_TYPE_H
#define PRIVATE_DTW_RESOURCE_ARRAY_MODULE_TYPE_H
typedef struct DtwResourceArrayModule{

    void (*append)(DtwResourceArray *self, DtwResource *element);
    DtwResource * (*get_by_name)(DtwResourceArray *self, const char *name);
    void (*represent)(DtwResourceArray *self);
    void (*free)(DtwResourceArray *self);

}DtwResourceArrayModule;
#endif
