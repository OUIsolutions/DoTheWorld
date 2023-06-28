

typedef struct DtwGarbage{
    void *value;
    int type;
}DtwGarbage;

DtwGarbage * newDtwObjectGarbage(int type, void *value);


void DtwObjectGarbage_free(struct DtwGarbage *self);
