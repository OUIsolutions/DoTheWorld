
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
    char *new_key;

    double number_value;
    void *any_value;
    int size;

    DtwObjectType type;
    bool seted;
    bool owner;
}DtwSubObject;

