
typedef struct DtwGarbageArray{
    DtwGarbage **elements;
    int size;

    void (*append)(struct DtwGarbageArray *self,int type, void *value);
    void (*free)(struct DtwGarbageArray *self);

}DtwGarbageArray;

DtwGarbageArray * newDtwGarbageArray();

void DtwGarbageArray_append(struct DtwGarbageArray *self,int type, void *value);
void DtwGarbageArray_free(struct DtwGarbageArray *self);
