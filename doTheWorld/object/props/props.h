
#define DTW_NOT_CACHE 1
#define DTW_ALLOW_CACHE 2
#define DTW_NOT_REUPDATE_CACHE 1


typedef struct DtwObjectProps{

    int cache;
    int transaction;
    int update_cache;

}DtwObjectProps;

DtwObjectProps DtwObjectProps_create_props(DtwObjectProps *props);


DtwObjectProps dtw_no_store= {
        .cache =DTW_NOT_CACHE
};

DtwObjectProps execute_now = {
        .transaction = DTW_EXECUTE_NOW
};

DtwObjectProps execute_now_and_no_store = {
        .cache =DTW_NOT_CACHE,
        .transaction = DTW_EXECUTE_NOW
};

