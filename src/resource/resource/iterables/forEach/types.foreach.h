
#include "../Resource.h"
#ifndef PRIVATE_DTW_RESOURCE_FOREACH_PROPS_TYPE
#define PRIVATE_DTW_RESOURCE_FOREACH_PROPS_TYPE
typedef struct{
    bool(*filtrage_callback)(DtwResource *item, void *args_filter);
    void(*callback)(DtwResource *item, void *args);
    void *args;
    int start;
    int qtd;
}DtwResourceForeachProps;
#endif
