
#define DTW_NOT_CACHE 1
#define DTW_ALLOW_CACHE 2


typedef struct DtwObjectProps{

    int cache;

}DtwObjectProps;

DtwObjectProps DtwObjectProps_create_props(DtwObjectProps *props);


DtwObjectProps dtw_no_store= {
        .cache =DTW_NOT_CACHE
};

DtwObjectProps dtw_store= {
        .cache =DTW_ALLOW_CACHE
};


