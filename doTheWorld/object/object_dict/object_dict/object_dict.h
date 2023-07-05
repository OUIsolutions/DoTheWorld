
typedef struct DtwObjectDict{

    DtwSubObject **elements;
    int size;

    void (*append)(struct DtwObjectDict *self, DtwSubObject *object);
    DtwSubObject *(*get)(struct DtwObjectDict *self, const char *name);
    void(*free)(struct DtwObjectDict *self);

}DtwObjectDict;

DtwObjectDict * newDtwSubObjectKeyVal();
void DtwSubObjectArray_append(struct DtwObjectDict *self, DtwSubObject *object);
DtwSubObject * DtwSubObjectArray_get(struct DtwObjectDict *self, const char *name);
void DtwSubObjectArray_free(struct DtwObjectDict *self);
