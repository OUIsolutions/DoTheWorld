

typedef struct DtwGarbageElement{
    void *value;
    int type;
}DtwGarbageElement;

DtwGarbageElement * newDtwObjectGarbage(int type, void *value);


void DtwObjectGarbage_free(struct DtwGarbageElement *self);
