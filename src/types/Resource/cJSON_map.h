#include "../unique.h"

typedef struct  {
    cJSON *(*callback)(DtwResource *item,void *args);
    bool (*filtrage)(DtwResource *item,void *args);
    int (*ordenation)(DtwResource *item1,DtwResource *item2,void *args);
    void *args;
}private_DtwResource_cJSON_args;
