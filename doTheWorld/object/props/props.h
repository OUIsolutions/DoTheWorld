
#define DTW_NOT_CACHE 1
#define DTW_ALLOW_CACHE 2
#define DTW_NOT_GARBAGE 1
#define DTW_ALLOW_GARBAGE 2

typedef struct DtwObjectProps{

    int cache;
    int garbage;
    int transaction;

}DtwObjectProps;

DtwObjectProps DtwObjectProps_create_props(DtwObjectProps *props);

DtwObjectProps DtwObjectProps_not_store();