
typedef enum {
    DTW_NONE,
    DTW_NUMBER,
    DTW_LONG,
    DTW_DOUBLE,
    DTW_STRING,
    DTW_OBJECT
} DtwObjectType;

typedef struct DtwSubObject{

    double number_value;
    void *any_value;
    DtwObjectType type;
    bool changed;
    bool owner;

}DtwSubObject;

