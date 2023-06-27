
typedef struct DtwGarbageArray{
    DtwObjectGarbage **elements;
    int size;

    void (*append)(struct DtwGarbageArray *self,DtwObjectGarbage *element);
    void (*free)(struct DtwGarbageArray *self);
    
}DtwGarbageArray;

DtwGarbageArray * newDtwGarbageArray();

void DtwGarbageArray_append(struct DtwGarbageArray *self,DtwObjectGarbage *element);
void DtwGarbageArray_free(struct DtwGarbageArray *self);

