

typedef struct DtwSubObject{

    char *key;

    double number_value;
    void *any_value;
    int size;

    DtwObjectType type;


}DtwSubObject;

DtwSubObject * newDtwSubObject();