

typedef struct DtwObjectGarbage{
    void *value;
    int type;
}DtwObjectGarbage;

DtwObjectGarbage * newDtwObjectGarbage(int type, void *value);


void DtwObjectGarbage_free(struct DtwObjectGarbage *self);
