

typedef struct DtwKeyVal{

    char *key;
    void *any_value;
    int size;
    int type;

}DtwKeyVal;

DtwKeyVal * newDtwKeyVal(const char *key, void *any_value, int type, int size);

void DtwKeyVal_free(DtwKeyVal *self);