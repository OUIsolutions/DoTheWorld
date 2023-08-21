


typedef struct DtwResourceArray{
    DtwResource **resources;
    long size;

}DtwResourceArray;

DtwResourceArray * newDtwResourceArray();

void DtwResourceArray_append(DtwResourceArray *self, DtwResource *element);

void DtwResourceArray_pop(DtwResourceArray *self, long position);


void DtwResourceArray_free(DtwResourceArray *self, DtwResource *element);

