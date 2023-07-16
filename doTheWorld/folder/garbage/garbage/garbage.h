
typedef struct DtwGarbage{
    DtwGarbageElement **elements;
    int size;

    void (*append)(struct DtwGarbage *self, int type, void *value);
    void (*free)(struct DtwGarbage *self);

}DtwGarbage;

DtwGarbage * newDtwGarbageArray();

void DtwGarbageArray_append(struct DtwGarbage *self, int type, void *value);
void DtwGarbageArray_free(struct DtwGarbage *self);
