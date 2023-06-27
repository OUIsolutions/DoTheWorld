
typedef enum {
    DTW_NONE,
    DTW_NUMBER,
    DTW_LONG,
    DTW_DOUBLE,
    DTW_STRING,
    DTW_OBJECT
} DtwObjectType;

typedef struct DtwSubObject{

    char *key;

    double number_value;
    void *any_value;
    int size;

    DtwObjectType type;


}DtwSubObject;

DtwSubObject * newDtwSubObject();