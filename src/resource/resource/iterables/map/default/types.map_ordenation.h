
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../../../imports/imports.macros.h"
//silver_chain_scope_end
#include "../../Resource.h"

#ifndef PRIVATE_DTW_RESOURCE_MAP_ELEMENT_TYPE_H
#define PRIVATE_DTW_RESOURCE_MAP_ELEMENT_TYPE_H

typedef struct {
    void *result;
    void *args;
    DtwResource *current;
    int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args);
}privateDtwResource_map_element;
#endif
