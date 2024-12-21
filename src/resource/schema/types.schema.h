#ifndef PRIVATE_DTW_SCHEMA_TYPE_H
#define PRIVATE_DTW_SCHEMA_TYPE_H
#include "../StringArray.h"

typedef struct DtwSchema{


    const char *value_name;
    const char *index_name;

    char *name;
    struct DtwSchema **sub_schemas;
    int size;
    DtwStringArray  *primary_keys;
}DtwSchema;

#endif
