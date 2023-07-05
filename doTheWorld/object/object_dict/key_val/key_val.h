

typedef struct DtwSubObject{

    char *key;
    void *any_value;
    int size;
    int type;

}DtwSubObject;

DtwSubObject * newDtwSubObject(char *key,void *any_value,int type,int size);

void DtwSubObject_free(DtwSubObject *self);