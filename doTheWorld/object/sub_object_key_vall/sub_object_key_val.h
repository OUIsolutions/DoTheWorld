
typedef struct DtwSubObjectKeyVal{

    DtwSubObject **elements;
    int size;

    void (*append)(struct DtwSubObjectKeyVal *self, DtwSubObject *object);
    DtwSubObject *(*get)(struct DtwSubObjectKeyVal *self, const char *name);
    void(*free)(struct DtwSubObjectKeyVal *self);

}DtwSubObjectKeyVal;

DtwSubObjectKeyVal * newDtwSubObjectArray();
void DtwSubObjectArray_append(struct DtwSubObjectKeyVal *self, DtwSubObject *object);
DtwSubObject * DtwSubObjectArray_get(struct DtwSubObjectKeyVal *self, const char *name);
void DtwSubObjectArray_free(struct DtwSubObjectKeyVal *self);
