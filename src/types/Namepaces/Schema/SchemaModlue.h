#include "DatabaseSchemaModule.h"
#ifndef PRIVATE_DTW_SCHEMA_MODULE_TYPE_H
#define PRIVATE_DTW_SCHEMA_MODULE_TYPE_H
typedef struct {
    void (*add_primary_key)(DtwSchema *self, const char *primary_key);
    DtwSchema * (*sub_schema)(DtwSchema *self,const char *name);
}DtwSchemaModule;
#endif
