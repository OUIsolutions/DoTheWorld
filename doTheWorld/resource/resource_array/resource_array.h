


typedef struct DtwResourceArray{
    DtwResource **resources;
    long size;

}DtwResourceArray;

DtwResourceArray * newDtwResourceArray();

void DtwResourceArray_append(DtwResourceArray *self, DtwResource *element);


DtwResource * DtwResourceArray_get_by_name(DtwResourceArray *self, const char *name);

void DtwResourceArray_free(DtwResourceArray *self);

