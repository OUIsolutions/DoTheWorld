
typedef struct DtwObjectDict{

    DtwKeyVal **elements;
    int size;

    void (*append)(struct DtwObjectDict *self, DtwKeyVal *object);
    DtwKeyVal *(*get)(struct DtwObjectDict *self, const char *name);
    void(*free)(struct DtwObjectDict *self);

}DtwObjectDict;

DtwObjectDict * newDtwSubObjectKeyVal();
void DtwObjectDict_append(struct DtwObjectDict *self, DtwKeyVal *object);
DtwKeyVal * DtwObjectDict_get(struct DtwObjectDict *self, const char *name);
void DtwObjectDict_free(struct DtwObjectDict *self);
