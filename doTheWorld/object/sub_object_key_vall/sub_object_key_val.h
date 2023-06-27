
typedef struct DtwSubObjectArray{

    DtwSubObject **elements;
    int size;

    void (*append)(struct DtwSubObjectArray *self,DtwSubObject *object);
    DtwSubObject *(*get)(struct DtwSubObjectArray *self, const char *name);
    void(*free)(struct DtwSubObjectArray *self);

}DtwSubObjectArray;

DtwSubObjectArray * newDtwSubObjectArray();
void DtwSubObjectArray_append(struct DtwSubObjectArray *self,DtwSubObject *object);
DtwSubObject * DtwSubObjectArray_get(struct DtwSubObjectArray *self, const char *name);
void DtwSubObjectArray_free(struct DtwSubObjectArray *self);
