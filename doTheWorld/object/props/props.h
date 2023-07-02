

#define DTW_NOT_GARBAGE 1
#define DTW_ALLOW_GARBAGE 2

typedef struct DtwObjectProps{
    int garbage;
}DtwObjectProps;

DtwObjectProps DtwObjectProps_create_props(DtwObjectProps *props);